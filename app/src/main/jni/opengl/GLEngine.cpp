/**
 * Copyright (c) 2014 Xavier Gouchet
 *
 * This file is licensed under The MIT License (MIT).
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#include "GLEngine.h"
#include "GLES2Renderer.h"
#include "GLUtils.h"
#include "../utils/Logs.h"

#include <stdlib.h>

#define TAG  "GLEngine"

// #define DISPLAY_ALL_CONFIG
#define DISPLAY_INFOS   1

/** Constructor */
GLEngine::GLEngine() {

    m_width = 0;
    m_height = 0;

    m_display = EGL_NO_DISPLAY;
    m_context = EGL_NO_CONTEXT;
    m_surface = EGL_NO_SURFACE;

    m_renderer = NULL;
}

/** Destructor */
GLEngine::~GLEngine() {
}

/**
 * Initialises the EGL interface and bind it to the application's window.
 */
void GLEngine::init_display(ANativeWindow *window) {
    LOG_D(TAG, " ❯ init_display(window)");

    EGLint width, height, dummy;

    // get the default display
    EGLDisplay display;
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, 0, 0);

#ifdef DISPLAY_INFOS
    print_egl_string(display, "EGL Client APIs", EGL_CLIENT_APIS);
    print_egl_string(display, "EGL Vendor", EGL_VENDOR);
    print_egl_string(display, "EGL Version", EGL_VERSION);
    print_egl_string(display, "EGL Extensions", EGL_EXTENSIONS);
#endif

    // Specifies the requirements for the display we want
    const EGLint attrib_list[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_DEPTH_SIZE, 24,
            EGL_STENCIL_SIZE, 8,
            EGL_NONE
    };


#ifdef DISPLAY_ALL_CONFIG

    // get the number of configs matching the requirements
    EGLint num_configs;
    eglChooseConfig(display, attrib_list, NULL, 0, &num_configs);
    LOG_D(TAG, "   • %d EGL configurations found", num_configs);

    // find matching configurations
    EGLConfig configs[num_configs];
    eglChooseConfig(display, attrib_list, configs, num_configs, &num_configs);

    // Display each config infos
    EGLint renderable_type = 0, surface_type = 0, transparent_type = 0, colorbuffer_type = 0;
    EGLint depth_size = 0, stencil_size = 0;
    for(int i = 0; i < num_configs; ++i){

        eglGetConfigAttrib(display, configs[i], EGL_RENDERABLE_TYPE, &renderable_type);
        eglGetConfigAttrib(display, configs[i], EGL_SURFACE_TYPE, &surface_type);
        eglGetConfigAttrib(display, configs[i], EGL_TRANSPARENT_TYPE, &transparent_type);
        eglGetConfigAttrib(display, configs[i], EGL_COLOR_BUFFER_TYPE, &colorbuffer_type);

        eglGetConfigAttrib(display, configs[i], EGL_DEPTH_SIZE, &depth_size);
        eglGetConfigAttrib(display, configs[i], EGL_STENCIL_SIZE, &stencil_size);


        LOG_D(TAG, "   • Configuration [%i] : ", i);
        LOG_D(TAG, "         renderable type = 0x%08x", renderable_type);
        LOG_D(TAG, "            surface type = %d", surface_type);
        LOG_D(TAG, "        transparent type = %d", transparent_type);
        LOG_D(TAG, "       color buffer type = %d", colorbuffer_type);

        LOG_D(TAG, "              depth size = %d", depth_size);
        LOG_D(TAG, "            stencil size = %d", stencil_size);
    }

#else

    EGLint num_configs;

#endif

    // Automatic get config
    EGLConfig config;
    eglChooseConfig(display, attrib_list, &config, 1, &num_configs);

    // Update the window format from the configuration
    EGLint format;
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    ANativeWindow_setBuffersGeometry(window, 0, 0, format);

    // create the surface
    EGLSurface surface = eglCreateWindowSurface(display, config, window, NULL);
    if (surface == EGL_NO_SURFACE){
        LOG_E(TAG, "   • Unable to create egl surface");
        return;
    }

    // Create the context
    const EGLint context_attrib_list[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    EGLContext context = eglCreateContext(display, config, NULL, context_attrib_list);
    if (context == EGL_NO_CONTEXT){
        EGLint error = eglGetError();
        LOG_E(TAG, "   • Unable to create egl context : 0x%08x", error);

        return;
    }

    // binds the EGL context to the surface
    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        LOG_E(TAG, "   • Unable to eglMakeCurrent");
        return;
    }

    // get the surface width / height
    eglQuerySurface(display, surface, EGL_WIDTH, &m_width);
    eglQuerySurface(display, surface, EGL_HEIGHT, &m_height);
    LOG_D(TAG, "   • Surface : %d x %d", m_width, m_height);

    m_display = display;
    m_surface = surface;
    m_context = context;

    // init the GL context
    init_gl_context();
}

/**
 * Initialises the Open GL ES context.
 */
void GLEngine::init_gl_context() {

#ifdef DISPLAY_INFOS
    print_gl_string("Open GL Version", GL_VERSION);
    print_gl_string("Open GL Vendor", GL_VENDOR);
    print_gl_string("Open GL Renderer", GL_RENDERER);
    print_gl_string("Open GL Extensions", GL_EXTENSIONS);
#endif

    // Check the OpenGL ES version
    const char *version = (const char *) glGetString(GL_VERSION);
    if (strstr(version, "OpenGL ES 2.")) {
        m_renderer = new GLES2Renderer();
    } else if (strstr(version, "OpenGL ES 3.")){
        m_renderer = new GLES2Renderer();
    } else {
        m_renderer = NULL;
        LOG_W(TAG, "   • OpenGL version not compatible (%s)", version);
    }

    if (m_renderer) {
        // make sure we initialise it properly
        if (!m_renderer->init()) {
            delete m_renderer;
            m_renderer = NULL;
        }
    }
}


/**
 * Destroys and cleans the OpenGL and EGL states to release the display
 */
void GLEngine::terminate_display() {

    if (m_display != EGL_NO_DISPLAY) {

        // make sure the display is current 
        eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

        if (m_context != EGL_NO_CONTEXT) {
            eglDestroyContext(m_display, m_context);
        }
        if (m_surface != EGL_NO_SURFACE) {
            eglDestroySurface(m_display, m_surface);
        }

        eglTerminate(m_display);
    }

    m_display = EGL_NO_DISPLAY;
    m_context = EGL_NO_CONTEXT;
    m_surface = EGL_NO_SURFACE;
}

/**
 * Renders a single frame on the current display
 */
void GLEngine::draw_frame() {

    LOG_D(TAG, " ❯ draw_frame()");

    if (m_display == NULL) {
        LOG_W(TAG, "   • no display");
        return;
    }

    // make the renderer draw a frame 
    if (m_renderer) {
        m_renderer->draw_frame();

        // Swap the display and surface buffer
        if (eglSwapBuffers(m_display, m_surface)) {
            LOG_V(TAG, "   • buffers swapped");
        } else {
            LOG_W(TAG, "   • swap failed");
        }
    } else {
        LOG_W(TAG, "   • no renderer");
    }
}


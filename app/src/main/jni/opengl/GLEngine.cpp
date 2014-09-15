/**
 * Copyright (c) 2014 Xavier Gouchet
 *
 * This file is licensed under The MIT License (MIT).
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#include "GLEngine.h"
#include "GLES2Renderer.h"
#include "../utils/Logs.h"

#include <stdlib.h>

#define TAG  "GLEngine"

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
 * Prints the GL String corresponding to the identifier, prefixed by the given name
 */
void GLEngine::print_gl_string(const char *name, GLenum identifier) {
    const char *value = (const char *) glGetString(identifier);
    LOG_D(TAG, "   • %s => %s", name, value);
}

/**
 * Initialises the EGL interface and bind it to the application's window.
 */
void GLEngine::init_display(ANativeWindow *window) {
    LOG_D(TAG, " ❯ init_display(window)");

    EGLint width, height, dummy, format;
    EGLint numConfigs;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;
    EGLDisplay display;

    // Specifies the requirements for the display we want
    const EGLint requirements[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
    };

    // get the default display
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, 0, 0);

    // choose the first configuration matching the requirements
    eglChooseConfig(display, requirements, &config, 1, &numConfigs);

    // get the format of the frame buffer from the chosen configuration...
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    // ... and update the native window accordingly
    ANativeWindow_setBuffersGeometry(window, 0, 0, format);

    // create the surface and context
    surface = eglCreateWindowSurface(display, config, window, NULL);
    context = eglCreateContext(display, config, NULL, NULL);

    // binds the EGL context to the surface
    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        LOG_W(TAG, "   • Unable to eglMakeCurrent");
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

    // print out some info 
    print_gl_string("Version", GL_VERSION);
    print_gl_string("Vendor", GL_VENDOR);
    print_gl_string("Renderer", GL_RENDERER);
    print_gl_string("Extensions", GL_EXTENSIONS);

    // Check the OpenGL ES version
    const char *version = (const char *) glGetString(GL_VERSION);
    if (strstr(version, "OpenGL ES 3.") || strstr(version, "OpenGL ES 2.")) {
        m_renderer = new GLES2Renderer();

        // make sure we initialise it properly    
        if (!m_renderer->init()) {
            delete m_renderer;
            m_renderer = NULL;
        }

    } else {
        LOG_E(TAG, "   • Unsupported OpenGL ES version : %s", version);
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
    }
}

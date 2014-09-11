#include <GLES2/gl2.h>

#include "GLEngine.h"
#include "../utils/Logs.h"

#define TAG  "GLEngine"

GLEngine::GLEngine() {

    m_width = 0;
    m_height = 0;

    m_display = EGL_NO_DISPLAY;
    m_context = EGL_NO_CONTEXT;
    m_surface = NULL;
}

GLEngine::~GLEngine() {
}

/**
* Initialises the OpenGL context and the EGL interface.
* EGL is the interface between OpenGL ES and the native Android window system.
*/
void GLEngine::init_display(ANativeWindow *window) {
    LOG_D(TAG, " ❯ init_display(window)");

    // Required configuration of the EGL display
    const EGLint requirements[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
    };


    EGLint width, height, dummy, format;
    EGLint numConfigs;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;
    EGLDisplay display;

    // get the default display
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, 0, 0);

    // choose a configuration matching the requirements
    eglChooseConfig(display, requirements, &config, 1, &numConfigs);

    // get the format of the frame buffer from the chosen configuration
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    // update the window with the format
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
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
}

void GLEngine::terminate_display() {

    if (m_display != EGL_NO_DISPLAY) {

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

void GLEngine::draw_frame() {

    LOG_D(TAG, " ❯ draw_frame()");

    if (m_display == NULL) {
        LOG_W(TAG, "   • no display");
        return;
    }

    // Just fill the screen with a color.
    glClearColor(0.1f, 0.5f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // Swap the display and surface buffer
    if (eglSwapBuffers(m_display, m_surface)){
        LOG_V(TAG, "   • buffers swapped");
    } else {
        LOG_W(TAG, "   • swap failed");
    }

}
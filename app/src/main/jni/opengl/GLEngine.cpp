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

    mWidth = 0;
    mHeight = 0;

    mDisplay = EGL_NO_DISPLAY;
    mContext = EGL_NO_CONTEXT;
    mSurface = EGL_NO_SURFACE;

    mRenderer = NULL;
    
    mInitialized = false;
}

/** Destructor */
GLEngine::~GLEngine() {
}

/**
 * Is the engine initialised
 */
bool GLEngine::isInitialized() {
    return mInitialized;
}

/**
 * Initialises the EGL interface and bind it to the application's window.
 */
void GLEngine::initDisplay(ANativeWindow *window) {
    LogD(TAG, " ❯ GLEngine::initDisplay(window)");

    EGLint width, height, dummy;

    // get the default display
    EGLDisplay display;
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, 0, 0);

#ifdef DISPLAY_INFOS
    printEGLString(display, "EGL Client APIs", EGL_CLIENT_APIS);
    printEGLString(display, "EGL Vendor", EGL_VENDOR);
    printEGLString(display, "EGL Version", EGL_VERSION);
    printEGLString(display, "EGL Extensions", EGL_EXTENSIONS);
#endif

    // Specifies the requirements for the display we want
    const EGLint attribList[] = {
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
    EGLint numConfigs;
    eglChooseConfig(display, attribList, NULL, 0, &numConfigs);
    LogD(TAG, "   • %d EGL configurations found", numConfigs);

    // find matching configurations
    EGLConfig configs[numConfigs];
    eglChooseConfig(display, attribList, configs, numConfigs, &numConfigs);

    // Display each config infos
    EGLint renderableType = 0, surfaceType = 0, transparentType = 0, colorBufferType = 0;
    EGLint depthSize = 0, stencilSize = 0;
    for(int i = 0; i < numConfigs; ++i){

        eglGetConfigAttrib(display, configs[i], EGL_RENDERABLE_TYPE, &renderableType);
        eglGetConfigAttrib(display, configs[i], EGL_SURFACE_TYPE, &surfaceType);
        eglGetConfigAttrib(display, configs[i], EGL_TRANSPARENT_TYPE, &transparentType);
        eglGetConfigAttrib(display, configs[i], EGL_COLOR_BUFFER_TYPE, &colorBufferType);

        eglGetConfigAttrib(display, configs[i], EGL_DEPTH_SIZE, &depthSize);
        eglGetConfigAttrib(display, configs[i], EGL_STENCIL_SIZE, &stencilSize);


        LogD(TAG, "   • Configuration [%i] : ", i);
        LogD(TAG, "         renderable type = 0x%08x", renderableType);
        LogD(TAG, "            surface type = %d", surfaceType);
        LogD(TAG, "        transparent type = %d", transparentType);
        LogD(TAG, "       color buffer type = %d", colorBufferType);

        LogD(TAG, "              depth size = %d", depthSize);
        LogD(TAG, "            stencil size = %d", stencilSize);
    }

#else

    EGLint numConfigs;

#endif

    // Automatic get config
    EGLConfig config;
    eglChooseConfig(display, attribList, &config, 1, &numConfigs);

    // Update the window format from the configuration
    EGLint format;
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    ANativeWindow_setBuffersGeometry(window, 0, 0, format);

    // create the surface
    EGLSurface surface = eglCreateWindowSurface(display, config, window, NULL);
    if (surface == EGL_NO_SURFACE){
        LogE(TAG, "   • Unable to create egl surface");
        return;
    }

    // Create the context
    const EGLint contextAttribList[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    EGLContext context = eglCreateContext(display, config, NULL, contextAttribList);
    if (context == EGL_NO_CONTEXT){
        EGLint error = eglGetError();
        LogE(TAG, "   • Unable to create egl context : 0x%08x", error);
        return;
    }

    // binds the EGL context to the surface
    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        LogE(TAG, "   • Unable to eglMakeCurrent");
        return;
    }

    // get the surface width / height
    eglQuerySurface(display, surface, EGL_WIDTH, &mWidth);
    eglQuerySurface(display, surface, EGL_HEIGHT, &mHeight);
    LogD(TAG, "   • Surface : %d x %d", mWidth, mHeight);

    mDisplay = display;
    mSurface = surface;
    mContext = context;

    // init the GL context
    initGLContext();
    
    mInitialized = true; 
}

/**
 * Initialises the Open GL ES context.
 */
void GLEngine::initGLContext() {

#ifdef DISPLAY_INFOS
    printGLString("Open GL Version", GL_VERSION);
    printGLString("Open GL Vendor", GL_VENDOR);
    printGLString("Open GL Renderer", GL_RENDERER);
    printGLString("Open GL Extensions", GL_EXTENSIONS);
#endif

    // Check the OpenGL ES version
    const char *version = (const char *) glGetString(GL_VERSION);
    if (strstr(version, "OpenGL ES 2.")) {
        mRenderer = new GLES2Renderer();
    } else if (strstr(version, "OpenGL ES 3.")){
        mRenderer = new GLES2Renderer();
    } else {
        mRenderer = NULL;
        LogW(TAG, "   • OpenGL version not compatible (%s)", version);
    }

    if (mRenderer) {
        // make sure we initialise it properly
        if (!mRenderer->init(mWidth, mHeight)) {
            delete mRenderer;
            mRenderer = NULL;
        }
    }
}


/**
 * Destroys and cleans the OpenGL and EGL states to release the display
 */
void GLEngine::terminateDisplay() {

    if (mDisplay != EGL_NO_DISPLAY) {

        // make sure the display is current 
        eglMakeCurrent(mDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

        if (mContext != EGL_NO_CONTEXT) {
            eglDestroyContext(mDisplay, mContext);
        }
        if (mSurface != EGL_NO_SURFACE) {
            eglDestroySurface(mDisplay, mSurface);
        }

        eglTerminate(mDisplay);
    }

    mDisplay = EGL_NO_DISPLAY;
    mContext = EGL_NO_CONTEXT;
    mSurface = EGL_NO_SURFACE;
}

/**
 * Renders a single frame on the current display
 */
void GLEngine::drawFrame(RenderablesListConstIterator it, RenderablesListConstIterator end) {

    LogD(TAG, " ❯ GLEngine::drawFrame()");

    if (mDisplay == NULL) {
        LogW(TAG, "   • no display");
        return;
    }

    // make the renderer draw a frame 
    if (mRenderer) {
        mRenderer->drawFrame(it, end);

        // Swap the display and surface buffer
        if (!eglSwapBuffers(mDisplay, mSurface)) {
            LogW(TAG, "   • swap failed");
        }
    } else {
        LogW(TAG, "   • no renderer");
    }
}


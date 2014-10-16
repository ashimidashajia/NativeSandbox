/**
 * Copyright (c) 2014 Xavier Gouchet
 *
 * This file is licensed under The MIT License (MIT).
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#ifndef GL_ENGINE_H
#define GL_ENGINE_H

#include "GLRenderer.h"
#include "../utils/Lists.h"

#include <EGL/egl.h>
#include <GLES2/gl2.h>


/**
 * The GLEngine class handles the setup and states of the OpenGL and EGL context.
 *
 * EGL is the interface between OpenGL ES and the native Android window system.
 */
class GLEngine {

public:

    /** Constructor */
    GLEngine();

    /** Destructor */
    ~GLEngine();

    /**
     * Initialises the EGL interface and bind it to the application's window
     */
    void initDisplay(ANativeWindow *window);


    /**
     * Destroys and cleans the OpenGL and EGL states to release the display
     */
    void terminateDisplay();

    /**
     * Renders a single frame on the current display
     */
    void drawFrame(RenderablesListConstIterator it, RenderablesListConstIterator end);
    
    /**
     * Is the engine initialised
     */
    bool isInitialized();

private :

    bool mInitialized;

    /** The Open GL Renderer */
    GLRenderer *mRenderer;

    /** The front buffer */
    EGLDisplay mDisplay;
    /** The back buffer */
    EGLSurface mSurface;
    /** The EGL context */
    EGLContext mContext;

    /** The surface's size */
    int32_t mWidth, mHeight;

    /**
     * Initialises the Open GL ES context.
     */
    void initGLContext();

};

#endif

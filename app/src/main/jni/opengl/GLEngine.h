/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 
#ifndef GL_ENGINE_H
#define GL_ENGINE_H

#include <EGL/egl.h>

/**
 * The GLEngine class handles the setup and states of the OpenGL and EGL context. 
 * 
 * EGL is the interface between OpenGL ES and the native Android window system.
 */
class GLEngine {

private :
    
    /** The front buffer */
    EGLDisplay m_display;
    /** The back buffer */
    EGLSurface m_surface;
    /** The EGL context */
    EGLContext m_context;
    
    /** The surface's size */
    int32_t m_width, m_height;

public:

    /** Constructor */
    GLEngine();

    /** Destructor */
    ~GLEngine();

    /**
     * Initialises the OpenGL context and the EGL interface.
     */
    void init_display(ANativeWindow *window);

    /**
     * Destroys and cleans the OpenGL and EGL states to release the display
     */
    void terminate_display();

    /**
     * Renders a single frame on the current display
     */
    void draw_frame();
};

#endif

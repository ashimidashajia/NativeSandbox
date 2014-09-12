/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 
#ifndef GL_ENGINE_H
#define GL_ENGINE_H

#include "GLRenderer.h"

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
    void init_display(ANativeWindow *window);
    
    
    /**
     * Destroys and cleans the OpenGL and EGL states to release the display
     */
    void terminate_display();

    /**
     * Renders a single frame on the current display
     */
    void draw_frame();
    
private :

    /** The Open GL Renderer */
    GLRenderer *m_renderer; 
    
    /** The front buffer */
    EGLDisplay m_display;
    /** The back buffer */
    EGLSurface m_surface;
    /** The EGL context */
    EGLContext m_context;
    
    /** The surface's size */
    int32_t m_width, m_height;
    
    /**
     * Initialises the Open GL ES context.
     */
    void init_gl_context();
    
    static void print_gl_string(const char* name, GLenum s);

};

#endif

/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 
#ifndef GL_ES_2_RENDERER_H
#define GL_ES_2_RENDERER_H

#include "GLRenderer.h"
#include "../model/Shader.h"

/**
 * The GLES2Renderer class is an implementation of GLRenderer using Open GL ES 2.0 apis. 
 */
class GLES2Renderer : public GLRenderer {

public:

    /** Constructor */
    GLES2Renderer();
    
    /** Destructor */
    ~GLES2Renderer();
    
    /**
     * Initialises the renderer. Returns true if the initialisation was  succesfull
     */
    virtual bool init();
    
    /**
     * Draws a single frame
     */
    virtual void draw_frame();
    
protected:
    
private:

    /** the shader */
    Shader* m_shader; 
    
};

#endif

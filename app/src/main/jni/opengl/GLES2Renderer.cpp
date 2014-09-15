/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 
#include "GLES2Renderer.h"
#include "GLUtils.h"
#include "../utils/Logs.h"

#include <GLES2/gl2.h>

#define TAG "GLES2Renderer"

/** Constructor */
GLES2Renderer::GLES2Renderer() {
    m_shader = NULL;
}

/** Destructor */
GLES2Renderer::~GLES2Renderer() {
    if (m_shader){
        delete m_shader; 
    }
}

/**
 * Initialises the renderer. Returns true if the initialisation was  succesfull
 */
bool GLES2Renderer::init() {
    LOG_D(TAG, " ❯ init()");

    // Global config     
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    // TODO foreach renderable  : renderable.init
    
    return true;
}

/**
 * Draws a single frame
 */
void GLES2Renderer::draw_frame(){

    // Clears the screen
    glClearColor(0.1f, 0.5f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // TODO foreach renderable : renderable.draw    
    //for (unsigned int i = 0; i < numInstances; i++) {
    //    glUniformMatrix2fv(mScaleRotUniform, 1, GL_FALSE, mScaleRot + 4*i);
    //    glUniform2fv(mOffsetUniform, 1, mOffsets + 2*i);
    //    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    //}
}
    


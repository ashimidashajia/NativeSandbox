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
    
    // create the shader 
    m_shader = new GLShader();
    if (!m_shader->init(VS_DEFAULT, FS_DEFAULT)){
        delete m_shader; 
        m_shader = NULL;
    }
        
    // TODO  create the geometry
    //glGenBuffers(1, &mVB);
    //glBindBuffer(GL_ARRAY_BUFFER, mVB);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(QUAD), &QUAD[0], GL_STATIC_DRAW);

    return true;
}

/**
 * Draws a single frame
 */
void GLES2Renderer::draw_frame(){
    
    // sets the shader as active 
    if (m_shader){
        m_shader->set_active();
    }
    
    // map the geometry to the shader attributes 
    // glBindBuffer(GL_ARRAY_BUFFER, mVB);
    // glVertexAttribPointer(mPosAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, pos));
    // glVertexAttribPointer(mColorAttrib, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, rgba));
    // glEnableVertexAttribArray(mPosAttrib);
    // glEnableVertexAttribArray(mColorAttrib);

    //for (unsigned int i = 0; i < numInstances; i++) {
    //    glUniformMatrix2fv(mScaleRotUniform, 1, GL_FALSE, mScaleRot + 4*i);
    //    glUniform2fv(mOffsetUniform, 1, mOffsets + 2*i);
    //    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    //}
}
    


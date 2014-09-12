/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#include "GLShader.h"
#include "GLUtils.h"

/** Constructor */
GLShader::GLShader(){
    m_program = 0; 
}

/** Destructor */
GLShader::~GLShader(){
    if (m_program){
        glDeleteProgram(m_program);
    }
}

/**
 * Initialises the shader. Returns true if the initialisation was  succesfull
 */
bool GLShader::init(const char* vs_source, const char* fs_source){
    
    // compile the shader programs 
    m_program = create_program(VS_DEFAULT, FS_DEFAULT);
    if (!m_program){
        return false;
    }
    
    // TODO retrieve the shader attributes 
    // mPosAttrib = glGetAttribLocation(m_program, "pos");
    // mColorAttrib = glGetAttribLocation(m_program, "color");
    // mScaleRotUniform = glGetUniformLocation(m_program, "scaleRot");
    // mOffsetUniform = glGetUniformLocation(m_program, "offset");

}

/**
 * Sets this Shader as the active one for the next renderings to be done
 */
void GLShader::set_active(){
    if (m_program){
        glUseProgram(m_program);
    }
}



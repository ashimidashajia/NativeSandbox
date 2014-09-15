/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#include "Shader.h"
#include "../opengl/GLUtils.h"

/** Constructor */
Shader::Shader(){
    m_program = 0; 
}

/** Destructor */
Shader::~Shader(){
    if (m_program){
        glDeleteProgram(m_program);
    }
}

/**
 * Initialises the shader. Returns true if the initialisation was  succesfull
 */
bool Shader::init(const char* vs_source, const char* fs_source){
    
    // compile the shader programs 
    m_program = create_program(VS_DEFAULT, FS_DEFAULT);
    if (!m_program){
        return false;
    }
    
    // retrieve the shader attributes 
    m_pos_attrib = glGetAttribLocation(m_program, "pos");
    m_color_attrib = glGetAttribLocation(m_program, "color");
    // mScaleRotUniform = glGetUniformLocation(m_program, "scaleRot");
    // mOffsetUniform = glGetUniformLocation(m_program, "offset");

}

/**
 * Sets this Shader as the active one for the next renderings to be done
 */
void Shader::set_active(){
    if (m_program){
        glUseProgram(m_program);
    }
}

/** 
 * Returns the vertex array position attribute index (or -1)
 */
GLint Shader::get_position_attrib() {
    return m_pos_attrib;
}

/** 
 * Returns the vertex array color attribute index (or -1)
 */
GLint Shader::get_color_attrib() {
    return m_color_attrib;
}

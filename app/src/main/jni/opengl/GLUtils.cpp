/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 
#include "GLUtils.h"
#include "../utils/Logs.h"

#include <stdlib.h>

#define TAG "GLUtils"

/**
 * Compiles the given vertex and fragment shaders and the combined program
 */
GLuint create_program(const char* vs_source, const char* fs_source) {
    
    LOG_D(TAG, " ❯ create_program(..., ...)");
   
    GLuint vs_name = 0;
    GLuint fs_name = 0;
    GLuint program_name = 0;
    

    // compile both shaders
    vs_name = create_shader(GL_VERTEX_SHADER, vs_source);
    fs_name = create_shader(GL_FRAGMENT_SHADER, fs_source);
    
    // compile the full program
    if (vs_name && fs_name){
       program_name = create_program(vs_name, fs_name);
    }    

    // delete the shaders, don't need them anymore
    glDeleteShader(vs_name);
    glDeleteShader(fs_name);
    
    return program_name;
}

/**
 * Compiles a full shader program with the given compiled vertex and fragment shaders. 
 */
GLuint create_program(GLuint vs_name, GLuint fs_name) {
    
    LOG_D(TAG, " ❯ create_program(%d, %d)", vs_name, fs_name);
    
    // create the program slot
    GLuint program_name = glCreateProgram();
    if (!program_name) {
        check_GL_error("glCreateProgram");
        return 0;
    }
    
    // attach the shaders to the program
    glAttachShader(program_name, vs_name);
    glAttachShader(program_name, fs_name);
    glLinkProgram(program_name);
    
    // check the linked status 
    GLint linked = GL_FALSE;
    glGetProgramiv(program_name, GL_LINK_STATUS, &linked);
    
    if (!linked) {
        
        // get log length
        GLint info_log_length = 0;
        glGetProgramiv(program_name, GL_INFO_LOG_LENGTH, &info_log_length);
        if (info_log_length) {
            // get log message
            GLchar* info_log = (GLchar*)malloc(info_log_length);
            if (info_log) {
                glGetProgramInfoLog(program_name, info_log_length, NULL, info_log);
                LOG_E(TAG, "   • Could not link program : %s", info_log);
                free(info_log);
            }
        }
        
        // delete the program slot
        glDeleteProgram(program_name);
        program_name = 0;
    }

    return program_name;
}

/**
 * Compiles the given shader
 */
GLuint create_shader(GLenum shader_type, const char* shader_source) {

    LOG_D(TAG, " ❯ create_shader(%d, ...)", shader_type);
    
    // create a slot for the shader
    GLuint shader_name = glCreateShader(shader_type);
    if (!shader_name) {
        check_GL_error("glCreateShader");
        return 0;
    }
    
    // set the shader source 
    glShaderSource(shader_name, 1, &shader_source, NULL);

    // try and compile it 
    GLint compiled = GL_FALSE;
    glCompileShader(shader_name);
    glGetShaderiv(shader_name, GL_COMPILE_STATUS, &compiled);
    
    if (!compiled) {
        
        // get log length
        GLint info_log_length = 0;
        glGetShaderiv(shader_name, GL_INFO_LOG_LENGTH, &info_log_length);
        if (info_log_length > 0) {
            // get log message
            GLchar* info_log = (GLchar*) malloc(info_log_length);
            if (info_log) {
                glGetShaderInfoLog(shader_name, info_log_length, NULL, info_log);
                LOG_E(TAG, "   • Could not compile shader: %s", info_log);
                free(info_log);
            }
        }
        
        // delete the shader slot
        glDeleteShader(shader_name);
        return 0;
    }

    return shader_name;
}

/**
 * Check any GL error message and log it, prefixed with the last GL called function name. 
 * Return true if an error is detected. 
 */
bool check_GL_error(const char* func_name) {
    GLint error_code = glGetError();
    if (error_code != GL_NO_ERROR) {
        LOG_E(TAG, "   • GL error after %s(): 0x%08x\n", func_name, error_code);
        return true;
    }
    return false;
}

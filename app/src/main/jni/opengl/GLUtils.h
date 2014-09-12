/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 
#ifndef GL_UTILS_H_
#define GL_UTILS_H_

#include "GLES2/gl2.h"

/**
 * Compiles the given vertex and fragment shaders and the combined program
 */
GLuint create_program(const char* vs_source, const char* fs_source);

/**
 * Compiles a full shader program with the given compiled vertex and fragment shaders. 
 */
GLuint create_program(GLuint vs_name, GLuint fs_name);

/**
 * Compiles the given shader
 */
GLuint create_shader(GLenum shader_type, const char* shader_source);

/**
 * Check any GL error message and log it, prefixed with the last GL called function name
 */
bool check_GL_error(const char* func_name);

#endif

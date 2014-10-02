/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#ifndef GL_UTILS_H_
#define GL_UTILS_H_

#include <EGL/egl.h>
#include <GLES2/gl2.h>

/**
 * Compiles the given vertex and fragment shaders and the combined program
 */
GLuint createProgram(const char *vsSource, const char *fsSource);

/**
 * Compiles a full shader program with the given compiled vertex and fragment shaders.
 */
GLuint createProgram(GLuint vsName, GLuint fsName);

/**
 * Compiles the given shader
 */
GLuint createShader(GLenum shader_type, const char *shader_source);

/**
 * Check any GL error message and log it, prefixed with the last GL called function name
 */
bool checkGLError(const char *func_name);

/**
 * Prints the GL String corresponding to the name, prefixed by the given text
 */
void printGLString(const char *text, GLenum name);

/**
* Prints the EGL String corresponding to the name for the given display, prefixed by the given text
*/
void printEGLString(EGLDisplay display, const char *text, EGLint name);

#endif

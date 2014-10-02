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
GLuint createProgram(const char *vsSource, const char *fsSource) {

    LogD(TAG, " ❯ createProgram(..., ...)");

    GLuint vsName = 0;
    GLuint fsName = 0;
    GLuint programName = 0;


    // compile both shaders
    vsName = createShader(GL_VERTEX_SHADER, vsSource);
    fsName = createShader(GL_FRAGMENT_SHADER, fsSource);
    
    LogD(TAG, "   • Shaders compiled : %d / %d", vsName, fsName);

    // compile the full program
    if (vsName && fsName) {
        programName = createProgram(vsName, fsName);
    }

    // delete the shaders, don't need them anymore
    glDeleteShader(vsName);
    glDeleteShader(fsName);
    
    LogD(TAG, "   • Program compiled : %d", programName);

    return programName;
}

/**
 * Compiles a full shader program with the given compiled vertex and fragment shaders.
 */
GLuint createProgram(GLuint vsName, GLuint fsName) {

    LogD(TAG, " ❯ createProgram(%d, %d)", vsName, fsName);

    // create the program slot
    GLuint programName = glCreateProgram();
    if (!programName) {
        checkGLError("glCreateProgram");
        return 0;
    }

    // attach the shaders to the program
    glAttachShader(programName, vsName);
    glAttachShader(programName, fsName);
    glLinkProgram(programName);

    // check the linked status 
    GLint linked = GL_FALSE;
    glGetProgramiv(programName, GL_LINK_STATUS, &linked);

    if (!linked) {

        // get log length
        GLint infoLogLength = 0;
        glGetProgramiv(programName, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength) {
            // get log message
            GLchar *infoLog = (GLchar *) malloc(infoLogLength);
            if (infoLog) {
                glGetProgramInfoLog(programName, infoLogLength, NULL, infoLog);
                LogE(TAG, "   • Could not link program : %s", infoLog);
                free(infoLog);
            }
        }

        // delete the program slot
        glDeleteProgram(programName);
        programName = 0;
    }

    return programName;
}

/**
 * Compiles the given shader
 */
GLuint createShader(GLenum shader_type, const char *shader_source) {

    LogD(TAG, " ❯ createShader(%d, ...)", shader_type);

    // create a slot for the shader
    GLuint shaderName = glCreateShader(shader_type);
    if (!shaderName) {
        checkGLError("glCreateShader");
        return 0;
    }

    // set the shader source 
    glShaderSource(shaderName, 1, &shader_source, NULL);

    // try and compile it 
    GLint compiled = GL_FALSE;
    glCompileShader(shaderName);
    glGetShaderiv(shaderName, GL_COMPILE_STATUS, &compiled);

    if (!compiled) {

        // get log length
        GLint infoLogLength = 0;
        glGetShaderiv(shaderName, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0) {
            // get log message
            GLchar *infoLog = (GLchar *) malloc(infoLogLength);
            if (infoLog) {
                glGetShaderInfoLog(shaderName, infoLogLength, NULL, infoLog);
                LogE(TAG, "   • Could not compile shader: %s", infoLog);
                free(infoLog);
            }
        }

        // delete the shader slot
        glDeleteShader(shaderName);
        return 0;
    }

    return shaderName;
}


/**
 * Prints the GL String corresponding to the name, prefixed by the given text
 */
void printGLString(const char *text, GLenum name) {
    const char *value = (const char *) glGetString(name);
    LogD(TAG, "   • %s => %s", text, value);
}

/**
* Prints the EGL String corresponding to the name, prefixed by the given text
*/
void printEGLString(EGLDisplay display, const char *text, EGLint name) {
    const char *value = (const char *) eglQueryString(display, name);
    LogD(TAG, "   • %s => %s", text, value);
}


/**
 * Check any GL error message and log it, prefixed with the last GL called function name.
 * Return true if an error is detected.
 */
bool checkGLError(const char *func_name) {
    GLint errorCode = glGetError();
    if (errorCode != GL_NO_ERROR) {
        LogE(TAG, "   • GL error after %s(): 0x%08x", func_name, errorCode);
        return true;
    }
    return false;
}

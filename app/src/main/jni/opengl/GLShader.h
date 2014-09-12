/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 
#ifndef GL_SHADER_H
#define GL_SHADER_H

#include "GLShader.h"
#include "GLES2/gl2.h"

/**
 * Default Vertex / Fragment Shader
 */
static const char VS_DEFAULT[] =
    "#version 100\n"
    "uniform mat2 scaleRot;\n"
    "uniform vec2 offset;\n"
    "attribute vec2 pos;\n"
    "attribute vec4 color;\n"
    "varying vec4 vColor;\n"
    "void main() {\n"
    "    gl_Position = vec4(scaleRot*pos + offset, 0.0, 1.0);\n"
    "    vColor = color;\n"
    "}\n";

static const char FS_DEFAULT[] =
    "#version 100\n"
    "precision mediump float;\n"
    "varying vec4 vColor;\n"
    "void main() {\n"
    "    gl_FragColor = vColor;\n"
    "}\n";

/**
 * The GLShader class handles the compilation and communication with a shader program
 */
class GLShader {

public:

    /** Constructor */
    GLShader();
    
    /** Destructor */
    ~GLShader();
    
    /**
     * Initialises the shader. Returns true if the initialisation was  succesfull
     */
    bool init(const char* vs_source, const char* fs_source);
    
    /**
     * Sets this Shader as the active one for the next renderings to be done
     */
    void set_active();
    
private:

    /** the id of the shader program */
    GLuint m_program;
    
};

#endif

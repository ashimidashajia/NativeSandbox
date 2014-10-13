/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 

#ifndef SHADER_H
#define SHADER_H

#include <GLES2/gl2.h>

/**
 * Default Vertex / Fragment Shader
 */
static const char VS_DEFAULT[] =
        "#version 100\n"
        "\n"
        "uniform mat4 uMMatrix;\n"
        "uniform mat4 uVPMatrix;\n"
        "uniform vec4 uDiffuse;\n"
        "attribute vec4 aPosition;\n"
        "varying vec4 vColor;\n"
        "void main() {\n"
        "    gl_Position = (uVPMatrix * uMMatrix) * aPosition;\n"
        "    vColor = vec4(1, 1, 1, 1);"
        "}\n";
        
static const char FS_DEFAULT[] =
        "#version 100\n"
        "precision mediump float;\n"
        "varying vec4 vColor;\n"
        "void main() {\n"
        "    gl_FragColor = vec4(1, 1, 0, 1);\n"
        "}\n";

/**
 * The Shader class handles the compilation and communication with a shader program
 */
class Shader {

public:

    /** Constructor */
    Shader();

    /** Destructor */
    ~Shader();

    /**
     * Initialises the shader. Returns true if the initialisation was  succesfull
     */
    bool init(const char *vsSource, const char *fsSource);

    /**
     * Sets this Shader as the active one for the next renderings to be done
     */
    void setActive();
    
    /**
     * Returns the Vertex Position attribute handle
     */
    GLint getPositionAttributeHandle();
    
    /**
     * Returns the VP matrix uniform handle
     */
    GLint getViewProjMatrixUniformHandle();
    
    /**
     * Returns the VP matrix uniform handle
     */
    GLint getModelMatrixUniformHandle();
    
private:



    /** the id of the shader program */
    GLuint mProgramHandle;

    /** the shader attributes handles */
    GLint mPositionAttributeHandle;

    /** the shader uniform params */
    GLint mViewProjMatrixUniformHandle, mModelMatrixUniformHandle, mDiffuseColorUniformHandle;

};

#endif

/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#include "Shader.h"
#include "../opengl/GLUtils.h"

/** Constructor */
Shader::Shader() {
    mProgramHandle = 0;
    mPositionAttributeHandle = -1;
    mViewProjMatrixUniformHandle = -1;
    mModelMatrixUniformHandle = -1;
    mDiffuseColorUniformHandle = -1;
}

/** Destructor */
Shader::~Shader() {
    if (mProgramHandle) {
        glDeleteProgram(mProgramHandle);
    }
}

/**
 * Initialises the shader. Returns true if the initialisation was  succesfull
 */
bool Shader::init(const char *vsSource, const char *fsSource) {

    // compile the shader programs 
    mProgramHandle = createProgram(VS_DEFAULT, FS_DEFAULT);
    if (!mProgramHandle) {
        return false;
    }


    // retrieve the shader attributes handles
    mPositionAttributeHandle = glGetAttribLocation(mProgramHandle, "aPosition");
  
    // retrieve the shader uniform handles
    mViewProjMatrixUniformHandle = glGetUniformLocation(mProgramHandle, "uVPMatrix");
    mModelMatrixUniformHandle = glGetUniformLocation(mProgramHandle, "uMMatrix");
    mDiffuseColorUniformHandle = glGetUniformLocation(mProgramHandle, "uDiffuse");

    return true;
}

/**
 * Sets this Shader as the active one for the next renderings to be done
 */
void Shader::setActive() {
    if (mProgramHandle) {
        glUseProgram(mProgramHandle);
    }
}

/**
 * Returns the Vertex Position attribute handle
 */
GLint Shader::getPositionAttributeHandle(){
    return mPositionAttributeHandle;
}

/**
 * Returns the View Projection matrix uniform handle
 */
GLint Shader::getViewProjMatrixUniformHandle() {
    return mViewProjMatrixUniformHandle;
}

/**
 * Returns the Model matrix uniform handle
 */
GLint Shader::getModelMatrixUniformHandle() {
    return mModelMatrixUniformHandle;
}

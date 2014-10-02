/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#include "Environment.h"


/** Constructor */
Environment::Environment() {
    mWidth = 1; 
    mHeight = 1;
    mCamera = NULL;
}

/** Destructor */
Environment::~Environment() {
}


/**
 * Set the size of the projection screen
 */
void Environment::setDisplaySize(int width, int height) {
    
    mWidth = width;
    mHeight = height;
    if (mCamera){
        mCamera->setProjectionSize(mWidth, mHeight);
    }
}

/** 
 * Sets the camera to use for the rendering
 */
void Environment::setActiveCamera(Camera *camera) {
    mCamera = camera;
    mCamera->setProjectionSize(mWidth, mHeight);
}


/**
 * Sets the values for various uniform parameters in the given shaders
 */
void Environment::setUniformValues(Shader *shader) {
    if (mCamera) {
        mCamera->setUniformValues(shader);
    }
}

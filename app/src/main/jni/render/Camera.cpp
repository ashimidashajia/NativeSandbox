/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#include "Camera.h"
#include <GLES2/gl2.h>
#include <math.h>

#include "../utils/Logs.h"

#define TAG "Camera"

/** Constructor */
Camera::Camera() {
    mNearPlane = 0.1;
    mFarPlane = 10.0; 
    mFov = M_PI_2; // 90°
    mAspectRatio = 1.0f;
    
    mProjMatrix = new Matrix();
    mViewProjMatrix = new Matrix();
}

/** Destructor */
Camera::~Camera() {
    delete(mProjMatrix);
    delete(mViewProjMatrix);
}


/**
 * Sets the projection width and height
 */
void Camera::setProjectionSize(int width, int height){
    LogD(TAG, " ❯ setProjectionSize(%d, %d)", width, height);
    mAspectRatio = (width * 1.0f) / height; 
    LogD(TAG, "   • aspect ratio = %f", mAspectRatio);
}
    
/**
 * Sets the values for various uniform parameters in the given shaders : 
 * ViewProj, View, Proj, ...
 */
void Camera::setUniformValues(Shader *shader) {
    LogD(TAG, " ❯ setUniformValues()");
    glUniformMatrix4fv(shader->getViewProjMatrixUniformHandle(), 1, false, mViewProjMatrix->getData());
}

/**
 */
void Camera::onPreRender() {
    LogD(TAG, " ❯ onPreRender()");
    
    // update projection matrix
    mProjMatrix->setProjectionMatrix(mFov, mAspectRatio, mNearPlane, mFarPlane);
    mProjMatrix->log();
    
    // update View Projection Matrix : VP = P * V
    // V = C⁻¹ where C is the Matrix of the Camera
    // P = Projection matrix
    mViewProjMatrix->set(getMatrix());
    mViewProjMatrix->inverse();
    mViewProjMatrix->preMultiply(mProjMatrix);
    mViewProjMatrix->log();
}

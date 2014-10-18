/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#include "Camera.h"
#include "../math/Matrix.h"
#include "../utils/Logs.h"

#include <GLES2/gl2.h>
#include <math.h>



#define TAG "Camera"

/** Constructor */
Camera::Camera() {
    mNearPlane = 1;
    mFarPlane = 15.0; 
    mFov = M_PI_2 * 0.8f; // 90°
    mAspectRatio = 1.0f;
    
    mProjMatrix = ALLOCATE_MATRIX();
    setIdentityMatrix(mProjMatrix, 0);
    mViewProjMatrix = ALLOCATE_MATRIX();
    setIdentityMatrix(mViewProjMatrix, 0);
    mInvertViewMatrix = ALLOCATE_MATRIX();
    setIdentityMatrix(mInvertViewMatrix, 0); 
    
    LogD(TAG, "   • View Matrix (in constructor)");
    setLookAtMatrix(getMatrix(),  0, 0, 1, -5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    logMatrix(getMatrix(), 0);  
}

/** Destructor */
Camera::~Camera() {
    free(mProjMatrix);
    free(mViewProjMatrix);
    free(mInvertViewMatrix);
}


/**
 * Sets the projection width and height
 */
void Camera::setProjectionSize(int width, int height){
    LogD(TAG, " ❯ Camera::setProjectionSize(%d, %d)", width, height);
    mAspectRatio = (width * 1.0f) / height; 
    LogD(TAG, "   • aspect ratio = %f", mAspectRatio);
}
    
/**
 * Sets the values for various uniform parameters in the given shaders : 
 * ViewProj, View, Proj, ...
 */
void Camera::setUniformValues(Shader *shader) {
    LogD(TAG, " ❯ Camera::setUniformValues()");
    glUniformMatrix4fv(shader->getViewProjMatrixUniformHandle(), 1, false, mViewProjMatrix);
}

/**
 * Called before a frame is rendered
 */
void Camera::onPreRender() {
    LogD(TAG, " ❯ Camera::onPreRender()");
    
    // update projection matrix
    setPerspectiveMatrix(mProjMatrix, 0, mFov, mAspectRatio, mNearPlane, mFarPlane);
    LogD(TAG, "   • Projection Matrix (fov : %f, ratio : %f, near : %f, far : %f)", mFov, mAspectRatio, mNearPlane, mFarPlane);
    logMatrix(mProjMatrix, 0);
    
    
    // update View Projection Matrix : VP = P * V
    // V = C⁻¹ where C is the Matrix of the Camera
    // P = Projection matrix
    invertMatrix(mInvertViewMatrix, 0, getMatrix(), 0); 
    LogD(TAG, "   • Invert View Matrix");
    logMatrix(mViewProjMatrix, 0); 
    
    multiplyMatrices(mViewProjMatrix, 0, mProjMatrix, 0, mInvertViewMatrix, 0); 
    LogD(TAG, "   • ViewProjection Matrix");
    logMatrix(mViewProjMatrix, 0); 
}


/**
 * Returns a unique value to identify the component's type 
 */
long long int Camera::getType() {
    return T_CAMERA;
}

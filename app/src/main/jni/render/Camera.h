/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "../behavior/Component.h"
#include "../component/Transform.h"
#include "Shader.h"

/**
 * The Camera class gives some easy features to manipulate the View and Projection matrix, using 
 * a virtual Camera object which can be moved around. 
 */
class Camera : public Transform {

public:

    /** Constructor */
    Camera();

    /** Destructor */
    ~Camera();
    
    /**
     * Sets the values for various uniform parameters in the given shaders : 
     * ViewProj, View, Proj, ...
     */
    void setUniformValues(Shader *shader); 
    
    /**
     * Sets the projection width and height
     */
    void setProjectionSize(int width, int height);
    
    /**
     * Called before a frame is rendered
     */
    void onPreRender();
    
    /**
     * Returns a unique value to identify the component's type 
     */
    long long int getType();
    
private: 
    
    /** projection informations */
    float mNearPlane, mFarPlane;
    float mFov, mAspectRatio;
    
    float *mProjMatrix; 
    float *mViewProjMatrix; 
    float *mInvertViewMatrix; 
    
};

#endif

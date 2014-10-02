/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Shader.h"
#include "Camera.h"

/**
 * The Environment class keeps information about the global environmental state of the scene 
 * (camera, light, fog, ...)
 */
class Environment {

public:

    /** Constructor */
    Environment();

    /** Destructor */
    ~Environment();
    
    /**
     * Set the size of the projection screen
     */
    void setDisplaySize(int width, int height);
    
    /** 
     * Sets the camera to use for the rendering
     */
    void setActiveCamera(Camera *camera);
    
    /**
     * Sets the values for various uniform parameters in the given shaders
     */
    void setUniformValues(Shader *shader); 
    
private: 
    
    Camera *mCamera;
    int mWidth, mHeight;
    
};

#endif

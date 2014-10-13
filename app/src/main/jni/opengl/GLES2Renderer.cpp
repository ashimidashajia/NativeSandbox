/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#include "GLES2Renderer.h"
#include "GLUtils.h"
#include "../utils/Logs.h"
#include "../render/Shader.h"
#include "../render/Square.h"

#include <GLES2/gl2.h>

#define TAG "GLES2Renderer"

/** Constructor */
GLES2Renderer::GLES2Renderer() {
    
    mModel = new Square();
    mCamera = new Camera();
    
    mEnvironment = new Environment(); 
    
}

/** Destructor */
GLES2Renderer::~GLES2Renderer() {
    delete mModel;
    delete mEnvironment; 
    delete mCamera;
}

/**
 * Initialises the renderer. Returns true if the initialisation was  succesfull
 */
bool GLES2Renderer::init(int width, int height)  {
    LogD(TAG, " ❯ init()");

    // Global config     
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    
    // pass the projection info to the environment
    mEnvironment->setDisplaySize(width, height);
    mEnvironment->setActiveCamera(mCamera);

    // TODO foreach renderable  : renderable.init
    mModel->init();

    return true;
}

/**
 * Draws a single frame
 */
void GLES2Renderer::drawFrame() {

    // Clears the screen
    glClearColor(0.1f, 0.5f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    mCamera->onPreRender();

    // TODO foreach renderable : renderable.draw  
    mModel->render(mEnvironment); 
}
    


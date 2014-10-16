/**
 * Copyright (c) 2014 Xavier Gouchet
 *
 * This file is licensed under The MIT License (MIT).
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#ifndef GL_ES_2_RENDERER_H
#define GL_ES_2_RENDERER_H

#include "GLRenderer.h"
#include "../render/Model.h"
#include "../render/Environment.h"
#include "../render/Camera.h"

/**
 * The GLES2Renderer class is an implementation of GLRenderer using Open GL ES 2.0 apis.
 */
class GLES2Renderer : public GLRenderer {

public:

    /** Constructor */
    GLES2Renderer();

    /** Destructor */
    ~GLES2Renderer();

    /**
     * Initialises the renderer. Returns true if the initialisation was  succesfull
     */
    bool init(int width, int height) ;

    /**
     * Draws a single frame
     */
    void drawFrame(RenderablesListConstIterator it, RenderablesListConstIterator end);

protected:

private:

    Camera *mCamera; 
    Model *mModel;
    Environment *mEnvironment; 

};

#endif

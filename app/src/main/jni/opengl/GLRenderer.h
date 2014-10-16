/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 
#ifndef GL_RENDERER_H
#define GL_RENDERER_H

#include "../utils/Lists.h"

/**
 * The GLRenderer class is the link to the chosen OpenGL ES implementation (2.0 / 3.0), 
 * and performs the rendering of the frames. 
 */
class GLRenderer {

public:

    /** Destructor */
    ~GLRenderer() {
    }

    /**
     * Initialises the renderer. Returns true if the initialisation was  succesfull
     */
    virtual bool init(int width, int height) = 0;

    /**
     * Draws a single frame
     */
    virtual void drawFrame(RenderablesListConstIterator it, RenderablesListConstIterator end) = 0;

protected:

    /** Protected constructor */
    GLRenderer() {
    }

};


#endif

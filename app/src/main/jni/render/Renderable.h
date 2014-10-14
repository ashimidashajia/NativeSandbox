/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 

#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Environment.h"

/* Component Type Implementations */
#define T_SHAPE_3D    T_RENDERABLE | 0x01
#define T_SHAPE_2D    T_RENDERABLE | 0x02

/**
 * A Renderable component makes an object renderable
 */
class Renderable : public Component  {

public:

    /** Destructor */
    ~Renderable() {
    }
    
    /**
     * Initializes the object
     */
    virtual void init() = 0;

    /**
     * Renders the object
     */
    virtual void render(Environment *env) = 0;
    

protected:

    /** Constructor */
    Renderable() {
    }

};

#endif

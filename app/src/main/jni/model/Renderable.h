/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 

#ifndef RENDERABLE_H
#define RENDERABLE_H


/**
 * A Renderable component makes an object renderable
 */
class Renderable /* : public Component */ {

public:

    /** Destructor */
    ~Renderable() {
    }

    /**
     * Renders the object
     */
    virtual void render() = 0;

protected:

    /** Constructor */
    Renderable() {
    }

};

#endif

/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 

#ifndef SQUARE_H
#define SQUARE_H

#include "Model.h"

/**
 * A basic 1x1 square
 */
class Square : public Model {

public:

    /** Constructor */
    Square();

    /** Destructor */
    ~Square();

    /**
     * Initializes the object
     */
    virtual void init();

};

#endif

/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 

#ifndef BEHAVIORAL_OBJECT_H
#define BEHAVIORAL_OBJECT_H

#include "Component.h"

/**
 * The BehavioralObject class represents an object which as (at least one of) : 
 *  - some effect in the game state
 *  - a renderable component 
 *  - an audio component 
 *  - ... 
 */
class BehavioralObject {

public:

    /** Constructor */
    BehavioralObject();

    /** Destructor */
    ~BehavioralObject();
    
    /** adds a component to this game object */
    void add_component(Component *component);

private:

    // List of components
};

#endif

/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#ifndef ROTATOR_H
#define ROTATOR_H

#include "../behavior/Component.h"
#include "Transform.h"

/**
 * The Rotator class rotates the given object
 */
class Rotator : public Component{

public:

    /** Constructor */
    Rotator();

    /** Destructor */
    ~Rotator();
    
    /**
     * Returns a unique value to identify the component's type 
     */
    long long int getType();
    

    /**
     * Called when this component is attached to an object. The parent object is accesible in the 
     * mObject field from now on. 
     */
    void onAttached();
    
    
    /**
     * Performs a step of this component's behavior
     */
    void onProcess(TimeUnit deltaTime);
    
private: 

    /** the Transform */
    Transform *mTransform;

    
};

#endif

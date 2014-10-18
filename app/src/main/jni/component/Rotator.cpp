/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#include "Rotator.h"

#include "../utils/Logs.h"

#define TAG "Rotator"

/** Constructor */
Rotator::Rotator() {
    mTransform = NULL; 
}

/** Destructor */
Rotator::~Rotator() {
}


/**
 * Called when this component is attached to an object. The parent object is accesible in the 
 * mObject field from now on. 
 */
void Rotator::onAttached(){
   mTransform = dynamic_cast<Transform *>(mObject->getComponent(T_TRANSFORM)); 
}


/**
 * Performs a step of this component's behavior
 */
void Rotator::onProcess(TimeUnit deltaTime) {
    if (mTransform) {
        float timeSec = deltaTime * NANO_TO_SEC;
        float angle = timeSec * 1.57f;
        LogD(TAG, "   • Rotating object by %f", angle);
        mTransform->rotate(0.0f, 1.0f, 0.0f, angle);
        logMatrix(mTransform->getMatrix(), 0);
    }
}

/**
 * Returns a unique value to identify the component's type 
 */
long long int Rotator::getType() {
    return T_USER | 1;
}

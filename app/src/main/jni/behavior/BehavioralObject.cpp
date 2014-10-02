/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 
#include "BehavioralObject.h"


/** Constructor */
BehavioralObject::BehavioralObject() {
}

/** Destructor */
BehavioralObject::~BehavioralObject() {
}

/** adds a component to this game object */
void BehavioralObject::addComponent(Component *component) {
    if (component->onAttach(this)) {
        // TODO add to the components list 
    }
}

/**
 * Triggered when this component is attached to an object. Must return true if this component
 * can be attached (component can only be attached once).
 */
bool Component::onAttach(BehavioralObject *object) {
     if (mObject){
         return false;
     }
     
     mObject = object; 
     onAttached();
}

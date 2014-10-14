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
    // TODO delete all components in the object 
}

/** adds a component to this game object */
void BehavioralObject::addComponent(Component *component) {
    if (component->onAttach(this)) {
        mComponents.push_back(component);
    }
}


/** Returns the first available component matching the given type */
Component *BehavioralObject::getComponent(long long int type) {
    
    ComponentsListIterator end = mComponents.end();
    for (ComponentsListIterator it = mComponents.begin(); it != end; ++it) {
        if (((*it)->getType() & type) == type) {
            return (*it); 
        }
    }
    
    return NULL; 
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

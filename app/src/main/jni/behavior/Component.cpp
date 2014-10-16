/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 
#include "Component.h"
#include "../utils/Logs.h"

#define TAG     "Component"

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


/**
 * Components sort by priority : returns true if lhs < rhs
 */
bool PrioritySortPredicate(Component *lhs, Component *rhs) {
    return lhs->getPriority() < rhs->getPriority();
}


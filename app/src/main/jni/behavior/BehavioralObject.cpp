/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 
#include "BehavioralObject.h"
#include "../utils/Logs.h"

#define TAG     "BehavioralObject"


/** Constructor */
BehavioralObject::BehavioralObject() {
}

/** Destructor */
BehavioralObject::~BehavioralObject() {
    // TODO delete all components in the object 
}


/**
 * Called when this object is attached to the engine
 */
void BehavioralObject::onAttach(BehaviorEngine *engine) {
    ComponentsListConstIterator end = mComponents.end(); 
    for (ComponentsListConstIterator it = mComponents.begin(); it != end; ++it) {
        LogV(TAG, "   • adding component to engine");
        engine->addComponent((*it)); 
    }
}

/**
 * Called when this object is detached to the engine
 */
void BehavioralObject::onDetach(BehaviorEngine *engine) {
    ComponentsListConstIterator end = mComponents.end(); 
    for (ComponentsListConstIterator it = mComponents.begin(); it != end; ++it) {
        engine->removeComponent((*it)); 
    }
}

/** adds a component to this game object */
void BehavioralObject::addComponent(Component *component) {
    if (component->onAttach(this)) {
        mComponents.push_back(component);
    } else {
         LogV(TAG, "   • can't attach component : already attached to someone else");
    }
}


/** Returns the first available component matching the given type */
Component *BehavioralObject::getComponent(long long int type) {
    
    ComponentsListConstIterator end = mComponents.end();
    for (ComponentsListConstIterator it = mComponents.begin(); it != end; ++it) {
        if (((*it)->getType() & type) == type) {
            return (*it); 
        }
    }
    
    return NULL; 
}


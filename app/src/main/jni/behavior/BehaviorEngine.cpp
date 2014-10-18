/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 
#include "BehaviorEngine.h"
#include "BehavioralObject.h"
#include "Component.h"
#include "../utils/Lists.h"
#include "../utils/Logs.h"
#include "../component/Transform.h"
#include "../component/Rotator.h"
#include "../render/Square.h"

#define TAG  "BehaviorEngine"

/** Constructor */
BehaviorEngine::BehaviorEngine() {
    mIsLoading = false; 
    
    BehavioralObject *square = new BehavioralObject(); 
    square->addComponent(new Transform());
    square->addComponent(new Square());
    square->addComponent(new Rotator());
    
    addObject(square);
}


/** Destructor */
BehaviorEngine::~BehaviorEngine() {
    // TODO clear the lists
}

/**
 * Adds an object to the engine
 */
void BehaviorEngine::addObject(BehavioralObject *object) {
    mObjectsToBeAdded.push_back(object); 
}

/**
 * Removes an object from the engine
 */
void BehaviorEngine::removeObject(BehavioralObject *object) {
    mObjectsToBeRemoved.push_back(object);
}

/**
 * Adds a component to the engine
 */
void BehaviorEngine::addComponent(Component *object) {
    mComponentsToBeAdded.push_back(object);
}

/**
 * Removes a component from the engine
 */
void BehaviorEngine::removeComponent(Component *object) {
    mComponentsToBeRemoved.push_back(object);
}

/**
 * Method to update the whole behavioral state
 */ 
void BehaviorEngine::updateState(TimeUnit deltaTime) {
    LogV(TAG, " ❯ BehaviorEngine::updateState(%lld)", deltaTime);

    // check the Bootstrapping case 
    if (mIsLoading) {
        return; 
    }
        
    // refresh list of objects
    updateInternalState();
    
    // foreach component
    ComponentsListConstIterator it;
    ComponentsListConstIterator start = mComponents.begin();
    ComponentsListConstIterator end = mComponents.end();
    
    // pre process
    LogV(TAG, "   • Pre process");
    for (it = start; it != end; ++it) {
        (*it)->onPreProcess();
    }
    
    // update
    LogV(TAG, "   • Process");
    for (it = start; it != end; ++it) {
        (*it)->onProcess(deltaTime);
    }
    
    // post process
    LogV(TAG, "   • Post process");
    for (it = start; it != end; ++it) {
        (*it)->onPostProcess();
    }
    
}

/**
 * Update the various lists inside the behavior engine
 */
void BehaviorEngine::updateInternalState() {
    LogV(TAG, " ❯ BehaviorEngine::updateInternalState()");
    
    updateInternalObjects();
    updateInternalComponents();
    
    // delete objects 
    BehavioralObjectsListConstIterator it; 
    BehavioralObjectsListConstIterator end = mObjectsToBeRemoved.end();
    for (it = mObjectsToBeRemoved.begin(); it != end; ++it){
        delete(*it); 
    }
    
    // clear all 
    mObjectsToBeAdded.clear(); 
    mObjectsToBeRemoved.clear(); 
    mComponentsToBeAdded.clear(); 
}

    
/**
 * Update the BehavioralObject lists
 */
void BehaviorEngine::updateInternalObjects() {
    
    // Remove objects 
    BehavioralObjectsListConstIterator it; 
    BehavioralObjectsListConstIterator end = mObjectsToBeRemoved.end();
    for (it = mObjectsToBeRemoved.begin(); it != end; ++it){
        LogV(TAG, "   • Removing Object");
        mObjectsToBeAdded.remove((*it));
        mObjects.remove((*it));
        
        (*it)->onDetach(this);
    }
    
    // add objects 
    end = mObjectsToBeAdded.end();
    for (it = mObjectsToBeAdded.begin(); it != end; ++it){
        LogV(TAG, "   • Adding Object");
        mObjects.push_back((*it)); 
        
        (*it)->onAttach(this);
    }
}

/**
 * Update the Component lists
 */
void BehaviorEngine::updateInternalComponents() {
    
    // Remove objects 
    ComponentsListConstIterator it; 
    ComponentsListConstIterator end = mComponentsToBeRemoved.end();
    for (it = mComponentsToBeRemoved.begin(); it != end; ++it){
        LogV(TAG, "   • Removing Component %lld", (*it)->getType());
        mComponentsToBeAdded.remove((*it));
        mComponents.remove((*it));
        
        if (((*it)->getType() & T_RENDERABLE) == T_RENDERABLE) {
            LogV(TAG, "   • Removing Renderable");
            mRenderables.remove((Renderable *)(*it));
        }
    }
    
    // add objects 
    end = mComponentsToBeAdded.end();
    for (it = mComponentsToBeAdded.begin(); it != end; ++it){
        LogV(TAG, "   • Adding Component %lld", (*it)->getType());
        mComponents.push_back((*it));
        if (((*it)->getType() & T_RENDERABLE) == T_RENDERABLE) {
            LogV(TAG, "   • Adding Renderable");
            mRenderables.push_back((Renderable *)(*it)); 
        }
    }
    
    // finally sort the components by priority
    mComponents.sort(PrioritySortPredicate); 
    // TODO mRenderables.sort(RenderPrioritySortPredicate);
}

/**
 * Called just before rendering a frame
 */
void BehaviorEngine::preRender() {
    ComponentsListConstIterator end = mComponents.end();
    for (ComponentsListConstIterator it = mComponents.begin(); it != end; ++it) {
        (*it)->onPreRender();
    }
}

/**
 * Called just after rendering a frame
 */
void BehaviorEngine::postRender() {
    ComponentsListConstIterator end = mComponents.end();
    for (ComponentsListConstIterator it = mComponents.begin(); it != end; ++it) {
        (*it)->on_post_render();
    }
}

/**
 * Returns an iterator on renderables
 */
RenderablesListConstIterator BehaviorEngine::getRenderablesIterator() {
    return mRenderables.begin();
}

/**
 * Returns the last renderable to iterate on
 */
RenderablesListConstIterator BehaviorEngine::getRenderablesEnd() {
    return mRenderables.end();
}

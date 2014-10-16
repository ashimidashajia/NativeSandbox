/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 

#ifndef BEHAVIOR_ENGINE_H
#define BEHAVIOR_ENGINE_H

#include "BehavioralObject.h"
#include "../core/TimeManager.h"
#include "../utils/Lists.h"

#include <stdint.h>
#include <android_native_app_glue.h>


#define MAX_FPS             60
#define FRAME_PERIOD_NANO   SECOND_IN_NANO / MAX_FPS;

#define MAX_FRAME_SKIPPED   2

/**
 * The Behavior Engine class handles the behavior of all objects
 */
class BehaviorEngine {

public:

    /** Constructor */
    BehaviorEngine();

    /** Destructor */
    ~BehaviorEngine();
    
    /**
     * Adds an object to the engine
     */
    void addObject(BehavioralObject *object);
    
    /**
     * Removes an object from the engine
     */
    void removeObject(BehavioralObject *object);
    
    /**
     * Adds a component to the engine
     */
    void addComponent(Component *object);
    
    /**
     * Removes a component from the engine
     */
    void removeComponent(Component *object);

    /**
     * Method to update the whole behavioral state
     */
    void updateState(TimeUnit deltaTime);
    
    /**
     * Called just before rendering a frame
     */
    void preRender();
    
    /**
     * Called just after rendering a frame
     */
    void postRender();
    
    /**
     * Returns an iterator on renderables
     */
    RenderablesListConstIterator getRenderablesIterator();
    
    /**
     * Returns the last renderable to iterate on
     */
    RenderablesListConstIterator getRenderablesEnd();
    
private :

    /**
     * Update the various lists inside the behavior engine
     */
    void updateInternalState();
    
    /**
     * Update the BehavioralObject lists
     */
    void updateInternalObjects();
    
    /**
     * Update the Component lists
     */
    void updateInternalComponents();
    
    // TODO replace lists by sets

    /** List of behavioral objects */
    BehavioralObjectsList mObjects ;
    /** List of behavioral objects to be added at the beginning of next frame */
    BehavioralObjectsList mObjectsToBeAdded;
    /** List of behavioral objects to be removed at the beginning of next frame */
    BehavioralObjectsList mObjectsToBeRemoved;
    
    /** List of components */
    ComponentsList mComponents;
    /** List of Renderables (subset of mComponents) */
    RenderablesList mRenderables;
    
    /** List of components to be added at the beginning of next frame */
    ComponentsList mComponentsToBeAdded;
    /** List of components to be removed at the beginning of next frame */
    ComponentsList mComponentsToBeRemoved;
    
    /** Is the current scene being loaded */
    bool mIsLoading;

};

#endif

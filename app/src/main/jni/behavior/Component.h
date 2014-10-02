/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 

#ifndef COMPONENT_H
#define COMPONENT_H

#include "BehavioralObject.h"
#include "../core/TimeManager.h"

// Double include loop
class BehavioralObject;

/**
 * The Component class describes one of the behaviors of a game object. 
 */
class Component {

public:

    /** Constructor */
    Component() {}

    /** Destructor */
    ~Component() {}
    
    /**
     * Triggered when this component is attached to an object. Must return true if this component
     * can be attached (component can only be attached once).
     */
    bool onAttach(BehavioralObject *object);
    
    /**
     * Called when this component is attached to an object. The parent object is accesible in the 
     * mObject field
     */
    virtual void onAttached() {}

    /** 
     * Returns the execution priority for this component 
     */
    virtual int getPriority() {}
    
    /**
     * Called before a step is processed. 
     */
    virtual void onPreProcess() {}
    
    /**
     * Performs a step of this component's behavior
     */
    virtual void onProcess(TimeUnit deltaTime) {}
    
    /**
     * Called after a step has been brocessed
     */
    virtual void onPostProcess() {}
    
    /**
     * Called before a frame is rendered
     */
    virtual void onPreRender() {}
    
    /**
     * Called after a frame was rendered
     */
    virtual void on_post_render() {}

protected:

    /** the parent of this component */
    BehavioralObject *mObject;
};

#endif

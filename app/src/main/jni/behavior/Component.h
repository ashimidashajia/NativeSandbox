/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 

#ifndef COMPONENT_H
#define COMPONENT_H

#include "../core/TimeManager.h"

/**
 * The Component class describes one of the behaviors of a game object. 
 */
class Component {

public:

    /** Constructor */
    Component();

    /** Destructor */
    ~Component();

    /** 
     * Returns the execution priority for this component 
     */
    virtual int get_priority() = 0;
    
    /**
     * Called before a step is processed. 
     */
    virtual void on_pre_process() = 0;
    
    /**
     * Performs a step of this component's behavior
     */
    virtual void on_process(TimeUnit delta_time) = 0;
    
    /**
     * Called after a step has been brocessed
     */
    virtual void on_post_process() = 0;
    
    /**
     * Called before a frame is rendered
     */
    virtual void on_pre_render() = 0;
    
    /**
     * Called after a frame was rendered
     */
    virtual void on_post_render() = 0;

private:

    // TODO List of components
};

#endif

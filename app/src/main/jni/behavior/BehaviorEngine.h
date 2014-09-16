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
     * Method to clean up everything at the start of a new frame
     */
    void start_frame();

    /**
     * Method to update the whole behavioral state
     */
    void update_state(TimeUnit delta_time);
    
    /**
     * Called just before rendering a frame
     */
    void pre_render();
    
    /**
     * Called just after rendering a frame
     */
    void post_render();
    
private :

    /** list of behavioral objects ? */
    // List<BehavioralObject> m_objects ??;
    
    /** List of components */
    // List<Component> m_components;

};

#endif
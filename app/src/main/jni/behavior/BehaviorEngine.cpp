/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 
#include "BehaviorEngine.h"
#include "../utils/Logs.h"

#define TAG  "BehaviorEngine"

/** Constructor */
BehaviorEngine::BehaviorEngine() {
}


/** Destructor */
BehaviorEngine::~BehaviorEngine() {
}

/**
 * Method to update the whole behavioral state
 */
void BehaviorEngine::update_state(TimeUnit delta_time) {
    LOG_V(TAG, " ❯ update_state(%lld)", delta_time);

    // TODO update some things 
    // foreach (GameComponent in m_game_objects) {
    //      object->update(delta_time);
    // }
}


/**
 * Method to clean up everything at the start of a new frame
 */
void BehaviorEngine::start_frame() {
    // TODO update some things 
}

/**
 * Called just before rendering a frame
 */
void BehaviorEngine::pre_render() {
    // TODO update some things 
}

/**
 * Called just after rendering a frame
 */
void BehaviorEngine::post_render() {
    // TODO update some things 
}

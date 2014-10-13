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
void BehaviorEngine::updateState(TimeUnit deltaTime) {
    LogV(TAG, " ❯ BehaviorEngine::updateState(%lld)", deltaTime);

    // TODO update some things 
    // foreach (GameComponent in mGameObjects) {
    //      object->update(deltaTime);
    // }
}


/**
 * Method to clean up everything at the start of a new frame
 */
void BehaviorEngine::startFrame() {
    // TODO update some things 
}

/**
 * Called just before rendering a frame
 */
void BehaviorEngine::preRender() {
    // TODO update some things 
}

/**
 * Called just after rendering a frame
 */
void BehaviorEngine::postRender() {
    // TODO update some things 
}

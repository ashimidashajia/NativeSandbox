/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 
#include "GameEngine.h"
#include "../utils/Logs.h"

#define TAG  "GameEngine"

/** Constructor */
GameEngine::GameEngine() {
}


/** Destructor */
GameEngine::~GameEngine() {
}


void GameEngine::update_game_state(TimeUnit delta_time) {
    LOG_V(TAG, " ❯ android_main(app)");
    
    LOG_V(TAG, "   • delta time %lld", delta_time);
    
    // TODO update some things 
    // foreach (GameObject in m_game_objects) {
    //      object->update(delta_time);
    // }
}

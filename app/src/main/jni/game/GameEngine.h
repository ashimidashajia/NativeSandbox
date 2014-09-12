/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "../core/TimeManager.h"

#include <stdint.h>
#include <android_native_app_glue.h>


#define MAX_FPS             60
#define FRAME_PERIOD_NANO   SECOND_IN_NANO / MAX_FPS;

#define MAX_FRAME_SKIPPED   2

/**
 * The Game Engine class handles the game mechanics and model
 */
class GameEngine {

public:

    /** Constructor */
    GameEngine();

    /** Destructor */
    ~GameEngine();

    /**
     * Method to update the whole game state
     */
    void update_game_state(TimeUnit delta_time);

private :
        
};

#endif

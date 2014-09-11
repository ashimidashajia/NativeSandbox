/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 
#ifndef CORE_ENGINE_H
#define CORE_ENGINE_H

#include "../opengl/GLEngine.h"
#include "../game/GameEngine.h"
#include "TimeManager.h"

#include <stdint.h>
#include <android_native_app_glue.h>


#define MAX_FPS             60
#define FRAME_PERIOD_NANO   SECOND_IN_NANO / MAX_FPS;

#define MAX_FRAME_SKIPPED   2

/**
 * The Core Engine class is the top most element, handling the main loop, 
 * as well as the communication with the Android ecosystem (touch / key inputs, 
 * application life cycle, device sensors, ...)
 */
class CoreEngine {

private :

    /** The OpenGL engine */
    GLEngine *m_gl_engine;
    /** The Game engine */
    GameEngine *m_game_engine; 
    /** The time manager */
    TimeManager *m_time_manager;

    /**
     * Callback triggered when the user perform a touch event
     * Return 0 to let the framework handle the key event, 1 if everything has been handled
     */
    int32_t on_touch_event(AInputEvent *event);

    /**
     * Callback triggered when the user uses a physical (or software ?) key
     * Return 0 to let the framework handle the key event, 1 if everything has been handled
     */
    int32_t on_key_event(AInputEvent *event);

    /**
     * Poll all available looper events
     */
    void poll_looper_events(struct android_app *app);


public:

    /** Constructor */
    CoreEngine();

    /** Destructor */
    ~CoreEngine();

    /**
     * Method to handle the application commands, usually linked to the application lifecycle
     */
    void handle_app_command(struct android_app *app, int32_t command);
    
    /**
     * Callback for input events (touch, key).
     * Return 1 to notify that the event was handled internally, or 0 to let the
     * default behavior (eg : back pressed)
     */
    int32_t handle_input_event(AInputEvent *event);

    /** The main loop */
    void main_loop(struct android_app *app);
};

#endif

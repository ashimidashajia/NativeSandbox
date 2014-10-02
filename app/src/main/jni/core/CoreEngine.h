/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 

#ifndef CORE_ENGINE_H
#define CORE_ENGINE_H

#include "../opengl/GLEngine.h"
#include "../behavior/BehaviorEngine.h"
#include "TimeManager.h"
#include "SavedState.h"

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

public:

    /** Constructor */
    CoreEngine();

    /** Destructor */
    ~CoreEngine();

    /**
     * Method to handle the application commands, usually linked to the application lifecycle
     */
    void handleAppCommand(struct android_app *app, int32_t command);

    /**
     * Callback for input events (touch, key).
     * Return 1 to notify that the event was handled internally, or 0 to let the
     * default behavior (eg : back pressed)
     */
    int32_t handleInputEvent(AInputEvent *event);

    /** The main loop */
    void mainLoop(struct android_app *app);

private :

    /** The OpenGL engine */
    GLEngine *mGLEngine;
    /** The behavior engine */
    BehaviorEngine *mBehaviorEngine;
    /** The time manager */
    TimeManager *mTimeManager;
    /** the saved state (for seamless app transitions) */
    SavedState *mSavedState;

    /**
     * Callback triggered when the user perform a touch event
     * Return 0 to let the framework handle the key event, 1 if everything has been handled
     */
    int32_t onTouchEvent(AInputEvent *event);

    /**
     * Callback triggered when the user uses a physical (or software ?) key
     * Return 0 to let the framework handle the key event, 1 if everything has been handled
     */
    int32_t onKeyEvent(AInputEvent *event);

    /**
     * Poll all available looper events
     */
    void pollLooperEvents(struct android_app *app);
};

#endif

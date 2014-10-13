/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#include "CoreEngine.h"
#include "../utils/Logs.h"

#define TAG  "CoreEngine"

/** Constructor */
CoreEngine::CoreEngine() {
    mBehaviorEngine = new BehaviorEngine();
    mGLEngine = new GLEngine();
    mTimeManager = new TimeManager();
    mSavedState = new SavedState();
}


/** Destructor */
CoreEngine::~CoreEngine() {
    delete mBehaviorEngine;
    delete mGLEngine;
    delete mTimeManager;
    delete mSavedState;
}

/**
 * Method to handle the application commands, usually linked to the application lifecycle
 */
void CoreEngine::handleAppCommand(struct android_app *app, int32_t command) {
    LogD(TAG, " ❯ CoreEngine::handle_app_cmd(app, command=%d)", command);

    switch (command) {

        case APP_CMD_INIT_WINDOW:
            // The window is being initialised, set it up
            if (app->window != NULL) {
                mGLEngine->initDisplay(app->window);
                mGLEngine->drawFrame();
            }
            break;

        case APP_CMD_SAVE_STATE: {
            // save current state
            size_t savedStateSize = mSavedState->getSize();
            app->savedState = malloc(savedStateSize);
            mSavedState->write(app->savedState);
            app->savedStateSize = savedStateSize;
        }
            break;

        case APP_CMD_TERM_WINDOW:
            // The window is being closed, release everything
            mGLEngine->terminateDisplay();
            break;


        case APP_CMD_WINDOW_RESIZED:
        case APP_CMD_WINDOW_REDRAW_NEEDED:
        case APP_CMD_CONTENT_RECT_CHANGED:
        case APP_CMD_GAINED_FOCUS:
        case APP_CMD_LOST_FOCUS:
        case APP_CMD_CONFIG_CHANGED:
        case APP_CMD_LOW_MEMORY:
        case APP_CMD_START:
        case APP_CMD_RESUME:
        case APP_CMD_INPUT_CHANGED:
            // TODO handle all commands
            break;
        default:
            LogI(TAG, "   • Unknown app command %d", command)
            break;
    }
}


/**
 * Callback for input events (touch, key).
 * Return 1 to notify that the event was handled internally, or 0 to let the
 * default behavior (eg : back pressed)
 */
int32_t CoreEngine::handleInputEvent(AInputEvent *event) {

    LogD(TAG, " ❯ CoreEngine::handle_input(app, event)");
    int32_t eventType = AInputEvent_getType(event);
    int32_t handled = 0;


    switch (eventType) {
        case AINPUT_EVENT_TYPE_MOTION :
            handled = onTouchEvent(event);
            break;

        case AINPUT_EVENT_TYPE_KEY:
            handled = onKeyEvent(event);
            break;

        default:
            LogI(TAG, "   • Unknown event type %d", eventType)
            break;
    }

    return handled;
}

/**
 * Callback triggered when the user perform a touch event
 * Return 0 to let the framework handle the key event, 1 if everything has been handled
 */
int32_t CoreEngine::onTouchEvent(AInputEvent *event) {

    LogD(TAG, " ❯ CoreEngine::onTouchEvent(app, event)");

    size_t i, pointerCount = AMotionEvent_getPointerCount(event);
    float x, y;

    for (i = 0; i < pointerCount; ++i) {
        x = AMotionEvent_getX(event, i);
        y = AMotionEvent_getY(event, i);
        LogD(TAG, "   • Motion event %zu: (%.2f, %.2f)", i, x, y);
    }

    return 0;
}


/**
 * Callback triggered when the user uses a physical (or software ?) key
 * Return 0 to let the framework handle the key event, 1 if everything has been handled
 */
int32_t CoreEngine::onKeyEvent(AInputEvent *event) {

    LogD(TAG, " ❯ CoreEngine::onKeyEvent(app, event)");

    int32_t action, code;

    // AKEY_EVENT_ACTION_DOWN / AKEY_EVENT_ACTION_UP / AKEY_EVENT_ACTION_MULTIPLE
    action = AKeyEvent_getAction(event);

    // The key code (ie : physical id)
    code = AKeyEvent_getKeyCode(event);
    LogD(TAG, "   • Event : action=%d, code=%d", action, code);


    switch (code) {
        // let the back key press be handled automatically by the framework
        case AKEYCODE_BACK:
            return 0;
        default :
            return 0;
    }

}

/**
 * Poll all available looper events
 */
void CoreEngine::pollLooperEvents(struct android_app *app) {

    // variables holding the polled events information
    int32_t events;
    struct android_poll_source *source;
    int pollTimeoutMs = 0; // 0 = non blocking

    int ident = ALooper_pollAll(pollTimeoutMs, NULL, &events, (void **) &source);
    if (ident >= 0) {

        // process events
        if (source != NULL) {
            LogD(TAG, "   • Processing an event %d", source->id);
            // let the source process the events and forward them to our callbacks
            source->process(app, source);
        }
    }
}

/** The main loop */
void CoreEngine::mainLoop(struct android_app *app) {

    // 
    TimeUnit loopStartTime, initialStepTime, deltaTime;
    int framesSkipped;
    struct timespec sleepTime = {0};

    // Main application loop
    while (1) {
        LogV(TAG, "   • Main loop");

        // 
        loopStartTime = mTimeManager->getTimeNano();
        framesSkipped = 0;

        // 1 : handle external events (input, app lifecycle)
        pollLooperEvents(app);

        // 2 : check if the app needs to be destroyed
        if (app->destroyRequested != 0) {
            LogI(TAG, "   • Destroy requested");
            // exit all loops
            return;
        }

        // 3 : update system
        mBehaviorEngine->updateState(mTimeManager->getDeltaTimeNano());


        // 4 : update rendering
        mBehaviorEngine->preRender();
        mGLEngine->drawFrame();
        mBehaviorEngine->postRender();

        // 5 : Compute the sleep time
        initialStepTime = mTimeManager->getTimeNano() - loopStartTime;
        sleepTime.tv_nsec = FRAME_PERIOD_NANO - initialStepTime;

        // 6a : sleep time is positive, we're ahead of schedule
        if (sleepTime.tv_nsec >= 0) {
            nanosleep(&sleepTime, (struct timespec *) NULL);
        }

        // 6b : we have an overhead, so we need to catch up
        // we'll force as many updates as the number of frames we missed (supposedly)
        // but will only catch up as much as MAX_FRAME_SKIPPED frames
        while ((sleepTime.tv_nsec < 0) && (framesSkipped < MAX_FRAME_SKIPPED)) {
            LogD(TAG, "   • Catching up on missed frames");

            mBehaviorEngine->updateState(mTimeManager->getDeltaTimeNano());

            // add frame period to check if we get to thein next frame
            sleepTime.tv_nsec += FRAME_PERIOD_NANO;
            ++framesSkipped;
        }

    }
}

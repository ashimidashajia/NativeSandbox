/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 

#include "AndroidMain.h"

#include "utils/Logs.h"
#include "core/CoreEngine.h"



// TODO Write a JNI_OnLoad mapping method

extern "C" {

#define TAG  "AndroidMain"

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app *app) {

    LOG_D(TAG, " ❯ android_main(app)");

    // Call a method from the android_native_app_glue to make sure it is linked
    app_dummy();

    // Create the engine
    CoreEngine *core_engine = new CoreEngine();

    // setup the application callbacks
    app->userData = (void *) core_engine;
    app->onAppCmd = handle_app_command;
    app->onInputEvent = handle_input_event;

    // Start the main loop
    core_engine->main_loop(app);
}

/**
 * Callback for input events (touch, key).
 * Return 1 to notify that the event was handled internally, or 0 to let the
 * default behavior (eg : back pressed)
 */
static int32_t handle_input_event(struct android_app *app, AInputEvent *event) {
    CoreEngine *engine = (CoreEngine *) app->userData;

    if (engine == NULL) {
        return 0;
    }

    return engine->handle_input_event(event);
}


/**
 * Callback to handle the application commands, usually linked to the application lifecycle
 */
static void handle_app_command(struct android_app *app, int32_t command) {
    CoreEngine *engine = (CoreEngine *) app->userData;

    if (engine != NULL) {
        engine->handle_app_command(app, command);
    }
}

}

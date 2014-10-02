/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 

#ifndef ANDROID_MAIN_H_
#define ANDROID_MAIN_H_

#include <jni.h>
#include <android_native_app_glue.h>

extern "C" {

/**
* This is the main entry point of a native application that is using
* android_native_app_glue.  It runs in its own thread, with its own
* event loop for receiving input events and doing other things.
*/
void android_main(struct android_app *state);

/**
 * Callback to handle the application commands, usually linked to the application lifecycle
 */
static void handleAppCommand(struct android_app *app, int32_t command);

/**
 * Callback for input events (touch, key).
 * Return 1 to notify that the event was handled internally, or 0 to let the
 * default behavior (eg : back pressed)
 */
static int32_t handleInputEvent(struct android_app *app, AInputEvent *event);

}

#endif

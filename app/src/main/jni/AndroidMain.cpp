#include <android_native_app_glue.h>

#include "AndroidMain.h"
#include "utils/Logs.h"


// TODO Write a JNI_OnLoad mapping method

extern "C" {

#define TAG  "AndroidMain"

/**
* Method to handle the application commands, usually linked to the application lifecycle
*/
static void handle_app_cmd(struct android_app *app, int32_t command) {
    LOG_D(TAG, " ❯ handle_app_cmd(app, command=%d)", command);

    switch (command) {
        case APP_CMD_INPUT_CHANGED:
            break;
        case APP_CMD_INIT_WINDOW:
            break;
        case APP_CMD_TERM_WINDOW:
            break;
        case APP_CMD_WINDOW_RESIZED:
            break;
        case APP_CMD_WINDOW_REDRAW_NEEDED:
            break;
        case APP_CMD_CONTENT_RECT_CHANGED:
            break;


        default:
            LOG_I(TAG, "   • Unknown app command %d", command)
            break;
    }
}

/**
* Callback triggered when the user perform a touch event
* Return 0 to let the framework handle the key event, 1 if everything has been handled
*/
static int32_t on_touch_event(struct android_app *app, AInputEvent *event) {

    LOG_D(TAG, " ❯ on_touch_event(app, event)");

    size_t i, pointer_count = AMotionEvent_getPointerCount(event);
    float x, y;

    for (i = 0; i < pointer_count; ++i) {
        x = AMotionEvent_getX(event, i);
        y = AMotionEvent_getY(event, i);
        LOG_D(TAG, "   • Motion event %zu: (%.2f, %.2f)", i, x, y);
    }

    return 0;
}

/**
* Callback triggered when the user uses a physical (or software) key
* Return 0 to let the framework handle the key event, 1 if everything has been handled
*/
static int32_t on_key_event(struct android_app *app, AInputEvent *event) {

    LOG_D(TAG, " ❯ on_key_event(app, event)");

    int32_t action, code;

    // AKEY_EVENT_ACTION_DOWN / AKEY_EVENT_ACTION_UP / AKEY_EVENT_ACTION_MULTIPLE
    action = AKeyEvent_getAction(event);

    // The key code (ie : physical id)
    code = AKeyEvent_getKeyCode(event);
    LOG_D(TAG, "   • Event : action=%d, code=%d", action,code);


    switch (code) {
        // let the back key press be handled automatically by the framework
        case AKEYCODE_BACK:
            return 0;
        default :
            return 0;
    }

}

/**
* Callback for input events (touch, key).
* Return 1 to notify that the event was handled internally, or 0 to let the
* default behavior (eg : back pressed)
*/
static int32_t handle_input_event(struct android_app *app, AInputEvent *event) {

    LOG_D(TAG, " ❯ handle_input(app, event)");
    int32_t event_type = AInputEvent_getType(event);
    int32_t handled = 0;


    switch (event_type) {
        case AINPUT_EVENT_TYPE_MOTION :
            handled = on_touch_event(app, event);
            break;

        case AINPUT_EVENT_TYPE_KEY:
            handled = on_key_event(app, event);
            break;

        default:
            LOG_I(TAG, "   • Unknown event type %d", event_type)
            break;
    }

    return handled;
}

/**
* This is the main entry point of a native application that is using
* android_native_app_glue.  It runs in its own thread, with its own
* event loop for receiving input events and doing other things.
*/
void android_main(struct android_app *app) {

    LOG_D(TAG, " ❯ android_main(app)");

    // Call a method from the android_native_app_glue to make sure it is linked
    app_dummy();

    // setup the application callbacks
    // app->userData = ... ;
    app->onAppCmd = handle_app_cmd;
    app->onInputEvent = handle_input_event;

    // variables holding the polled events information
    int32_t events;
    struct android_poll_source *source;
    int poll_timeout_ms;


    // Main application loop
    while (1) {

        // -1 = no timeout
        // 0 = non blocking
        // >0 = timeout in milliseconds
        poll_timeout_ms = -1;

        // Poll looper events
        while (ALooper_pollAll(poll_timeout_ms, NULL, &events, (void **) &source) >= 0) {

            // process events
            if (source != NULL) {
                LOG_D(TAG, "   • Processing an event %d", source->id);
                // let the source process the events and forward them to our callbacks
                source->process(app, source);
            }

            // check if the app needs to be destroyed
            if (app->destroyRequested != 0) {
                LOG_D(TAG, "   • Destroy requested");
                // exit all loops
                return;
            }
        }

        // perform animations, updates, ...

    }
}

}
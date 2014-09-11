#include "CoreEngine.h"

#include "../utils/Logs.h"

#define TAG  "CoreEngine"

CoreEngine::CoreEngine() {
    m_gl_engine = new GLEngine();
    m_time_manager = new TimeManager();
}


CoreEngine::~CoreEngine() {
    delete m_gl_engine;
    delete m_time_manager;
}

/**
* Method to handle the application commands, usually linked to the application lifecycle
*/
void CoreEngine::handle_app_command(struct android_app *app, int32_t command) {
    LOG_D(TAG, " ❯ handle_app_cmd(app, command=%d)", command);

    switch (command) {

        case APP_CMD_INIT_WINDOW:
            // The window is being initialised, set it up
            if (app->window != NULL) {
                m_gl_engine->init_display(app->window);
                m_gl_engine->draw_frame();
            }
            break;

        case APP_CMD_SAVE_STATE:
            // TODO save current state
            // app->savedState =  malloc(sizeof(...));
            // app->savedStateSize = ... ;
            break;


        case APP_CMD_TERM_WINDOW:
            // The window is being closed, release everything
            m_gl_engine->terminate_display();
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
            LOG_I(TAG, "   • Unknown app command %d", command)
            break;
    }
}


/**
* Callback for input events (touch, key).
* Return 1 to notify that the event was handled internally, or 0 to let the
* default behavior (eg : back pressed)
*/
int32_t CoreEngine::handle_input_event(AInputEvent *event) {

    LOG_D(TAG, " ❯ handle_input(app, event)");
    int32_t event_type = AInputEvent_getType(event);
    int32_t handled = 0;


    switch (event_type) {
        case AINPUT_EVENT_TYPE_MOTION :
            handled = on_touch_event(event);
            break;

        case AINPUT_EVENT_TYPE_KEY:
            handled = on_key_event(event);
            break;

        default:
            LOG_I(TAG, "   • Unknown event type %d", event_type)
            break;
    }

    return handled;
}

/**
* Callback triggered when the user perform a touch event
* Return 0 to let the framework handle the key event, 1 if everything has been handled
*/
int32_t CoreEngine::on_touch_event(AInputEvent *event) {

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
int32_t CoreEngine::on_key_event(AInputEvent *event) {

    LOG_D(TAG, " ❯ on_key_event(app, event)");

    int32_t action, code;

    // AKEY_EVENT_ACTION_DOWN / AKEY_EVENT_ACTION_UP / AKEY_EVENT_ACTION_MULTIPLE
    action = AKeyEvent_getAction(event);

    // The key code (ie : physical id)
    code = AKeyEvent_getKeyCode(event);
    LOG_D(TAG, "   • Event : action=%d, code=%d", action, code);


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
void CoreEngine::poll_looper_events(struct android_app *app) {

    // variables holding the polled events information
    int32_t events;
    struct android_poll_source *source;
    int poll_timeout_ms = 0; // 0 = non blocking

    int ident = ALooper_pollAll(poll_timeout_ms, NULL, &events, (void **) &source);
    if (ident >= 0) {

        // process events
        if (source != NULL) {
            LOG_D(TAG, "   • Processing an event %d", source->id);
            // let the source process the events and forward them to our callbacks
            source->process(app, source);
        }
    }
}

/**
* The main loop
*/
void CoreEngine::main_loop(struct android_app *app) {


    TimeUnit loop_begin_time, initial_step_time, delta_time;
    int frames_skipped;
    struct timespec sleep_time = {0};

    // Main application loop
    while (1) {
        // TODO monitor delta time
        loop_begin_time = m_time_manager->get_nano_time();
        frames_skipped = 0;

        // 1 : handle external events (input, app lifecycle)
        poll_looper_events(app);

        // 2 : check if the app needs to be destroyed
        if (app->destroyRequested != 0) {
            LOG_D(TAG, "   • Destroy requested");
            // exit all loops
            return;
        }

        // 3 : TODO update game system
delta_time = m_time_manager->get_delta_time();

        // 4 : update rendering
        m_gl_engine->draw_frame();

        // 5 : Compute the sleep time
        initial_step_time = m_time_manager->get_nano_time() - loop_begin_time;
        sleep_time.tv_nsec = FRAME_PERIOD_NANO
        -initial_step_time;

        // 5a : sleep time is positive, we're ahead of schedule
        if (sleep_time.tv_nsec >= 0) {
            nanosleep(&sleep_time, (struct timespec *) NULL);
        }

        // TODO 5b : update game system to catch up
//        while (sleepTime < 0 && framesSkipped < MAX_FRAME_SKIPS) {
//            this.gamePanel.update();
//            // add frame period to check if in next frame
//            sleepTime += FRAME_PERIOD;
//            framesSkipped++;
//        }

    }
}
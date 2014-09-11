#ifndef CORE_ENGINE_H
#define CORE_ENGINE_H


#include "../opengl/GLEngine.h"
#include "TimeManager.h"

#include <stdint.h>
#include <android_native_app_glue.h>

#define MAX_FPS             60
#define FRAME_PERIOD_NANO   SECOND_IN_NANO / MAX_FPS;


class CoreEngine {

private :

    GLEngine *m_gl_engine;
    TimeManager *m_time_manager;

    int32_t on_touch_event(AInputEvent *event);

    int32_t on_key_event(AInputEvent *event);

    void poll_looper_events(struct android_app *app);


public:

    CoreEngine();

    ~CoreEngine();

    int32_t handle_input_event(AInputEvent *event);

    void handle_app_command(struct android_app *app, int32_t command);

    void main_loop(struct android_app *app);
};

#endif
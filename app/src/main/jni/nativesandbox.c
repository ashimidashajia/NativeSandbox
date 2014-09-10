
#include "nativesandbox.h"

#define TAG  "SANDBOX"

/**
 * Method to handle the activity lifecycle
 */
static void handle_cmd(struct android_app* app, int32_t cmd) {
	__android_log_print(3, TAG, " ❯ handle_cmd");

	switch (cmd) {
	case APP_CMD_SAVE_STATE:
		// the OS asked us to save the state of the app
		__android_log_print(3, TAG, "   • APP_CMD_SAVE_STATE");
		break;
	case APP_CMD_INIT_WINDOW:
		// get the window ready for showing
		__android_log_print(3, TAG, "   • APP_CMD_INIT_WINDOW");
		break;
	case APP_CMD_TERM_WINDOW:
		// clean up the window because it is being hidden/closed
		__android_log_print(3, TAG, "   • APP_CMD_TERM_WINDOW");
		break;
	case APP_CMD_LOST_FOCUS:
		// if the app lost focus, avoid unnecessary processing (like monitoring the accelerometer)
		__android_log_print(3, TAG, "   • APP_CMD_LOST_FOCUS");
		break;
	case APP_CMD_GAINED_FOCUS:
		// bring back a certain functionality, like monitoring the accelerometer
		__android_log_print(3, TAG, "   • APP_CMD_GAINED_FOCUS");
		break;
	}
}

static int32_t handle_input(struct android_app* app, AInputEvent* event) {

	__android_log_print(3, TAG, " ❯ handle_input");

	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
		size_t pointerCount = AMotionEvent_getPointerCount(event);
		size_t i;
		for (i = 0; i < pointerCount; ++i) {
			__android_log_print(3, TAG,
					"   • Motion event %zu: (%.2f, %.2f)", i,
					AMotionEvent_getX(event, i), AMotionEvent_getY(event, i));
		}
		return 1;
	} else if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_KEY) {
		__android_log_print(3, TAG, "   • Key event: %d",
				AKeyEvent_getKeyCode(event));

        // Return 1 to intercept the key (eg : the back button)
		return 0;
	}

	return 0;
}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* app) {

	// Make sure glue isn't stripped.
	app_dummy();

	//
	__android_log_print(3, TAG, " ❯ android_main");
	int32_t lResult;
	int32_t lEvents;
	struct android_poll_source* lSource;

	app->onAppCmd = handle_cmd;
	app->onInputEvent = handle_input;

	// main loop, residing in a seperate thread
	while (1) {

		while ((lResult = ALooper_pollAll(-1, NULL, &lEvents, (void**) &lSource))
				>= 0) {

			// process events
			if (lSource != NULL) {
				__android_log_print(3, TAG, "   • Processing an event %d",
						lSource->id);

				lSource->process(app, lSource);
			}

			if (app->destroyRequested != 0) {
				__android_log_print(3, TAG, "   • Destroy requested");
				return;
			}
		}
	}
}
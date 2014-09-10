#ifndef NATIVE_SANDBOX_H_
#define NATIVE_SANDBOX_H_

#include <jni.h>

#include <android_native_app_glue.h>
#include <android/log.h>

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* state);

#endif
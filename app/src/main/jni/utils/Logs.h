/*
 * Logs.h
 *
 *     Author : Xavier Gouchet (2014)
 */

#ifndef LOGS_H_
#define LOGS_H_

#include <android/log.h>

// define set in the compilation CFlags
#ifdef LOGCAT

#define LOG_V(tag, ...) __android_log_print(ANDROID_LOG_VERBOSE,  tag, __VA_ARGS__);
#define LOG_D(tag, ...) __android_log_print(ANDROID_LOG_DEBUG,    tag, __VA_ARGS__);
#define LOG_I(tag, ...) __android_log_print(ANDROID_LOG_INFO,     tag, __VA_ARGS__);
#define LOG_W(tag, ...) __android_log_print(ANDROID_LOG_WARN,     tag, __VA_ARGS__);
#define LOG_E(tag, ...) __android_log_print(ANDROID_LOG_ERROR,    tag, __VA_ARGS__);

#else

// Empty definition
#define LOG_V(...)
#define LOG_D(...)
#define LOG_I(...)
#define LOG_W(...)
#define LOG_E(...)

#endif

#endif
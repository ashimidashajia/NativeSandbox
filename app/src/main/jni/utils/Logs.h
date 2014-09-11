/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#ifndef LOGS_H_
#define LOGS_H_

#include <android/log.h>

/**
 * Define easy proxy Macros to log information in Android's LogCat. 
 * The preprocessor is usefull to remove completely every string sent to the log output. 
 * 
 * The usage is pretty straight forward, for instance 
 * 
 * LOG_D("My tag", "Logging a couple of values : %d, %f", 42, 3.1415f)
 */

#ifdef LOGCAT 

#define LOG_V(tag, ...) __android_log_print(ANDROID_LOG_VERBOSE,  tag, __VA_ARGS__);
#define LOG_D(tag, ...) __android_log_print(ANDROID_LOG_DEBUG,    tag, __VA_ARGS__);
#define LOG_I(tag, ...) __android_log_print(ANDROID_LOG_INFO,     tag, __VA_ARGS__);
#define LOG_W(tag, ...) __android_log_print(ANDROID_LOG_WARN,     tag, __VA_ARGS__);
#define LOG_E(tag, ...) __android_log_print(ANDROID_LOG_ERROR,    tag, __VA_ARGS__);

#else

#define LOG_V(...)
#define LOG_D(...)
#define LOG_I(...)
#define LOG_W(...)
#define LOG_E(...)

#endif

#endif

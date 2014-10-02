/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 

#include "TimeManager.h"
#include <time.h>

/** Constructor */
TimeManager::TimeManager() {

}

/** Destructor */
TimeManager::~TimeManager() {

}

/**
 * Get the current time in nanoseconds 
 */
TimeUnit TimeManager::getTimeNano() {

    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);

    return (now.tv_sec * SECOND_IN_NANO) + now.tv_nsec;
}

/**
 * Get the elapsed time since the last game update
 */
TimeUnit TimeManager::getDeltaTimeNano() {

    TimeUnit now = getTimeNano();
    TimeUnit delta = now - mLastUpdateTime;

    mLastUpdateTime = now;

    return delta;
}


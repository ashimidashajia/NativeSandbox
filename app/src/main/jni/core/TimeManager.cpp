#include "TimeManager.h"
#include <time.h>


TimeManager::TimeManager() {

}

TimeManager::~TimeManager() {

}


TimeUnit TimeManager::get_nano_time() {
    struct timespec now;
    int err = clock_gettime(CLOCK_MONOTONIC, &now);
    return (now.tv_sec * SECOND_IN_NANO) + now.tv_nsec;
}

/**
* Get the elapsed time since the last rendered frame
*/
TimeUnit TimeManager::get_delta_time() {
    // TODO store and compute delta time
    return 0;
}

/**
* Get the remaining time before starting a new loop
*/
TimeUnit TimeManager::get_remaining_time() {
}
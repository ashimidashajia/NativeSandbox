/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 
#ifndef TIME_UTILS_H
#define TIME_UTILS_H

/** A unified unit to talk about time */
typedef long long TimeUnit;

#define SECOND_IN_NANO 1000000000LL

/**
 * A simple utility class used to compute times 
 */
class TimeManager {

private :
    
    /** the last time get_delta_time_nano() was called */
    TimeUnit m_last_update_time;


public:

    /** Constructor */
    TimeManager();
    
    /** Destructor */
    ~TimeManager();

    /**
     * Get the current time in nanoseconds 
     */
    TimeUnit get_time_nano();

    /**
     * Get the elapsed time since the last game update
     */
    TimeUnit get_delta_time_nano();

};

#endif

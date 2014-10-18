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
#define NANO_TO_SEC (1.0f / 1000000000.0f)

/**
 * A simple utility class used to compute times 
 */
class TimeManager {

private :

    /** the last time getDeltaTimeNano() was called */
    TimeUnit mLastUpdateTime;


public:

    /** Constructor */
    TimeManager();

    /** Destructor */
    ~TimeManager();

    /**
     * Get the current time in nanoseconds 
     */
    TimeUnit getTimeNano();

    /**
     * Get the elapsed time since the last game update
     */
    TimeUnit getDeltaTimeNano();

};

#endif

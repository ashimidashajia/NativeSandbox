#ifndef TIME_UTILS_H
#define TIME_UTILS_H

typedef long long TimeUnit;

#define SECOND_IN_NANO 1000000000LL

class TimeManager {

private :

    static TimeManager s_instance;

    TimeUnit m_last_frame;


public:

    TimeManager();

    ~TimeManager();

    TimeUnit get_nano_time();

    TimeUnit get_delta_time();

    TimeUnit get_remaining_time();


};

#endif
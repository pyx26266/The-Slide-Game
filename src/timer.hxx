 
//Contains the timer related functions
#ifndef TIMER_HXX
#define TIMER_HXX
#include <iostream>
#include <ctime>
#include <mutex>
class Timer {
  public:
    static time_t avail_time;
    Timer();
    void StartTimer();
    void StopTimer();
    void ResetTimer();
    bool isRunning();
    time_t ElapTime();
    bool isOver();
    void ShowWatch();

  private:
        std::mutex mutex;
    bool running_;
    time_t beg_, end_;

};



#endif

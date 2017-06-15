#include "timer.hxx"

Timer::Timer() {
    running_ = false;
    beg_ = end_ = 0x00;
}

void Timer::ShowWatch() {
    std::cout << ElapTime();
}

void Timer::StartTimer() {

    if (!running_) {
        if (beg_ == end_)
            beg_ = std::time(0);
        else
            beg_ += time(0) - end_;
        running_ = true;
    }
}

void Timer::StopTimer() {
    //std::lock_guard<std::mutex> lock_guard(mutex);
    if (running_) {
        end_ = time(0);
        running_ = false;
    }
}

void Timer::ResetTimer() {
    //std::lock_guard<std::mutex> lock_guard(mutex);
    if (running_)
        StopTimer();
    beg_= 0x00;
    end_= 0x00;
}

bool Timer::isRunning() {
    //std::lock_guard<std::mutex> lock_guard(mutex);
    return running_;
}

time_t Timer::ElapTime() {
    //std::lock_guard<std::mutex> lock_guard(mutex);
    if (running_)
        return (time(0) - beg_);
    else
        return (end_ - beg_);
}

bool Timer::isOver() {
    //std::lock_guard<std::mutex> lock_guard(mutex);
    if (ElapTime() >= avail_time)
        return true;
    else
        return false;
}
time_t Timer::avail_time = 60;

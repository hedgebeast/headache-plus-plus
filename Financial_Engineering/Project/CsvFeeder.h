#ifndef QF633_CODE_CSVFEEDER_H
#define QF633_CODE_CSVFEEDER_H

#include <string>
#include <functional>   //general-purpose wrapper for callable objects
#include <chrono>   //provides facilities for working with time and durations
#include <fstream>

#include "Msg.h"

class CsvFeeder {
public:
    using FeedListener = std::function<void(const Msg& msg)>;       //listen to current market status
    using TimerListener = std::function<void(uint64_t ms_now)>;     //output something
    
    CsvFeeder(const std::string ticker_filename,    //the filename of the input csv file
              FeedListener feed_listener,           //the function to be called inside Step() after an update message is loaded
              std::chrono::minutes interval,        //the time interval to call timer_listener
              TimerListener timer_listener);        //the function to be called at a given frequency
              
    ~CsvFeeder();
    bool Step();

private:
    std::ifstream ticker_file_;
    FeedListener feed_listener_;
    const std::chrono::milliseconds interval_;
    TimerListener timer_listener_;

//    uint64_t* now_ms_{nullptr};
    uint64_t now_ms_{};
    Msg msg_;
    
    // your member variables and member functions below, if any
    Msg diffMsg_;
    
};

#endif //QF633_CODE_CSVFEEDER_H

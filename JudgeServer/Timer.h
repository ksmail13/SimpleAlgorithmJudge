//
// Created by micky on 15. 5. 24.
//

#ifndef JUDGESERVER_TIMER_H
#define JUDGESERVER_TIMER_H


#include "Thread.h"
#include "SemaphoreObejct.h"

namespace Timer {
    class TimerTask {
    public:
        virtual void task() = 0;
    };

    class Timer : public Thread::Thread
    {
    private:
        int _time;
        bool _allow;
        TimerTask *_t;

    public:
        Timer(int time, TimerTask &t) : _time(time), _t(&t), _allow(true) { }

        virtual void run() {
            time_t start;
            start = time(NULL);

            while(_allow && difftime(time(NULL), start)<_time) {}
            if(_allow)
                _t->task();
        }

        void stop() {
            _allow = false;
        }
    };
}


#endif //JUDGESERVER_TIMER_H

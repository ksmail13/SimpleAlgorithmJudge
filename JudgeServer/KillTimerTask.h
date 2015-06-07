//
// Created by mikcy on 15. 6. 7.
//

#ifndef JUDGESERVER_KILLTIMERTASK_H
#define JUDGESERVER_KILLTIMERTASK_H
#include "Timer.h"

namespace Timer {

    class KillTimerTask : public TimerTask {
    private :
        pid_t _target;
    public :
        KillTimerTask(pid_t pid) : _target(pid) { }

        virtual void task();
    };
};

#endif //JUDGESERVER_KILLTIMERTASK_H

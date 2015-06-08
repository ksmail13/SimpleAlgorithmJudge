//
// Created by mikcy on 15. 6. 7.
//

#include "KillTimerTask.h"


void Timer::KillTimerTask::task() {
    kill(_target, SIGKILL);
}
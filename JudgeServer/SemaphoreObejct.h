//
// Created by micky on 15. 5. 22.
//

#ifndef JUDGESERVER_SEMAPHORE_H
#define JUDGESERVER_SEMAPHORE_H

#include <pthread.h>
#include <semaphore.h>
#include <iostream>

namespace Thread{
    class SemaphoreObejct {
    private:

        sem_t _sema;

    public:
        SemaphoreObejct(int pshared, int value) { sem_init(&_sema, pshared, value); }
        ~SemaphoreObejct() {close();}

        void close() { sem_destroy(&_sema); }
        void post() { sem_post(&_sema); }
        void wait() { sem_wait(&_sema); }
    };
};


#endif //JUDGESERVER_MUTEX_H

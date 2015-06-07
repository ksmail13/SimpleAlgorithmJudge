//
// Created by micky on 15. 5. 22.
//

#include "Thread.h"
#include "logger.h"

std::map<pthread_t, Thread::Thread *> Thread::Thread::_threads;

Thread::Thread::Thread()
{ }


void *Thread::thread_main(void *args)
{
    Thread *thread = (Thread *)args;
    thread->run();
    InformMessage("thread finish");
    thread->_running = false;
    return NULL;
}


void Thread::Thread::start()
{
    int res = ::pthread_create(&_id, NULL, thread_main, this);

    if(res < 0) {
        throw ThreadException(const_cast<char *>("Thread create"));
    }

    _threads[_id] = this;
    _running = true;
}

void Thread::Thread::join(void **ret_data)
{
    if(_running) {
        _running = false;
        InformMessage("thread join");
        ::pthread_join(_id, ret_data);
    }
}

void Thread::Thread::detach() {
    if(_running) {
        InformMessage("thread detach");
        ::pthread_detach(_id);
        _running = false;
    }
}

void Thread::Thread::run() {
    /// nothing using for override
}

void Thread::Thread::stop() {
    InformMessage("thread kill");
    pthread_kill(_id, SIGKILL);
    _running = false;
}
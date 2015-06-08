#ifndef READTHREAD_H
#define READTHREAD_H

#include "Thread.h"
#include "socketmanager.h"
#include "json.h"

class ReadThread : public Thread::Thread
{
public:
    ReadThread(SocketManager *socketManager);
    ~ReadThread();
    virtual void run();

private:
    SocketManager *socketManager;
};

#endif // READTHREAD_H

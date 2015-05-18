#ifndef POLLMANAGER_H
#define POLLMANAGER_H

#include <sys/epoll.h>
#include <vector>
#include "InetSocket.h"

typedef int EpollDescriptor;
class PollManager
{
    public:
        static const int MAX_POLL = 10000;
        void init(PollHandler &handler, bool isEdge=false);
        bool addEvent(int fd, int events);
        bool removeEvent(int fd);
        void wait(int timeout);

    private:
        EpollDescriptor _ed;
        PollHandler *_handler;
        void onEvent(const struct epoll_event &event);
    protected:
    friend class InetSocket;
};

class PollHandler
{
    virtual void onRead(int fd) = 0;
    virtual void onWrite(int fd) = 0;
    virtual void onError(int fd) = 0;
};


#endif

#ifndef POLLMANAGER_H
#define POLLMANAGER_H

#include <sys/epoll.h>
#include <vector>
#include "InetSocket.h"

class PollHandler
{
public :
    virtual void onRead(int fd) = 0;
    virtual void onWrite(int fd) = 0;
    virtual void onError(int fd) = 0;
};

typedef int EpollDescriptor;

class PollManager
{
    public:
        static const int MAX_POLL = 10000;
        void init(PollHandler &handler, bool isEdge=false);
        bool addEvent(int fd, int events);
        bool removeEvent(int fd);
        void polling(int timeout);

    private:
        EpollDescriptor _ed;
        PollHandler *_handler;
        void onEvent(const struct epoll_event &event);
    protected:
    friend class InetSocket;
};



#endif

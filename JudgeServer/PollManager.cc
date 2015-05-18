#include "PollManager.h"
#include "logger.h"
void PollManager::init(PollHandler &handler, bool isEdge = false)
{
    if(isEdge) throw "Not ready";

    this->_handler = &handler;
    _ed = epoll_create(PollManager::MAX_POLL);

    if (_ed == -1) {
        ErrorMessage("epoll_create() error");
        return ;
    }
}


bool PollManager::addEvent(int fd, int events = EPOLLIN)
{
    struct epoll_event ev;

    ev.events = events;
    ev.data.fd = fd;
    
    return epoll_ctl(_ed, EPOLL_CTL_ADD, fd, &ev) != -1;
}

bool PollManager::removeEvent(int fd)
{
    return epoll_ctl(_ed, EPOLL_CTL_DEL, fd, NULL) != -1;
}


void PollManager::onEvent(const struct epoll_event &event)
{
    if(event.events & EPOLLIN) {
        _handler->onRead(event.data.fd);
    }
    if(event.events & EPOLLOUT) {
        _handler->onWrite(event.data.fd);
    }
    if(event.events & EPOLLERR) {
        _handler->onError(event.data.fd);
    }
}

void PollManager::polling(int timeout)
{
    int nevs, i;
    struct epoll_event evs[MAX_POLL] = {0,};
    while(true) {
        nevs = epoll_wait(_ed, evs, MAX_POLL, timeout);

        if(nevs == -1) {
            ErrorMessage("epoll_wait() error");
            break;
        }

        for(i=0;i<nevs;i++) {
            onEvent(evs[i]);
        }
    }
}

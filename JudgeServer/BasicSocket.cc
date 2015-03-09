#include "BasicSocket.h"
#include "logger.h"

std::string Network::BasicSocket::getAddress() 
{
    std::string s;
    s = inet_ntoa(_addr_info->sin_addr);
    return s;
}

bool Network::BasicSocket::connect(struct sockaddr *addr, socklen_t adr_sz)
{
    return ::connect(_fd, addr, adr_sz) != -1;
}

bool Network::BasicSocket::bind(struct sockaddr *addr, socklen_t adr_sz)
{
    return ::bind(_fd, addr, adr_sz) != -1;
}

bool Network::BasicSocket::listen(int backlog)
{
    return ::listen(_fd, backlog);
}

SignedSize Network::BasicSocket::recv(void *buf, size_t buf_len, int msgtype)
{
    return ::recv(_fd, buf, buf_len, msgtype);
}

SignedSize Network::BasicSocket::send(void *buf, size_t buf_len, int msgtype)
{
    return ::send(_fd, buf, buf_len, msgtype);
}

void Network::BasicSocket::setNonblockSocket(bool accept)
{
    int flag = fcntl(_fd, F_GETFL, 0);
    if(accept) {
        flag = flag|O_NONBLOCK;
    }
    else {
        flag = flag^O_NONBLOCK;    
    }
    fcntl(_fd, F_SETFL, flag);
}

bool Network::BasicSocket::isNonblockSocket()
{
    return _nonblock;   
}


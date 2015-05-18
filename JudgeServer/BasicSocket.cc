#include "BasicSocket.h"
#include "logger.h"

std::string Network::BasicSocket::getIpAddress() 
{
    std::string s;
    s = inet_ntoa(_addr_info.sin_addr);
    return s;
}

void Network::BasicSocket::setAddress(struct sockaddr_in &addr)
{
    _addr_info = addr;
}

bool Network::BasicSocket::connect(struct sockaddr *addr, socklen_t adr_sz)
{
    setAddress(*((struct sockaddr_in *)addr));
    return ::connect(_fd, addr, adr_sz) != -1;
}

bool Network::BasicSocket::bind(struct sockaddr *addr, socklen_t adr_sz)
{
    setAddress(*((struct sockaddr_in *)addr));
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

SignedSize Network::BasicSocket::write(void *buf, size_t buf_len)
{
    return ::write(_fd, buf, buf_len);
}

SignedSize Network::BasicSocket::read(void *buf, size_t buf_len)
{
    return ::read(_fd, buf, buf_len);
}

Network::BasicSocket Network::BasicSocket::accept() 
{
     struct sockaddr_in clnt_adr;
     socklen_t adr_sz = sizeof(clnt_adr);
     
     int clnt_sock = ::accept(_fd, (struct sockaddr*) &clnt_adr, &adr_sz);
     BasicSocket new_clnt	= clnt_sock;
     new_clnt.setAddress(clnt_adr);
     
     return new_clnt;
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


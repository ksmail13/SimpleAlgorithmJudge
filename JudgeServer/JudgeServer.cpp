//
// Created by micky on 15. 5. 20.
//

#include <iostream>
#include "logger.h"
#include "JudgeServer.h"


JudgeServer *JudgeServer::instance;

void JudgeServer::createNewConnection()
{
    InetSocket *clnt = nullptr;
    clnt = _serv.accept();
    if(_conn.size() < (size_t)clnt->getFileDescriptor()) {
        _conn.resize(clnt->getFileDescriptor()+1);
    }
    _conn[clnt->getFileDescriptor()] = clnt;
    InformMessage("new connection from %s", clnt->getIpAddress().c_str());
}

void JudgeServer::removeConnection(InetSocket *sock)
{
    InformMessage("disconnect with %s", sock->getIpAddress().c_str());
    sock->close();
    _pm.removeEvent(sock->getFileDescriptor());
    delete sock;
}

void JudgeServer::receiveData(int fd)
{
    InetSocket &sock = *_conn[fd];
    char buf[1024] = {};
    ssize_t strlen = sock.read(buf, 1024);
    if(strlen < 0) {
        removeConnection(&sock);
        return ;
    }
    buf[strlen] = 0;

    printf("recv %s from %d\n", buf, fd);

}

void JudgeServer::onRead(int fd)
{

    if(fd == _serv.getFileDescriptor()) {
        createNewConnection();
    }
    else {
        receiveData(fd);
    }
}

void JudgeServer::run()
{

    _pm.addEvent(_serv.getFileDescriptor(), EPOLLIN);
    _pm.polling(-1);
}
//
// Created by micky on 15. 5. 20.
//

#include <iostream>
#include "JudgeServer.h"


JudgeServer *JudgeServer::instance = NULL;

void JudgeServer::createNewConnection()
{
    InetSocket *clnt = nullptr;
    clnt = _serv.accept();
    if(_conn.size() < (size_t)clnt->getFileDescriptor()) {
        _conn.resize(clnt->getFileDescriptor()+1);
    }
    _conn[clnt->getFileDescriptor()] = clnt;
    _pm.addEvent(clnt->getFileDescriptor(), EPOLLIN);
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
    InformMessage("receive data from %s", sock.getIpAddress().c_str());
    struct packet p;

    InformMessage("before %s \n", p.buf.c_str());
    if(!sock.recvPacket(p))
        removeConnection(&sock);

    InformMessage("recv %s from %d\n", p.buf.c_str(), fd);

    #if 0
    Json::Reader reader;
    Json::Value value;
    reader.parse(p.buf, value);
    // TODO : switch to submit or other job




    // TODO : message to question
    question q;
    q.examinee = &sock;

    _jud_man.submit(q);

    #endif
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
    InformMessage("server start");
    _jud_man.start();
    _pm.addEvent(_serv.getFileDescriptor(), EPOLLIN);
    _pm.polling(-1);
}
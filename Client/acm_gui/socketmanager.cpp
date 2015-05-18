#include "socketmanager.h"
#include <cstring>
#include <stdio.h>

SocketManager::SocketManager()
{

    _socket = new InetSocket(SOCK_STREAM, 0);


}

bool SocketManager::setIP(QString ip)
{

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(ip.toStdString().c_str());
    serv_adr.sin_port = htons(port);

    bool ret = _socket->connect((struct sockaddr*)&serv_adr, (socklen_t)sizeof(serv_adr));
    return ret;
}

void SocketManager::send(QString str)
{
    size_t len;
    len = str.size();
    char buf[100] = {0,};

    sprintf(buf, "%s", str.toStdString().c_str());

    _socket->send(buf, len, 0);
}

void SocketManager::close()
{
    _socket->close();
}

SocketManager::~SocketManager()
{
    //delete _socket;
}


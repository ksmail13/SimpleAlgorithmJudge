#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include "InetSocket.h"
#include <QString>

using namespace Network;

class SocketManager
{
private:
    InetSocket *_socket;


public:
    SocketManager();
    ~SocketManager();
    struct sockaddr_in serv_adr;
    const u_int16_t port = 54321;

    bool setIP(QString ip);
    void send(QString str);
    void close();

};

#endif // SOCKETMANAGER_H

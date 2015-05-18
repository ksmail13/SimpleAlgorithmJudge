#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include "InetSocket.h"

class SocketManager
{
private:
    InetSocket *_socket;


public:
    SocketManager();
    ~SocketManager();
    struct sockaddr_in serv_adr;
    const u_int16_t port = 54321;

};

#endif // SOCKETMANAGER_H

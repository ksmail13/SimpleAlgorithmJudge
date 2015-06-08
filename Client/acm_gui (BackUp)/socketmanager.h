#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include "InetSocket.h"
#include <QString>
#include "json.h"
#include <cstring>

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
    void send(Json::Value &root);
    void close();

};

#endif // SOCKETMANAGER_H

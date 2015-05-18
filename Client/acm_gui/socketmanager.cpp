#include "socketmanager.h"

SocketManager::SocketManager()
{
    _socket = new InetSocket(SOCK_STREAM, 0);

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(port);


    _socket->connect((struct sockaddr*)&serv_adr, sizeof(serv_adr));
}

SocketManager::~SocketManager()
{
    delete _socket;
}


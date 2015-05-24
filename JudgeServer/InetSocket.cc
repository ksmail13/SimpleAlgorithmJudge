#include "InetSocket.h"

using namespace Network;

BasicSocket *InetSocket::accept()
{
    InetSocket *new_clnt = nullptr;
    struct sockaddr_in clnt_adr;
    socklen_t adr_sz = sizeof(clnt_adr);

    int clnt_sock = ::accept(getFileDescriptor(), (struct sockaddr*) &clnt_adr, &adr_sz);
    new_clnt = new InetSocket(clnt_sock);
    new_clnt->setAddress(clnt_adr);

    return new_clnt;
}
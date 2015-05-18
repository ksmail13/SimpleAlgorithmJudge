#include "ServerSocket.h"

using namespace Network;

void ServerSocket::init(int port)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    this->socket.bind((struct sockaddr*)&addr, sizeof(addr));
}

InetSocket ServerSocket::accept()
{
    InetSocket clnt;
    struct sockaddr_in clnt_adr;
    socklen_t adr_sz;
    clnt = ::accept(socket._fd, (struct sockaddr*)&clnt_adr, &adr_sz); 
    clnt.setAddress(clnt_adr);
    
    return clnt;
}

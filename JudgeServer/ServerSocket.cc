#include "ServerSocket.h"

using namespace Network;

void ServerSocket::init(int port)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    this->_socket.bind((struct sockaddr*)&addr, sizeof(addr));
    this->_socket.listen(5);
}

InetSocket ServerSocket::accept()
{
    InetSocket clnt;
    struct sockaddr_in clnt_adr;
    socklen_t adr_sz;
    clnt = _socket.accept((struct sockaddr*)&clnt_adr, &adr_sz); 
    clnt.setAddress(clnt_adr);
    
    return clnt;
}

#include "ServerSocket.h"
#include <cstring>
using namespace Network;

void ServerSocket::init(int port)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int option = 1;
    setsockopt(_socket.getFileDescriptor(), SOL_SOCKET, SO_REUSEADDR, (void*)&option, sizeof(int));

    this->_socket.bind((struct sockaddr*)&addr, sizeof(addr));
    this->_socket.listen(5);
}

InetSocket *ServerSocket::accept()
{
    return dynamic_cast<InetSocket *>(_socket.accept());
}

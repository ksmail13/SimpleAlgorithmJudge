#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "BasicSocket.h"

namespace Network
{
    class ServerSocket
    {
        private:
            InetSocket _socket;
            void init(int port);
        public:
            InetSocket accept();
            ServerSocket(int port): _socket(SOCK_STREAM, 0){
               this->init(port);
            }

            FileDescriptor getFileDescriptor() const {
                return _socket.getFileDescriptor();
            }
        protected:

        friend class InetSocket;
    };
};

#endif

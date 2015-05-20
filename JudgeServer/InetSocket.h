#ifndef INETSOCKET_H
#define INETSOCKET_H
#include "BasicSocket.h"

namespace Network
{

    class InetSocket : public BasicSocket
    {
        public:
            virtual ~InetSocket() {}

            InetSocket() {}
            InetSocket(FileDescriptor fd) : BasicSocket(fd) {}
            InetSocket(int socktype, int proto_type):
                BasicSocket(PF_INET, socktype, proto_type){}

            
            virtual BasicSocket operator= (const FileDescriptor &fd) {
                InetSocket new_sock(fd);
                
                return new_sock;
            }
                
    };
};
#endif

#ifndef INETSOCKET_H
#define INETSOCKET_H
#include "BasicSocket.h"

namespace Network
{

    class InetSocket : public BasicSocket
    {
        public:
            virtual ~InetSocket() {}

        
            InetSocket(int socktype, int proto_type):
                BasicSocket(PF_INET, socktype, proto_type){}
                
    };

};
#endif

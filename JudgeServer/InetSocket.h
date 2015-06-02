#ifndef INETSOCKET_H
#define INETSOCKET_H
#include "BasicSocket.h"
#include <cstring>
namespace Network
{

    struct packet
    {
        int len;
        std::string buf;

        packet() : len(4), buf(""){}
    };

    class InetSocket : public BasicSocket
    {
    public:
        const static unsigned int BUF_SIZE = 1024;
        virtual ~InetSocket() {}

        InetSocket() {}
        InetSocket(FileDescriptor fd) : BasicSocket(fd) {}
        InetSocket(int socktype, int proto_type):
            BasicSocket(PF_INET, socktype, proto_type){}

        virtual BasicSocket *accept();

        virtual BasicSocket operator= (const FileDescriptor &fd) {
            InetSocket new_sock(fd);

            return new_sock;
        }

        bool sendPacket(packet p);

        bool recvPacket(packet &p);
                
    };
};
#endif

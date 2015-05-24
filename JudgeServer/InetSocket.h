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


        virtual BasicSocket operator= (const FileDescriptor &fd) {
            InetSocket new_sock(fd);

            return new_sock;
        }

        bool sendPacket(packet p) {
            char *temp = new char[p.len+sizeof(p.len)];
            int *size = (int*)temp;
            *size = p.len;
            strcpy(temp+4, p.buf.c_str());
            write(temp, p.len+sizeof(p.len));

            delete[] temp;
        }

        bool recvPacket(packet &p) {
            char buf[BUF_SIZE];
            std::string &packet = p.buf;
            int &tot_size=p.len;
            int curr_recv = 0;

            if( read(buf, BUF_SIZE) < 0) return false;

            tot_size = *(int*)buf;
            packet.append(buf+sizeof(tot_size));

            while(curr_recv < tot_size) {
                if( read(buf, BUF_SIZE) <0) return false;
                packet.append(buf);
            }

            return true;
        }
                
    };
};
#endif

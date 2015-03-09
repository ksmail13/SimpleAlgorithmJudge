#ifndef BASICSOCKET_H
#define BASICSOCKET_H

#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>


// type for common fd(posix) or handle(winsock) type
typedef int FileDescriptor;

typedef ssize_t SignedSize;

namespace Network
{
    class BasicSocket {
        private:
            FileDescriptor _fd;
            char *_buf;
            bool _nonblock;
        public:
            BasicSocket(int socktype, int proto_type):_fd(socket(PF_INET, socktype, proto_type)), _nonblock(false){}
            ~BasicSocket(){}
            void setAddress(struct sockaddr_in &);
            struct sockaddr_in &getAddress();
            std::string getIpAddress();
            bool connect(struct sockaddr *addr, socklen_t adr_sz);
            bool bind(struct sockaddr *addr, socklen_t adr_sz);
            bool listen(int backlog);

            BasicSocket accept();
            
            SignedSize recv(void *buf, size_t buf_len, int msgtype);
            SignedSize send(void *buf, size_t buf_len, int msgtype);

            void setNonblockSocket(bool);
            bool isNonblockSocket();

            // TODO : Accept & buffer mode
        protected:
            struct sockaddr_in _addr_info;

    };
}

#endif

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
            BasicSocket(int proto_fam, int socktype, int proto_type):
                _fd(socket(proto_fam, socktype, proto_type)), 
                _nonblock(false){}

            BasicSocket(int fd):_fd(fd){};
            
            virtual ~BasicSocket() = 0;
            
            void setAddress(struct sockaddr_in &);
            struct sockaddr_in &getAddress() const;
            std::string getIpAddress();
            bool connect(struct sockaddr *addr, socklen_t adr_sz);
            bool bind(struct sockaddr *addr, socklen_t adr_sz);
            bool listen(int backlog);

            BasicSocket accept();
            
            SignedSize recv(void *buf, size_t buf_len, int msgtype);
            SignedSize send(void *buf, size_t buf_len, int msgtype);
            
            SignedSize write(void *buf, size_t buf_len);
            SignedSize read(void *buf, size_t buf_len);

            void setNonblockSocket(bool);
            bool isNonblockSocket();

            // TODO : buffer mode
            
            BasicSocket operator= (const FileDescriptor &fd) {
                BasicSocket new_sock(fd);
                
                return new_sock;
            }

            

        protected:
            struct sockaddr_in _addr_info;

    };
}

#endif

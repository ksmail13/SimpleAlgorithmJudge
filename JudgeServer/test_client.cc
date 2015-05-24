#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "InetSocket.h"

#define BUF_SIZE 1024

int main()
{
    int sock;
    char buf[BUF_SIZE] = {};
    int buf_len = 0;
    struct sockaddr_in adr;
    int i;
    sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&adr, 0, sizeof(adr));

    adr.sin_family = AF_INET;
    adr.sin_addr.s_addr = inet_addr("127.0.0.1");
    adr.sin_port = htons(54321);

    if(connect(sock, (struct sockaddr*) &adr, sizeof(adr)) == -1) {
    perror("connect error");
    exit(1);
    }
    Network::InetSocket i_sock(sock);
    

    for(i=0;i<5;i++) {
        Network::packet p;
        scanf("%s", buf);
        p.len = strlen(buf);
        p.buf.append(buf);
        i_sock.sendPacket(p);
        printf("send : %s\n", buf);
    }

    i_sock.close(); 

    return 0;
}

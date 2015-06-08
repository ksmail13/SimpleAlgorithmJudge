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
    char buf[BUF_SIZE] = "{\"type\":\"login\"}";
    int buf_len = 0;
    struct sockaddr_in adr;
    int i;
    FILE *fp = fopen("test.json", "r");
    sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&adr, 0, sizeof(adr));

    adr.sin_family = AF_INET;
    adr.sin_addr.s_addr = inet_addr("192.168.0.14");
    adr.sin_port = htons(54321);
#if 0
    if(connect(sock, (struct sockaddr*) &adr, sizeof(adr)) == -1) {
    perror("connect error");
    exit(1);
    }
#endif
    Network::InetSocket i_sock(sock);
    if(i_sock.connect((struct sockaddr*)&adr, sizeof(adr)) == false) {
        perror("connect error");
        exit(1);
    }

    for(i=0;!feof(fp);i++) {
        Network::packet p;
        fgets(buf, 1024, fp);
        p.len = strlen(buf);
        p.buf.append(buf);
        if(!i_sock.sendPacket(p)) {
            perror("send error");
            exit(1);
        }
        printf("send : %s len : %d\n", buf, p.len);
        i_sock.recvPacket(p);
        printf("recved %s\n", p.buf.c_str());
    }
    fclose(fp);
    i_sock.close();

    return 0;
}

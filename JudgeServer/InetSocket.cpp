#include "InetSocket.h"
#include "logger.h"
using namespace Network;

BasicSocket *InetSocket::accept()
{
    InetSocket *new_clnt = nullptr;
    struct sockaddr_in clnt_adr;
    socklen_t adr_sz = sizeof(clnt_adr);

    int clnt_sock = ::accept(getFileDescriptor(), (struct sockaddr*) &clnt_adr, &adr_sz);
    new_clnt = new InetSocket(clnt_sock);
    new_clnt->setAddress(clnt_adr);

    return new_clnt;
}

bool InetSocket::sendPacket(packet p)
{
    char *temp = new char[p.len+sizeof(p.len)];
    int *size = (int*)temp;
    *size = p.len;
    strcpy(temp+4, p.buf.c_str());
    write(temp, p.len+sizeof(p.len));

    delete[] temp;
    return true;
}

bool InetSocket::recvPacket(packet &p) {
    char buf[BUF_SIZE] = {};
    std::string &packet = p.buf;
    int &tot_size=p.len;
    int curr_recv = 0, recv_len=0;

    if((curr_recv = read(buf, BUF_SIZE)) <= 0) return false;

    tot_size = *(int*)buf;
    InformMessage("size %d", tot_size);
    packet.append(buf+sizeof(tot_size));
    curr_recv -= sizeof(tot_size);
    while(curr_recv < tot_size) {
        recv_len = read(buf, BUF_SIZE);
        if(recv_len < 0) return false;
        else if(recv_len == 0) break;

        curr_recv += recv_len;
        packet.append(buf);
    }

    return true;
}
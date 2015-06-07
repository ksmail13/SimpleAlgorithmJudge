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
    SignedSize tot_recv = 0, recv_len=0, remain_len=0;

    if((tot_recv = read(buf, sizeof(tot_size))) <= 0) return false;

    tot_size = *(int*)buf;
    //InformMessage("size %d\n%s", tot_size, buf);
    //packet.append(buf+sizeof(tot_size));
    //tot_recv -= sizeof(tot_size);
    remain_len = tot_size;
    while(remain_len) {
        //InformMessage("remain %lds data", remain_len);
        recv_len = read(buf, remain_len>BUF_SIZE ? BUF_SIZE : remain_len);
        //InformMessage("recv %lds data", recv_len);
        if(recv_len < 0) return false;
        else if(recv_len == 0) break;

        tot_recv += recv_len;
        remain_len -= recv_len;
        //InformMessage("recv buf : %s", buf);
        packet.append(buf);
    }

    return true;
}

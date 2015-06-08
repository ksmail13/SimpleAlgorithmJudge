#ifndef CLIENT_H
#define CLIENT_H


class client
{
public:
    client();
    ~client();

    error_handling(QString msg);

private:
    int sock;
    int BUF_SIZE  = 1024;
    int str_len;
    char buf[BUF_SIZE];

    FILE *readfp;
    FILE *writefp;

    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t adr_sz;


};

#endif // CLIENT_H

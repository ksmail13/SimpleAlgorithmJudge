#include <iostream>
#include "InetSocket.h"
#include "PollManager.h"
#include "ServerSocket.h"
#include "logger.h"

using namespace std;
using namespace Network;

class JudgeServer: public PollHandler
{
private:
    static JudgeServer *instance;
    PollManager _pm;
    ServerSocket _serv;

    std::vector<InetSocket *> _conn;

    JudgeServer():_serv(PORT) { _pm.init(*this); }
    ~JudgeServer() {}
    void createNewConnection();
    void removeConnection(InetSocket *sock);
    
public:
    const static int PORT = 54321;

    static JudgeServer *getInstance() {
        if(JudgeServer::instance == NULL)
            JudgeServer::instance = new JudgeServer();
        return JudgeServer::instance;
    }

    void run();

    virtual void onRead(int fd);
    virtual void onWrite(int fd) {}
    virtual void onError(int fd) {}

    void receiveData(int fd);
};

JudgeServer *JudgeServer::instance;

void JudgeServer::createNewConnection()
{
    InetSocket *clnt = nullptr;
    clnt = _serv.accept();
    if(_conn.size() < (size_t)clnt->getFileDescriptor()) {
        _conn.resize(clnt->getFileDescriptor()+1);
    }
    _conn[clnt->getFileDescriptor()] = clnt;
    InformMessage("new connection from %s", inet_ntoa(clnt->getAddress().sin_addr));
}

void JudgeServer::removeConnection(InetSocket *sock)
{
    InformMessage("disconnect with %s", inet_ntoa(sock->getAddress().sin_addr));
}

void JudgeServer::receiveData(int fd)
{
    InetSocket &sock = *_conn[fd];
    char buf[1024] = {};
    ssize_t strlen = sock.read(buf, 1024);
    if(strlen < 0) {

        return ;
    }
    buf[strlen] = 0;

    printf("recv %s from %d\n", buf, fd);

}

void JudgeServer::onRead(int fd)
{

    if(fd == _serv.getFileDescriptor()) {
        createNewConnection();
    }
    else {
        receiveData(fd);
    }
}

void JudgeServer::run()
{

    _pm.addEvent(_serv.getFileDescriptor(), EPOLLIN);
    _pm.polling(-1);
}

int main(int argc, const char *argv[])
{
    InformMessage("information %d", 1);

    JudgeServer::getInstance()->run();
    return 0;
}

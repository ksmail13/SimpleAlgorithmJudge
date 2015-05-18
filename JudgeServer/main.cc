#include <iostream>
#include "InetSocket.h"
#include "PollManager.h"
#include "ServerSocket.h"
#include "logger.h"

using namespace std;
using namespace Network;

class JudgeServer: public PollHandler
{
    public:
        const static int PORT = 54321;

        JudgeServer *getInstance() {
            if(instance == NULL)
                instance = new JudgeServer();
            return instance;
        }

        void run();

        virtual void onRead(int fd);
        virtual void onWrite(int fd);
        virtual void onError(int fd);

        void createNewConnection();
        void receiveData(int fd);
    private:
        static JudgeServer *instance;
        PollManager _pm;
        ServerSocket _serv;

        std::vector<InetSocket *> _conn;

        JudgeServer():_serv(PORT) { _pm.init(*this); }
};

void JudgeServer::createNewConnection()
{
    InetSocket *clnt = new InetSocket();
    *clnt = _serv.accept();
    if(_conn.size() < clnt->getFileDescriptor()) {
        _conn.resize(clnt->getFileDescriptor()+1);
    }
    _conn[clnt->getFileDescriptor()] = clnt;
}

void JudgeServer::receiveData(int fd)
{
    InetSocket &sock = _conn[fd];


    char buf[1024] = {};

    ssize_t strlen = sock.read(buf, 1024);

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

void JudgeServer::onWrite(int fd)
{

}

void JudgeServer::onError(int fd)
{

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

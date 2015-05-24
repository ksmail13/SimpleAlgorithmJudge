//
// Created by micky on 15. 5. 20.
//

#ifndef JUDGESERVER_JUDGESERVER_H
#define JUDGESERVER_JUDGESERVER_H

#include "InetSocket.h"
#include "PollManager.h"
#include "ServerSocket.h"
#include "JudgeManager.h"
#include "json.h"

using namespace Network;
class JudgeServer: public PollHandler
{
private:
    static JudgeServer *instance;
    PollManager _pm;
    ServerSocket _serv;
    JudgeManager _jud_man;

    std::vector<InetSocket *> _conn;

    JudgeServer():_serv(PORT), _jud_man(JUDGES) { _pm.init(*this); }
    ~JudgeServer() {}
    void createNewConnection();
    void removeConnection(InetSocket *sock);

public:
    const static int PORT = 54321;
    const static int JUDGES = 4;
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

#endif //JUDGESERVER_JUDGESERVER_H

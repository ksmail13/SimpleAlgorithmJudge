//
// Created by micky on 15. 5. 20.
//

#ifndef JUDGESERVER_JUDGESERVER_H
#define JUDGESERVER_JUDGESERVER_H

#include <map>
#include <tuple>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>

#include "DBConnection.h"
#include "InetSocket.h"
#include "PollManager.h"
#include "ServerSocket.h"
#include "JudgeManager.h"
#include "logger.h"
#include "json.h"
#include "Task.h"


using namespace Network;
class JudgeServer: public PollHandler
{
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
    virtual void onWrite(int fd) {InformMessage("write on %d", fd);}
    virtual void onError(int fd) {InformMessage("error on %d", fd);}

    void receiveData(int fd);

private:
    static JudgeServer *instance;
    PollManager _pm;
    ServerSocket _serv;
    JudgeManager _judgeManager;

    std::vector<InetSocket *> _conn;

    JudgeServer():_serv(PORT), _judgeManager(JUDGES) { _pm.init(*this); }
    ~JudgeServer() {}
    void createNewConnection();
    void removeConnection(InetSocket *sock);


    void process(Json::Value &value, InetSocket &socket);

    void loginProcess(std::string id, std::string pw, InetSocket &sock);

    void submitProcess(Json::Value &value, InetSocket &socket);

    void loginSuccess(InetSocket &sock, DataBase::DBConnection &dbc,
                      bsoncxx::document::view doc);

    void loginFailed(InetSocket &sock);

    Json::Value getProblemList(DataBase::DBConnection &dbc);

    Json::Value getLanguageList(DataBase::DBConnection &connection);

    void getQuestionData(Json::Reader &reader, DataBase::DBConnection &dbc, bsoncxx::builder::stream::document &d,
                         question &q, Json::Value &temp);

    question &getCompilerData(question &q, Json::Reader &reader, Json::Value &temp, DataBase::DBConnection &dbc,
                              bsoncxx::builder::stream::document &d);
};

#endif //JUDGESERVER_JUDGESERVER_H

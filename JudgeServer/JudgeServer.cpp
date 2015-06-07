//
// Created by micky on 15. 5. 20.
//

#include <iostream>
#include "JudgeServer.h"


JudgeServer *JudgeServer::instance = NULL;

void JudgeServer::createNewConnection()
{
    InetSocket *clnt = nullptr;
    clnt = _serv.accept();
    if(_conn.size() < (size_t)clnt->getFileDescriptor()) {
        _conn.resize(clnt->getFileDescriptor()+1);
    }
    _conn[clnt->getFileDescriptor()] = clnt;
    _pm.addEvent(clnt->getFileDescriptor(), EPOLLIN);
    InformMessage("new connection from %s", clnt->getIpAddress().c_str());
}

void JudgeServer::removeConnection(InetSocket *sock)
{
    InformMessage("disconnect with %s", sock->getIpAddress().c_str());
    sock->close();
    _pm.removeEvent(sock->getFileDescriptor());
    delete sock;
}

void JudgeServer::receiveData(int fd)
{
    InetSocket &sock = *_conn[fd];
    InformMessage("receive data from %s", sock.getIpAddress().c_str());
    struct packet p;

    if(!sock.recvPacket(p)) {
        removeConnection(&sock);
        return ;
    }

    //Json parsing
    Json::Reader reader;
    Json::Value root;
    reader.parse(p.buf, root);


    InformMessage("%d message type %s, buf %s", fd, root.get("type", "notype").asCString(), p.buf.c_str());

    process(root, sock);
}

void JudgeServer::onRead(int fd)
{
    InformMessage("read!");
    if(fd == _serv.getFileDescriptor()) {
        createNewConnection();
    }
    else {
        receiveData(fd);
    }
}

void JudgeServer::run()
{
    InformMessage("server start");
    _judgeManager.start();
    _pm.addEvent(_serv.getFileDescriptor(), EPOLLIN);
    _pm.polling(-1);
}

void JudgeServer::process(Json::Value &value, InetSocket &socket) {
    std::string str = value.get("type", "notype").asString();

    if(str=="login") {
        loginProcess(value.get("id", "null").asString()
                , value.get("pw", "null").asString(), socket);
    }
    else if(str=="submit") {
        submitProcess(value, socket);
    }
    else {

    }
}

void JudgeServer::loginProcess(std::string id, std::string pw, InetSocket &sock) {
    Json::StyledWriter writer;
    DataBase::DBConnection dbc("mongodb://192.168.0.38");
    auto collection = dbc.getCollection("judge_user", "judge_user");

    bsoncxx::builder::stream::document filter;
    filter << "id" << id;
    filter << "pw" << pw;
    InformMessage("login id : %s pw : %s", id.c_str(), pw.c_str());

    for(auto &&doc : collection.find(filter)) {
        loginSuccess(sock, dbc, doc);
        return ;
    }

    loginFailed(sock);
}

void JudgeServer::loginFailed(InetSocket &sock) {
    Json::StyledWriter writer;
    packet p;
    Json::Value val;

    val["result"] = "false";
    p.buf = writer.write(val);
    p.len = static_cast<int>(p.buf.size());

    sock.sendPacket(p);
    val.clear();
    InformMessage("login failed");
}

void JudgeServer::loginSuccess(InetSocket &sock, DataBase::DBConnection &dbc,
                               bsoncxx::document::view doc) {
    Json::StyledWriter writer;
    std::string tmp;
    packet p;
    Json::Value val;
    InformMessage("login success");

    tmp = bsoncxx::to_json(doc["name"].get_value());
    tmp = tmp.substr(1, tmp.size()-2);
    InformMessage("name %s", tmp.c_str());
    val["result"] = "true";
    val["id"] = tmp;
    val["problems"] = getProblemList(dbc);
    val["languages"] = getLanguageList(dbc);

    p.buf = writer.write(val);
    p.len = static_cast<int>(p.buf.size());

    sock.sendPacket(p);
    val.clear();
}

Json::Value JudgeServer::getProblemList(DataBase::DBConnection &dbc) {
    Json::Reader reader;
    Json::Value tempValue;
    mongocxx::options::find optProj;
    bsoncxx::builder::basic::document proj;
    Json::Value questionObj;
    Json::Value questionList;
    std::string tmp;

    auto collection = dbc.getCollection("judge_question", "judge_question");
    proj.append(std::tuple<std::string, std::string>("_id","true")); //proj["_id"] = "true";
    proj.append(std::tuple<std::string, std::string>("title", "true")); //proj["title"] = "true";
    optProj.projection(proj.view());
    for(auto &&doc : collection.find({}, optProj)) {
        reader.parse(bsoncxx::to_json(doc), tempValue);
        questionObj["title"]=tempValue["title"];
        questionObj["qno"]=tempValue["_id"]["$oid"];

        questionList.append(questionObj);
        questionObj.clear();
    }
    return questionList;
}

Json::Value JudgeServer::getLanguageList(DataBase::DBConnection &dbc) {
    Json::Reader reader;
    Json::Value tempValue;
    mongocxx::options::find optProj;
    bsoncxx::builder::basic::document proj;
    Json::Value languageObj;
    Json::Value languageList;
    std::string tmp;

    auto collection = dbc.getCollection("judge_language", "judge_language");
    proj.append(std::tuple<std::string, std::string>("_id","true")); //proj["_id"] = "true";
    proj.append(std::tuple<std::string, std::string>("name", "true")); //proj["title"] = "true";
    optProj.projection(proj.view());
    for(auto &&doc : collection.find({}, optProj)) {
        reader.parse(bsoncxx::to_json(doc), tempValue);
        languageObj["lang"]=tempValue["name"];

        InformMessage("qno : %s", tmp.c_str());

        languageObj["langno"]=tempValue["_id"]["$oid"];

        languageList.append(languageObj);
        languageObj.clear();
    }
    return languageList;
}

void JudgeServer::submitProcess(Json::Value &value, InetSocket &socket) {
    question q;
    Json::Reader reader;
    Json::Value temp;
    DataBase::DBConnection dbc;
    bsoncxx::builder::stream::document d;
    q.code = value.get("code", "").asString();
    q.extends = value.get("lang", "").asString();
    q.qno = value.get("qno", "0").asString();
    q.title = value.get("title", "").asString();
    q.lang = value.get("lang", "cpp").asString();
    q.examinee_id = value.get("id", "").asString();
    // session
    q.examinee = &socket;
    // from db

    getQuestionData(reader, dbc, d, q, temp);

    getCompilerData(q, reader, temp, dbc, d);

    InformMessage("code %s, extends %s, qno %s, q.limit %d, q.title %s"
    , q.code.c_str(), q.extends.c_str(), q.qno.c_str(), q.limit, q.title.c_str());
    _judgeManager.submit(q);
}

question &JudgeServer::getCompilerData(question &q, Json::Reader &reader, Json::Value &temp,
                                       DataBase::DBConnection &dbc, bsoncxx::builder::stream::document &d) {
    mongocxx::collection collection = dbc.getCollection("judge_language", "judge_language");
    d << "name" << q.lang;

    for(auto&& doc : collection.find(d)) {
        InformMessage("language doc %s",bsoncxx::to_json(doc).c_str());
        reader.parse(bsoncxx::to_json(doc), temp);
        q.compiler = temp.get("compiler", "").asString();
        q.compileOption= temp.get("compile_option", "").asString();
        q.extends = temp.get("extend", "").asString();
        break;
    }
    return q;
}

void JudgeServer::getQuestionData(Json::Reader &reader, DataBase::DBConnection &dbc,
                                  bsoncxx::builder::stream::document &d, question &q, Json::Value &temp) {
    mongocxx::collection collection = dbc.getCollection("judge_question", "judge_question");
    d << "title" << q.title;
    for(auto&& doc : collection.find(d)) {
        InformMessage("question doc %s",bsoncxx::to_json(doc).c_str());
        reader.parse(bsoncxx::to_json(doc), temp);
        q.limit = temp.get("limit", 1).asInt();
        for(auto inputIt = temp["input"].begin(), ansIt=temp["output"].begin();
                inputIt!=temp["input"].end() && ansIt!=temp["output"].end();) {
            InformMessage("input %s ans %s", inputIt->asString().c_str(), ansIt->asString().c_str());
            std::string in = inputIt->asString();
            in.push_back('\n');
            q.testcases.push_back(std::make_pair(in, ansIt->asString()));
            inputIt++;
            ansIt++;
        }


        break;
    }
    d.clear();
}
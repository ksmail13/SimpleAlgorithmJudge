//
// Created by micky on 15. 5. 22.
//

#include <iostream>
#include <fstream>
#include "Judge.h"
#include "Grading.h"
#include "logger.h"


Judge::Judge() : Thread(), in(0, 0), out(0, 1), mutex(0, 1)
{ }

Judge::~Judge()
{
}

void Judge::submit(question q)
{
    out.wait();
    mutex.wait();
    _q_list.push_back(q);
    mutex.post();
    in.post();
}


int Judge::remain()
{
    int r_time = 0;
    mutex.wait();
    for(auto it = this->_q_list.begin(); it != _q_list.end() ; it ++) {
        r_time += (*it).limit;
    }
    mutex.post();
    return r_time;
}

void Judge::run()
{
    InformMessage("Judge Start id:%ld", this->getThreadId());
    while(isRunning()) {
        question &q = getQuestion();
        InformMessage("recv question!! from=%ld qno=%s", this->getThreadId(), q.qno.c_str());

        if(isCorrectCode(q.code)) {
            std::string codeName = createCode(q);
            Compile c(codeName, q.compiler, std::map<std::string, std::string>());
            Grading g(q, codeName, c);

            grading_result g_r = g.grade();

            //TODO : send message to examiner
        }

        // 현재 채점중인 로직에 대한 시간도 작업량에 반영하기 위해서
        // 리스트에서 제거를 따로함
        popQuestion();

        InformMessage("finish Judge id:%ld", this->getThreadId());
    }

    InformMessage("Judge END id:%ld", this->getThreadId());
}

question &Judge::getQuestion() {
    // 데이터가 들어올 때 까지 반복??
    //do {
        in.wait();
        mutex.wait();
    //} while(_q_list.size() == 0);
    question &q = _q_list[0];
    mutex.post();
    out.post();

    InformMessage("get question!");
    return q;
}

void Judge::popQuestion() {
    mutex.wait();
    _q_list.erase(_q_list.begin());
    mutex.post();
}

std::string Judge::createCode(const question &q) const {
    char name[100];
    sprintf(name, "submits/%s_%s_%ld.%s", q.title.c_str(), q.examinee_id.c_str(), time(NULL), q.extends.c_str());
    InformMessage("name %s", name);
    std::fstream codeFile(name, std::ios_base::out);
    codeFile << q.code;
    codeFile.flush();
    codeFile.close();

    return std::string(name);
}

bool Judge::isCorrectCode(const std::string &code) {

    return code.length() > 0 && code.find("#include <sys/socket.h>") == std::string::npos &&
            code.find("#include <unistd.h>") == std::string::npos;
}

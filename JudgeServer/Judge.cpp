//
// Created by micky on 15. 5. 22.
//

#include <iostream>
#include <fstream>
#include "Judge.h"
#include "Grading.h"
#include "logger.h"


Judge::Judge() : Thread(), in(0, 1), out(0, 0), mutex(1,1)
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
    while(isRunning()) {
        InformMessage("Judge Start id:%ld", this->getThreadId());
        question &q = getQuestion();

        if(isCorrectCode(q.code)) {
            std::string codeName = createCode(q);
            Grading g(q, codeName, "");

            grading_result g_r = g.grade();

            //TODO : send message to examiner
        }

        // 현재 채점중인 로직에 대한 시간도 작업량에 반영하기 위해서
        // 리스트에서 제거를 따로함
        popQuestion();

        InformMessage("finish Judge id:%ld", this->getThreadId());
    }
}

question &Judge::getQuestion() {
    in.wait();
    mutex.wait();
    question &q = _q_list[0];
    mutex.post();
    out.post();
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

    std::fstream codeFile(name, std::ios_base::out);
    codeFile << q.code;
    codeFile.flush();
    codeFile.close();

    return name;
}

bool Judge::isCorrectCode(const std::string &code) {

    return code.find("#include <sys/socket.h>") == std::string::npos &&
            code.find("#include <unistd.h>") == std::string::npos;
}

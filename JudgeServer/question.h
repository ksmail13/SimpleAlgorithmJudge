//
// Created by micky on 15. 5. 23.
//

#ifndef JUDGESERVER_QUESTION_H
#define JUDGESERVER_QUESTION_H

#include "InetSocket.h"
#include <string>
#include <vector>
#include <utility>

/**
 * 문제를 저장하고 제출자의 정보를 저장하기 위한 구조체
 */
struct question
{
    int limit;
    Network::InetSocket *examinee;
    std::string qno;
    std::string extends;
    std::string examinee_id;
    std::string title;
    std::string code;
    std::vector<std::pair<std::string, std::string> > testcases;

    std::string lang;
    std::string compiler;
    std::string compileOption;
};

#include <iostream>
#include <vector>
#include "Thread.h"
#include "InetSocket.h"

#endif //JUDGESERVER_QUESTION_H

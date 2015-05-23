//
// Created by micky on 15. 5. 23.
//

#ifndef JUDGESERVER_QUESTION_H
#define JUDGESERVER_QUESTION_H

#include "InetSocket.h"
#include <string>

/**
 * 문제를 저장하고 제출자의 정보를 저장하기 위한 구조체
 */
struct question
{
    int qno;
    int limit;
    Network::InetSocket examinee;
    std::string extends;
    std::string examinee_id;
    std::string title;
    std::string code;
};

#include <iostream>
#include <vector>
#include "Thread.h"
#include "InetSocket.h"

#endif //JUDGESERVER_QUESTION_H

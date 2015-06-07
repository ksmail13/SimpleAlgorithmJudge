//
// Created by micky on 15. 5. 23.
//

#ifndef JUDGESERVER_GRADING_H
#define JUDGESERVER_GRADING_H

#include "logger.h"
#include "question.h"
#include "KillTimerTask.h"
#include "result.h"
#include "Compile.h"

#include <iostream>
#include <map>
#include <unistd.h>
#include <string.h>
#include <string>
#include <time.h>
#include <wait.h>


struct grading_result:public result
{
public:
    bool correct;

    grading_result() : result(), correct(false) {}
};


class Grading {
public:
    Grading();

    Grading(question q, std::string codePath, Compile &c);

    ~Grading(){ }
    grading_result grade();

private:
    std::string _codePath;
    std::vector<std::pair<std::string, std::string> > *_testCases;
    question _q;
    Compile *_compiler;


};


#endif //JUDGESERVER_GRADING_H

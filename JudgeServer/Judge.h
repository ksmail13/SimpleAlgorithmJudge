//
// Created by micky on 15. 5. 22.
//

#ifndef JUDGESERVER_JUDGE_H
#define JUDGESERVER_JUDGE_H

#include <iostream>
#include <string>
#include <vector>
#include "Thread.h"
#include "SemaphoreObejct.h"
#include "question.h"

using namespace Thread;


class Judge : public Thread::Thread{
private:
    SemaphoreObejct in, out;
    SemaphoreObejct mutex;
    volatile std::vector<question> _q_list;
    Judge();
    ~Judge();

    std::string createCode(const question &q) const;
    bool isCorrectCode(const std::string &code);
    inline question &getQuestion();
    inline void popQuestion();
public:
    void submit(struct question q);
    int remain() const;

    virtual void run();

};


#endif //JUDGESERVER_JUDGE_H

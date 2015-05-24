//
// Created by micky on 15. 5. 24.
//

#ifndef JUDGESERVER_JUDGEMANAGER_H
#define JUDGESERVER_JUDGEMANAGER_H

#include "Judge.h"
#include <vector>
#include "json.h"
#include "include/mongo/bson/bson.h"

class JudgeManager {
private:
    std::vector<Judge> _judges;

    Judge &nextJudge();
public:
    JudgeManager(int cnt);
    void start();
    void stop();
    void submit(question &q);

    friend class Judge;
};


#endif //JUDGESERVER_JUDGEMANAGER_H

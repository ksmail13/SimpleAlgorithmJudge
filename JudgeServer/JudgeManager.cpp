//
// Created by micky on 15. 5. 24.
//

#include "JudgeManager.h"

JudgeManager::JudgeManager(int cnt) {
    _judges.resize(cnt);
}

Judge& JudgeManager::nextJudge() {
    int min = 0x7fffffff;
    int min_idx = 0;

    for(auto it=_judges.begin(); it!= _judges.end() ;it++) {
        if(it->remain() < min) {
            min_idx = it - _judges.begin();
        }
    }

    return _judges[min_idx];
}

void JudgeManager::submit(question &q) {
    Judge &n_judge = nextJudge();
    n_judge.submit(q);
}

void JudgeManager::stop() {
    for(auto it = _judges.begin(); it!= _judges.end() ;it++) {
        it->stop();
    }
}

void JudgeManager::start() {
    for(auto it=_judges.begin(); it!= _judges.end() ;it++) {
        it->start();
    }
}

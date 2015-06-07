//
// Created by mikcy on 15. 6. 7.
//

#ifndef JUDGESERVER_RESULT_H
#define JUDGESERVER_RESULT_H


struct result {
    bool error;
    std::string message;

    result() : error(false), message("") {}
};

#endif //JUDGESERVER_RESULT_H

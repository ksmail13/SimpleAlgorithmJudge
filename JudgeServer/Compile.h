//
// Created by mikcy on 15. 6. 7.
//

#ifndef JUDGESERVER_COMPILE_H
#define JUDGESERVER_COMPILE_H

#include <string>
#include <map>

#include "result.h"

struct compile_result:public result { };

class Compile {
public:
    virtual compile_result compile();
    virtual std::string getBinaryPath();
    virtual std::string getCommand();

    Compile(
            std::string codePath
            , std::string compiler
            , std::map<std::string, std::string> compileOpt) :
            _codePath(codePath),
            _compiler(compiler),
            _compile_opt(compileOpt){
        _compile_opt["-o"] = getBinaryPath();
    }
private:
    std::string _codePath;
    std::string _compiler;
    std::map<std::string, std::string> _compile_opt;

};



#endif //JUDGESERVER_COMPILE_H

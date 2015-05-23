//
// Created by micky on 15. 5. 23.
//

#ifndef JUDGESERVER_GRADING_H
#define JUDGESERVER_GRADING_H

#include "logger.h"

#include <map>
#include <unistd.h>
#include <string.h>
#include <string>

class Grading {
public:
    Grading();
    Grading(std::string codePath);
    Grading(std::string codePath, std::string answer);

    bool compile();
private:
    std::string codePath;
    std::string answer;


};


struct compile_result{
    bool error;
    std::string message;
};

class Compile {
public:
    virtual compile_result compile() = 0;
    std::string getCommand();
protected:
    std::string _codePath;
    std::string _compiler;
    std::map<std::string, std::string> _compile_opt;

private:
};

class CCompiler : public Compile {
public:
    CCompiler(std::string path):
            _codePath(path), _compiler("gcc") {
        _compile_opt["-o"] = path.substr(0, path.find('.'));
    }

    virtual compile_result compile();
};

class JavaCompiler : public Compile {
public:
    JavaCompiler(std::string path):
            _codePath(path), _compiler("javac") {

    }
    virtual compile_result compile();
};


#endif //JUDGESERVER_GRADING_H

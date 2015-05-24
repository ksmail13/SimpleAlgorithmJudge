//
// Created by micky on 15. 5. 23.
//

#ifndef JUDGESERVER_GRADING_H
#define JUDGESERVER_GRADING_H

#include "logger.h"
#include "question.h"

#include <iostream>
#include <map>
#include <unistd.h>
#include <string.h>
#include <string>
#include <time.h>
#include <wait.h>


struct result {
    bool error;
    std::string message;

    result() : error(false), message("") {}
};

struct compile_result:public result { };
struct grading_result:public result
{
public:
    bool correct;

    grading_result() : result(), correct(false) {}
};

class Compile {
public:
    virtual compile_result compile() = 0;
    virtual std::string getBinaryPath() = 0;
    std::string getCommand();

protected:
    std::string _codePath;
    std::string _compiler;
    static std::map<std::string, std::string> _compile_opt;

private:
};

class CCompile : public Compile {
public:
    CCompile(std::string path):
            _codePath(path), _compiler("gcc") {
        _compile_opt["-o"] = path.substr(0, path.find('.'));
    }

    virtual std::string getBinaryPath() {
        return _compile_opt["-o"];
    }

    virtual compile_result compile();
protected:
    std::string _codePath;
    std::string _compiler;
};

class JavaCompile : public Compile {
public:
    JavaCompile(std::string path):
            _codePath(path), _compiler("javac") {

    }

    virtual std::string getBinaryPath() {
        return "nothing";
    }

    virtual compile_result compile();
protected:
    std::string _codePath;
    std::string _compiler;
};


class Grading {
public:
    Grading();
    Grading(question q, std::string codePath, std::string answer);
    ~Grading(){ delete _compiler; }
    grading_result grade();

private:
    std::string _codePath;
    std::string _answer;
    question _q;
    Compile *_compiler;


};


#endif //JUDGESERVER_GRADING_H

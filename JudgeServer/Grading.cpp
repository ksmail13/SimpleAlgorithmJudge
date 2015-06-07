//
// Created by micky on 15. 5. 23.
//

#include "Grading.h"
#include "logger.h"
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

bool execute(const char *binPath, int excute_limit, const std::string &send, std::string &recv)
{
    pid_t child;
    int status;
    int pipes[2][2];
    pipe(pipes[0]);
    pipe(pipes[1]);
    child = fork();
    if(child < 0) {
        ErrorMessage("fork error()");
        return false;
    } else if(child == 0) { // child
        close(pipes[0][1]);
        close(pipes[1][0]);
        close(fileno(stdin));
        close(fileno(stdout));
        close(fileno(stderr));
        dup2(pipes[0][0], 0);

        //int fd = open("./temp", O_RDWR | O_CREAT | O_TRUNC, 0777);
        //dup2(fd, 1);
        dup2(pipes[1][1], 1);
        //dup2(pipes[1][1], 2);
        InformMessage("exec path %s", binPath);
        if(::execl(binPath, binPath, (char*)NULL) == -1) {
            perror("exec() failed");
            ErrorMessage("exec() error");
        }
    } else { // parent
        //for(int i=10000000;i>=0;i--);
        close(pipes[0][0]);
        close(pipes[1][1]);

        Timer::KillTimerTask task(child);
        Timer::Timer t(excute_limit, task);

        int &read = pipes[1][0];
        int &write = pipes[0][1];
        char buf[1024];
        //t.start();
        ::write(write, send.c_str(), send.size());

        while(::read(read, buf, 1024) != 0) {
            recv.append(buf);
        }
        //t.detach();
        InformMessage("recv buf %s", recv.c_str());
        ::waitpid(child, &status, WNOHANG);
    }

    return true;
}

Grading::Grading()
{ }

Grading::Grading(question &q, std::string codePath
        , Compile &c):
        _q(q), _codePath(codePath), _testCases(&q.testcases), _compiler(&c)
{ }

grading_result Grading::grade()
{
    grading_result result;
    result.message = "";
    compile_result c_result = _compiler->compile();
    InformMessage("compile was %s", c_result.error?"failed":"success");
    if(c_result.error) {
        result.message = c_result.message;
    }
    else {
        InformMessage("testcase count %ld", _testCases->size());

        for(int i=0;i<_testCases->size(); i++) {
            std::string p_answer;
            std::string test_case = _testCases->at(i).first;
            std::string answer = _testCases->at(i).second;
            InformMessage("test_case %s answer %s", test_case.c_str(), answer.c_str());
            if (execute(_compiler->getBinaryPath().c_str(), _q.limit, test_case, p_answer)) {
                if (trim(answer) == trim(p_answer)) {
                    result.correct = true;
                    result.message = "accept";
                }
                else {
                    result.message = "wrong answer your answer is ";
                    result.message.append(p_answer);
                }
            }
            else {
                ErrorMessage("execute() error");
                result.error = true;
                result.message.append("grade error:please re submit");
            }
        }
    }
    return result;
}



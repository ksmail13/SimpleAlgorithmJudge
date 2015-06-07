//
// Created by micky on 15. 5. 23.
//

#include "Grading.h"
#include "logger.h"

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
        dup2(pipes[0][0], fileno(stdin));
        dup2(pipes[1][1], fileno(stdout));
        dup2(pipes[1][1], fileno(stderr));

        ::execlp(binPath, binPath, (char*)NULL);
    } else { // parent
        close(pipes[0][0]);
        close(pipes[1][1]);

        Timer::KillTimerTask task(child);
        Timer::Timer t(excute_limit, task);

        int &read = pipes[1][0];
        int &write = pipes[0][1];
        char buf[1024];
        t.start();
        ::write(write, send.c_str(), send.size());

        while(::read(read, buf, 1024) != 0) {
            recv.append(buf);
        }
        t.stop();
        ::waitpid(child, &status, WNOHANG);
    }

    return true;
}

Grading::Grading()
{ }

Grading::Grading(question q, std::string codePath
        , Compile &c):
        _q(q), _codePath(codePath), _testCases(&q.testcases), _compiler(&c)
{ }

grading_result Grading::grade()
{
    grading_result result;
    compile_result c_result = _compiler->compile();
    if(c_result.error) {
        result.message = c_result.message;
    }
    else {
        for(int i=0;i<_testCases->size(); i++) {
            std::string p_answer;
            std::string test_case = _testCases->at(i).first;
            std::string answer = _testCases->at(i).second;

            if (execute(_codePath.c_str(), _q.limit, test_case, p_answer)) {
                if (answer == p_answer) {
                    result.correct = true;
                    result.message = "accept";
                }
                else {
                    result.message = "wrong answer";
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



//
// Created by micky on 15. 5. 23.
//

#include "Grading.h"
#include "Timer.h"
#include "logger.h"

class KillTimerTask :public Timer::TimerTask {
private :
    pid_t _target;
public :
    KillTimerTask(pid_t pid):_target(pid) { }

    virtual void task() {
        kill(_target, SIGKILL);
    }
};

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

        KillTimerTask task(child);
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

Grading::Grading(question q, std::string codePath, std::string answer):
        _q(q), _codePath(codePath), _answer(answer), _compiler(new CCompile(codePath))
{ }

grading_result Grading::grade()
{
    grading_result result;
    compile_result c_result = _compiler->compile();
    if(c_result.error) {
        result.message = c_result.message;
    }
    else {
        std::string p_answer;
        std::string test_case;
        if(execute(_codePath.c_str(), _q.limit, test_case, p_answer)) {
            if(_answer == p_answer) {
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
    return result;
}



#pragma mark NonGrading

std::map<std::string, std::string> Compile::_compile_opt;

compile_result CCompile::compile()
{
    std::string cmd(getCommand());
    FILE *pp = popen(cmd.c_str(), "r");
    struct compile_result result;
    result.error = false;
    // 임시저장용
    char buf[1024];

    // 컴파일 성공시 아무런 메시지를 출력하지 않는다.
    while(!feof(pp)) {
        fgets(buf, 1024, pp);
        result.error = true;
        result.message.append(buf);
    }

    return result;
}

compile_result JavaCompile::compile()
{
    struct compile_result result;
    result.error=false;

    return result;
}

std::string Compile::getCommand()
{

    std::string cmd(_compiler);
    cmd.push_back(' ');


    for (auto it = _compile_opt.begin(); it!=_compile_opt.end(); it++) {
        cmd.append(it->first);
        cmd.push_back(' ');
        cmd.append(it->second);
    }

    cmd.push_back(' ');

    cmd.append(_codePath);

    return cmd;
}


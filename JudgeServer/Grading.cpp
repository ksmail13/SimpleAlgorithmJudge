//
// Created by micky on 15. 5. 23.
//

#include "Grading.h"




#pragma mark NonGrading

compile_result CCompiler::compile()
{
    std::string cmd(getCommand());
    FILE *pp = popen(cmd.c_str(), "r");
    struct compile_result result;
    result.error = false;
    char buf[1024];
    while(!feof(pp)) {
        fgets(buf, 1024, pp);
        result.error = true;
    }

    if(result.error) {

    }

    return result;
}

compile_result JavaCompiler::compile()
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

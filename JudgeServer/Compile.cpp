//
// Created by mikcy on 15. 6. 7.
//

#include <iostream>
#include "Compile.h"
#include "logger.h"

//std::map<std::string, std::string> Compile::_compile_opt;

compile_result Compile::compile()
{
    std::string cmd(getCommand());
    InformMessage("cmd %s", cmd.c_str());
    FILE *pp = popen(cmd.c_str(), "r");
    struct compile_result result;
    result.error = false;
    if(pp==NULL) {
        result.error = true;
        result.message = "pipe open failed";
        return result;
    }

    // 임시저장용
    char buf[1024];

    // 컴파일 성공시 아무런 메시지를 출력하지 않는다.
    while(fgets(buf, 1024, pp) != NULL) {
        result.error = true;
        result.message.append(buf);
    }

    pclose(pp);
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

std::string Compile::getBinaryPath() {
    return _codePath.substr(0, _codePath.find('.'));
}

#include <iostream>
#include "JudgeServer.h"
#include "logger.h"
#include <unistd.h>
#include <signal.h>

using namespace std;
using namespace Network;




int main(int argc, const char *argv[])
{
    //InformMessage("information %d", 1);
    signal(SIGPIPE, SIG_IGN);
    JudgeServer *server = JudgeServer::getInstance();
    if(server != NULL) server->run();

    return 0;
}

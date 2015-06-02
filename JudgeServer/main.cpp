#include <iostream>
#include "JudgeServer.h"
#include "logger.h"

using namespace std;
using namespace Network;




int main(int argc, const char *argv[])
{
    InformMessage("information %d", 1);
    JudgeServer *server = JudgeServer::getInstance();
    if(server != NULL) server->run();

    return 0;
}

#include <iostream>
#include "InetSocket.h"
#include "PollManager.h"
#include "logger.h"

using namespace std;
using namespace Network;

class JudgeServer: public PollHandler
{
    public:
        JudgeServer *getInstance() {
            if(instance == null)
                instance = new JudgeServer();
            return instance;
        }

        void run();

        virtual void onRead(int fd);
        virtual void onWrite(int fd);
        virtual void onError(int fd);
    private:
        static JudgeServer *instance;
        PollManager _pm;
        JudgeServer() {_pm.init(*this);}
}

void JudgeServer::onRead(int fd)
{
    
}

void JudgeServer::onWrite(int fd)
{
    
}

void JudgeServer::onError(int fd)
{
    
}
int main()
{ 
	InformMessage("information %d", 1);
    return 0;
}

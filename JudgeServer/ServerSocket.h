#include "BasicSocket.h"

namespace Network
{
    class ServerSocket
    {
        private:
            InetSocket socket;
            void init(int port);
        public:
            InetSocket accept();
            ServerSocket(int port) {
               this->init(port);
            }
        protected:

        friend class InetSocket;
    }
};

//
// Created by micky on 15. 5. 22.
//

#ifndef JUDGESERVER_THREAD_H
#define JUDGESERVER_THREAD_H

#include <pthread.h>
#include <signal.h>
#include <string>
#include <exception>
#include <map>

namespace Thread{
    void *thread_main(void *args);

    class Thread {
    private:
        static std::map<pthread_t, Thread *> _threads;
        pthread_t _id;

        bool _running;
    public:
        Thread();
        ~Thread() {_threads.erase(_id);}

        bool isRunning() const { return _running; }

        virtual void run();
        void start();

        void join(void **ret_data);
        void detach();

        void stop();

        pthread_t getThreadId() const {return _id;}
        static Thread *currentThread(){};

        friend void *thread_main(void *args);
    };

    class ThreadException : public std::exception {
    private :
        std::string _what;
    public :
        ThreadException(const char *msg) {
            _what = msg;
        }

        virtual const char *what() const throw() {
            return _what.c_str();
        }
        virtual ~ThreadException(){}
    };
};



#endif //JUDGESERVER_THREAD_H

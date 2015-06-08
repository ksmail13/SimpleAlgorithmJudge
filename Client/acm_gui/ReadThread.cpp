#include "ReadThread.h"
#include <QMessageBox>
#include <iostream>

ReadThread::ReadThread(SocketManager *socketManager) : socketManager(socketManager)
{

}

void ReadThread::run()
{
    //Read Response From Server
    while(1)
    {
/*
        std::cout << "receive start" << std::endl;
        Json::StyledWriter writer;

        QString msg = QString::fromStdString(writer.write(socketManager->receive()));
        //QApplication::instance()->thread() will give you main threadid.
        std::cout << msg.toStdString() << std::endl;

        QObject *m = &(QObject)msg;
        m.moveToThread(QApplication::instance()->thread());
        std::cout << msg.toStdString() << std::endl;
*/

    }
    //return NULL;
}

ReadThread::~ReadThread()
{

}




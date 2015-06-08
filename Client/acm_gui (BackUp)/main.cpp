#include "loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //LoginWidget mywidget;
    LoginWindow loginwindow;

    //mywindow.setCentralWidget(&mywidget);
    loginwindow.show();
    return app.exec();
}

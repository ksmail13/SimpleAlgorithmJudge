#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //LoginWidget mywidget;
    MainWindow mainwindow;

    //mywindow.setCentralWidget(&mywidget);
    mainwindow.show();
    return app.exec();
}

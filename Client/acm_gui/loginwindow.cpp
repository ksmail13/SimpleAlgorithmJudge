#include "loginwindow.h"
//#include "ui_loginwindow.h"
#include <QMessageBox>
#include <stdio.h>
#include <string>

using namespace std;

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent)//, ui(new Ui::MainWindow)
{
   // ui->setupUi(this);
    //LoginWidget mywidget;
    setFixedSize(600, 400);
    setWindowTitle("Login");

    widget_login = new LoginWidget;
    setCentralWidget(widget_login);
    show();

    connect(widget_login->button_help, SIGNAL(clicked()), this, SLOT(helpBox()));
    connect(widget_login->button_login, SIGNAL(clicked()), this, SLOT(sendLoginInfo()));
}

//void MainWindow::

void LoginWindow::sendLoginInfo()
{
    QMessageBox msgBox;

    id = widget_login->getID();
    pw = widget_login->getPW();
    ip = widget_login->getIP();

    QString str;

    if(id == NULL)
    {
        str = "Please Enter Your ID";
    }
    else if(pw == NULL)
    {
        str = "Please Enter Your PW";
    }
    else if(ip == NULL)
    {
        str = "Please Enter Correct IP";
    }
    else
    {
        socket_manager = new SocketManager();
        if(socket_manager->setIP(ip) == false)
        {
            str = "Set IP Error";
        }
        else
        {
            str = QString("id : %1\npw : %2\nip : %3").arg(id, pw, ip);

            socket_manager->send(str);
            newWidget();
        }
    }

    msgBox.setText(str);
    msgBox.exec();



}

void LoginWindow::helpBox()
{
    QMessageBox msgBox;
    msgBox.setText("This is help Box about IP address");

    msgBox.exec();
}

void LoginWindow::newWidget()
{
    this->takeCentralWidget();

    setWindowTitle("Welcome " + id + "!");
    widget_main = new MainWidget;
    connect(widget_main->button_logout, SIGNAL(clicked()), this, SLOT(logOut()));
    setCentralWidget(widget_main);
}

void LoginWindow::logOut()
{
    this->takeCentralWidget();

    //close socket
    socket_manager->close();

    setWindowTitle("Login");
    widget_login = new LoginWidget;
    connect(widget_login->button_help, SIGNAL(clicked()), this, SLOT(helpBox()));
    connect(widget_login->button_login, SIGNAL(clicked()), this, SLOT(sendLoginInfo()));
    setCentralWidget(widget_login);
}

LoginWindow::~LoginWindow()
{
    //delete ui;
}


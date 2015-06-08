#include "MainWindow.h"
//#include "ui_loginwindow.h"

#include <stdio.h>
#include <string>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)//, ui(new Ui::MainWindow)
{
    setFixedSize(600, 400);
    setWindowTitle("Login");

    loginWidget = new LoginWidget(this);
    setCentralWidget(loginWidget);
    show();
}

void MainWindow::setSubmitWidget(QString title, Json::Value &loginResponse, SocketManager *(_socketManager))
{
    submitWidget = new SubmitWidget(this, loginResponse, _socketManager);
    setCentralWidget(submitWidget);
    setWindowTitle(title);
    //show();

}

void MainWindow::setLoginWidget()
{
    loginWidget = new LoginWidget(this);
    setCentralWidget(loginWidget);
    setWindowTitle("Login");
    show();
}

MainWindow::~MainWindow()
{
    //delete ui;
}


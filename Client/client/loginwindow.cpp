#include "loginwindow.h"
#include "loginwidget.h"
//#include "ui_loginwindow.h"
#include <QMessageBox>

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
    connect(widget_login->button_login, SIGNAL(clicked()), this, SLOT(newWidget()));
}

//void MainWindow::

void LoginWindow::helpBox()
{
    QMessageBox msgBox;
    msgBox.setText("This is help Box about IP address");

    msgBox.exec();
}

void LoginWindow::newWidget()
{
    this->takeCentralWidget();

    setWindowTitle("Welcome " + widget_login->getID() + "!");
    widget_main = new MainWidget;
    connect(widget_main->button_logout, SIGNAL(clicked()), this, SLOT(logOut()));
    setCentralWidget(widget_main);
}

void LoginWindow::logOut()
{
    this->takeCentralWidget();

    setWindowTitle("Login");
    widget_login = new LoginWidget;
    connect(widget_login->button_help, SIGNAL(clicked()), this, SLOT(helpBox()));
    connect(widget_login->button_login, SIGNAL(clicked()), this, SLOT(newWidget()));
    setCentralWidget(widget_login);
}

LoginWindow::~LoginWindow()
{
    //delete ui;
}


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "LoginWidget.h"
#include "SubmitWidget.h"

#include "socketmanager.h"
#include "json.h"

/*
namespace Ui {
class MainWindow;
}*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    LoginWidget *loginWidget;
    SubmitWidget *submitWidget;

    void setSubmitWidget(QString title, Json::Value &loginResponse, SocketManager *socketManager);
    void setLoginWidget();

private:
     //Ui::MainWindow *ui;
    //SocketManager *socketManager;

public slots:

};

#endif // MAINWINDOW_H

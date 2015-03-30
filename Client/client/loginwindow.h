#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginwidget.h"
#include "mainwidget.h"
/*
namespace Ui {
class MainWindow;
}*/

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    LoginWidget *widget_login;
    MainWidget *widget_main;

private:
     //Ui::MainWindow *ui;

public slots:
    void helpBox();
    void newWidget();
    void logOut();

};

#endif // MAINWINDOW_H

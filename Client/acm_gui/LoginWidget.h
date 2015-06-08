#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QString>
#include <QMainWindow>

//#include "MainWindow.h"
#include "socketmanager.h"
#include "json.h"

//#include <QtGui>

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QMainWindow *parent);
    ~LoginWidget();

    QPushButton *button_login;
    QPushButton *button_help;

    QString getID();
    QString getPW();
    QString getIP();
    void clearText();
    void doResponse(Json::Value &response);

public slots:
    void helpBox();
    void sendLoginInfo();


private:
    QFont       font_title;
    QLabel      *label_title;
    QLabel      *label_id;
    QLabel      *label_pw;
    QLabel      *label_ip;
    QLabel      *label_fake[2];
    QLineEdit   *edit_id;
    QLineEdit   *edit_pw;
    QLineEdit   *edit_ip[4];

    QGroupBox   *group_login;
    QGridLayout *layout_grid;
    QGridLayout *layout_grid_button;
    QVBoxLayout  *layout_box;

    QMainWindow *parentWindow;

    SocketManager *socketManager;

    QString id;
    QString pw;
    QString ip;

    Json::Value loginResponse;

    void setGUI();
    void newWidget(Json::Value &loginResponse);
};

#endif // LOGINWIDGET_H

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QLabel>
#include <QBoxLayout>
#include <QString>
#include <QTabWidget>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QMainWindow>

//#include "MainWindow.h"
#include "socketmanager.h"
#include "json.h"
#include "ReadThread.h"

class SubmitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SubmitWidget(QMainWindow *parent, Json::Value &loginResponse, SocketManager *socketManager);
    ~SubmitWidget();
    QPushButton  *button_logout;
    QPushButton  *button_submit;

    void setLabel(QString msg);

    SocketManager *socketManager;

public slots:
    void submit();
    void logOut();

private:
    QLabel      *label;
    QTabWidget  *widget_tab;
    QWidget     *tab_submit;
    QWidget     *tab_history;

    QVBoxLayout *layout_main;
    QGridLayout *layout_grid_submit;
    QGridLayout *layout_grid_history;
    QGridLayout *layout_grid_buttons;

    QLabel      *label_problem;
    QLabel      *label_language;
    QLabel      *label_upload;
    QLabel      *label_code;

    QComboBox   *combo_problem;
    QComboBox   *combo_language;

    QTextEdit   *text_code;

    QMainWindow *parentWindow;
    ReadThread *readThread;

    Json::Value loginResponse;
    Json::Value submitResponse;

    void setGUI();
    void createReadThread();
    void readMessage();
    void setProblems(Json::Value &problems);
    void setLanguages(Json::Value &languages);
    void doResponse();

};

#endif // MAINWIDGET_H

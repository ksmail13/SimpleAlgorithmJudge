#include "SubmitWidget.h"
#include "MainWindow.h"
#include <QMessageBox>

SubmitWidget::SubmitWidget(QMainWindow *parent, Json::Value &loginResponse, SocketManager *socketManager)
    : QWidget(), parentWindow(parent), loginResponse(loginResponse), socketManager(socketManager)
{
    setGUI();
    //TODO : make thread
    //createReadThread();
    //readThread = new ReadThread(socketManager);
    //readThread->start();

}
void SubmitWidget::setGUI()
{
    setFixedSize(600, 400);
    widget_tab = new QTabWidget();
    widget_tab->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Ignored);
    widget_tab->setTabShape(QTabWidget::Rounded);

    //Submit Tab
    tab_submit = new QWidget();
    label_problem = new QLabel("Problem");
    label_language = new QLabel("Language");
    label_upload = new QLabel("Upload");
    label_code = new QLabel("Source Code");
    text_code = new QTextEdit();

    combo_problem = new QComboBox();
    setProblems(loginResponse["problems"]);
    //combo_problem->addItem("p1");
    //combo_problem->addItem("p2");

    combo_language = new QComboBox();
    setLanguages(loginResponse["languages"]);
    //combo_language->addItem("C++");
    //combo_language->addItem("JAVA");

    layout_grid_submit = new QGridLayout();
    layout_grid_submit->addWidget(label_problem, 0, 0);
    layout_grid_submit->addWidget(combo_problem, 0, 1, 1, 4);
    layout_grid_submit->addWidget(label_language, 1, 0);
    layout_grid_submit->addWidget(combo_language, 1, 1, 1, 4);
    layout_grid_submit->addWidget(label_code, 2, 0);
    layout_grid_submit->addWidget(text_code, 2, 1);

    tab_submit->setLayout(layout_grid_submit);

    //buttons
    button_logout = new QPushButton("Logout");
    button_submit = new QPushButton("Submit");
    layout_grid_buttons = new QGridLayout();
    layout_grid_buttons->addWidget(button_logout, 0, 0);
    layout_grid_buttons->addWidget(button_submit, 0, 1);


    //History Tab
    //tab_history = new QWidget();

    //Add Tab, Icon Img?
    static QIcon Img_submit(QPixmap("./image/submit.png"));
    widget_tab->addTab(tab_submit, Img_submit, tr("Submit"));
    //static QIcon Img_history(QPixmap("history.png"));
    //widget_tab->addTab(tab_history, Img_history, tr("History"));

    //add tab widget and buttons to layout_main
    layout_main = new QVBoxLayout;
    layout_main->addWidget(widget_tab);
    layout_main->addLayout(layout_grid_buttons);

    setLayout(layout_main);

    //Setting Slot
    connect(button_submit, SIGNAL(clicked()), this, SLOT(submit()));
    connect(button_logout, SIGNAL(clicked()), this, SLOT(logOut()));
}

void SubmitWidget::setProblems(Json::Value &problems)
{
    for(auto it = problems.begin(); it != problems.end(); ++it)
    {
        Json::Value prob = (*it);
        Json::Value tmp = prob["title"];
        QString item = QString::fromStdString(tmp.asString());
        combo_problem->addItem(item);
    }
}

void SubmitWidget::setLanguages(Json::Value &languages)
{
    for(auto it = languages.begin(); it != languages.end(); ++it)
    {
        Json::Value lang = (*it);
        Json::Value tmp = lang["lang"];
        QString item = QString::fromStdString(tmp.asString());
        combo_language->addItem(item);
    }
}

void SubmitWidget::createReadThread()
{
    //readThread = new Thread();
}

void SubmitWidget::setLabel(QString msg)
{
    label->setText(msg);
}

void SubmitWidget::submit()
{
    QString problem = combo_problem->currentText();
    QString language = combo_language->currentText();
    QString code = text_code->toPlainText();

    Json::Value root;
    root["type"] = "submit";
    root["id"] = loginResponse.get("id", "").asString();
    root["title"] = problem.toStdString();
    root["lang"] = language.toStdString();
    root["code"] = code.toStdString();

    submitResponse = socketManager->send(root);
    doResponse();
}

void SubmitWidget::doResponse()
{
    Json::Value t = submitResponse["result"];
    QString result= QString::fromStdString(t.asString());
    QMessageBox msgBox;
    if(QString::compare(result, "true") == 0)
    {
        msgBox.setText("Correct!");
    }
    else
    {
        //Json::Value t = submitResponse["message"];
        //QString result = QString::fromStdString(t.asString());
        //msgBox.setText("Wrong Answer : \n" + result);
        msgBox.setText("Wrong Answer");
    }
    msgBox.setWindowTitle("Submit Result");
    msgBox.exec();
}

void SubmitWidget::logOut()
{
    //this->deleteLater();

    //TODO : thread detach, socket close
    socketManager->close();
    //readThread->detach();

    MainWindow *mainWindow = dynamic_cast<MainWindow *>(parentWindow);
    mainWindow->setLoginWidget();
}

SubmitWidget::~SubmitWidget()
{

}

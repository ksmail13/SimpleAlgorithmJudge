#include "mainwidget.h"

MainWidget::MainWidget() : QWidget()
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
    combo_problem->addItem("p1");
    combo_problem->addItem("p2");

    combo_language = new QComboBox();
    combo_language->addItem("C++");
    combo_language->addItem("JAVA");

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
    tab_history = new QWidget();



    //Add Tab, Icon Img?
    static QIcon Img_submit(QPixmap("./image/submit.png"));
    widget_tab->addTab(tab_submit, Img_submit, tr("Submit"));
    static QIcon Img_history(QPixmap("history.png"));
    widget_tab->addTab(tab_history, Img_history, tr("History"));


    //add tab widget and buttons to layout_main
    layout_main = new QVBoxLayout;
    layout_main->addWidget(widget_tab);

    layout_main->addLayout(layout_grid_buttons);

    setLayout(layout_main);
}
void MainWidget::setLabel(QString msg)
{
    label->setText(msg);
}

MainWidget::~MainWidget()
{

}


#include "loginwidget.h"

#include <QIntValidator>
#include <stdio.h>

LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(300, 300);
    label_title     = new QLabel("UOS ACM 체점 프로그램");
    label_title->setAlignment(Qt::AlignCenter);
    font_title = label_title->font();
    font_title.setPointSize(20);
    font_title.setBold(true);
    label_title->setFont(font_title);

    button_login    = new QPushButton("Login");
    button_help     = new QPushButton("help");
    label_id        = new QLabel("ID");
    label_pw        = new QLabel("PW");
    label_ip        = new QLabel("IP");
    edit_id         = new QLineEdit;
    edit_pw         = new QLineEdit;
    for(int i = 0; i < 4; i++)
    {
        edit_ip[i] = new QLineEdit;
        edit_ip[i]->setValidator(new QIntValidator(0, 255, this));
        edit_ip[i]->setAlignment(Qt::AlignRight);
        //line edit size modify
    }
    edit_pw->setEchoMode(QLineEdit::Password);



    //grid layout
    layout_grid = new QGridLayout;

    layout_grid->addWidget(label_id, 0, 0);
    layout_grid->addWidget(edit_id, 0, 1, 1, 4);
    layout_grid->addWidget(label_pw, 1, 0);
    layout_grid->addWidget(edit_pw, 1, 1, 1, 4);
    layout_grid->addWidget(label_ip, 2, 0);
    for(int i = 0; i < 4; i++)
    {
        layout_grid->addWidget(edit_ip[i], 2, i+1);
    }
    layout_grid->setVerticalSpacing(10);

    //Group Box
    setStyleSheet("QGroupBox{border : 1px solid black;}");
    group_login = new QGroupBox();
    group_login->setLayout(layout_grid);

    //Button layout
    layout_grid_button = new QGridLayout;
    label_fake[0] = new QLabel("");
    label_fake[1] = new QLabel("");
    layout_grid_button->addWidget(label_fake[0], 0, 0);
    layout_grid_button->addWidget(label_fake[1], 0, 1);
    layout_grid_button->addWidget(button_help, 0, 2);
    layout_grid_button->addWidget(button_login, 0, 3);
    layout_grid_button->setSpacing(10);

    //Total Layout
    layout_box = new QVBoxLayout;
    layout_box->addWidget(label_title);
    layout_box->addWidget(group_login);
    layout_box->addLayout(layout_grid_button);


    setLayout(layout_box);

}

QString LoginWidget::getID()
{
    return edit_id->text();
}

QString LoginWidget::getPW()
{
    return edit_pw->text();
}

QString LoginWidget::getIP()
{
    QString ip;

    QString ip1 = edit_ip[0]->text();
    QString ip2 = edit_ip[1]->text();
    QString ip3 = edit_ip[2]->text();
    QString ip4 = edit_ip[3]->text();

    if(ip1 == NULL || ip2 == NULL || ip3 == NULL || ip4 == NULL)
    {
        ip = "";
    }
    else
    {
        ip = QString("%1.%2.%3.%4").arg(ip1, ip2, ip3, ip4);
    }

    return ip;
}


LoginWidget::~LoginWidget()
{

}



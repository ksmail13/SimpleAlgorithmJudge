#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QString>

//#include <QtGui>

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();

    QPushButton *button_login;
    QPushButton *button_help;

    QString getID();
    QString getPW();
    QString getIP();

public slots:

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


};

#endif // LOGINWIDGET_H

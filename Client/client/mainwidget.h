#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QLabel>
#include <QBoxLayout>
#include <QString>
#include <QTabWidget>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget();
    ~MainWidget();
    QPushButton  *button_logout;

    void setLabel(QString msg);

private:
    QLabel      *label;
    QTabWidget  *widget_tab;
    QWidget     *tab_submit;
    QWidget     *tab_history;

    QVBoxLayout *layout_main;
    QGridLayout *layout_grid_submit;
    QGridLayout *layout_grid_history;

    QLabel      *label_problem;
    QLabel      *label_language;
    QLabel      *label_upload;
    QLabel      *label_code;

    QComboBox   *combo_problem;
    QComboBox   *combo_language;

    QTextEdit   *text_code;

};

#endif // MAINWIDGET_H

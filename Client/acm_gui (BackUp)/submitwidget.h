#ifndef SUBMITWIDGET_H
#define SUBMITWIDGET_H

#include <QWidget>
#include <QLabel>


class SubmitWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SubmitWidget(QWidget *parent = 0);
    ~SubmitWidget();

signals:

public slots:

private:
    QLabel *label_test;
};

#endif // SUBMITWIDGET_H

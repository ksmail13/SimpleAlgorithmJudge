#include "submitwidget.h"

SubmitWidget::SubmitWidget(QWidget *parent) : QWidget(parent)
{
    label_test = new QLabel("This is new Widget");
    label_test->setGeometry(20, 20, 20, 20);
}

SubmitWidget::~SubmitWidget()
{

}


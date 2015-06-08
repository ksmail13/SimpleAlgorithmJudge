#include "messagebox.h"


MessageBox::MessageBox(QString message)
{
    //label_dialog = new QLabel(message, this);
   // label_dialog->setGeometry(20, 20, 20, 20);
    setText(message);
    exec();

}

MessageBox::~MessageBox()
{

}


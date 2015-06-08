#ifndef DIALOG_H
#define DIALOG_H

#include <QMessageBox>
#include <QPushButton>
#include <QLabel>

class MessageBox : public QMessageBox
{
    public:
        MessageBox(QString message);
        ~MessageBox();

    private:
        QPushButton *button_dialog;
        QLabel      *label_dialog;
};

#endif // DIALOG_H

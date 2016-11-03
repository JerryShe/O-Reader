#ifndef ANSWERDIALOG_H
#define ANSWERDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLabel>



class AnswerDialog : public QDialog
{
    Q_OBJECT
public:
    AnswerDialog(int pos_x, int pos_y, QString text);

private:
    QLabel *message;
    QPushButton *yes;
    QPushButton *no;
    QString styles[3];
};

#endif // ANSWERDIALOG_H

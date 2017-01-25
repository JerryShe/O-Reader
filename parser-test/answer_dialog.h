#ifndef ANSWERDIALOG_H
#define ANSWERDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class AnswerDialog : public QDialog
{
    Q_OBJECT
public:
    AnswerDialog(int pos_x, int pos_y, QString text, QString Style);
    ~AnswerDialog();

private:
    QLabel *message;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *windowLayout;
    QPushButton *yes;
    QPushButton *no;
    QString styles[3];
};

#endif // ANSWERDIALOG_H

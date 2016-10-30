#include "answerdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>


AnswerDialog::AnswerDialog(int pos_x, int pos_y, QString text)
{
    AnswerDialog::resize(300,90);
    AnswerDialog::move(pos_x, pos_y);

    AnswerDialog::setWindowFlags(Qt::FramelessWindowHint);
    AnswerDialog::setWindowFlags(Qt::Popup);

    AnswerDialog::setStyleSheet("AnswerDialog{background-color:rgb(130, 0, 55);}");

    AnswerDialog::yes = new QPushButton("&Yes");
    AnswerDialog::yes->setFlat(true);
    AnswerDialog::yes->setMinimumHeight(25);

    QString a = "QPushButton"
                "{background-color:rgb(25, 156, 255);"
                "border: none;}"
                "QPushButton:hover"
                "{background-color:rgb(25, 156, 255);"
                "border: none;}";

    AnswerDialog::yes->setStyleSheet(a);


    AnswerDialog::no = new QPushButton("No");
    AnswerDialog::no->setFlat(true);
    AnswerDialog::no->setMinimumHeight(25);

    a = "QPushButton"
        "{background-color: rgb(162, 0, 70);"
        "border: none;}"
        "QPushButton:hover"
        "{background-color:rgb(210, 68, 68);"
        "border: none;}";

    AnswerDialog::no->setStyleSheet(a);




    AnswerDialog::message= new QLabel(text);
    AnswerDialog::message->setFont(QFont("MS Shell Dlg 2", 12, QFont::Normal));
    AnswerDialog::message->setStyleSheet("color: white");

    connect(yes, SIGNAL(clicked()), SLOT(accept()));
    connect(no, SIGNAL(clicked()), SLOT(reject()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(yes);
    buttonLayout->addWidget(no);

    QVBoxLayout *windowLayout = new QVBoxLayout;
    windowLayout->addWidget(AnswerDialog::message,0,Qt::AlignCenter);
    windowLayout->addLayout(buttonLayout);


    setLayout(windowLayout);

}

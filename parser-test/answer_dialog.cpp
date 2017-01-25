#include "answer_dialog.h"

#include <styles.h>


AnswerDialog::AnswerDialog(int pos_x, int pos_y, QString text, QString Style)
{
    resize(300,70);
    move(pos_x, pos_y);

    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(Qt::Popup);

    yes = new QPushButton(QObject::tr("Yes"), this);
    yes->setFlat(true);
    yes->setMinimumHeight(25);

    no = new QPushButton(QObject::tr("No"), this);
    no->setFlat(true);
    no->setMinimumHeight(25);

    message = new QLabel(text, this);
    message->setFont(QFont("MS Shell Dlg 2", 12, QFont::Normal));

    //////////////////////////////////////////////////////////////
    QString styles[3];
    setAnswerDialogStyle (styles, Style);
    setStyleSheet(styles[0]);
    yes->setStyleSheet(styles[1]);
    no->setStyleSheet(styles[2]);
    //////////////////////////////////////////////////////////////

    connect(yes, SIGNAL(clicked()), SLOT(accept()));
    connect(no, SIGNAL(clicked()), SLOT(reject()));

    buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(yes);
    buttonLayout->addWidget(no);

    windowLayout = new QVBoxLayout(this);
    windowLayout->addWidget(message,0,Qt::AlignCenter);
    windowLayout->addLayout(buttonLayout);

    setLayout(windowLayout);
}

AnswerDialog::~AnswerDialog()
{
    delete buttonLayout;
}

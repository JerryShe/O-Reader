#include "reading_mini_window.h"

#include <QEvent>
#include <QVBoxLayout>
#include <QPropertyAnimation>

#include <QDebug>

ReadingMiniWindow::ReadingMiniWindow(QWidget *parent): QDialog(parent)
{
    qDebug()<<"create MiniWindow";

    resizeWindow();
    parent->installEventFilter(this);


    setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);

    setContentsMargins(0,0,0,0);

    QVBoxLayout *MiniWindowLayout = new QVBoxLayout(this);
    setLayout(MiniWindowLayout);
    MiniWindowLayout->setContentsMargins(0,0,0,0);


    connect(this, SIGNAL(accepted()), this, SLOT(closeWindow()));
    connect(this, SIGNAL(rejected()), this, SLOT(closeWindow()));
}


ReadingMiniWindow::~ReadingMiniWindow()
{
    qDebug()<<"delete MiniWindow";
}


void ReadingMiniWindow::openWindow()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry", this);
    animation->setDuration(150);
    animation->setStartValue(QRect(this->width()*(-1), this->y(), this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation->setEasingCurve(QEasingCurve::OutCubic);

    animation->start();
}


void ReadingMiniWindow::closeWindow()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry", this);
    animation->setDuration(150);
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation->setEndValue(QRect(this->width()*(-1), this->y(), this->width(), this->height()));
    animation->setEasingCurve(QEasingCurve::InCubic);

    connect(animation, SIGNAL(finished()), this, SLOT(close()));

    animation->start();
}


bool ReadingMiniWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == this->parent())
        if (event->type() == QEvent::Resize)
            resizeWindow();

    return true;
}


void ReadingMiniWindow::resizeWindow()
{
    int frame, w, h;

    if (this->parentWidget()->width() - 100 < 1066)
        w = 1066;
    else
        w = this->parentWidget()->width() - 100;

    if (this->parentWidget()->height() - 100 < 536)
        h = 536;
    else
        h = this->parentWidget()->height() - 100;

    frame = (this->parentWidget()->height() - h)/2;

    this->setGeometry(frame, frame, w, h);
}

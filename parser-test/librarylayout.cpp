#include "librarylayout.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QWidget>

librarylayout::librarylayout(QWidget *parent): QWidget(parent) {
    layout = new QGridLayout;
    area = new QScrollArea;
    QWidget* widget = new QWidget;
    widget -> setLayout(layout);
    area -> setWidget(widget);
    row = column = 0;
    layout -> setSpacing(10);
    setLayout(layout);
}



void librarylayout::addWidget(QWidget *widget) {
    if(column > 4) {
        column = 0;
        ++row;
    }

    layout -> addWidget(widget,row, column++);
}

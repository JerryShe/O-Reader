#include "librarylayout.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
//#include <QWidget>
#include <QPair>
#include <QMouseEvent>



librarylayout::librarylayout(QWidget *AreaLayout)
{
    librarylayout::windowSize = AreaLayout->size().width();
    AreaLayout->setStyleSheet(QString("QWidget{background-color:rgb(170, 0, 73); border:none;}"));

    librarylayout::setAttribute(Qt::WA_MouseTracking);
    librarylayout::setMouseTracking(true);

    gridLayout = new QGridLayout;
    scrollArea = new QScrollArea;

    QWidget* widget = new QWidget;
    widget -> setLayout(gridLayout);

    scrollArea -> setWidget(widget);


    row = column = 0;

    setLayout(gridLayout);
}


void librarylayout::setColumnsAndMargins()
{

    int lMargin, rMargin;
    librarylayout::gridLayout->getContentsMargins(&lMargin, NULL, &rMargin, NULL);


    int layoutSize = librarylayout::windowSize - lMargin - rMargin;
    //if (max_columns)
    librarylayout::max_columns = layoutSize/(librarylayout::content->size().width()+5);

    int spacing = (layoutSize - librarylayout::content->size().width() * librarylayout::max_columns) / (librarylayout::max_columns - 1);
    librarylayout::gridLayout->setHorizontalSpacing(spacing);
    librarylayout::gridLayout->setVerticalSpacing(spacing);

}

void librarylayout::addWidget(QWidget *widget)
{
    if (librarylayout::content == NULL)
    {
        content = widget;
        librarylayout::setColumnsAndMargins();
    }

    if(column >= max_columns) {
        column = 0;
        ++row;
    }

    gridLayout -> addWidget(widget, row, column++);
}


void librarylayout::decrimentColumn()
{
    librarylayout::column--;
}





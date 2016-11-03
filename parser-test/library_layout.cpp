#include "library_layout.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QPair>
#include <QMouseEvent>

librarylayout::librarylayout(QWidget *AreaLayout)
{
    librarylayout::windowSize = AreaLayout->size().width();
    content = NULL;

    gridLayout = new QGridLayout;

    QWidget* widget = new QWidget;
    widget -> setLayout(gridLayout);
    setLayout(gridLayout);
    
    row = column = 0;    
}

void librarylayout::setWidget(QWidget *widget)
{
    if (librarylayout::content == NULL)
    {
        librarylayout::content = widget;
        librarylayout::setColumnsAndMargins();
    }    
}


void librarylayout::setColumnsAndMargins()
{

    int lMargin, rMargin;
    librarylayout::gridLayout->getContentsMargins(&lMargin, NULL, &rMargin, NULL);

    int layoutSize = librarylayout::windowSize - lMargin - rMargin;
    librarylayout::max_columns = layoutSize/(librarylayout::content->size().width()+5);

    int spacing = (layoutSize - librarylayout::content->size().width() * librarylayout::max_columns) / (librarylayout::max_columns - 1);
    librarylayout::gridLayout->setHorizontalSpacing(spacing);
    librarylayout::gridLayout->setVerticalSpacing(spacing);

}

void librarylayout::addWidget(QWidget *widget)
{
    if(column >= max_columns) 
    {
        column = 0;
        ++row;
    }

    gridLayout -> addWidget(widget, row, column++);
}





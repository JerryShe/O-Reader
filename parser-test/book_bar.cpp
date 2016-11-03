#include "book_bar.h"

BookBar::BookBar(QString FileName)
{
    BookBar::File = FileName;


    BookBar::setMinimumHeight(150);
    BookBar::setMaximumHeight(150);
    BookBar::setMaximumWidth(100);
    BookBar::setMinimumWidth(100);

    BookBar::setFlat(true);
    BookBar::setStyleSheet(QString("BookBar{background-color:rgb(0, 0, 73); border:none;}"));

}


QWidget BookBar::getBarWidget()
{


}

#include "selectionbox.h"

SelectionBox::SelectionBox(QWidget *parent = 0, const char *text = 0)
{
    this->resize(300,150);
    this->move(parent->pos().x()+90, parent->pos().y());
    this->setWindowFlags(Qt::FramelessWindowHint);


    message.move(10,10);
    message.show();

    yes.setText("Yes");
    yes.resize(50,20);
    yes.move(10, 50);
    yes.show();

    no.setText("No");
    yes.resize(50,20);
    yes.move(10, 50);
    no.show();
    message.setText(text);
    this->show();

}

void SelectionBox::setParametrs(QWidget *parent)
{


}

void SelectionBox::setTextAndShow(QString text)
{
                       //костыль для того, чтобы мы не выводили окно без надписи
}

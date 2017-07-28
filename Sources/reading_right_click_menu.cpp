#include "reading_right_click_menu.h"
#include "ui_reading_right_click_menu.h"

ReadingRightClickMenu::ReadingRightClickMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReadingRightClickMenu)
{
    ui->setupUi(this);
}

ReadingRightClickMenu::~ReadingRightClickMenu()
{
    delete ui;
}

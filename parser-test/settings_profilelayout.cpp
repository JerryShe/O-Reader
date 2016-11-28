#include "settings_profilelayout.h"
#include "ui_settings_profilelayout.h"

Settings_ProfileLayout::Settings_ProfileLayout(QWidget *parent, QString style) : QFrame(parent), ui(new Ui::Settings_ProfileLayout)
{
    Style = style;
    ui->setupUi(this);
}

Settings_ProfileLayout::~Settings_ProfileLayout()
{
    delete ui;
}

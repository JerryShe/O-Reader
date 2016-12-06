#include "settings_profilelayout.h"
#include "ui_settings_profilelayout.h"

Settings_ProfileLayout::Settings_ProfileLayout(QWidget *parent) : QFrame(parent), ui(new Ui::Settings_ProfileLayout)
{
    ui->setupUi(this);
}

Settings_ProfileLayout::~Settings_ProfileLayout()
{
    delete ui;
}


void Settings_ProfileLayout::setSettingsData(settings *Settings)
{

}

void Settings_ProfileLayout::on_ChangePasswordButton_clicked()
{

}

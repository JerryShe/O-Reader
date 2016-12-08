#include "settings_profilelayout.h"
#include "ui_settings_profilelayout.h"
#include "styles.h"

void Settings_ProfileLayout::setLayoutStyle()
{
    QString a[2];
    setProfileLayoutStyle(a, ProgramSettings->getInterfaceStyle());
    this->setStyleSheet(a[0]);
    ui->SaveButton->setStyleSheet(a[1]);
}

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
    ProgramSettings = Settings;
    setLayoutStyle();
}

void Settings_ProfileLayout::on_ChangePasswordButton_clicked()
{

}

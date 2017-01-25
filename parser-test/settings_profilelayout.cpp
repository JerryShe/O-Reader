#include "settings_profilelayout.h"
#include "ui_settings_profilelayout.h"
#include "styles.h"

void Settings_ProfileLayout::setLayoutStyle()
{
    QString a[2];
    setProfileLayoutStyle(a, ProgramSettings->getInterfaceStyle());
    this->setStyleSheet(a[0]);

    setSavebuttonStyle(savebuttonStyle, ProgramSettings->getInterfaceStyle());
    ui->SaveButton->setStyleSheet(savebuttonStyle[0]);
}

Settings_ProfileLayout::Settings_ProfileLayout(QWidget *parent) : QFrame(parent), ui(new Ui::Settings_ProfileLayout)
{
    ui->setupUi(this);
}

Settings_ProfileLayout::~Settings_ProfileLayout()
{
    delete ui;
}


void Settings_ProfileLayout::setSettingsData()
{
    ProgramSettings = settings::getSettings();
    setLayoutStyle();
}

void Settings_ProfileLayout::on_ChangePasswordButton_clicked()
{

}

void Settings_ProfileLayout::on_SaveButton_clicked()
{
    emit settingsChanged(0);
}

void Settings_ProfileLayout::setSavebuttonView(int type)
{
    if (type)
        ui->SaveButton->setStyleSheet(savebuttonStyle[1]);
    else
        ui->SaveButton->setStyleSheet(savebuttonStyle[0]);
}

void Settings_ProfileLayout::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}


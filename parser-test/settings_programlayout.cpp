#include "settings_programlayout.h"
#include "ui_settings_programlayout.h"
#include "styles.h"

void Settings_ProgramLayout::setLayoutStyle()
{
    QString a[2];
    setProgramLayoutStyle(a, ProgramSettings->getInterfaceStyle());
    this->setStyleSheet(a[0]);
    ui->SaveButton->setStyleSheet(a[1]);
}

Settings_ProgramLayout::Settings_ProgramLayout(QWidget *parent) : QFrame(parent), ui(new Ui::Settings_ProgramLayout)
{
    ui->setupUi(this);
}

Settings_ProgramLayout::~Settings_ProgramLayout()
{
    delete ui;
}

void Settings_ProgramLayout::setProgramData()
{
    ui->InterfaceStyleBox->setCurrentText(ProgramSettings->getInterfaceStyle());
    ui->LanguageBox->setCurrentText(ProgramSettings->getCurrentLanguage());
    ui->TopBarShowBox->setCurrentIndex(ProgramSettings->getHideTopBar());
}

void Settings_ProgramLayout::setSettingsData(settings *Settings)
{
    ProgramSettings = Settings;
    setLayoutStyle();
    setProgramData();

}

void Settings_ProgramLayout::on_InterfaceStyleBox_currentTextChanged(const QString &arg1)
{
    emit InterfaceStyleChanged();
}

void Settings_ProgramLayout::on_LanguageBox_currentTextChanged(const QString &arg1)
{
    emit LanguageChanged();
}

void Settings_ProgramLayout::on_SaveButton_clicked()
{
    ProgramSettings->setHideTopBar(ui->TopBarShowBox->currentIndex());
    ProgramSettings->setLanguage(ui->LanguageBox->currentText());
    ProgramSettings->setInterfaceStyle(ui->InterfaceStyleBox->currentText());
    ProgramSettings->saveSettings();
}

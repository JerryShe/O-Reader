#include "settings_readerlayout.h"
#include "ui_settings_readerlayout.h"

Settings_ReaderLayout::Settings_ReaderLayout(QWidget *parent, QString style) : QFrame(parent), ui(new Ui::Settings_ReaderLayout)
{
    Style = style;
    ui->setupUi(this);

    ui->_OverallSettingsWidget->hide();
    ui->_RegularSettingsWidget->hide();
    ui->_TitleSettingsWidget->hide();
    ui->_SubtitleSettingsWidget->hide();
    ui->_NoteSettingsWidget->hide();
}

Settings_ReaderLayout::~Settings_ReaderLayout()
{
    delete ui;
}

void Settings_ReaderLayout::on_ExampleButton_clicked()
{
    if (ui->TextExample->isHidden())
        ui->TextExample->show();
    else
        ui->TextExample->hide();
}

void Settings_ReaderLayout::on_OverallSettings_clicked()
{
    if (ui->_OverallSettingsWidget->isHidden())
        ui->_OverallSettingsWidget->show();
    else
        ui->_OverallSettingsWidget->hide();
}


void Settings_ReaderLayout::on_RegularSettings_clicked()
{
    if (ui->_RegularSettingsWidget->isHidden())
        ui->_RegularSettingsWidget->show();
    else
        ui->_RegularSettingsWidget->hide();
}

void Settings_ReaderLayout::on_TitleSettings_clicked()
{
    if (ui->_TitleSettingsWidget->isHidden())
        ui->_TitleSettingsWidget->show();
    else
        ui->_TitleSettingsWidget->hide();
}

void Settings_ReaderLayout::on_SubtitleSettings_clicked()
{
    if (ui->_SubtitleSettingsWidget->isHidden())
        ui->_SubtitleSettingsWidget->show();
    else
        ui->_SubtitleSettingsWidget->hide();
}

void Settings_ReaderLayout::on_NoteSettings_clicked()
{
    if (ui->_NoteSettingsWidget->isHidden())
        ui->_NoteSettingsWidget->show();
    else
        ui->_NoteSettingsWidget->hide();
}

#include "settings_programlayout.h"
#include "ui_settings_programlayout.h"
#include "styles.h"

#include <QKeyEvent>
#include <QDebug>
#include <QListView>

void Settings_ProgramLayout::setLayoutStyle()
{
    QString a[2];
    setProgramLayoutStyle(a, ProgramSettings->getInterfaceStyle());
    this->setStyleSheet(a[0]);
    ui->FTurnForward->setStyleSheet(a[1]);
    ui->STurnForward->setStyleSheet(a[1]);
    ui->FTurnBackward->setStyleSheet(a[1]);
    ui->STurnBackward->setStyleSheet(a[1]);

    setSavebuttonStyle(savebuttonStyle, ProgramSettings->getInterfaceStyle());
    ui->SaveButton->setStyleSheet(savebuttonStyle[0]);
}

Settings_ProgramLayout::Settings_ProgramLayout(QWidget *parent) : QFrame(parent), ui(new Ui::Settings_ProgramLayout)
{
    ui->setupUi(this);
    ui->InterfaceStyleBox->setView(new QListView());
    ui->LanguageBox->setView(new QListView());
    ui->TopBarShowBox->setView(new QListView());
    ui->TurnByTapBox->setView(new QListView());
    ui->TurnByWheelBox->setView(new QListView());
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
    ui->TurnByWheelBox->setCurrentIndex(ProgramSettings->getTurnByWheel());
    ui->TurnByTapBox->setCurrentIndex(ProgramSettings->getTurnByTap());

    connect(ui->InterfaceStyleBox, SIGNAL(activated(QString)), this, SLOT(settChanged()));
    connect(ui->LanguageBox, SIGNAL(activated(QString)), this, SLOT(settChanged()));
    connect(ui->TopBarShowBox, SIGNAL(activated(QString)), this, SLOT(settChanged()));
    connect(ui->TurnByWheelBox, SIGNAL(activated(QString)), this, SLOT(settChanged()));

    ui->FTurnForward->setText(QKeySequence(ProgramSettings->getFForwardKey()).toString());
    ui->STurnForward->setText(QKeySequence(ProgramSettings->getSForwardKey()).toString());
    ui->FTurnBackward->setText(QKeySequence(ProgramSettings->getFBackwardKey()).toString());
    ui->STurnBackward->setText(QKeySequence(ProgramSettings->getSBackwardKey()).toString());

    ui->FTurnBackward->installEventFilter(this);
    ui->FTurnForward->installEventFilter(this);
    ui->STurnBackward->installEventFilter(this);
    ui->STurnForward->installEventFilter(this);
}

void Settings_ProgramLayout::settChanged()
{
    emit settingsChanged(1);
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

    emit settingsChanged(0);
}

void Settings_ProgramLayout::setSavebuttonView(int type)
{
    if (type)
        ui->SaveButton->setStyleSheet(savebuttonStyle[1]);
    else
        ui->SaveButton->setStyleSheet(savebuttonStyle[0]);
}

void Settings_ProgramLayout::on_FTurnForward_toggled(bool checked)
{
    ui->STurnForward->setChecked(false);
    ui->STurnBackward->setChecked(false);
    ui->FTurnBackward->setChecked(false);
}

void Settings_ProgramLayout::on_STurnForward_toggled(bool checked)
{
    ui->FTurnForward->setChecked(false);
    ui->STurnBackward->setChecked(false);
    ui->FTurnBackward->setChecked(false);
}

void Settings_ProgramLayout::on_FTurnBackward_toggled(bool checked)
{
    ui->STurnForward->setChecked(false);
    ui->FTurnForward->setChecked(false);
    ui->STurnBackward->setChecked(false);
}

void Settings_ProgramLayout::on_STurnBackward_toggled(bool checked)
{
    ui->STurnForward->setChecked(false);
    ui->FTurnForward->setChecked(false);
    ui->FTurnBackward->setChecked(false);
}

bool Settings_ProgramLayout::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        if (ui->FTurnForward->isChecked())
        {
            QKeyEvent *KeyEvent = static_cast<QKeyEvent*>(event);

            if (KeyEvent->key() != ProgramSettings->getSForwardKey()
                    && KeyEvent->key() != ProgramSettings->getFBackwardKey()
                    && KeyEvent->key() != ProgramSettings->getSBackwardKey())
            {
                ui->FTurnForward->setText(QKeySequence(KeyEvent->key()).toString());
                ProgramSettings->setFForwardKey(KeyEvent->key());
                ui->FTurnForward->setChecked(false);
                emit settingsChanged(1);
            }
            return true;
        }
        else
        if (ui->STurnForward->isChecked())
        {
            QKeyEvent *KeyEvent = static_cast<QKeyEvent*>(event);
            if (KeyEvent->key() != ProgramSettings->getFForwardKey()
                    && KeyEvent->key() != ProgramSettings->getFBackwardKey()
                    && KeyEvent->key() != ProgramSettings->getSBackwardKey())
            {
                ui->STurnForward->setText(QKeySequence(KeyEvent->key()).toString());
                ProgramSettings->setSForwardKey(KeyEvent->key());
                ui->STurnForward->setChecked(false);
                emit settingsChanged(1);
            }
            return true;
        }
        else
        if (ui->FTurnBackward->isChecked())
        {
            QKeyEvent *KeyEvent = static_cast<QKeyEvent*>(event);
            if (KeyEvent->key() != ProgramSettings->getFForwardKey()
                    && KeyEvent->key() != ProgramSettings->getSForwardKey()
                    && KeyEvent->key() != ProgramSettings->getSBackwardKey())
            {
                ui->FTurnBackward->setText(QKeySequence(KeyEvent->key()).toString());
                ProgramSettings->setFBackwardKey(KeyEvent->key());
                ui->FTurnBackward->setChecked(false);
                emit settingsChanged(1);
            }
            return true;
        }
        else
        if (ui->STurnBackward->isChecked())
        {
            QKeyEvent *KeyEvent = static_cast<QKeyEvent*>(event);
            if (KeyEvent->key() != ProgramSettings->getFForwardKey()
                    && KeyEvent->key() != ProgramSettings->getSForwardKey()
                    && KeyEvent->key() != ProgramSettings->getFBackwardKey())
            {
                ui->STurnBackward->setText(QKeySequence(KeyEvent->key()).toString());
                ProgramSettings->setSBackwardKey(KeyEvent->key());
                ui->STurnBackward->setChecked(false);
                emit settingsChanged(1);
            }
            return true;
        }
    }
    return false;
}

void Settings_ProgramLayout::on_LanguageBox_activated(const QString &arg1)
{
    if (arg1 != ProgramSettings->getCurrentLanguage())
    {
        ProgramSettings->setLanguage(arg1);
        ui->retranslateUi(this);
    }
}


void Settings_ProgramLayout::on_TurnByWheelBox_activated(int index)
{
    if (index != ProgramSettings->getTurnByWheel())
    {
        ProgramSettings->setTurnByWheel(index);
        emit settingsChanged(1);
    }
}


void Settings_ProgramLayout::on_TurnByTapBox_activated(int index)
{
    if (index != ProgramSettings->getTurnByTap())
    {
        ProgramSettings->setTurnByTap(index);
        emit settingsChanged(1);
    }
}

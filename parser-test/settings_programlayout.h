#ifndef SETTINGS_PROGRAMLAYOUT_H
#define SETTINGS_PROGRAMLAYOUT_H

#include <QFrame>
#include <settings.h>

namespace Ui {
class Settings_ProgramLayout;
}

class Settings_ProgramLayout : public QFrame
{
    Q_OBJECT

public:
    explicit Settings_ProgramLayout(QWidget *parent = 0);
    ~Settings_ProgramLayout();
    void setSettingsData(settings *Settings);
    void setLayoutStyle();

private slots:
    void setProgramData();
    void on_InterfaceStyleBox_currentTextChanged(const QString &arg1);
    void on_LanguageBox_currentTextChanged(const QString &arg1);
    void on_SaveButton_clicked();

signals:
    void InterfaceStyleChanged();
    void LanguageChanged();

private:
    Ui::Settings_ProgramLayout *ui;
    settings * ProgramSettings;

};

#endif // SETTINGS_PROGRAMLAYOUT_H

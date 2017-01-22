#ifndef SETTINGS_PROGRAMLAYOUT_H
#define SETTINGS_PROGRAMLAYOUT_H

#include <QFrame>
#include <settings.h>
#include <QTranslator>

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

    void setSavebuttonView(int type);

private slots:
    void setProgramData();
    void on_InterfaceStyleBox_currentTextChanged(const QString &arg1);
    void on_LanguageBox_currentTextChanged(const QString &arg1);
    void on_SaveButton_clicked();
    void settChanged();

    void on_FTurnForward_toggled(bool checked);
    void on_STurnForward_toggled(bool checked);
    void on_FTurnBackward_toggled(bool checked);
    void on_STurnBackward_toggled(bool checked);

    void on_LanguageBox_activated(const QString &arg1);

signals:
    void InterfaceStyleChanged();
    void LanguageChanged();
    void settingsChanged(int type);

protected:
   bool eventFilter(QObject *obj, QEvent *event);

private:
    Ui::Settings_ProgramLayout *ui;
    settings* ProgramSettings;
    QString savebuttonStyle[2];

    int FTurnForwardKey = -1;
    int STurnForwardKey = -1;
    int FTurnBackwardKey = -1;
    int SFTurnBackwardKey = -1;
};

#endif // SETTINGS_PROGRAMLAYOUT_H

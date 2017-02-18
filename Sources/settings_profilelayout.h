#ifndef SETTINGS_PROFILELAYOUT_H
#define SETTINGS_PROFILELAYOUT_H

#include <QFrame>
#include "settings.h"

namespace Ui {
class Settings_ProfileLayout;
}

class Settings_ProfileLayout : public QFrame
{
    Q_OBJECT

public:
    explicit Settings_ProfileLayout(QWidget *parent = 0);
    ~Settings_ProfileLayout();

    void setSettingsData();
    void setLayoutStyle();
    void setSavebuttonView(const int &type);

private slots:
    void on_ChangePasswordButton_clicked();
    void on_SaveButton_clicked();

protected:
    void changeEvent(QEvent *event);

signals:
    void settingsChanged(int type);

private:
    Ui::Settings_ProfileLayout *ui;
    Settings *ProgramSettings;
    QString savebuttonStyle[2];
};

#endif // SETTINGS_PROFILELAYOUT_H

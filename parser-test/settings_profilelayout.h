#ifndef SETTINGS_PROFILELAYOUT_H
#define SETTINGS_PROFILELAYOUT_H

#include <QFrame>
#include <settings.h>

namespace Ui {
class Settings_ProfileLayout;
}

class Settings_ProfileLayout : public QFrame
{
    Q_OBJECT

public:
    explicit Settings_ProfileLayout(QWidget *parent = 0);
    ~Settings_ProfileLayout();    
    void setSettingsData(settings *Settings);

private slots:
    void on_ChangePasswordButton_clicked();

private:
    Ui::Settings_ProfileLayout *ui;
    QString Style;
};

#endif // SETTINGS_PROFILELAYOUT_H

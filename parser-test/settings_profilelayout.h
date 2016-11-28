#ifndef SETTINGS_PROFILELAYOUT_H
#define SETTINGS_PROFILELAYOUT_H

#include <QFrame>

namespace Ui {
class Settings_ProfileLayout;
}

class Settings_ProfileLayout : public QFrame
{
    Q_OBJECT

public:
    explicit Settings_ProfileLayout(QWidget *parent = 0, QString style = "red");
    ~Settings_ProfileLayout();

private:
    Ui::Settings_ProfileLayout *ui;
    QString Style;
};

#endif // SETTINGS_PROFILELAYOUT_H

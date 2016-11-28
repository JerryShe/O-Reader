#ifndef SETTINGS_PROGRAMLAYOUT_H
#define SETTINGS_PROGRAMLAYOUT_H

#include <QFrame>

namespace Ui {
class Settings_ProgramLayout;
}

class Settings_ProgramLayout : public QFrame
{
    Q_OBJECT

public:
    explicit Settings_ProgramLayout(QWidget *parent = 0, QString style = "red");
    ~Settings_ProgramLayout();

private:
    Ui::Settings_ProgramLayout *ui;
    QString Style;

};

#endif // SETTINGS_PROGRAMLAYOUT_H

#ifndef SETTINGS_READERLAYOUT_H
#define SETTINGS_READERLAYOUT_H

#include <QFrame>

namespace Ui {
class Settings_ReaderLayout;
}

class Settings_ReaderLayout : public QFrame
{
    Q_OBJECT

public:
    explicit Settings_ReaderLayout(QWidget *parent = 0, QString style = "red");
    ~Settings_ReaderLayout();

private slots:
    void on_ExampleButton_clicked();

    void on_OverallSettings_clicked();

    void on_RegularSettings_clicked();

    void on_TitleSettings_clicked();

    void on_SubtitleSettings_clicked();

    void on_NoteSettings_clicked();

private:
    Ui::Settings_ReaderLayout *ui;
    QString Style;
};

#endif // SETTINGS_READERLAYOUT_H

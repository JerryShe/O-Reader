#ifndef SETTINGS_READERLAYOUT_H
#define SETTINGS_READERLAYOUT_H

#include <QFrame>
#include <settings.h>
#include <answer_dialog.h>

namespace Ui {
class Settings_ReaderLayout;
}

class Settings_ReaderLayout : public QFrame
{
    Q_OBJECT

public:
    explicit Settings_ReaderLayout(QWidget *parent = 0);
    ~Settings_ReaderLayout();
    void setSettingsData(settings * const Settings);

    void setStyleData(const ReadingStyle style);
    ReadingStyle getStyleData();



private slots:
    void on_OverallSettings_clicked();
    void on_RegularSettings_clicked();
    void on_TitleSettings_clicked();
    void on_SubtitleSettings_clicked();
    void on_NoteSettings_clicked();
    void on_YepButton_clicked();
    void on_NopeButton_clicked();
    void on_SaveButton_clicked();
    void updateTextBox();
    void on_StyleBox_activated(const QString &arg1);
    void on_RegularColorBox_clicked();
    void on_TitleColorBox_clicked();
    void on_SubtitleColorBox_clicked();
    void on_NoteColorBox_clicked();
    void on_BackgroundColorBox_clicked();
    void on_EmphasizedColorBox_clicked();
    void on_EmphasizedSettings_clicked();

    void setLayoutStyle();

signals:
    void settingsChanged();

private:
    Ui::Settings_ReaderLayout *ui;
    AnswerDialog * StyleDeleteConfirm;

    settings * ProgramSettings;
    QString currentTextStyle;
};

#endif // SETTINGS_READERLAYOUT_H

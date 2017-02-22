#ifndef SETTINGS_READERLAYOUT_H
#define SETTINGS_READERLAYOUT_H

#include <QFrame>
#include "settings.h"
#include "answer_dialog.h"

namespace Ui {
class Settings_ReaderLayout;
}

class Settings_ReaderLayout : public QFrame
{
    Q_OBJECT

public:
    explicit Settings_ReaderLayout(QWidget *parent = 0);
    ~Settings_ReaderLayout();

    void setSettingsData();

    void setStyleData(const ReadingProfile &style);
    ReadingProfile getStyleData();

    void setSavebuttonView(const int &type);

private slots:
    void setStyle();


    void on_OverallSettings_clicked();

    void on_YepButton_clicked();
    void on_NopeButton_clicked();

    void on_SaveButton_clicked();
    void updateTextBox();

    void on_BackgroundColorBox_clicked();
    void on_BackgroundImageBox_clicked();
    void on_BackgroundTypeBox_currentIndexChanged(int index);


    void on_StyleBox_activated(const QString &styleName);

signals:
    void settingsChanged(int type);

protected:
    void changeEvent(QEvent *event);


private:
    Ui::Settings_ReaderLayout *ui;
    AnswerDialog * StyleDeleteConfirm;

    Settings * ProgramSettings;
    QString currentTextStyle;
    QString currentBackgroundImage;
    QString savebuttonStyle[2];
    QString nopeButtonStyle[2];
    QString yepButtonStyle[2];

    int changedSignal = 0;
};

#endif // SETTINGS_READERLAYOUT_H

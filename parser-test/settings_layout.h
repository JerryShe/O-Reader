#ifndef SETTINGSLAYOUT_H
#define SETTINGSLAYOUT_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include "settings_programlayout.h"
#include "settings_profilelayout.h"
#include "settings_readerlayout.h"
#include <synchronization.h>


class settingslayout : public QWidget
{
    Q_OBJECT
public:
    explicit settingslayout(QWidget *Parent=0);
    ~settingslayout();

    void setSettingsData();
    void hideWithoutSaving();
    void setSettWindowStyle();

signals:
    void settingsClosed();
    void settingsChanged();

public slots:
    void showProfile();
    void showProgram();
    void showReader();
    void addExitButton();

private slots:
    void updateSavebuttons(int type);
    void exit_button_clicked();

protected:
    void changeEvent(QEvent *event);

private:

    QVBoxLayout* MainLayout;
    QHBoxLayout* TabsLayout;

    Settings_ProfileLayout *ProfileWidget;  //0
    Settings_ProgramLayout *ProgramWidget;  //2
    Settings_ReaderLayout *ReaderWidget;    //1

    QHBoxLayout* ButtonsLayout;
    QPushButton* _SettingsProfile;
    QPushButton* _SettingsProgram;
    QPushButton* _SettingsReader;
    QPushButton* exit_button;

    Synchronization* UserActions;

    short currentTab = 1;
    bool settingsWasChanged = false;
    QString tabsStyleSheets[5];

    settings * ProgramSettings;
};

#endif // SETTINGSLAYOUT_H

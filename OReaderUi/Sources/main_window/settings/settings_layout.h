#ifndef SETTINGS_LAYOUT_H
#define SETTINGS_LAYOUT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "main_window/settings/program/settings_programlayout.h"
#include "main_window/settings/profile/settings_profilelayout.h"
#include "main_window/settings/reading/settings_readerlayout.h"

#include "data_handlers/synchronization.h"
#include "data_handlers/settings_handler.h"

#include "QTabSwitcher.h"


class SettingsLayout : public QWidget
{
    Q_OBJECT
public:
    SettingsLayout(QWidget *Parent=0);
    ~SettingsLayout();

    void setSettingsData();
    void hideWithoutSaving();
    void setStyle();

signals:
    void settingsClosed();
    void settingsChanged();

public slots:
    void addExitButton();

private slots:
    void updateSaveButtons(const int &type);
    void exit_button_clicked();

protected:
    void changeEvent(QEvent *event);

private:

    QVBoxLayout* MainLayout;
    QHBoxLayout* TabsLayout;

    Settings_ProfileLayout *ProfileWidget;
    Settings_ProgramLayout *ProgramWidget;
    Settings_ReaderLayout *ReaderWidget;

    QHBoxLayout* ButtonsLayout;
    QPushButton* ProfileButton;
    QPushButton* ProgramButton;
    QPushButton* ReaderButton;
    QPushButton* exit_button;

    Synchronization* UserActions;

    QTabSwitcher* tabSwitcher;

    bool settingsWasChanged = false;

    SettingsHandler * ProgramSettings;
};

#endif // SETTINGS_LAYOUT_H

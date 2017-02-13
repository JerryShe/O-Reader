#ifndef SETTINGSLAYOUT_H
#define SETTINGSLAYOUT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "settings_programlayout.h"
#include "settings_profilelayout.h"
#include "settings_readerlayout.h"
#include "synchronization.h"

#include "QTabSwitcher.h"


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
    void addExitButton();

private slots:
    void updateSavebuttons(int type);
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

    Settings * ProgramSettings;
};

#endif // SETTINGSLAYOUT_H

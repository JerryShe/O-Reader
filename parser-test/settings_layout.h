#ifndef SETTINGSLAYOUT_H
#define SETTINGSLAYOUT_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include "settings_programlayout.h"
#include "settings_profilelayout.h"
#include "settings_readerlayout.h"

class settingslayout : public QWidget
{
    Q_OBJECT
public:
    explicit settingslayout(QWidget *Parent=0);
    ~settingslayout();
    void showProfile();
    void showProgram();
    void showReader();
    void setSettingsData(settings *Settings);

    void hideWithoutSaving();

signals:
    void tabChanged(int prevTab);

public slots:

private:

    QHBoxLayout *settingsMainLayout;
    settings * ProgramSettings;

    Settings_ProfileLayout *ProfileWidget;  //0
    Settings_ProgramLayout *ProgramWidget;  //2
    Settings_ReaderLayout *ReaderWidget;    //1

    short currentTab = 1;
    QString Style;
};

#endif // SETTINGSLAYOUT_H

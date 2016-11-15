#include "settings_layout.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>


settingslayout::settingslayout(QWidget *AreaLayout)
{
    settingsMainLayout = new QHBoxLayout();

    ProfileWidget = new QWidget();
    ProgramWidget = new QWidget();
    ReaderWidget = new QWidget();
    SynchronizationWidget = new QWidget();

    ProfileLayout = new QGridLayout();
    ProgramLayout = new QGridLayout();
    ReaderLayout = new QGridLayout();
    SynchronizationLayout = new QGridLayout();

    settingslayout::setLayout(settingsMainLayout);

    settingsMainLayout->addWidget(ProfileWidget, 0);
    settingsMainLayout->addWidget(ProgramWidget, 1);
    settingsMainLayout->addWidget(ReaderWidget, 2);
    settingsMainLayout->addWidget(SynchronizationWidget, 3);

    ProfileWidget->setLayout(ProfileLayout);
    ProgramWidget->setLayout(ProgramLayout);
    ReaderWidget->setLayout(ReaderLayout);
    SynchronizationWidget->setLayout(SynchronizationLayout);


    QPushButton *sett1 = new QPushButton("profile");
    ProfileLayout->addWidget(sett1, 0, 0);

    QPushButton *sett2 = new QPushButton("program");
    ProgramLayout->addWidget(sett2, 0, 0);

    QPushButton *sett3 = new QPushButton("reader");
    ReaderLayout->addWidget(sett3, 0, 0);

    QPushButton *sett4 = new QPushButton("Synchronization");
    SynchronizationLayout->addWidget(sett4, 0, 0);

    settingslayout::hide();
    ProfileWidget->hide();
    ReaderWidget->hide();
    SynchronizationWidget->hide();
}

void settingslayout::showProfile()
{
    switch (currentTab)
    {
    case 0:
        break;
    case 1:
        ProgramWidget->hide();
        emit tabChanged(1);
        ProfileWidget->show();
        break;
    case 2:
        ReaderWidget->hide();
        emit tabChanged(2);
        ProfileWidget->show();
        break;
    case 3:
        SynchronizationWidget->hide();
        emit tabChanged(3);
        ProfileWidget->show();
        break;
    default:
        break;
    }
    currentTab = 0;
}

void settingslayout::showProgram()
{
    switch (currentTab)
    {
    case 0:
        ProfileWidget->hide();
        emit tabChanged(0);
        ProgramWidget->show();
        break;
    case 1:
        break;
    case 2:
        ReaderWidget->hide();
        emit tabChanged(2);
        ProgramWidget->show();
        break;
    case 3:
        SynchronizationWidget->hide();
        emit tabChanged(3);
        ProgramWidget->show();
        break;
    default:
        break;
    }
    currentTab = 1;
}

void settingslayout::showReader()
{
    switch (currentTab)
    {
    case 0:
        ProfileWidget->hide();
        emit tabChanged(0);
        ReaderWidget->show();
        break;
    case 1:
        ProgramWidget->hide();
        emit tabChanged(1);
        ReaderWidget->show();
        break;
    case 2:
        break;
    case 3:
        SynchronizationWidget->hide();
        emit tabChanged(3);
        ReaderWidget->show();
        break;
    default:
        break;
    }
    currentTab = 2;
}

void settingslayout::showSynchronization()
{
    switch (currentTab)
    {
    case 0:
        ProfileWidget->hide();
        emit tabChanged(0);
        SynchronizationWidget->show();
        break;
    case 1:
        ProgramWidget->hide();
        emit tabChanged(1);
        SynchronizationWidget->show();
        break;
    case 2:
        ReaderWidget->hide();
        emit tabChanged(2);
        SynchronizationWidget->show();
        break;
    case 3:
        break;
    default:
        break;
    }
    currentTab = 3;
}



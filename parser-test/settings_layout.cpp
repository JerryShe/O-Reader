#include "settings_layout.h"

#include "settings_programlayout.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>



settingslayout::settingslayout(QWidget *Parent)
{
    this->setParent(Parent);
    Style = "red";
    ProgramWidget = new Settings_ProgramLayout(this,Style);
    ReaderWidget = new Settings_ReaderLayout(this,Style);
    ProfileWidget = new Settings_ProfileLayout(this,Style);

    settingsMainLayout = new QHBoxLayout();

    settingslayout::setLayout(settingsMainLayout);

    settingsMainLayout->addWidget(ProfileWidget, 0);
    settingsMainLayout->addWidget(ProgramWidget, 1);
    settingsMainLayout->addWidget(ReaderWidget, 2);

    this->setStyleSheet("QLabel{color:white;}");

    settingslayout::hide();
    ProfileWidget->hide();
    ReaderWidget->hide();
}

settingslayout::~settingslayout()
{
    delete settingsMainLayout;
    delete ProfileWidget;
    delete ProgramWidget;
    delete ReaderWidget;
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
    default:
        break;
    }
    currentTab = 2;
}



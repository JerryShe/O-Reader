#include "settings_layout.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QEvent>

#include "styles.h"


void settingslayout::setSettWindowStyle()
{
    setTabButtonsStyle(tabsStyleSheets, ProgramSettings->getInterfaceStyle());
    _SettingsProfile->setStyleSheet(tabsStyleSheets[0]);
    _SettingsProgram->setStyleSheet(tabsStyleSheets[1]);
    _SettingsReader->setStyleSheet(tabsStyleSheets[0]);

    this->setStyleSheet("QLabel{color:white;}");
}

settingslayout::settingslayout(QWidget *Parent)
{
    this->setParent(Parent);
    ProgramWidget = new Settings_ProgramLayout(this);
    ReaderWidget = new Settings_ReaderLayout(this);
    ProfileWidget = new Settings_ProfileLayout(this);

    connect(ProgramWidget, SIGNAL(settingsChanged(int)), this, SLOT(updateSavebuttons(int)));
    connect(ReaderWidget, SIGNAL(settingsChanged(int)), this, SLOT(updateSavebuttons(int)));
    connect(ProfileWidget, SIGNAL(settingsChanged(int)), this, SLOT(updateSavebuttons(int)));

    MainLayout = new QVBoxLayout(this);
    settingslayout::setLayout(MainLayout);
    MainLayout->setContentsMargins(0,0,0,0);
    MainLayout->setSpacing(0);

    TabsLayout = new QHBoxLayout();
    TabsLayout->addWidget(ProfileWidget);
    TabsLayout->addWidget(ProgramWidget);
    TabsLayout->addWidget(ReaderWidget);

    ButtonsLayout = new QHBoxLayout();
    MainLayout->addLayout(ButtonsLayout);
    MainLayout->addLayout(TabsLayout);

    _SettingsProfile = new QPushButton(QObject::tr("Profile"), this);
    _SettingsProgram = new QPushButton(QObject::tr("Program"), this);
    _SettingsReader = new QPushButton(QObject::tr("Reader"), this);

    _SettingsProfile->setFixedHeight(30);
    _SettingsProgram->setFixedHeight(30);
    _SettingsReader->setFixedHeight(30);

    ButtonsLayout->addWidget(_SettingsProfile);
    ButtonsLayout->addWidget(_SettingsProgram);
    ButtonsLayout->addWidget(_SettingsReader);

    connect(this->_SettingsProfile, SIGNAL(clicked(bool)), this, SLOT(showProfile()));
    connect(this->_SettingsProgram, SIGNAL(clicked(bool)), this, SLOT(showProgram()));
    connect(this->_SettingsReader, SIGNAL(clicked(bool)), this, SLOT(showReader()));

    ProfileWidget->hide();
    ReaderWidget->hide();
}

void settingslayout::setSettingsData()
{
    ProgramSettings = settings::getSettings();
    UserActions = Synchronization::getSynchronization();
    setSettWindowStyle();
    ReaderWidget->setSettingsData();
    ProgramWidget->setSettingsData();
    ProfileWidget->setSettingsData();
}

settingslayout::~settingslayout()
{
    delete TabsLayout;
    delete ProfileWidget;
    delete ProgramWidget;
    delete ReaderWidget;
    delete exit_button;
}

void settingslayout::addExitButton()
{
    exit_button = new QPushButton(this);
    exit_button->setFixedSize(30,30);
    QString style[2];
    setExitButtonStyle(style, ProgramSettings->getInterfaceStyle());
    exit_button->setStyleSheet(style[0]);
    ButtonsLayout->addWidget(exit_button,0);
    connect(this->exit_button, SIGNAL(clicked(bool)), this, SLOT(exit_button_clicked()));
}

void settingslayout::exit_button_clicked()
{
    hideWithoutSaving();
    emit settingsClosed();
    close();
}


void settingslayout::showProfile()
{
    switch (currentTab)
    {
    case 0:
        break;
    case 1:
        ProgramWidget->hide();
        _SettingsProgram->setStyleSheet(tabsStyleSheets[0]);
        ProfileWidget->show();
        break;
    case 2:
        ReaderWidget->hide();
        _SettingsReader->setStyleSheet(tabsStyleSheets[0]);
        ProfileWidget->show();
        break;
    default:
        break;
    }
    currentTab = 0;
    _SettingsProfile->setStyleSheet(tabsStyleSheets[1]);
}

void settingslayout::showProgram()
{
    switch (currentTab)
    {
    case 0:
        ProfileWidget->hide();
        _SettingsProfile->setStyleSheet(tabsStyleSheets[0]);
        ProgramWidget->show();
        break;
    case 1:
        break;
    case 2:
        ReaderWidget->hide();
        _SettingsReader->setStyleSheet(tabsStyleSheets[0]);
        ProgramWidget->show();
        break;
    default:
        break;
    }
    currentTab = 1;
    _SettingsProgram->setStyleSheet(tabsStyleSheets[1]);
}

void settingslayout::showReader()
{
    switch (currentTab)
    {
    case 0:
        ProfileWidget->hide();
        _SettingsProfile->setStyleSheet(tabsStyleSheets[0]);
        ReaderWidget->show();
        break;
    case 1:
        ProgramWidget->hide();
        _SettingsProgram->setStyleSheet(tabsStyleSheets[0]);
        ReaderWidget->show();
        break;
    case 2:
        break;
    default:
        break;
    }
    currentTab = 2;
    _SettingsReader->setStyleSheet(tabsStyleSheets[1]);

}

void settingslayout::hideWithoutSaving()
{
    hide();
    ProgramSettings->loadSettings();
}

void settingslayout::updateSavebuttons(int type)
{
    ProfileWidget->setSavebuttonView(type);
    ProgramWidget->setSavebuttonView(type);
    ReaderWidget->setSavebuttonView(type);

    if (type)
        settingsWasChanged = true;
    else if (settingsWasChanged == true)
        UserActions->addAction(UActions::UpdateSettings, "kostil");
}

void settingslayout::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        _SettingsProfile->setText(QObject::tr("Profile"));
        _SettingsProgram->setText(QObject::tr("Program"));
        _SettingsReader->setText(QObject::tr("Reader"));
    }
}

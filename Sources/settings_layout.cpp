#include "settings_layout.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QEvent>

#include "styles.h"


void SettingsLayout::setSettWindowStyle()
{
    QString tabsStyleSheets[5];

    setTabButtonsStyle(tabsStyleSheets, ProgramSettings->getInterfaceStyle());

    for (int i = 0; i < tabSwitcher->getTabCount(); i++)
        tabSwitcher->setButtonStyleSheet(i, tabsStyleSheets[1], tabsStyleSheets[0]);

    this->setStyleSheet("QLabel{color:white;}");
}

SettingsLayout::SettingsLayout(QWidget *Parent)
{
    this->setParent(Parent);
    ProgramWidget = new Settings_ProgramLayout(this);
    ReaderWidget = new Settings_ReaderLayout(this);
    ProfileWidget = new Settings_ProfileLayout(this);

    connect(ProgramWidget, SIGNAL(settingsChanged(int)), this, SLOT(updateSavebuttons(int)));
    connect(ReaderWidget, SIGNAL(settingsChanged(int)), this, SLOT(updateSavebuttons(int)));
    connect(ProfileWidget, SIGNAL(settingsChanged(int)), this, SLOT(updateSavebuttons(int)));

    MainLayout = new QVBoxLayout(this);
    SettingsLayout::setLayout(MainLayout);
    MainLayout->setContentsMargins(0,0,0,0);
    MainLayout->setSpacing(0);

    TabsLayout = new QHBoxLayout();
    TabsLayout->addWidget(ProfileWidget);
    TabsLayout->addWidget(ProgramWidget);
    TabsLayout->addWidget(ReaderWidget);

    ButtonsLayout = new QHBoxLayout();
    MainLayout->addLayout(ButtonsLayout);
    MainLayout->addLayout(TabsLayout);

    ProfileButton = new QPushButton(QObject::tr("Profile"), this);
    ProgramButton = new QPushButton(QObject::tr("Program"), this);
    ReaderButton = new QPushButton(QObject::tr("Reader"), this);

    ProfileButton->setFixedHeight(30);
    ProgramButton->setFixedHeight(30);
    ReaderButton->setFixedHeight(30);

    ButtonsLayout->addWidget(ProfileButton);
    ButtonsLayout->addWidget(ProgramButton);
    ButtonsLayout->addWidget(ReaderButton);

    tabSwitcher = new QTabSwitcher(this);

    tabSwitcher->addTab(ProfileWidget, ProfileButton);
    tabSwitcher->addTab(ProgramWidget, ProgramButton);
    tabSwitcher->addTab(ReaderWidget, ReaderButton);

}

void SettingsLayout::setSettingsData()
{
    ProgramSettings = Settings::getSettings();
    UserActions = Synchronization::getSynchronization();
    setSettWindowStyle();
    tabSwitcher->start(1);

    ReaderWidget->setSettingsData();
    ProgramWidget->setSettingsData();
    ProfileWidget->setSettingsData();
}

SettingsLayout::~SettingsLayout()
{
    delete TabsLayout;
}

void SettingsLayout::addExitButton()
{
    exit_button = new QPushButton(this);
    exit_button->setFixedSize(30,30);
    QString style[2];
    setExitButtonStyle(style, ProgramSettings->getInterfaceStyle());
    exit_button->setStyleSheet(style[0]);
    ButtonsLayout->addWidget(exit_button,0);
    connect(this->exit_button, SIGNAL(clicked(bool)), this, SLOT(exit_button_clicked()));
}

void SettingsLayout::exit_button_clicked()
{
    hideWithoutSaving();
    emit settingsClosed();
    close();
}

void SettingsLayout::hideWithoutSaving()
{
    hide();
    ProgramSettings->loadSettings();
}

void SettingsLayout::updateSavebuttons(const int &type)
{
    ProfileWidget->setSavebuttonView(type);
    ProgramWidget->setSavebuttonView(type);
    ReaderWidget->setSavebuttonView(type);

    if (type)
        settingsWasChanged = true;
    else if (settingsWasChanged == true)
        UserActions->addAction(UActions::UpdateSettings, "kostil");
}

void SettingsLayout::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ProfileButton->setText(QObject::tr("Profile"));
        ProgramButton->setText(QObject::tr("Program"));
        ReaderButton->setText(QObject::tr("Reader"));
    }
}

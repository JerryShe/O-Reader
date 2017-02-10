#include "qtabswitcher.h"


QTab::QTab(QWidget *Widget, QPushButton *Button, QString AStyle, QString IStyle)
{
    widget = Widget;
    button = Button;
    activeStyle = AStyle;
    inactiveStyle = IStyle;
    hiden = false;
}

QPushButton* QTab::getButton()
{
    return button;
}

QWidget* QTab::getWidget()
{
    return widget;
}

QString QTab::getActiveStyle()
{
    return activeStyle;
}

QString QTab::getInactiveStyle()
{
    return inactiveStyle;
}

bool QTab::isHiden()
{
    return hiden;
}

void QTab::setButton(QPushButton* Button)
{
    button = Button;
}

void QTab::setWidget(QWidget* Widget)
{
    widget = Widget;
}

void QTab::setStyles(QString ActiveStyle, QString InactiveStyle)
{
    activeStyle = ActiveStyle;
    inactiveStyle = InactiveStyle;
}

void QTab::openTab()
{
    if (!hiden)
    {
        button->setStyleSheet(activeStyle);
        widget->show();
    }
}

void QTab::closeTab()
{
    button->setStyleSheet(inactiveStyle);
    widget->hide();
}

void QTab::show()
{
    button->show();
    hiden = false;
}

void QTab::hide()
{
    button->hide();
    hiden = true;
}



QTabSwitcher::QTabSwitcher(QObject* parent)
{
    setParent(parent);
    SignalMapper = new QSignalMapper(this);
    connect(SignalMapper, SIGNAL(mapped(int)), this, SLOT(switchTab(int)));

    CurrentTab = -1;
}

QTabSwitcher::~QTabSwitcher()
{
    for (int i = 0; i < tabList.size(); i++)
        delete tabList[i];

    delete SignalMapper;
}

void QTabSwitcher::addTab(QWidget *tabWidget, QPushButton *tabButton, QString activeStyle, QString inactiveStyle)
{
    tabList.append(new QTab(tabWidget, tabButton, activeStyle, inactiveStyle));

    connect(tabButton, SIGNAL(clicked()), SignalMapper, SLOT(map()));
    SignalMapper->setMapping(tabButton, tabList.size() - 1);
}

void QTabSwitcher::addTab(QTab* tab)
{
    tabList.append(tab);

    connect(tab->getButton(), SIGNAL(clicked()), SignalMapper, SLOT(map()));
    SignalMapper->setMapping(tab->getButton(), tabList.size() - 1);
}

void QTabSwitcher::setButtonStyleSheet(int tabIndex, QString ActiveStyle, QString inactiveStyle)
{
    if (tabIndex < 0 || tabIndex >= tabList.size())
        return;

    tabList[tabIndex]->setStyles(ActiveStyle, inactiveStyle);
}

void QTabSwitcher::setButtonStyleSheet(QPushButton *tabButton, QString activeStyle, QString inactiveStyle)
{
    setButtonStyleSheet(indexOf(tabButton), activeStyle, inactiveStyle);
}

void QTabSwitcher::setButtonStyleSheet(QWidget* tabWidget, QString activeStyle, QString inactiveStyle)
{
    setButtonStyleSheet(indexOf(tabWidget), activeStyle, inactiveStyle);
}


void QTabSwitcher::removeTab(int tabIndex)
{
    if (tabIndex < 0 || tabIndex >= tabList.size())
        return;

    if (CurrentTab > tabIndex)
        CurrentTab--;
    else
    if (CurrentTab == tabIndex)
    {
        if (tabIndex != tabList.size() - 1)
        {
            switchTab(tabIndex + 1);
            CurrentTab--;
        }
        else
            switchTab(tabIndex - 1);
    }

    SignalMapper->removeMappings(tabList[tabIndex]->getButton());

    delete tabList[tabIndex];
    tabList.removeAt(tabIndex);

    for (int i = tabIndex; i < tabList.size(); i++)
    {
        SignalMapper->removeMappings(tabList[i]->getButton());
        SignalMapper->setMapping(tabList[i]->getButton(), i);
    }


}

void QTabSwitcher::removeTab(QPushButton *tabButton)
{
    removeTab(indexOf(tabButton));
}

void QTabSwitcher::removeTab(QWidget *tabWidget)
{
    removeTab(indexOf(tabWidget));
}

int QTabSwitcher::indexOf(QPushButton *tabButton)
{
    for (int i = 0; i < tabList.size(); i++)
        if (tabList[i]->getButton() == tabButton)
            return i;

    return -1;
}

int QTabSwitcher::indexOf(QWidget *tabWidget)
{
    for (int i = 0; i < tabList.size(); i++)
        if (tabList[i]->getWidget() == tabWidget)
            return i;

    return -1;
}

int QTabSwitcher::indexOf(QTab* tab)
{
    for (int i = 0; i < tabList.size(); i++)
        if (tabList[i] == tab)
            return i;

    return -1;
}

int QTabSwitcher::getCurrentTabIndex()
{
    return CurrentTab;
}

QTab* QTabSwitcher::getCurrentTab()
{
    return tabList[CurrentTab];
}

QPushButton* QTabSwitcher::getCurrentButton()
{
    if (CurrentTab != -1)
        return tabList[CurrentTab]->getButton();
    else
        return 0;
}

QWidget* QTabSwitcher::getCurrentWidget()
{
    if (CurrentTab != -1)
        return tabList[CurrentTab]->getWidget();
    else
        return 0;
}

int QTabSwitcher::getTabCount()
{
    return tabList.size();
}

void QTabSwitcher::start(int startTab)
{
    if (startTab < 0)
        startTab = 0;

    if (startTab >= tabList.size())
        return;

    CurrentTab = startTab;

    for (int i = 0; i < tabList.size(); i++)
        tabList[i]->closeTab();

    tabList[CurrentTab]->openTab();
}

void QTabSwitcher::start(QPushButton* startTabButton)
{
    start(indexOf(startTabButton));
}

void QTabSwitcher::start(QWidget* startTabWidget)
{
    start(indexOf(startTabWidget));
}

void QTabSwitcher::switchTab(int tabIndex)
{
    if (tabIndex < 0 || tabIndex >= tabList.size())
        return;

    if (tabList[tabIndex]->isHiden() || tabIndex == CurrentTab)
        return;

    tabList[CurrentTab]->closeTab();
    tabList[tabIndex]->openTab();

    CurrentTab = tabIndex;
}


void QTabSwitcher::switchTab(QPushButton* tabButton)
{
    switchTab(indexOf(tabButton));
}

void QTabSwitcher::switchTab(QWidget* tabWidget)
{
    switchTab(indexOf(tabWidget));
}


void QTabSwitcher::activateTab(int index)
{
    if (index < 0 || index >= tabList.size())
        return;

    if (tabList[index]->isHiden())
        tabList[index]->show();
}

void QTabSwitcher::activateTab(QPushButton* tabButton)
{
    activateTab(indexOf(tabButton));
}

void QTabSwitcher::activateTab(QWidget* tabWidget)
{
    activateTab(indexOf(tabWidget));
}

void QTabSwitcher::deactivateTab(int index)
{
    if (index < 0 || index >= tabList.size())
        return;

    if (!tabList[index]->isHiden())
    {
        if (index == CurrentTab)
        {
            if (index == 0)
                switchTab(1);
            else
                switchTab(0);
        }
        tabList[index]->hide();
    }
}

void QTabSwitcher::deactivateTab(QPushButton* tabButton)
{
    deactivateTab(indexOf(tabButton));
}

void QTabSwitcher::deactivateTab(QWidget* tabWidget)
{
    deactivateTab(indexOf(tabWidget));
}

void QTabSwitcher::clear()
{
    for (int i = 0; i < tabList.size(); i++)
        delete tabList[i];
    tabList.clear();

    delete SignalMapper;
    SignalMapper = new QSignalMapper(this);

    CurrentTab = -1;
}

bool QTabSwitcher::contains(QPushButton* tabButton)
{
    return (indexOf(tabButton) == -1) ? false : true;
}

bool QTabSwitcher::contains(QWidget* tabWidget)
{
    return (indexOf(tabWidget) == -1) ? false : true;
}

bool QTabSwitcher::contains(QTab* tab)
{
    return (indexOf(tab) == -1) ? false : true;
}

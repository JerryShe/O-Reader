#include "reading_menu.h"
#include "ui_reading_menu.h"

#include "settings.h"
#include "styles.h"

#include <QDebug>

void ReadingMenu::setStyle()
{
    QString styleSheets[6];

    setReaderWindowMenuButtons(styleSheets, Settings::getSettings()->getInterfaceStyle());

    ui->BackButton->setStyleSheet(styleSheets[4]);
    ui->ContentsButton->setStyleSheet(styleSheets[0]);
    ui->SettingsButton->setStyleSheet(styleSheets[2]);

    ui->MainWidget->setStyleSheet(styleSheets[5]);
}

ReadingMenu::ReadingMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReadingMenu)
{
    ui->setupUi(this);
    this->setStyle();

    this->parentWidget()->installEventFilter(this);

    machine = new QStateMachine(this);
    s1 = new QState(machine);
    s2 = new QState(machine);

    animation = new QPropertyAnimation(this, "pos");

    animation->setDuration(100);

    s2->assignProperty(this, "pos", QPoint(-70, 25));
    s1->assignProperty(this, "pos", QPoint(0, 25));

    transition1 = s1->addTransition(this, SIGNAL(MenuButtonClicked()), s2);
    transition2 = s2->addTransition(this, SIGNAL(MenuButtonClicked()), s1);

    connect(s2, SIGNAL(entered()), this, SIGNAL(hideMenuWidget()));

    transition1->addAnimation(animation);
    transition2->addAnimation(animation);
    machine->setInitialState(s2);
    machine->start();

    this->resize(70, this->parentWidget()->height() - 25);
    this->move(-70, 25);
}


ReadingMenu::~ReadingMenu()
{
    delete ui;
}


void ReadingMenu::hideMenu()
{
    if (machine->configuration().contains(s1))
    {
        emit MenuButtonClicked();
    }
}


void ReadingMenu::showMenu()
{
    if (machine->configuration().contains(s2))
        emit MenuButtonClicked();
}


void ReadingMenu::on_ContentsButton_clicked()
{
    hideMenu();
    emit showContentsTable();
}


void ReadingMenu::on_SettingsButton_clicked()
{
    hideMenu();
    emit showSettingsWindow();
}


void ReadingMenu::on_BackButton_clicked()
{
    emit showMainWindow();
}


bool ReadingMenu::menuIsHidden()
{
    if (machine->configuration().contains(s2))
        return true;
    return false;
}


bool ReadingMenu::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Resize)
    {
        this->resize(70, this->parentWidget()->height() - 25);
    }
    return false;
}

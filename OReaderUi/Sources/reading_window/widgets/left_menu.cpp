#include "reading_window/widgets/left_menu.h"
#include "ui_left_menu.h"
#include "data_handlers/settings_handler.h"
#include "styles.h"

#include <QMouseEvent>

#include <QDebug>

void LeftMenu::setStyle()
{
    QString styleSheets[6];

    setReaderWindowMenuButtons(styleSheets, SettingsHandler::getSettings()->getInterfaceStyle());

    ui->BackButton->setStyleSheet(styleSheets[4]);
    ui->ContentsButton->setStyleSheet(styleSheets[0]);
    ui->SettingsButton->setStyleSheet(styleSheets[2]);
    ui->SearchButton->setStyleSheet(styleSheets[1]);

    ui->MainWidget->setStyleSheet(styleSheets[5]);
}

LeftMenu::LeftMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LeftMenu)
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


LeftMenu::~LeftMenu()
{
    delete ui;
}


void LeftMenu::hideMenu()
{
    if (machine->configuration().contains(s1))
    {
        emit MenuButtonClicked();
    }
}


void LeftMenu::showMenu()
{
    if (machine->configuration().contains(s2))
        emit MenuButtonClicked();

    setFocus();
}


void LeftMenu::on_ContentsButton_clicked()
{
    hideMenu();
    emit showContentsTable();
}


void LeftMenu::on_SettingsButton_clicked()
{
    hideMenu();
    emit showSettingsWindow();
}


void LeftMenu::on_SearchButton_clicked()
{
    hideMenu();
    emit showSearchWindow();
}


void LeftMenu::on_BackButton_clicked()
{
    emit showMainWindow();
}


bool LeftMenu::menuIsHidden()
{
    if (machine->configuration().contains(s2))
        return true;
    return false;
}


bool LeftMenu::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj)

    if (event->type() == QEvent::Resize)
    {
        this->resize(70, this->parentWidget()->height() - 25);
    }
    return false;
}



#include "reading_window.h"
#include "ui_readingwindow.h"
#include "books.h"
#include "answer_dialog.h"
#include "settings_layout.h"
#include "synchronization_layout.h"
#include "search_window.h"
#include "settings.h"
#include "styles.h"

#include <QTimer>
#include <styles.h>
#include <QMouseEvent>
#include <QWindow>

#include <QThread>

#include <QDebug>



void ReadingWindow::setStyle(QString currentStyle)
{
    QString styleSheets[8];
    setWindowTopButtonsStyle(styleSheets, currentStyle);
    ui->min_button->setStyleSheet(styleSheets[0]);
    ui->full_size_button->setStyleSheet(styleSheets[1]);
    ui->exit_button->setStyleSheet(styleSheets[2]);

    setBackgroundWindowColor(styleSheets, currentStyle);
    ui->MainWidget->setStyleSheet(styleSheets[0]);

    setReaderWindowStyle(styleSheets, currentStyle);
    ui->Clock->setStyleSheet(styleSheets[1]);
    ui->Progress->setStyleSheet(styleSheets[1]);
    ui->MenuButton->setStyleSheet(styleSheets[0]);

    setReaderWindowMenuButtons(styleSheets, currentStyle);
    _BackToMainWindowButton->setStyleSheet(styleSheets[0]);
    _ContentsButton->setStyleSheet(styleSheets[0]);
    _SynchronizationButton->setStyleSheet(styleSheets[0]);
    _FindButton->setStyleSheet(styleSheets[0]);
    _SettingsButton->setStyleSheet(styleSheets[0]);
}

ReadingWindow::ReadingWindow(settings * PSettings, Book book) : ui(new Ui::ReadingWindow)
{
    ui->setupUi(this);
    ui->TextPage->setAlignment(Qt::AlignJustify);
    show();
    BookParse = new FB2TextParser(book, PSettings,ui->TextPage->width(), ui->TextPage->height() - ui->TopBarWidget->height());
    parserThread = new QThread(this);
    BookParse->moveToThread(parserThread);

    connect(this, SIGNAL(destroyed(QObject*)), parserThread, SLOT(quit()));
    parserThread->start();
    ui->TextPage->setHtml(BookParse->getPageFrom());

    ui->TextPage->setMouseTracking(true);
    ui->MainWidget->setMouseTracking(true);

    setMouseTracking(true);
    prev_geometry = geometry();
    TopBarNeedHide = true;
    HidenTimer = 0;

    MenuWidget = new QWidget(this);

    MenuWidget->hide();
    MenuWidget->setGeometry(0, 0, ui->MenuButton->width(),ui->MenuButton->width()*5);

    MenuLayout = new QVBoxLayout();
    MenuWidget->setLayout(MenuLayout);
    MenuLayout->setContentsMargins(0,0,0,0);
    MenuLayout->setSpacing(0);

    _ContentsButton = new QPushButton("cont");
    _ContentsButton->setFixedSize(QSize(ui->MenuButton->width(),ui->MenuButton->width()));
    MenuLayout->addWidget(_ContentsButton, 0);
    connect(_ContentsButton, SIGNAL(clicked(bool)), this, SLOT(ContentsButton_clicked()));

    _FindButton = new QPushButton("find");
    _FindButton->setFixedSize(QSize(ui->MenuButton->width(),ui->MenuButton->width()));
    MenuLayout->addWidget(_FindButton, 1);
    connect(_FindButton, SIGNAL(clicked(bool)), this, SLOT(FindButton_Clicked()));

    _SettingsButton = new QPushButton("sett");
    _SettingsButton->setFixedSize(QSize(ui->MenuButton->width(),ui->MenuButton->width()));
    MenuLayout->addWidget(_SettingsButton, 2);
    connect(_SettingsButton, SIGNAL(clicked(bool)), this, SLOT(SettingsButton_Clicked()));

    _SynchronizationButton = new QPushButton("synch");
    _SynchronizationButton->setFixedSize(QSize(ui->MenuButton->width(),ui->MenuButton->width()));
    MenuLayout->addWidget(_SynchronizationButton, 3);
    connect(_SynchronizationButton, SIGNAL(clicked(bool)), this, SLOT(SynchronizationButton_Clicked()));

    _BackToMainWindowButton = new QPushButton("back");
    _BackToMainWindowButton->setFixedSize(QSize(ui->MenuButton->width(),ui->MenuButton->width()));
    MenuLayout->addWidget(_BackToMainWindowButton, 4);
    connect(_BackToMainWindowButton, SIGNAL(clicked(bool)), this, SLOT(BackToMainWindowButton_Clicked()));

    ProgramSettings = PSettings;
    setStyle(ProgramSettings->getInterfaceStyle());
    ui->Clock->setText(QTime::currentTime().toString("hh:mm"));

    QTimer *clockTimer = new QTimer(this);
    connect(clockTimer, SIGNAL(timeout()), this, SLOT(clockStep()));
    clockTimer->start(1000);
}

ReadingWindow::~ReadingWindow()
{
    delete ui;
    delete ProgramSettings;
    delete MenuWidget;
    delete MenuLayout;
    delete _BackToMainWindowButton;
    delete _ContentsButton;
    delete _SynchronizationButton;
    delete _FindButton;
    delete SettingsPage;
    delete WindowLayout;
    delete SettingsTabsLayout;
    delete MiniWindow;
    delete ProfileButton;
    delete ProgramButton;
    delete ReaderButton;
    delete parserThread;
}


void ReadingWindow::clockStep()
{
    ui->Clock->setText(QDateTime::currentDateTime().toString("hh:mm:ss"));
    if (ProgramSettings->getHideTopBar() == true && this->isMaximized())
        if (!ui->TopBarWidget->isHidden() && MenuWidget->isHidden() && TopBarNeedHide)
        {
            if (HidenTimer == 2)
            {
                ui->TopBarWidget->hide();
                HidenTimer = 0;
            }
            else
            {
                HidenTimer++;
            }
        }
}

void ReadingWindow::on_min_button_clicked()
{
    if(isMinimized())
    {
        normalGeometry() = prev_geometry;
        showNormal();
    }
    else
    {
        prev_geometry = geometry();
        showMinimized();
    }
}

void ReadingWindow::on_full_size_button_clicked()
{
    if(isMaximized())
    {
        normalGeometry() = prev_geometry;
        showNormal();
    }
    else
    {
        prev_geometry = geometry();
        showMaximized();
    }
}

void ReadingWindow::on_exit_button_clicked()
{
    AnswerDialog *answer_window = new AnswerDialog(ui->exit_button->mapToGlobal(QPoint(0,0)).x() - 300 + ui->exit_button->width(),
                                                   ui->exit_button->mapToGlobal(QPoint(0,0)).y() + ui->exit_button->height(),"Exit?",
                                                   ProgramSettings->getInterfaceStyle());
    answer_window->show();

    if (answer_window->exec() == QDialog::Accepted)
    {
        exit(0);
    }
    else
        delete answer_window;
}

void ReadingWindow::on_MenuButton_clicked()
{
    if (MenuWidget->isHidden())
    {
        MenuWidget->move(ui->MenuButton->x(), ui->MenuButton->y() + ui->MenuButton->height());
        MenuWidget->show();
    }
    else
        MenuWidget->hide();

}

void ReadingWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (e->pos().y() <= 50 && ui->TopBarWidget->isHidden() && ProgramSettings->getHideTopBar())
    {
        ui->TopBarWidget->show();
        TopBarNeedHide = false;
    }
    if (e->pos().y() > 50 && !ui->TopBarWidget->isHidden())
        TopBarNeedHide = true;


    if (moving)
    {
        if (!isMaximized())
        {
            move(e->globalX() - lastPoint.x() - 7, e->globalY() - lastPoint.y() - 7);
            if (!MenuWidget->isHidden())
                MenuWidget->move(ui->MenuButton->x(), ui->MenuButton->y() + ui->MenuButton->height());
        }
        else
        {
            prev_geometry.setY(e->globalY());
            normalGeometry() = prev_geometry;
            showNormal();
        }
    }
}

void ReadingWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        if (e->pos().y() <= 20)
        {
            moving = true;
            lastPoint = e->pos();
        }
    }
}

void ReadingWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        if (moving)
            moving = false;
    }
}

void ReadingWindow::ContentsButton_clicked()
{
    MenuWidget->hide();
}

void ReadingWindow::FindButton_Clicked()
{
    MenuWidget->hide();
    Search = new SearchWindow(0, this->height() - 80, ProgramSettings->getInterfaceStyle(), true, this);
    connect(Search, SIGNAL(startSearch(QString,QString)), this, SLOT(StartSearch(QString,QString)));
    connect(Search, SIGNAL(nextResult()), this, SLOT(NextSearchStep()));
    connect(Search, SIGNAL(previousResult()), this, SLOT(PrevSearchStep()));
}

void ReadingWindow::StartSearch(QString key, QString type)
{

}

void ReadingWindow::NextSearchStep()
{

}

void ReadingWindow::PrevSearchStep()
{

}

void ReadingWindow::SettingsButton_Clicked()
{
    MenuWidget->hide();

    MiniWindow = new QDialog(this);
    MiniWindow->setWindowFlags(Qt::FramelessWindowHint);

    int frame, w, h;
    if (this->width() - 100 < 1066)
        w = 1066;
    else
        w = this->width() - 100;
    if (this->height() - 100 < 536)
        h = 536;
    else
        h = this->height() - 100;
    frame = (this->height() - h)/2;

    MiniWindow->setGeometry(frame, frame, w, h);

    WindowLayout = new QVBoxLayout(MiniWindow);
    WindowLayout->setContentsMargins(0,0,0,0);
    WindowLayout->setSpacing(0);

    SettingsPage = new settingslayout();
    SettingsPage->setSettingsData(ProgramSettings);

    SettingsTabsLayout = new QHBoxLayout();
    SettingsTabsLayout->setContentsMargins(0,0,0,0);

    WindowLayout->addLayout(SettingsTabsLayout, 0);
    WindowLayout->addWidget(SettingsPage, 1);

    ProfileButton = new QPushButton("Profile", MiniWindow);
    ProgramButton = new QPushButton("Program", MiniWindow);
    ReaderButton = new QPushButton("Reader", MiniWindow);
    SettingsExitButton = new QPushButton(MiniWindow);

    int wSize = (w - 30)/3;
    ProfileButton->setFixedSize(wSize, 30);
    ProgramButton->setFixedSize(wSize, 30);
    ReaderButton->setFixedSize(wSize, 30);
    SettingsExitButton->setFixedSize(30, 30);


    SettingsTabsLayout->addWidget(ProfileButton, 0);
    SettingsTabsLayout->addWidget(ProgramButton, 1);
    SettingsTabsLayout->addWidget(ReaderButton, 2);
    SettingsTabsLayout->addWidget(SettingsExitButton, 3);

    setReaderSettingsExitButton(styles, ProgramSettings->getInterfaceStyle());
    SettingsExitButton->setStyleSheet(styles[0]);

    setBackgroundWindowColor(styles, ProgramSettings->getInterfaceStyle());
    MiniWindow->setStyleSheet(styles[1]);

    setTabButtonsStyle(styles, ProgramSettings->getInterfaceStyle());
    ProfileButton->setStyleSheet(styles[0]);
    ProgramButton->setStyleSheet(styles[1]);
    ReaderButton->setStyleSheet(styles[0]);

    connect(ProfileButton, SIGNAL(clicked(bool)), SettingsPage, SLOT(showProfile()));
    connect(ProfileButton, SIGNAL(clicked(bool)), this, SLOT(settings_profile_clicked()));

    connect(ProgramButton, SIGNAL(clicked(bool)), SettingsPage, SLOT(showProgram()));
    connect(ProgramButton, SIGNAL(clicked(bool)), this, SLOT(settings_program_clicked()));

    connect(ReaderButton, SIGNAL(clicked(bool)), SettingsPage, SLOT(showReader()));
    connect(ReaderButton, SIGNAL(clicked(bool)), this, SLOT(settings_reader_clicked()));

    connect(SettingsExitButton, SIGNAL(clicked(bool)), MiniWindow, SLOT(close()));

    SettingsPage->show();
    MiniWindow->show();
}

void ReadingWindow::settings_profile_clicked()
{
    ProfileButton->setStyleSheet(styles[1]);
    changeSettingsTab(0);
}
void ReadingWindow::settings_program_clicked()
{
    ProgramButton->setStyleSheet(styles[1]);
    changeSettingsTab(1);
}
void ReadingWindow::settings_reader_clicked()
{
    ReaderButton->setStyleSheet(styles[1]);
    changeSettingsTab(2);
}

void ReadingWindow::changeSettingsTab(int i)
{
    switch (SettingsTab) {
    case 0:
        ProfileButton->setStyleSheet(styles[0]);
        break;
    case 1:
        ProgramButton->setStyleSheet(styles[0]);
        break;
    case 2:
        ReaderButton->setStyleSheet(styles[0]);
        break;
    default:
        break;
    }
    SettingsTab = i;
}

void ReadingWindow::SynchronizationButton_Clicked()
{
    MenuWidget->hide();

    MiniWindow = new QDialog(this);
    MiniWindow->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);

    int frame, w, h;
    if (this->width() - 100 < 1066)
        w = 1066;
    else
        w = this->width() - 100;
    if (this->height() - 100 < 536)
        h = 536;
    else
        h = this->height() - 100;
    frame = (this->height() - h)/2;

    MiniWindow->setGeometry(this->x() + frame, this->y() + frame, w, h);

    WindowLayout = new QVBoxLayout(MiniWindow);
    WindowLayout->setContentsMargins(0,0,0,0);
    WindowLayout->setSpacing(0);

    SynchronizationPage = new synchronizationlayout(MiniWindow);
    SynchronizationPage->setSettingsData(ProgramSettings);

    WindowLayout->addWidget(SynchronizationPage, 0);
    setBackgroundWindowColor(styles, ProgramSettings->getInterfaceStyle());
    MiniWindow->setStyleSheet(styles[1]);

    SynchronizationPage->show();
    MiniWindow->show();
}

void ReadingWindow::BackToMainWindowButton_Clicked()
{
    emit showMainWindow();
    this->close();
}

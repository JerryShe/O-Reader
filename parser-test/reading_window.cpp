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
#include <QKeyEvent>
#include <QWindow>
#include <QThread>

#include <QDebug>




void ReadingWindow::setStyle(QString currentStyle)
{
    QString styleSheets[8];

    setTopBarBackgroundColor(styleSheets, currentStyle);
    ui->TopBarWidget->setStyleSheet(styleSheets[0]);

    setWindowTopButtonsStyle(styleSheets, currentStyle);
    ui->min_button->setStyleSheet(styleSheets[0]);
    ui->full_size_button->setStyleSheet(styleSheets[1]);

    setExitButtonStyle(styleSheets, currentStyle);
    ui->exit_button->setStyleSheet(styleSheets[0]);

    setBackgroundWindowColor(styleSheets, currentStyle);
    ui->MainWidget->setStyleSheet(styleSheets[0]);

    setReaderWindowStyle(styleSheets, currentStyle);
    ui->Clock->setStyleSheet(styleSheets[1]);
    ui->Progress->setStyleSheet(styleSheets[1]);
    ui->BookName->setStyleSheet(styleSheets[1]);
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
    show();
    BookParse = new FB2TextParser(book, PSettings,ui->TextPage->width(), ui->TextPage->height());
    parserThread = new QThread(this);
    BookParse->moveToThread(parserThread);

    connect(this, SIGNAL(windowWasResized()), this, SLOT(reprintResizedText()));
    connect(this, SIGNAL(destroyed(QObject*)), parserThread, SLOT(quit()));
    parserThread->start();
    ui->TextPage->setHtml(BookParse->getPageForward());
    updateProgress();
    ui->BookName->setText(book.getAuthorName() + ": " + book.getTitle());

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

    ui->TextPage->installEventFilter(this);
    ui->TopBarWidget->installEventFilter(this);
}

void ReadingWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}

ReadingWindow::~ReadingWindow()
{
    delete ui;
    delete MenuWidget;
    delete MenuLayout;
    delete _BackToMainWindowButton;
    delete _ContentsButton;
    delete _SynchronizationButton;
    delete _FindButton;
    delete _SettingsButton;
    delete SettingsPage;
    delete SynchronizationPage;
    delete Search;
    delete MiniWindow;
    delete parserThread;
    delete BookParse;
}


void ReadingWindow::clockStep()
{
    ui->Clock->setText(QDateTime::currentDateTime().toString("hh:mm:ss"));
    if (ProgramSettings->getHideTopBar() == true && this->isMaximized())
        if (!ui->TopBarWidget->isHidden() && MenuWidget->isHidden() && TopBarNeedHide)
        {
            if (HidenTimer == 4)
            {
                ui->TopBarWidget->hide();
                reprintResizedText();
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

bool ReadingWindow::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
        case QEvent::MouseMove:
        {
            QMouseEvent* MouseMoveEvent = static_cast<QMouseEvent*>(event);
            if (ProgramSettings->getHideTopBar())
            {
                if (MouseMoveEvent->pos().y() <= 50 && ui->TopBarWidget->isHidden())
                {
                    ui->TopBarWidget->show();
                    reprintResizedText();
                    TopBarNeedHide = false;
                }
                if (MouseMoveEvent->pos().y() > 50 && !ui->TopBarWidget->isHidden())
                    TopBarNeedHide = true;
            }
            if (moving)
            {
                if (!isMaximized())
                {
                    move(MouseMoveEvent->globalX() - lastPoint.x() - 7, MouseMoveEvent->globalY() - lastPoint.y() - 7);
                    if (!MenuWidget->isHidden())
                        MenuWidget->move(ui->MenuButton->x(), ui->MenuButton->y() + ui->MenuButton->height());
                }
                else
                {
                    prev_geometry.setY(MouseMoveEvent->globalY());
                    normalGeometry() = prev_geometry;
                    showNormal();
                }
            }
            break;
        }

        case QEvent::KeyPress:
        {
            QKeyEvent *KeyEvent = static_cast<QKeyEvent*>(event);
            if (KeyEvent->key() == ProgramSettings->getFForwardKey() || KeyEvent->key() == ProgramSettings->getSForwardKey())
            {
                ui->TextPage->setHtml(BookParse->getPageForward());
                updateProgress();
            }
            else
            if (KeyEvent->key() == ProgramSettings->getFBackwardKey() || KeyEvent->key() == ProgramSettings->getSBackwardKey())
            {
                ui->TextPage->setHtml(BookParse->getPageBackward());
                updateProgress();
            }
            break;
        }

        case QEvent::Wheel:
        {
            if (ProgramSettings->getTurnByWheel() == true)
            {
                QWheelEvent* Wheel = static_cast<QWheelEvent*>(event);
                if (Wheel->delta() < 0)
                {
                    ui->TextPage->setHtml(BookParse->getPageForward());
                    updateProgress();
                }
                else if (Wheel->delta() > 0)
                {
                    ui->TextPage->setHtml(BookParse->getPageBackward());
                    updateProgress();
                }
            }
            break;
        }

        case QEvent::MouseButtonPress:
        {
            QMouseEvent* MousePressEvent = static_cast<QMouseEvent*>(event);
            if(MousePressEvent->button() == Qt::LeftButton)
                if (MousePressEvent->pos().y() <= 20)
                {
                    moving = true;
                    lastPoint = MousePressEvent->pos();
                }
            break;
        }

        case QEvent::MouseButtonRelease:
        {
            QMouseEvent* MouseReleaseEvent = static_cast<QMouseEvent*>(event);
            if (MouseReleaseEvent->button() == Qt::LeftButton)
            {
                if (moving)
                    moving = false;
            }
            break;
        }

        case QEvent::Resize:
        {
            emit windowWasResized();
            break;
        }

        default:
            break;
    }

    return true;
}

void ReadingWindow::reprintResizedText()
{
    ui->TextPage->setHtml(BookParse->updatePage(ui->TextPage->width(), ui->TextPage->height()));
}

void ReadingWindow::updateProgress()
{
    ui->Progress->setText(QString::number(floor(BookParse->getProgress()*10)/10) + "%");
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

void ReadingWindow::reprintNewSettText()
{
    ui->TextPage->setHtml(BookParse->updateSettings(ui->TextPage->width(), ui->TextPage->height()));
}

void ReadingWindow::SettingsButton_Clicked()
{
    MenuWidget->hide();

    MiniWindow = new QDialog(this);
    QString style[2];
    setBackgroundWindowColor(style, ProgramSettings->getInterfaceStyle());
    setStyleSheet(style[1]);

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
    MiniWindow->setContentsMargins(0,0,0,0);
    settingsLayout = new QVBoxLayout(MiniWindow);
    MiniWindow->setLayout(settingsLayout);
    settingsLayout->setContentsMargins(0,0,0,0);

    SettingsPage = new settingslayout();
    SettingsPage->setSettingsData(ProgramSettings);
    settingsLayout->addWidget(SettingsPage);
    SettingsPage->addExitButton();
    connect(SettingsPage, SIGNAL(settingsClosed()), MiniWindow, SLOT(close()));
    connect(SettingsPage, SIGNAL(settingsChanged()), this, SLOT(reprintNewSettText()));

    MiniWindow->show();
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


    MiniWindow->show();
}

void ReadingWindow::BackToMainWindowButton_Clicked()
{
    emit showMainWindow();
    this->close();
}



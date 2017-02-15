
#include "window_manager.h"

#include "main_window.h"
#include "login_window.h"
#include "reading_window.h"

#include <QApplication>
#include <QTranslator>
#include <QDesktopWidget>
#include <QDir>

//////////////-
#include "books.h"

WindowManager::WindowManager(QWidget *parent) : QMainWindow(parent)
{
    QString resoursesFolderPath = "LibraryResources";
    if ( ! QDir(resoursesFolderPath).exists()==true)
        QDir().mkdir(resoursesFolderPath);
    if ( ! QDir("Downloaded books").exists()==true)
        QDir().mkdir("Downloaded books");


    setMouseTracking(true);
    setWindowFlags(Qt::CustomizeWindowHint);

    this->setGeometry(qApp->desktop()->width()/6, qApp->desktop()->height()/6, qApp->desktop()->width()/1.5, qApp->desktop()->height()/1.5);
    prev_geometry = geometry();

    HandlerThread = new QThread(this);
    connect(this, SIGNAL(destroyed(QObject*)), HandlerThread, SLOT(quit()));

    ProgramSettings = Settings::getSettings();
    UserSynchro = Synchronization::getSynchronization();
    LibHandler = LibraryHandler::getLibraryHandler();


    ProgramSettings->moveToThread(HandlerThread);
    UserSynchro->moveToThread(HandlerThread);
    LibHandler->moveToThread(HandlerThread);

    HandlerThread->start();

    ProgramSettings->loadSettings();

    UserSynchro->loadLog();

    LibHandler->loadBookList();

    LanguageTranslator = new QTranslator(this);

    bool done = false;
    if (ProgramSettings->getCurrentLanguage() == "Русский")
        done = LanguageTranslator->load("ru.qm", "LibraryResources/Languages");
    if (ProgramSettings->getCurrentLanguage() == "English")
        done = LanguageTranslator->load("en.qm", "LibraryResources/Languages");

    if (done)
        qApp->installTranslator(LanguageTranslator);

    ProgramSettings->setTranslator(LanguageTranslator);

    LastWindow = 0;

    this->layout()->setContentsMargins(0,0,0,0);


    windowMachine = new QStateMachine(this);
    loginState = new QState(windowMachine);
    mainState = new QState(windowMachine);
    readingState = new QState(windowMachine);

    loginState->addTransition(this, SIGNAL(showMainWindow()), mainState);
    mainState->addTransition(this, SIGNAL(showLoginWindow()), loginState);
    mainState->addTransition(this, SIGNAL(showReadingWindow()), readingState);
    readingState->addTransition(this, SIGNAL(showMainWindow()), mainState);

    connect(loginState, SIGNAL(entered()), this, SLOT(showLogin()));
    connect(mainState, SIGNAL(entered()), this, SLOT(showMain()));
    connect(mainState, SIGNAL(exited()), this, SLOT(hideMain()));
    connect(readingState, SIGNAL(entered()), this, SLOT(showReading()));


    switch (UserSynchro->getLastOpenedWindow()) {
    case 0:
        windowMachine->setInitialState(loginState);
        break;

    case 1:
/// добавить залогинивание
        windowMachine->setInitialState(mainState);
        break;

    case 2:
/// добавить залогинивание
        windowMachine->setInitialState(readingState);
        break;

    default:
        windowMachine->setInitialState(loginState);
        break;
    }


    windowMachine->start();
}



void WindowManager::showLogin()
{
    loginWindow = new LoginWindow(this);
    this->setCentralWidget(loginWindow);

    if (LastWindow != 0)
        delete LastWindow;
    LastWindow = loginWindow;

    connect(loginWindow, SIGNAL(showMainWindow()), this, SIGNAL(showMainWindow()));

    connect(loginWindow, SIGNAL(closeWindow()), this, SLOT(closeWindow()));
    connect(loginWindow, SIGNAL(showWindowMinimazed()), this, SLOT(showWindowMinimazed()));
    connect(loginWindow, SIGNAL(showWindowMaximazed()), this, SLOT(showWindowMaximazed()));
    this->show();

    UserSynchro->setLastOpenedWindow(0);

}

void WindowManager::showMain()
{
    mainWindow = new MainWindow(this);
    this->setCentralWidget(mainWindow);

    LibHandler->setLibraryWidget(mainWindow->getLibraryWidget());


    if (LastWindow != 0)
        delete LastWindow;
    LastWindow = mainWindow;

    connect(mainWindow, SIGNAL(showLoginWindow()), this, SIGNAL(showLoginWindow()));
    connect(mainWindow, SIGNAL(showReadingWindow()), this, SIGNAL(showReadingWindow()));

    connect(mainWindow, SIGNAL(closeWindow()), this, SLOT(closeWindow()));
    connect(mainWindow, SIGNAL(showWindowMinimazed()), this, SLOT(showWindowMinimazed()));
    connect(mainWindow, SIGNAL(showWindowMaximazed()), this, SLOT(showWindowMaximazed()));
    this->show();

    UserSynchro->setLastOpenedWindow(1);

}

void WindowManager::hideMain()
{
    LibHandler->setLibraryWidget(0);
}


void WindowManager::showReading()
{
    if (LibHandler->getLastOpenedBook() == 0)
        return;

    readingWindow = new ReadingWindow(this, LibHandler->getLastOpenedBook());

    if (LastWindow != 0)
        delete LastWindow;
    LastWindow = readingWindow;

    this->setCentralWidget(readingWindow);
    this->show();
    readingWindow->show();

    connect(readingWindow, SIGNAL(showMainWindow()), this, SIGNAL(showMainWindow()));

    connect(readingWindow, SIGNAL(closeWindow()), this, SLOT(closeWindow()));
    connect(readingWindow, SIGNAL(showWindowMinimazed()), this, SLOT(showWindowMinimazed()));
    connect(readingWindow, SIGNAL(showWindowMaximazed()), this, SLOT(showWindowMaximazed()));

    readingWindow->startReading();

    UserSynchro->setLastOpenedWindow(2);

}


void WindowManager::closeWindow()
{
    if(!LibHandler->saveBookList())
    {

    }
    if(!ProgramSettings->saveSettings())
    {

    }
    if(!UserSynchro->saveLog())
    {

    }


    delete LastWindow;
    HandlerThread->quit();
    exit(0);
}


void WindowManager::mouseMoveEvent(QMouseEvent *e)
{
    if (moving)
    {
        if (!isMaximized())
        {
            move(e->globalX() - lastPoint.x() - 7, e->globalY() - lastPoint.y() - 7);
        }
        else
        {
            prev_geometry.setY(e->globalY());
            normalGeometry() = prev_geometry;
            showNormal();
        }
    }
}

void WindowManager::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        if (e->pos().y() <= 50 && e->pos().y() > resizingFrame)
        {
            moving = true;
            lastPoint = e->pos();
        }
    }
}

void WindowManager::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        if (moving)
            moving = false;
    }
}

void WindowManager::showWindowMinimazed()
{
    if( isMinimized())
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

void WindowManager::showWindowMaximazed()
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

WindowManager::~WindowManager()
{
    delete windowMachine;
}

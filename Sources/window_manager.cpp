
#include "window_manager.h"

#include "main_window.h"
#include "login_window.h"
#include "reading_window.h"

#include <QApplication>
#include <QTranslator>
#include <QDesktopWidget>
#include <QDir>
#include <QMessageBox>



WindowManager::WindowManager(QWidget *parent) : QMainWindow(parent)
{
    LastWindow = 0;
    loadingLabel = 0;
    moving = false;

    QString resoursesFolderPath = "LibraryResources";
    if ( ! QDir(resoursesFolderPath).exists()==true)
        QDir().mkdir(resoursesFolderPath);
    //if ( ! QDir("Downloaded books").exists()==true)
       // QDir().mkdir("Downloaded books");


    HandlerThread = new QThread(this);
    connect(this, SIGNAL(destroyed(QObject*)), HandlerThread, SLOT(quit()));

    ProgramSettings = Settings::getSettings();
    UserSynchro = Synchronization::getSynchronization();
    LibHandler = LibraryHandler::getLibraryHandler();
    clientHandler = ClientHandler::getClientHandler();
    deviceSettings = DeviceSettings::getDeviceSettings();


    ProgramSettings->moveToThread(HandlerThread);
    deviceSettings->moveToThread(HandlerThread);
    UserSynchro->moveToThread(HandlerThread);
    LibHandler->moveToThread(HandlerThread);
    clientHandler->moveToThread(HandlerThread);

    HandlerThread->start();


    setMouseTracking(true);
    setWindowFlags(Qt::CustomizeWindowHint);

    connect(LibHandler, SIGNAL(showLoadImage(QString)), this, SLOT(showLoadingImage(QString)));
    connect(LibHandler, SIGNAL(hideLoadImage()), this, SLOT(hideLoadingImage()));

    ProgramSettings->loadSettings();
    deviceSettings->loadDeviceSettings();
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


    switch (UserSynchro->getLastOpenedWindow())
    {
    case 0:
        windowMachine->setInitialState(loginState);
        break;

    case 1:
        if (clientHandler->autoLoginOnServer())
            windowMachine->setInitialState(mainState);
        else
            windowMachine->setInitialState(loginState);
        break;

    case 2:
        if (clientHandler->autoLoginOnServer())
        {
            //TODO: сделать красиво
            if (LibHandler->getLastOpenedBook() == 0)
            {
                windowMachine->setInitialState(mainState);
                break;
            }

            QFile bookFile(LibHandler->getLastOpenedBook()->getFileName());
            if (!bookFile.exists())
            {
                QMessageBox::information(0, tr("Error!"), tr("Book file lost :( \nReturning to library..."));
                windowMachine->setInitialState(mainState);
            }
            else
                windowMachine->setInitialState(readingState);
        }
        else
            windowMachine->setInitialState(loginState);
        break;

    default:
        windowMachine->setInitialState(loginState);
        break;
    }


    windowMachine->start();

    prev_geometry = deviceSettings->getWindowGeometry();
    this->setGeometry(deviceSettings->getWindowGeometry());

    if (deviceSettings->windowWasMaximized())
        this->setWindowState(Qt::WindowFullScreen);
    else
        this->setWindowState(Qt::WindowNoState);

    qDebug()<<QTime::currentTime()<<" create windowManager";
}


void WindowManager::saveProgramData()
{
    if (!this->isFullScreen())
        prev_geometry = geometry();
    deviceSettings->setWindowGeometry(this->isFullScreen(), prev_geometry);

    deviceSettings->saveDeviceSettings();
    ProgramSettings->saveSettings();
    UserSynchro->saveLog();
    LibHandler->saveBookList();
}


void WindowManager::showLogin()
{
    loginWindow = new LoginWindow(this);
    this->setCentralWidget(loginWindow);

    if (LastWindow != 0)
    {
        delete LastWindow;
        saveProgramData();
    }
    LastWindow = loginWindow;

    connect(loginWindow, SIGNAL(showMainWindow()), this, SIGNAL(showMainWindow()));

    connect(loginWindow, SIGNAL(closeWindow()), this, SLOT(closeWindow()));
    connect(loginWindow, SIGNAL(showWindowMinimazed()), this, SLOT(showWindowMinimazed()));
    connect(loginWindow, SIGNAL(showWindowMaximazed()), this, SLOT(showWindowMaximazed()));
    this->show();

    UserSynchro->setLastOpenedWindow(0);

    qDebug()<<"showing login window";
}


void WindowManager::showMain()
{
    mainWindow = new MainWindow(this);

    this->setCentralWidget(mainWindow);
    LibHandler->setLibraryWidget(mainWindow->getLibraryWidget());

    this->show();
    mainWindow->show();

    if (LastWindow != 0)
    {
        saveProgramData();
        delete LastWindow;
    }
    LastWindow = mainWindow;

    connect(mainWindow, SIGNAL(showLoginWindow()), this, SIGNAL(showLoginWindow()));
    connect(mainWindow, SIGNAL(showReadingWindow()), this, SIGNAL(showReadingWindow()));

    connect(mainWindow, SIGNAL(closeWindow()), this, SLOT(closeWindow()));
    connect(mainWindow, SIGNAL(showWindowMinimazed()), this, SLOT(showWindowMinimazed()));
    connect(mainWindow, SIGNAL(showWindowMaximazed()), this, SLOT(showWindowMaximazed()));


    UserSynchro->setLastOpenedWindow(1);

    qDebug()<<"showing main window";
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
    connect(readingWindow, SIGNAL(closeWindow()), this, SLOT(closeWindow()));

    this->setCentralWidget(readingWindow);

    this->show();
    readingWindow->show();

    readingWindow->startReading();


    if (LastWindow != 0)
    {
        delete LastWindow;
        saveProgramData();
    }


    LastWindow = readingWindow;

    connect(readingWindow, SIGNAL(showMainWindow()), this, SIGNAL(showMainWindow()));

    connect(readingWindow, SIGNAL(showWindowMinimazed()), this, SLOT(showWindowMinimazed()));
    connect(readingWindow, SIGNAL(showWindowMaximazed()), this, SLOT(showWindowMaximazed()));

    UserSynchro->setLastOpenedWindow(2);

    qDebug()<<"showing reading window";
}


void WindowManager::closeWindow()
{
    if (!this->isFullScreen())
        prev_geometry = geometry();
    deviceSettings->setWindowGeometry(this->isFullScreen(), prev_geometry);

    if(!LibHandler->saveBookList())
    {

    }
    if(!ProgramSettings->saveSettings())
    {

    }
    if(!deviceSettings->saveDeviceSettings())
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
        if (!isFullScreen())
        {
            move(prev_geometry.topLeft() + QPoint(e->globalX() - lastClickPoint.x() - 7, e->globalY() - lastClickPoint.y() - 7));
        }
        else
        {
            showNormal();
            setGeometry(prev_geometry);
            move(e->globalX() - prev_geometry.width()/2, e->globalY());

            prev_geometry = geometry();
            lastClickPoint = e->globalPos();
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
            lastClickPoint = e->globalPos();

            if (!isFullScreen())
                prev_geometry = geometry();
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
    if(isMinimized())
    {
        showNormal();
        setGeometry(prev_geometry);
    }
    else
    {
        prev_geometry = geometry();
        showMinimized();
    }
}


void WindowManager::showWindowMaximazed()
{
    if(isFullScreen())
    {
        showNormal();
        setGeometry(prev_geometry);
    }
    else
    {
        prev_geometry = geometry();
        showFullScreen();
    }
}


void WindowManager::showLoadingImage(QString imageFile)
{
    if (!imageFile.isEmpty())
    {
        QImage img(imageFile);
        if (!img.isNull())
        {
            loadingLabel = new QLabel(this);

            loadingLabel->setFixedSize(img.size());
            loadingLabel->move(this->width()/2 - img.width()/2, this->height()/2 - img.height()/2);

            loadingLabel->setPixmap(QPixmap::fromImage(img));
            loadingLabel->show();
        }
    }
}


void WindowManager::hideLoadingImage()
{
    if (loadingLabel != 0)
    {
        delete loadingLabel;
        loadingLabel = 0;
    }
}


WindowManager::~WindowManager()
{
    delete windowMachine;
}

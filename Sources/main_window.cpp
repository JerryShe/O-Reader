#include "main_window.h"
#include "ui_mainwindow.h"
#include "answer_dialog.h"
#include "styles.h"
#include "genresmap.h"
#include "synchronization.h"
#include "settings.h"

#include <QSizePolicy>
#include <QKeyEvent>
#include <QThread>
#include <QDir>
#include <QProcess>

#if defined(Q_OS_LINUX)
    #define CurrentOS 0
#elif defined(Q_OS_WIN)
    #define CurrentOS 1
#endif

#include <QDebug>

void MainWindow::setStyle()
{
    QString currentStyle = ProgramSettings->getInterfaceStyle();

    setTopBarBackgroundColor(styleSheets, currentStyle);
    ui->TopBarWidget->setStyleSheet(styleSheets[0]);

    setWindowTopButtonsStyle(styleSheets, currentStyle);
    ui->min_button->setStyleSheet(styleSheets[0]);
    ui->full_size_button->setStyleSheet(styleSheets[1]);

    setExitButtonStyle(styleSheets, currentStyle);
    ui->exit_button->setStyleSheet(styleSheets[0]);

    setBackgroundWindowColor(styleSheets, currentStyle);
    ui->MainWidget->setStyleSheet(styleSheets[0]);

    setMenusButtonsStyle(styleSheets, currentStyle);

    tabSwitcher->setButtonStyleSheet(0, styleSheets[4], styleSheets[0]);
    tabSwitcher->setButtonStyleSheet(1, styleSheets[5], styleSheets[1]);
    tabSwitcher->setButtonStyleSheet(2, styleSheets[6], styleSheets[2]);

    ui->Logout->setStyleSheet(styleSheets[3]);

    ui->LeftExpandingWidget->setStyleSheet(styleSheets[8]);
}

MainWindow::MainWindow(QTranslator *translator, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    resoursesFolderPath = "LibraryResources";
    if ( ! QDir(resoursesFolderPath).exists()==true)
        QDir().mkdir(resoursesFolderPath);
    if ( ! QDir("Downloaded books").exists()==true)
        QDir().mkdir("Downloaded books");

    HandlerThread = new QThread(this);
    connect(this, SIGNAL(destroyed(QObject*)), HandlerThread, SLOT(quit()));

    UserActions = Synchronization::getSynchronization();
    ProgramSettings = settings::getSettings();
    ProgramSettings->setTranslator(translator);

    ProgramSettings->moveToThread(HandlerThread);
    UserActions->moveToThread(HandlerThread);
    HandlerThread->start();

    ProgramSettings->loadSettings();

    ui->setupUi(this);

    ui->SettingsWidget->hide();
    prev_geometry = geometry();

    ui->MainWidget->setAttribute(Qt::WA_MouseTracking);
    setMouseTracking(true);

    connect(ui->LibraryWidget, SIGNAL(showBookPage(int)), this, SLOT(showBookPage(int)));

    ui->SettingsWidget->setSettingsData();

    tabSwitcher = new QTabSwitcher;

    tabSwitcher->addTab(ui->LibraryWidget, ui->Library);
    tabSwitcher->addTab(ui->SettingsWidget, ui->Settings);
    tabSwitcher->addTab(ui->SynchronizationWidget, ui->Synchronization);

    setStyle();

    tabSwitcher->start(0);
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete readingWindow;
    delete HandlerThread;
}

void MainWindow::showBookPage(const int index)
{
    page = new BookPage(ui->LibraryWidget->getBookByIndex(index), ProgramSettings->getInterfaceStyle(), this);
    connect(page, SIGNAL(startReading(int)), this, SLOT(startReading(int)));
    connect(page, SIGNAL(deleteBook(int)), ui->LibraryWidget, SLOT(deleteBook(int)));
}

void MainWindow::startReading(const int index)
{
    readingWindow = new ReadingWindow(ui->LibraryWidget->getBookByIndex(index));

    if (CurrentOS)
        readingWindow->setWindowFlags(Qt::CustomizeWindowHint);
    else
        readingWindow->setWindowFlags(Qt::Dialog);

    connect(readingWindow, SIGNAL(showMainWindow(bool)), this, SLOT(showWindow(bool)));

    readingWindow->show();
    this->hide();
}

void MainWindow::showWindow(bool closeType)
{
    ui->LibraryWidget->saveBookList();
    readingWindow->close();
    if (closeType)
        exit(0);
    else
        this->show();
}

void MainWindow::on_exit_button_clicked()
{
    AnswerDialog *answer_window = new AnswerDialog(ui->exit_button->mapToGlobal(QPoint(ui->exit_button->width() - 300, ui->exit_button->height())),
                                                   QObject::tr("Exit?"),
                                                   ProgramSettings->getInterfaceStyle(),
                                                   this);
    answer_window->show();

    if (answer_window->exec() == QDialog::Accepted)
    {
        delete answer_window;
        exit(0);
    }
    else
        delete answer_window;
}

void MainWindow::on_full_size_button_clicked()
{
    if( isMaximized())
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

void MainWindow::on_min_button_clicked()
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

void MainWindow::mouseMoveEvent(QMouseEvent *e)
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

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        if (e->pos().y() <= 30 && e->pos().y() > resizingFrame)
        {
            moving = true;
            lastPoint = e->pos();
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        if (moving)
            moving = false;
    }
}

void MainWindow::on_Logout_clicked()
{
    ui->Logout->setStyleSheet(styleSheets[7]);

    AnswerDialog *answer_window = new AnswerDialog(ui->Logout->mapToGlobal(QPoint(ui->Logout->width(),0)),
                                                   QObject::tr("Logout?"),
                                                   ProgramSettings->getInterfaceStyle(),
                                                   this);
    answer_window->show();

    if (answer_window->exec() == QDialog::Accepted)
    {
        ui->Logout->setStyleSheet(styleSheets[3]);
        QProcess::startDetached(QApplication::applicationFilePath(), QStringList(), QApplication::applicationDirPath());
        delete answer_window;
        MainWindow::close();
    }
    else
        delete answer_window;
    ui->Logout->setStyleSheet(styleSheets[3]);
}

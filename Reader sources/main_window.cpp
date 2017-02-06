#include "main_window.h"
#include "ui_mainwindow.h"
#include "answer_dialog.h"
#include "books.h"
#include "styles.h"
#include "book_or_folder.h"
#include "book_page.h"
#include "genresmap.h"
#include "synchronization.h"
#include "settings.h"
#include "library_layout.h"

#include <QFileDialog>
#include <QSizePolicy>
#include <QKeyEvent>
#include <QProcess>
#include <QListWidget>
#include <QThread>

#if defined(Q_OS_LINUX)
    #define CurrentOS 0
#elif defined(Q_OS_WIN)
    #define CurrentOS 1
#endif

#include <QDebug>

void MainWindow::libraryButtonsHide()
{
    for (int i = 0; i < ui->LibraryButtons->count(); i++)
        ui->LibraryButtons->itemAt(i)->widget()->hide();
}
void MainWindow::libraryButtonsShow()
{
    for (int i = 0; i < ui->LibraryButtons->count(); i++)
        ui->LibraryButtons->itemAt(i)->widget()->show();
}

void MainWindow::setWindowStyle(QString currentStyle)
{
    setTopBarBackgroundColor(styleSheets, currentStyle);
    ui->TopBarWidget->setStyleSheet(styleSheets[0]);

    setLibraryLayoutButtons(styleSheets, currentStyle);
    ui->_ChangeViewMode->setStyleSheet(styleSheets[0]);
    ui->_Upscale->setStyleSheet(styleSheets[1]);
    ui->_Downscale->setStyleSheet(styleSheets[2]);

    setWindowTopButtonsStyle(styleSheets, currentStyle);
    ui->min_button->setStyleSheet(styleSheets[0]);
    ui->full_size_button->setStyleSheet(styleSheets[1]);

    setExitButtonStyle(styleSheets, currentStyle);
    ui->exit_button->setStyleSheet(styleSheets[0]);

    setBackgroundWindowColor(styleSheets, currentStyle);
    ui->MainWidget->setStyleSheet(styleSheets[0]);

    setTabButtonsStyle(tabsStyleSheets, currentStyle);
    ui->_Find->setStyleSheet(tabsStyleSheets[4]);
    ui->_AddBooks->setStyleSheet(tabsStyleSheets[0]);
    ui->_Delete->setStyleSheet(tabsStyleSheets[0]);
    ui->_Group->setStyleSheet(tabsStyleSheets[2]);
    ui->_Sort->setStyleSheet(tabsStyleSheets[2]);
    ui->_SortBox->setStyleSheet(tabsStyleSheets[3]);
    ui->_GroupBox->setStyleSheet(tabsStyleSheets[3]);

    setMenusButtonsStyle(styleSheets, currentStyle);
    ui->Settings->setStyleSheet(styleSheets[1]);
    ui->Synchronization->setStyleSheet(styleSheets[2]);
    ui->Logout->setStyleSheet(styleSheets[3]);
    ui->Library->setStyleSheet(styleSheets[4]);
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
    ui->_Group->hide();
    ui->_GroupBox->hide();

    LibraryLayout = new librarylayout();
    LibHandler = new LibraryHandler(LibraryLayout);
    LibHandler->moveToThread(HandlerThread);

    ui->TabsLayout->addWidget(LibraryLayout, 0);
    if (ProgramSettings->getLibraryReprezentation())
    {
        LibraryLayout->changeViewMod();
        ui->_ChangeViewMode->setChecked(true);
    }
    LibHandler->loadBookList();

    MainWindow::setWindowStyle(ProgramSettings->getInterfaceStyle());
    ui->SettingsLayout->hide();
    MainWindow::prev_geometry = MainWindow::geometry();

    ui->MainWidget->setAttribute(Qt::WA_MouseTracking);
    MainWindow::setMouseTracking(true);

    ui->_SortBox->setView(new QListView());
    ui->_GroupBox->setView(new QListView());

    connect(LibraryLayout, SIGNAL(showBookPage(int)), this, SLOT(showBookPage(int)));

    ui->SettingsLayout->setSettingsData();
    LibraryLayout->setSettingsData();
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
        ui->_Group->hide();
        ui->_GroupBox->hide();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete LibraryLayout;
    delete readingWindow;
    delete searchWindow;
    delete page;
    delete HandlerThread;
    delete LibHandler;
}

void MainWindow::showBookPage(const int index)
{
    page = new BookPage(LibHandler->getBookByIndex(index), ProgramSettings->getInterfaceStyle(), this);
    connect(page, SIGNAL(startReading(int)), this, SLOT(startReading(int)));
    connect(page, SIGNAL(deleteBook(int)), LibHandler, SLOT(deleteBook(int)));
}

void MainWindow::startReading(const int index)
{
    readingWindow = new ReadingWindow(LibHandler->getBookByIndex(index));

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
    LibHandler->saveBookList();
    readingWindow->close();
    if (closeType)
        exit(0);
    else
        this->show();
}

void MainWindow::on_exit_button_clicked()
{
    ui->_Find->setChecked(false);
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
    ui->_Find->setChecked(false);
    if( MainWindow::isMaximized())
    {
        MainWindow::normalGeometry() = MainWindow::prev_geometry;
        MainWindow::showNormal();
    }
    else
    {
        MainWindow::prev_geometry = MainWindow::geometry();
        MainWindow::showMaximized();
    }
}

void MainWindow::on_min_button_clicked()
{
    ui->_Find->setChecked(false);
    if( MainWindow::isMinimized())
    {
        MainWindow::normalGeometry() = MainWindow::prev_geometry;
        MainWindow::showNormal();
    }
    else
    {
        MainWindow::prev_geometry = MainWindow::geometry();
        MainWindow::showMinimized();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (MainWindow::moving)
    {
        if (!MainWindow::isMaximized())
        {
            move(e->globalX() - lastPoint.x() - 7, e->globalY() - lastPoint.y() - 7);
        }
        else
        {
            MainWindow::prev_geometry.setY(e->globalY());
            MainWindow::normalGeometry() = MainWindow::prev_geometry;
            MainWindow::showNormal();
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        if (e->pos().y() <= 30 && e->pos().y() > MainWindow::resizingFrame)
        {
            MainWindow::moving = true;
            MainWindow::lastPoint = e->pos();
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        if (MainWindow::moving)
            MainWindow::moving = false;
    }
}

void MainWindow::on_Library_clicked()
{
    ui->_Find->setChecked(false);
    if (MainWindow::activeWindow != 1)
    {
        switch (MainWindow::activeWindow)
        {
            case 2:
                ui->Settings->setStyleSheet(styleSheets[1]);
                ui->SettingsLayout->hideWithoutSaving();
                break;
            case 3:
                ui->Synchronization->setStyleSheet(styleSheets[2]);
                ui->SynchronizationLayout->hide();
                break;
            default: break;
        }
        MainWindow::activeWindow = 1;

        LibraryLayout->show();
        MainWindow::libraryButtonsShow();
        ui->Library->setStyleSheet(styleSheets[4]);
    }
}

void MainWindow::on_Settings_clicked()
{
    ui->_Find->setChecked(false);
    if (MainWindow::activeWindow != 2)
    {
        switch (MainWindow::activeWindow)
        {
            case 1:
                ui->Library->setStyleSheet(styleSheets[0]);
                LibraryLayout->hide();
                MainWindow::libraryButtonsHide();
                break;
            case 3:
                ui->Synchronization->setStyleSheet(styleSheets[2]);
                ui->SynchronizationLayout->hide();
                break;
            default: break;
        }
        MainWindow::activeWindow = 2;

        ui->SettingsLayout->show();
        ui->Settings->setStyleSheet(styleSheets[5]);
    }
}

void MainWindow::on_Synchronization_clicked()
{
    ui->_Find->setChecked(false);
    if (MainWindow::activeWindow != 3)
    {
        switch (MainWindow::activeWindow)
        {
            case 1:
                ui->Library->setStyleSheet(styleSheets[0]);
                LibraryLayout->hide();
                MainWindow::libraryButtonsHide();
                break;
            case 2:
                ui->Settings->setStyleSheet(styleSheets[1]);
                ui->SettingsLayout->hideWithoutSaving();
                break;
            default: break;
        }
        MainWindow::activeWindow = 3;

        ui->SynchronizationLayout->show();
        ui->Synchronization->setStyleSheet(styleSheets[6]);
    }
}

void MainWindow::on_Logout_clicked()
{
    ui->_Find->setChecked(false);
    if (MainWindow::activeWindow != 4)
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


void MainWindow::on__AddBooks_clicked()
{
    ui->_Find->setChecked(false);
    BookOrFolder *bookOrFolderAnsw = new BookOrFolder(ui->_AddBooks->mapToGlobal(QPoint(0,ui->_AddBooks->height())),
                                                      ui->_AddBooks->size().width(), ProgramSettings->getInterfaceStyle(), this);

    connect(bookOrFolderAnsw, SIGNAL(AddBookSignal()), this, SLOT(addBooksFiles()));
    connect(bookOrFolderAnsw, SIGNAL(AddFolderSignal()), this, SLOT(addBooksFolder()));
}

void MainWindow::addBooksFolder()
{
    QString path = QFileDialog::getExistingDirectory(this, QObject::tr("Open Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    LibHandler->AddFolder(path);
}

void MainWindow::addBooksFiles()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this, QObject::tr("Open files"), "", "(*.FB2)");
    LibHandler->AddBooks(fileList);
}

void MainWindow::on__Delete_clicked()
{
    ui->_Find->setChecked(false);
    if (LibraryLayout->getSelectedItemsCount() != 0)
    {
        AnswerDialog *answer_window = new AnswerDialog(ui->_Delete->mapToGlobal(QPoint(ui->_Delete->width() - 300, ui->_Delete->height())),
                                                       QObject::tr("Delete books?"),
                                                       ProgramSettings->getInterfaceStyle(),
                                                       this);
        answer_window->show();

        if (answer_window->exec() == QDialog::Accepted)
            LibHandler->deleteBooks(LibraryLayout->deleteItems());
        else
            delete answer_window;
    }
}

void MainWindow::on__ChangeViewMode_toggled(bool checked)
{
    LibraryLayout->changeViewMod();
    ProgramSettings->setLibraryReprezentation(checked);
}

void MainWindow::on__Upscale_clicked()
{
    LibraryLayout->iconUpscale();
}

void MainWindow::on__Downscale_clicked()
{
    LibraryLayout->iconDownscale();
}

void MainWindow::returnButton()
{
    ui->_Find->setChecked(false);
}

void MainWindow::on__Find_toggled(bool checked)
{
    if (checked == true)
    {
        searchWindow = new SearchWindow(QPoint(ui->_Find->x(),ui->_Find->y() + ui->_Find->height()),
                                        ProgramSettings->getInterfaceStyle(), false,
                                        this);
        //            _____   ___
        //  \  /\  /    |     |__
        //   \/  \/     |     |
        // MEGA BUG, Wiiiiii

        connect(searchWindow, SIGNAL(startSearch(QString,QString)), LibHandler, SLOT(findBooks(QString, QString)));
        connect(searchWindow, SIGNAL(finished(int)), this, SLOT(returnButton()));
    }
    else
    {
        searchWindow->close();        
        LibHandler->RefreshLibrary();
    }
}

void MainWindow::on__SortBox_activated(const QString &arg1)
{
    LibHandler->sortBooks(arg1);
}


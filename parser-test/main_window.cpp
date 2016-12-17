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

#include <qxmlstream.h>
#include <QtXml/qdom.h>

#include <QFileDialog>
#include <QDirIterator>

#include <QSizePolicy>
#include <QKeyEvent>
#include <QProcess>
#include <QListWidget>

#include <QDebug>

#include <QThread>

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
void MainWindow::settingsButtonsHide()
{
    for (int i = 0; i < ui->SettingsButtons->count(); i++)
        ui->SettingsButtons->itemAt(i)->widget()->hide();
}
void MainWindow::settingsButtonsShow()
{
    for (int i = 0; i < ui->SettingsButtons->count(); i++)
        ui->SettingsButtons->itemAt(i)->widget()->show();
}


void MainWindow::setStyle()
{
    setWindowTopButtonsStyle(styleSheets, MainWindow::currentStyle);
    ui->min_button->setStyleSheet(styleSheets[0]);
    ui->full_size_button->setStyleSheet(styleSheets[1]);
    ui->exit_button->setStyleSheet(styleSheets[2]);

    setBackgroundWindowColor(styleSheets, MainWindow::currentStyle);
    ui->MainWidget->setStyleSheet(styleSheets[0]);

    setTabButtonsStyle(tabsStyleSheets, MainWindow::currentStyle);
    ui->_Find->setStyleSheet(tabsStyleSheets[4]);
    ui->_AddBooks->setStyleSheet(tabsStyleSheets[0]);
    ui->_Delete->setStyleSheet(tabsStyleSheets[0]);
    ui->_Group->setStyleSheet(tabsStyleSheets[2]);
    ui->_Sort->setStyleSheet(tabsStyleSheets[2]);
    ui->_SettingsProfile->setStyleSheet(tabsStyleSheets[0]);
    ui->_SettingsProgram->setStyleSheet(tabsStyleSheets[1]);
    ui->_SettingsReader->setStyleSheet(tabsStyleSheets[0]);
    ui->_SortBox->setStyleSheet(tabsStyleSheets[3]);
    ui->_GroupBox->setStyleSheet(tabsStyleSheets[3]);

    setMenusButtonsStyle(styleSheets, MainWindow::currentStyle);
    ui->Settings->setStyleSheet(styleSheets[1]);
    ui->Synchronization->setStyleSheet(styleSheets[2]);
    ui->Logout->setStyleSheet(styleSheets[3]);
    ui->Library->setStyleSheet(styleSheets[4]);
    ui->LeftExpandingWidget->setStyleSheet(styleSheets[8]);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::prev_geometry = MainWindow::geometry();
    LibraryLayout = new librarylayout();

    ui->MainWidget->setAttribute(Qt::WA_MouseTracking);
    MainWindow::setMouseTracking(true);

    MainWindow::settingsButtonsHide();

    ui->_SortBox->setView(new QListView());
    ui->_GroupBox->setView(new QListView());

    connect(ui->SettingsLayout, SIGNAL(tabChanged(int)), this, SLOT(settingsTabChanged(int)));
    connect(LibraryLayout, SIGNAL(showBookPage(int)), this, SLOT(showBookPage(int)));

    resoursesFolderPath = "LibraryResources";
    if ( ! QDir(resoursesFolderPath).exists()==true)
        QDir().mkdir(resoursesFolderPath);
    if ( ! QDir("Downloaded books").exists()==true)
        QDir().mkdir("Downloaded books");

    HandlerThread = new QThread(this);
    connect(this, SIGNAL(destroyed(QObject*)), HandlerThread, SLOT(quit()));

    UserActions = new Synchronization();
    ProgramSettings = new settings();

    ProgramSettings->moveToThread(HandlerThread);
    UserActions->moveToThread(HandlerThread);

    ui->TabsLayout->addWidget(LibraryLayout, 0);

    LibHandler = new LibraryHandler(this);
    LibHandler->moveToThread(HandlerThread);

    HandlerThread->start();
    ProgramSettings->loadSettings();
    currentStyle = ProgramSettings->getInterfaceStyle();
    MainWindow::setStyle();
    ui->SettingsLayout->setSettingsData(ProgramSettings);

    LibHandler->loadBookList();
}


MainWindow::~MainWindow()
{
    delete ui;
    delete LibHandler;
    delete LibraryLayout;
}

void LibraryHandler::loadBookList()
{
    QFile bookFileList(window->resoursesFolderPath + "/BookList.lb");

    if(bookFileList.open(QIODevice::ReadOnly | QIODevice::Text ))
        qDebug() << "File Has Been Created" << endl;
    else
    {
        qDebug() << "Failed to Create File" << endl;
        ///оповещение - невозможно открыть или создать файл библиотеки
        return;
    }

    QDataStream in(&bookFileList);
    Book temp;
    while (!in.atEnd())
    {
        in>>temp;
        temp.setBookIndex(currentBookIndex++);
        bookList.push_back(temp);
        window->LibraryLayout->addItem(temp.getBookIndex(), temp.getAuthorName(), temp.getTitle(), temp.getCover());
    }
    bookFileList.close();
}

void LibraryHandler::saveBookList()
{
    QFile bookFileList(window->resoursesFolderPath + "/BookList.lb");

    if(bookFileList.open(QIODevice::WriteOnly | QIODevice::Text ))
    {
        qDebug() << "File Has Been Created" << endl;
    }
    else
    {
        qDebug() << "Failed to Create File" << endl;
        ///оповещение - невозможно открыть или создать файл библиотеки
        /// return;
    }

    QDataStream out(&bookFileList);
    for (int i = 0; i < bookList.size(); i++)
    {
        out<<bookList[i];
    }

    bookFileList.close();
    window->UserActions->saveLog();
}


QString LibraryHandler::getFileTipe(QString fileName)
{
    QString tipe;
    for (int i = 1; i <= 4; i++)
        tipe.push_front(fileName[fileName.length()-i]);

    if (tipe == ".zip" || tipe == ".ZIP")
        return "zip";
    if (tipe == ".FB2" || tipe == ".fb2")
        return "fb2";
    return "unknown format!";
}


void LibraryHandler::openNewBooks(QString file, GenresMap *Gmap)
{
    for (int j = 0; j < bookList.size(); j++)
    {
        if (file == bookList.at(j).File)
        {
            /// оповещение - такая книга уже есть
            return;
        }
    }

    QString tipe = getFileTipe(file);

    if (tipe == "fb2")
    {
        Book boo(file, Gmap);
        boo.setBookIndex(currentBookIndex++);
        bookList.push_back(boo);

        window->UserActions->addAction(1, file, -1, "");
        window->LibraryLayout->addItem(boo.getBookIndex(), boo.getAuthorName(), boo.getTitle(), boo.getCover());

    }
    if (tipe == "zip")
    {
        qDebug()<<"zip!";
    }
}

void MainWindow::showBookPage(int index)
{
    int i;
    for (i = 0; i < LibHandler->bookList.size(); i++)
        if (LibHandler->bookList[i].getBookIndex() == index)
            break;

    page = new BookPage(LibHandler->bookList[i], currentStyle, this);
    connect(page, SIGNAL(startReading(int)), LibHandler, SLOT(startReading(int)));
    connect(page, SIGNAL(deleteBook(int)), LibHandler, SLOT(deleteBook(int)));
}

void MainWindow::startReading(int BookIndex)
{
    int i;
    for (i = 0; i < LibHandler->bookList.size(); i++)
        if (LibHandler->bookList[i].getBookIndex() == BookIndex)
            break;

    readingWindow = new ReadingWindow(ProgramSettings, LibHandler->bookList[i]);
    readingWindow->setWindowFlags(Qt::CustomizeWindowHint);
    connect(readingWindow, SIGNAL(showMainWindow()), this, SLOT(showWindow()));
    readingWindow->show();
    this->hide();
}

void LibraryHandler::deleteBook(int index)
{
    window->LibraryLayout->deleteBook(index);
    for (int i = 0; i < bookList.size(); i++)
        if (bookList[i].getBookIndex() == index)
        {
            window->UserActions->addAction(2, bookList.at(i).File, -1, "");
            bookList.remove(i);
            break;
        }
}

void MainWindow::showWindow()
{
    this->show();
}

void MainWindow::on_exit_button_clicked()
{
    ui->_Find->setChecked(false);
    AnswerDialog *answer_window = new AnswerDialog(ui->exit_button->mapToGlobal(QPoint(0,0)).x() - 300 + ui->exit_button->width(),
                                                   ui->exit_button->mapToGlobal(QPoint(0,0)).y() + ui->exit_button->height(),"Exit?",
                                                   MainWindow::currentStyle);
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
                MainWindow::settingsButtonsHide();
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
        MainWindow::settingsButtonsShow();
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
                MainWindow::settingsButtonsHide();
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

    AnswerDialog *answer_window = new AnswerDialog(ui->Logout->mapToGlobal(QPoint(90,0)).x(),
                                                   ui->Logout->mapToGlobal(QPoint(0,0)).y(),"Logout?",
                                                   MainWindow::currentStyle);
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
    BookOrFolder *bookOrFolderAnsw = new BookOrFolder(ui->_AddBooks->mapToGlobal(QPoint(0,0)).x(),
                                                      ui->_AddBooks->mapToGlobal(QPoint(0,0)).y() + ui->_AddBooks->height(),
                                                      ui->_AddBooks->size().width(), true, MainWindow::currentStyle);
    connect(bookOrFolderAnsw, SIGNAL(AddBookSignal()), this, SLOT(addBooksFiles()));
    connect(bookOrFolderAnsw, SIGNAL(AddFolderSignal()), this, SLOT(addBooksFolder()));
}

void MainWindow::addBooksFolder()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    LibHandler->AddFolder(path);
}

void MainWindow::addBooksFiles()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this, "Open files", "", "(*.FB2 *.zip)");
    LibHandler->AddBooks(fileList);
}



void MainWindow::on__Delete_clicked()
{
    ui->_Find->setChecked(false);
    if (LibraryLayout->getSelectedItemsCount() != 0)
    {
        AnswerDialog *answer_window = new AnswerDialog(ui->_Delete->mapToGlobal(QPoint(0,0)).x() - 300 + ui->_Delete->width(),
                                                       ui->_Delete->mapToGlobal(QPoint(0,0)).y() + ui->_Delete->height(), "Delete books?",
                                                       MainWindow::currentStyle);
        answer_window->show();

        if (answer_window->exec() == QDialog::Accepted)
            LibHandler->deleteBooks(LibraryLayout->deleteItems());
        else
            delete answer_window;
    }
}

void LibraryHandler::deleteBooks(QVector<int> deletedItemsIndexes)
{
    for (int i = 0; i < deletedItemsIndexes.size(); i++)
    {
        for (int j = 0; j < bookList.size(); j++)
        {
            if (bookList[j].getBookIndex() == deletedItemsIndexes.at(i))
            {
                window->UserActions->addAction(2, bookList.at(j).File, -1, "");
                bookList.remove(j);
                break;
            }
        }
    }
    if (deletedItemsIndexes.size())
        saveBookList();
}

void LibraryHandler::AddBooks(QStringList fileList)
{
    if (!fileList.size())
        return;

    GenresMap *Gmap = new GenresMap();

    for (int i = 0; i < fileList.size(); i++)
        openNewBooks(fileList[i], Gmap);

    delete Gmap;
    saveBookList();
}


void LibraryHandler::AddFolder(QString path)
{
    QStringList fileList;

    if (path.isEmpty())
        return;

    QDirIterator it(path, filesMask, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
        fileList << it.next();

    if (!fileList.size())
        return;

    GenresMap *Gmap = new GenresMap();

    for (int i = 0; i < fileList.size(); ++i)
        openNewBooks(fileList[i], Gmap);

    saveBookList();
    delete Gmap;
}

void MainWindow::settingsTabChanged(int tab)
{
    switch (tab)
    {
    case 0:
        ui->_SettingsProfile->setStyleSheet(tabsStyleSheets[0]);
        break;
    case 1:
        ui->_SettingsProgram->setStyleSheet(tabsStyleSheets[0]);
        break;
    case 2:
        ui->_SettingsReader->setStyleSheet(tabsStyleSheets[0]);
        break;
    default:
        break;
    }
}

void MainWindow::on__SettingsProfile_clicked()
{
    ui->SettingsLayout->showProfile();
    ui->_SettingsProfile->setStyleSheet(tabsStyleSheets[1]);
}

void MainWindow::on__SettingsProgram_clicked()
{
    ui->SettingsLayout->showProgram();
    ui->_SettingsProgram->setStyleSheet(tabsStyleSheets[1]);
}

void MainWindow::on__SettingsReader_clicked()
{
    ui->SettingsLayout->showReader();
    ui->_SettingsReader->setStyleSheet(tabsStyleSheets[1]);
}

void MainWindow::on__ChangeViewMode_clicked()
{
    LibraryLayout->changeViewMod();
}

void MainWindow::on__Upscale_clicked()
{
    LibraryLayout->iconUpscale();
}

void MainWindow::on__Downscale_clicked()
{
    LibraryLayout->iconDownscale();
}

void LibraryHandler::findBooks(QString token, QString type)
{
    if (token != "")
    {

    }
    else
    {
        return;
    }
}

void MainWindow::returnButton()
{
    ui->_Find->setChecked(false);
}

void MainWindow::on__Find_toggled(bool checked)
{
    if (checked == true)
    {
        searchWindow = new SearchWindow(ui->_Find->x(),
                                        ui->_Find->y() + ui->_Find->height(),
                                        ProgramSettings->getInterfaceStyle(), false, this);
        //            _____   ___
        //  \  /\  /    |     |__
        //   \/  \/     |     |
        // MEGA BUG, Wiiiiii



        connect(searchWindow, SIGNAL(startSearch(QString,QString)), LibHandler, SLOT(findBooks(QString, QString)));
        connect(searchWindow, SIGNAL(finished(int)), LibHandler, SLOT(returnButton()));
    }
    else
    {
        searchWindow->close();
    }
}

bool AuthorComparator(Book &boo1, Book &boo2)
{
    if (boo1.getAuthorName() <= boo2.getAuthorName())
        return true;
    else
        return false;
}

bool TitleComparator(Book &boo1, Book & boo2)
{
    if (boo1.getTitle() <= boo2.getTitle())
        return true;
    else
        return false;
}


void MainWindow::on__SortBox_activated(const QString &arg1)
{
    if (arg1 == "Date")
    {
        LibraryLayout->clear();
        for (int i = 0; i < LibHandler->bookList.size(); i++)
            LibraryLayout->addItem(LibHandler->bookList[i].getBookIndex(), LibHandler->bookList[i].getAuthorName(), LibHandler->bookList[i].getTitle(), LibHandler->bookList[i].getCover());
        return;
    }
    if (arg1 == "Author")
    {

        QVector <Book> indexVector = LibHandler->bookList;
        qSort(indexVector.begin(), indexVector.end(), &AuthorComparator);
        LibraryLayout->clear();
        for (int i = 0; i < indexVector.size(); i++)
            LibraryLayout->addItem(indexVector[i].getBookIndex(), indexVector[i].getAuthorName(), indexVector[i].getTitle(), indexVector[i].getCover());
        return;
    }
    if (arg1 == "Title")
    {
        LibraryLayout->clear();
        QVector <Book> indexVector = LibHandler->bookList;
        qSort(indexVector.begin(), indexVector.end(), TitleComparator);
        LibraryLayout->clear();
        for (int i = 0; i < indexVector.size(); i++)
            LibraryLayout->addItem(indexVector[i].getBookIndex(), indexVector[i].getAuthorName(), indexVector[i].getTitle(), indexVector[i].getCover());
        return;
    }

}

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

    UserActions = new Synchronization();
    ProgramSettings = new settings(translator);

    ProgramSettings->moveToThread(HandlerThread);
    UserActions->moveToThread(HandlerThread);
    HandlerThread->start();

    ProgramSettings->loadSettings();

    ui->setupUi(this);
    ui->_Group->hide();
    ui->_GroupBox->hide();

    LibHandler = new LibraryHandler(this);
    LibHandler->moveToThread(HandlerThread);
    LibraryLayout = new librarylayout();
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

    ui->SettingsLayout->setSettingsData(ProgramSettings);
    LibraryLayout->setSettingsData(ProgramSettings);
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
    delete LibHandler;
    delete LibraryLayout;
    delete UserActions;
    delete ProgramSettings;
    delete readingWindow;
    delete searchWindow;
    delete page;
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
    qDebug()<<"saving books";
    QFile bookFileList(window->resoursesFolderPath + "/BookList.lb");

    if(bookFileList.open(QIODevice::WriteOnly | QIODevice::Text ))
    {
        qDebug() << "File Has Been Created" << endl;
    }
    else
    {
        qDebug() << "Failed to Create File" << endl;
        ///оповещение - невозможно открыть или создать файл библиотеки
        return;
    }

    QDataStream out(&bookFileList);
    for (int i = 0; i < bookList.size(); i++)
    {
        out<<bookList[i];
    }

    bookFileList.close();
    window->UserActions->saveLog();
}


QString LibraryHandler::getFileTipe(const QString fileName)
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


void LibraryHandler::openNewBooks(const QString file, GenresMap *Gmap)
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

        window->UserActions->addAction(1, file, 0);
        window->LibraryLayout->addItem(boo.getBookIndex(), boo.getAuthorName(), boo.getTitle(), boo.getCover());

    }
    if (tipe == "zip")
    {
        qDebug()<<"zip!";
    }
}

void MainWindow::showBookPage(const int index)
{
    int i;
    for (i = 0; i < LibHandler->bookList.size(); i++)
        if (LibHandler->bookList[i].getBookIndex() == index)
            break;

    page = new BookPage(LibHandler->bookList[i], ProgramSettings->getInterfaceStyle(), this);
    connect(page, SIGNAL(startReading(int)), this, SLOT(startReading(int)));
    connect(page, SIGNAL(deleteBook(int)), LibHandler, SLOT(deleteBook(int)));
}

void MainWindow::startReading(const int BookIndex)
{
    int i;
    for (i = 0; i < LibHandler->bookList.size(); i++)
        if (LibHandler->bookList[i].getBookIndex() == BookIndex)
            break;

    readingWindow = new ReadingWindow(ProgramSettings, &LibHandler->bookList[i]);
    readingWindow->setWindowFlags(Qt::CustomizeWindowHint);
    connect(readingWindow, SIGNAL(showMainWindow()), this, SLOT(showWindow()));
    readingWindow->show();
    connect(readingWindow, SIGNAL(saveBookProgress()), LibHandler, SLOT(saveBookList()));
    this->hide();
}

void LibraryHandler::deleteBook(const int index)
{
    window->LibraryLayout->deleteBook(index);
    for (int i = 0; i < bookList.size(); i++)
        if (bookList[i].getBookIndex() == index)
        {
            window->UserActions->addAction(2, bookList.at(i).File, 0);
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
                                                   ui->exit_button->mapToGlobal(QPoint(0,0)).y() + ui->exit_button->height(),QObject::tr("Exit?"),
                                                   MainWindow::ProgramSettings->getInterfaceStyle());
    answer_window->show();

    if (answer_window->exec() == QDialog::Accepted)
    {
        delete answer_window;
        UserActions->saveLog();
        ProgramSettings->saveSettings();
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

    AnswerDialog *answer_window = new AnswerDialog(ui->Logout->mapToGlobal(QPoint(ui->Logout->width(),0)).x(),
                                                   ui->Logout->mapToGlobal(QPoint(0,0)).y(),QObject::tr("Logout?"),
                                                   MainWindow::ProgramSettings->getInterfaceStyle());
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
                                                      ui->_AddBooks->size().width(), true, MainWindow::ProgramSettings->getInterfaceStyle());
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
    QStringList fileList = QFileDialog::getOpenFileNames(this, QObject::tr("Open files"), "", "(*.FB2 *.zip)");
    LibHandler->AddBooks(fileList);
}

void MainWindow::on__Delete_clicked()
{
    ui->_Find->setChecked(false);
    if (LibraryLayout->getSelectedItemsCount() != 0)
    {
        AnswerDialog *answer_window = new AnswerDialog(ui->_Delete->mapToGlobal(QPoint(0,0)).x() - 300 + ui->_Delete->width(),
                                                       ui->_Delete->mapToGlobal(QPoint(0,0)).y() + ui->_Delete->height(), QObject::tr("Delete books?"),
                                                       MainWindow::ProgramSettings->getInterfaceStyle());
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
                window->UserActions->addAction(2, bookList.at(j).File, 0);
                bookList.remove(j);
                break;
            }
        }
    }
    if (deletedItemsIndexes.size())
        saveBookList();
}

void LibraryHandler::AddBooks(const QStringList fileList)
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

void LibraryHandler::findBooks(QString token, QString mode)
{
    if (token != "")
    {
        needRefresh = true;
        window->LibraryLayout->clear();
        if (mode == QObject::tr("Title"))
        {
            for (int i = 0; i < bookList.size(); i++)
                if (bookList[i].getTitle().indexOf(token, 0, Qt::CaseInsensitive) != -1)
                    window->LibraryLayout->addItem(bookList[i].getBookIndex(), bookList[i].getAuthorName(), bookList[i].getTitle(), bookList[i].getCover());
            return;
        }
        if (mode == QObject::tr("Author"))
        {
            for (int i = 0; i < bookList.size(); i++)
                if (bookList[i].getAuthorName().indexOf(token, 0, Qt::CaseInsensitive) != -1)
                    window->LibraryLayout->addItem(bookList[i].getBookIndex(), bookList[i].getAuthorName(), bookList[i].getTitle(), bookList[i].getCover());
            return;
        }
        if (mode == QObject::tr("Series"))
        {
            for (int i = 0; i < bookList.size(); i++)
                if (bookList[i].getSeries().indexOf(token, 0, Qt::CaseInsensitive) != -1)
                    window->LibraryLayout->addItem(bookList[i].getBookIndex(), bookList[i].getAuthorName(), bookList[i].getTitle(), bookList[i].getCover());
            return;
        }
    }
    else
        return;
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
        connect(searchWindow, SIGNAL(finished(int)), this, SLOT(returnButton()));
    }
    else
    {
        searchWindow->close();        
        if (LibHandler->needRefresh == true)
        {
            LibraryLayout->clear();
            LibHandler->needRefresh = false;
            for (int i = 0; i < LibHandler->bookList.size(); i++)
                LibraryLayout->addItem(LibHandler->bookList[i].getBookIndex(), LibHandler->bookList[i].getAuthorName(), LibHandler->bookList[i].getTitle(), LibHandler->bookList[i].getCover());
        }
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

void LibraryHandler::sortBooks(const QString mode)
{
    if (mode == QObject::tr("Date"))
    {
        window->LibraryLayout->clear();
        for (int i = 0; i < bookList.size(); i++)
            window->LibraryLayout->addItem(bookList[i].getBookIndex(), bookList[i].getAuthorName(), bookList[i].getTitle(), bookList[i].getCover());
        return;
    }
    if (mode == QObject::tr("Author"))
    {

        QVector <Book> indexVector = bookList;
        qSort(indexVector.begin(), indexVector.end(), &AuthorComparator);
        window->LibraryLayout->clear();
        for (int i = 0; i < indexVector.size(); i++)
            window->LibraryLayout->addItem(indexVector[i].getBookIndex(), indexVector[i].getAuthorName(), indexVector[i].getTitle(), indexVector[i].getCover());
        return;
    }
    if (mode == QObject::tr("Title"))
    {
        window->LibraryLayout->clear();
        QVector <Book> indexVector = bookList;
        qSort(indexVector.begin(), indexVector.end(), TitleComparator);
        window->LibraryLayout->clear();
        for (int i = 0; i < indexVector.size(); i++)
            window->LibraryLayout->addItem(indexVector[i].getBookIndex(), indexVector[i].getAuthorName(), indexVector[i].getTitle(), indexVector[i].getCover());
        return;
    }
}

void MainWindow::on__SortBox_activated(const QString &arg1)
{
    LibHandler->sortBooks(arg1);
}



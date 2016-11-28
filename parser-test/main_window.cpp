#include "main_window.h"
#include "ui_mainwindow.h"
#include "answer_dialog.h"
#include "books.h"
#include "styles.h"
#include "book_or_folder.h"
#include "book_page.h"
#include "genresmap.h"

#include <qxmlstream.h>
#include <QtXml/qdom.h>

#include <QFileDialog>
#include <QDirIterator>

#include <QSizePolicy>
#include <QKeyEvent>
#include <QProcess>
#include <QListWidget>

#include <QDebug>
#include <synchronization.h>

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
    ui->_Find->setStyleSheet(tabsStyleSheets[0]);
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
    MainWindow::filesMask<<"*.fb2"<<"*.zip";

    ui->MainWidget->setAttribute(Qt::WA_MouseTracking);
    MainWindow::setMouseTracking(true);

    MainWindow::settingsButtonsHide();

    currentBookIndex = 0;

    ui->_SortBox->setView(new QListView());
    ui->_GroupBox->setView(new QListView());

    connect(ui->SettingsLayout, SIGNAL(tabChanged(int)), this, SLOT(settingsTabChanged(int)));
    connect(ui->LibraryLayout, SIGNAL(showBookPage(int)), this, SLOT(showBookPage(int)));

    MainWindow::currentStyle = "red";
    MainWindow::setStyle();

    //начало работы с файлами ресурсов библиотеки
    resoursesFolderPath = "LibraryResources";
    if ( ! QDir(resoursesFolderPath).exists()==true)
    {
        QDir().mkdir(resoursesFolderPath);
    }

    loadBookList();

    UserActions = new Synchronization();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete page;
}


void MainWindow::loadBookList()
{
    QFile bookFileList(resoursesFolderPath + "/BookList.lb");

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
        ui->LibraryLayout->addItem(temp.getBookIndex(), temp.getAuthorName(), temp.getTitle(), temp.getCover());
    }
    bookFileList.close();
}

void MainWindow::saveBookList()
{
    QFile bookFileList(resoursesFolderPath + "/BookList.lb");

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
    UserActions->saveLog();
}


QString MainWindow::getFileTipe(QString fileName)
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


void MainWindow::openNewBooks(QString file, GenresMap *Gmap)
{

    for (int j = 0; j < bookList.size(); j++)
    {
        if (file == bookList.at(j).File)
        {
            /// оповещение - такая книга уже есть
            return;
        }
    }

    QString tipe = MainWindow::getFileTipe(file);

    if (tipe == "fb2")
    {
        Book boo(file, Gmap);
        boo.setBookIndex(currentBookIndex++);
        bookList.push_back(boo);

        UserActions->addAction(1, file, -1, "");
        ui->LibraryLayout->addItem(boo.getBookIndex(), boo.getAuthorName(), boo.getTitle(), boo.getCover());

    }
    if (tipe == "zip")
    {
        qDebug()<<"zip!";
    }
}

void MainWindow::showBookPage(int index)
{
    int i;
    for (i = 0; i < bookList.size(); i++)
        if (bookList[i].getBookIndex() == index)
            break;

    page = new BookPage(bookList[i], currentStyle, this);
}


void MainWindow::on_exit_button_clicked()
{
    AnswerDialog *answer_window = new AnswerDialog(ui->exit_button->mapToGlobal(QPoint(0,0)).x()-280,ui->exit_button->mapToGlobal(QPoint(0,0)).y()+20,"Exit?", MainWindow::currentStyle);
    answer_window->show();

    if (answer_window->exec() == QDialog::Accepted)
    {
        exit(0);
    }
    else
        delete answer_window;
}


void MainWindow::on_full_size_button_clicked()
{
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
            move(e->globalX() - MainWindow::lastPoint.x(),  e->globalY() - MainWindow::lastPoint.y());
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
    if (MainWindow::activeWindow != 1)
    {
        switch (MainWindow::activeWindow)
        {
            case 2:
                ui->Settings->setStyleSheet(styleSheets[1]);
                ui->SettingsLayout->hide();
                MainWindow::settingsButtonsHide();
                break;
            case 3:
                ui->Synchronization->setStyleSheet(styleSheets[2]);
                ui->SynchronizationLayout->hide();
                break;
            default: break;
        }
        MainWindow::activeWindow = 1;

        ui->LibraryLayout->show();
        MainWindow::libraryButtonsShow();
        ui->Library->setStyleSheet(styleSheets[4]);
    }
}


void MainWindow::on_Settings_clicked()
{
    if (MainWindow::activeWindow != 2)
    {
        switch (MainWindow::activeWindow)
        {
            case 1:
                ui->Library->setStyleSheet(styleSheets[0]);
                ui->LibraryLayout->hide();
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
    if (MainWindow::activeWindow != 3)
    {
        switch (MainWindow::activeWindow)
        {
            case 1:
                ui->Library->setStyleSheet(styleSheets[0]);
                ui->LibraryLayout->hide();
                MainWindow::libraryButtonsHide();
                break;
            case 2:
                ui->Settings->setStyleSheet(styleSheets[1]);
                ui->SettingsLayout->hide();
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
    if (MainWindow::activeWindow != 4)
        ui->Logout->setStyleSheet(styleSheets[7]);

    AnswerDialog *answer_window = new AnswerDialog(ui->Logout->mapToGlobal(QPoint(90,0)).x(),ui->Logout->mapToGlobal(QPoint(0,0)).y(),"Logout?", MainWindow::currentStyle);
    answer_window->show();

    if (answer_window->exec() == QDialog::Accepted)
    {
        ui->Logout->setStyleSheet(styleSheets[3]);
        QProcess::startDetached(QApplication::applicationFilePath(), QStringList(), QApplication::applicationDirPath());
        MainWindow::close();
    }
    ui->Logout->setStyleSheet(styleSheets[3]);
    delete answer_window;
}


void MainWindow::on__AddBooks_clicked()
{
    BookOrFolder *bookOrFolderAnsw = new BookOrFolder(ui->_AddBooks->mapToGlobal(QPoint(0,0)).x(), ui->_AddBooks->mapToGlobal(QPoint(0,0)).y() + 30, ui->_AddBooks->size().width(), true, MainWindow::currentStyle);
    connect(bookOrFolderAnsw, SIGNAL(AddBookSignal()), this, SLOT(AddBook()));
    connect(bookOrFolderAnsw, SIGNAL(AddFolderSignal()), this, SLOT(AddFolder()));
}


void MainWindow::on__Delete_clicked()
{
    BookOrFolder *bookOrFolderAnsw = new BookOrFolder(ui->_Delete->mapToGlobal(QPoint(0,0)).x(), ui->_Delete->mapToGlobal(QPoint(0,0)).y() + 30, ui->_AddBooks->size().width(), false, MainWindow::currentStyle);
    connect(bookOrFolderAnsw, SIGNAL(DeleteBookSignal()), this, SLOT(DeleteBook()));
    connect(bookOrFolderAnsw, SIGNAL(DeleteFolderSignal()), this, SLOT(DeleteFolder()));
}


void MainWindow::AddBook()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this, "Open files", "", "(*.FB2 *.zip)");

    if (!fileList.size())
        return;

    GenresMap *Gmap = new GenresMap();

    for (int i = 0; i < fileList.size(); ++i)
        openNewBooks(fileList[i], Gmap);

    delete Gmap;
    saveBookList();

}


void MainWindow::AddFolder()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QStringList fileList;

    if (path.isEmpty())
        return;

    QDirIterator it(path, MainWindow::filesMask, QDir::Files, QDirIterator::Subdirectories);
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


void MainWindow::DeleteBook()
{
    QVector <int> deletedItemsIndexes = ui->LibraryLayout->deleteItems();
    for (int i = 0; i < deletedItemsIndexes.size(); i++)
    {
        for (int j = 0; j < bookList.size(); j++)
        {
            if (bookList[j].getBookIndex() == deletedItemsIndexes.at(i))
            {
                UserActions->addAction(2, bookList.at(i).File, -1, "");
                bookList.remove(j);                
                break;
            }
        }
    }
    if (deletedItemsIndexes.size())
        saveBookList();

    MainWindow::setFocus();
}

void MainWindow::DeleteFolder()
{
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
    ui->LibraryLayout->changeViewMod();
}

void MainWindow::on__Upscale_clicked()
{
    ui->LibraryLayout->iconUpscale();
}

void MainWindow::on__Downscale_clicked()
{
    ui->LibraryLayout->iconDownscale();
}

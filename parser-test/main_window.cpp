#include "main_window.h"
#include "ui_mainwindow.h"
#include "ui_loginwindow.h"
#include <answer_dialog.h>
#include <books.h>
#include <styles.h>

#include <qxmlstream.h>
#include <QtXml/qdom.h>

#include <QFileDialog>
#include <QDirIterator>

#include <QSizePolicy>
#include <QKeyEvent>
#include <QProcess>
#include <QString>
#include <QListWidget>

#include <QDebug>

void MainWindow::libraryButtonsHide()
{
    ui->_AddBook->hide();
    ui->_AddFolder->hide();
    ui->_Delete->hide();
    ui->_Sort->hide();
    ui->_Group->hide();
    ui->_Find->hide();
}
void MainWindow::libraryButtonsShow()
{
    ui->_AddBook->show();
    ui->_AddFolder->show();
    ui->_Delete->show();
    ui->_Sort->show();
    ui->_Group->show();
    ui->_Find->show();
}
void MainWindow::settingsButtonsHide()
{
    ui->_SettingsProfile->hide();
    ui->_SettingsProgram->hide();
    ui->_SettingsReader->hide();
    ui->_SettingsSynchronization->hide();
}
void MainWindow::settingsButtonsShow()
{
    ui->_SettingsProfile->show();
    ui->_SettingsProgram->show();
    ui->_SettingsReader->show();
    ui->_SettingsSynchronization->show();
}



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::prev_geometry = MainWindow::geometry();
    MainWindow::filesMask<<"*.fb2"<<"*.zip";

    ui->MainWidget->setAttribute(Qt::WA_MouseTracking);
    MainWindow::setMouseTracking(true);

    settingsLayout = new QWidget();
    settingsLayout->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ui->tabs->addWidget(settingsLayout);
    
    QPushButton *button = new QPushButton();
    button->setMinimumSize(100,150);
    button->setMaximumSize(100,150);
    ui->LibraryLayout->setWidget(button);

    MainWindow::settingsButtonsHide();


    connect(ui->SettingsLayout, SIGNAL(tabChanged(int)), this, SLOT(settingsTabChanged(int)));

///////////////////////////////////////////////////////////////////////////////////////////
    setWindowTopButtonsStyle(styleSheets, "red");
    ui->min_button->setStyleSheet(styleSheets[0]);
    ui->full_size_button->setStyleSheet(styleSheets[1]);
    ui->exit_button->setStyleSheet(styleSheets[2]);

    setBackgroundWindowColor(styleSheets, "red");
    ui->MainWidget->setStyleSheet(styleSheets[0]);

    setMainWindowStyle(styleSheets, "red");
    ui->scrollAreaWidget->setStyleSheet(styleSheets[0]);
    ui->scrollArea->setStyleSheet(styleSheets[1]);

    setTabButtonsStyle(tabsStyleSheets, "red");
    ui->_Find->setStyleSheet(tabsStyleSheets[0]);
    ui->_AddBook->setStyleSheet(tabsStyleSheets[0]);
    ui->_AddFolder->setStyleSheet(tabsStyleSheets[0]);
    ui->_Delete->setStyleSheet(tabsStyleSheets[0]);
    ui->_Group->setStyleSheet(tabsStyleSheets[0]);
    ui->_Sort->setStyleSheet(tabsStyleSheets[0]);
    ui->_SettingsProfile->setStyleSheet(tabsStyleSheets[0]);
    ui->_SettingsProgram->setStyleSheet(tabsStyleSheets[1]);
    ui->_SettingsReader->setStyleSheet(tabsStyleSheets[0]);
    ui->_SettingsSynchronization->setStyleSheet(tabsStyleSheets[0]);

    setMenusButtonsStyle(styleSheets, "red");
    ui->Settings->setStyleSheet(styleSheets[1]);
    ui->Synchronization->setStyleSheet(styleSheets[2]);
    ui->Logout->setStyleSheet(styleSheets[3]);
    ui->Library->setStyleSheet(styleSheets[4]);
    ui->LeftExpandingWidget->setStyleSheet(styleSheets[8]);


    /////////////////////////////////////////////////////////////////////////////////////

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_exit_button_clicked()
{
    AnswerDialog *answer_window = new AnswerDialog(ui->exit_button->mapToGlobal(QPoint(0,0)).x()-280,ui->exit_button->mapToGlobal(QPoint(0,0)).y()+20,"Exit?");
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

    AnswerDialog *answer_window = new AnswerDialog(ui->Logout->mapToGlobal(QPoint(90,0)).x(),ui->Logout->mapToGlobal(QPoint(0,0)).y(),"Logout?");
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


QString MainWindow::FileTipe(QString fileName)
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


void MainWindow::openNewBooks(QStringList fileList)
{
    for (int i = 0; i < fileList.size(); ++i)
    {
        QString tipe = MainWindow::FileTipe(fileList[i]);

        QPushButton *button;

        if (tipe == "fb2")
        {
            Book boo(fileList[i]);
            MainWindow::bookList.push_back(boo);
            button = new QPushButton(boo.Title);
        }
        if (tipe == "zip")
        {
            qDebug()<<"zip!";
            button = new QPushButton("zip");
        }


        button->setStyleSheet(QString("QPushButton{background-color:rgb(0, 0, 73); border:none; color:white;}"));
        button->setMinimumSize(100,150);
        button->setMaximumSize(100,150);

        ui->LibraryLayout->addWidget(button);
    }
}


void MainWindow::on__AddBook_clicked()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this, "Open files", "", "(*.FB2 *.zip)");
    openNewBooks(fileList);
}


void MainWindow::on__AddFolder_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QStringList fileList;

    if (path.isEmpty())
        return;

    QDirIterator it(path, MainWindow::filesMask, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
        fileList << it.next();

    openNewBooks(fileList);
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
    case 3:
        ui->_SettingsSynchronization->setStyleSheet(tabsStyleSheets[0]);
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

void MainWindow::on__SettingsSynchronization_clicked()
{
    ui->SettingsLayout->showSynchronization();
    ui->_SettingsSynchronization->setStyleSheet(tabsStyleSheets[1]);
}

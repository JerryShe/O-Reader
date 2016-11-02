#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_loginwindow.h"

#include "pugiconfig.hpp"
#include "pugixml.hpp"
#include "menubuttonsstyles.h"

#include <QFileDialog>
#include <QLabel>
#include <QKeyEvent>
#include <QProcess>
#include <answerdialog.h>
#include <QGraphicsBlurEffect>

#include <iostream>
#include <string>
using namespace pugi;
using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    MainWindow::prev_geometry = MainWindow::geometry();

    ui->MainWidget->setAttribute(Qt::WA_MouseTracking);
    MainWindow::setMouseTracking(true);


    setMenusButtonsStyle(MenuButtonsSheets);

    ui->Library->setStyleSheet(MainWindow::MenuButtonsSheets[4]);

    ui->Settings->setStyleSheet(MainWindow::MenuButtonsSheets[1]);

    ui->Synchronization->setStyleSheet(MainWindow::MenuButtonsSheets[2]);

    ui->Logout->setStyleSheet(MainWindow::MenuButtonsSheets[3]);

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *target, QEvent *event) //наш обработчик событий
{
    if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent *mouseEvent = (QMouseEvent *) event;
        std::cout<<mouseEvent->pos().x()<<"     "<<mouseEvent->pos().y()<<std::endl;    //в консоль выводим координаты
        return true;    //возвращаю true, событие обработано, дальнейшая обработка не требуется
    }
    return false;    //Событие должно быть обработано родительским виджетом
}


void MainWindow::on_exit_button_clicked()
{
    AnswerDialog *answer_window = new AnswerDialog(ui->exit_button->mapToGlobal(QPoint(0,0)).x()-280,ui->exit_button->mapToGlobal(QPoint(0,0)).y()+20,"Fuck?");
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
    if (MainWindow::resizing && !MainWindow::moving)
    {
        switch (MainWindow::resizingMethod)
        {
        case 1:
            MainWindow::resize(MainWindow::width(), MainWindow::lastWindowHeight + (MainWindow::lastMouseGlobalPos.y() - e->globalY()));
            if (MainWindow::height() > 643)
            MainWindow::move(MainWindow::x(), e->globalY());
            break;
        case 3:
            MainWindow::resize(MainWindow::lastWindowWidth + (MainWindow::lastMouseGlobalPos.x() - e->globalX()), MainWindow::height());
            if (MainWindow::width() > 566)
                MainWindow::move(e->globalX(), MainWindow::y());
            break;
        case 2:
            MainWindow::resize(MainWindow::width(), MainWindow::lastWindowHeight - (MainWindow::lastMouseGlobalPos.y() - e->globalY()));
            break;
        case 6:
            MainWindow::resize(MainWindow::lastWindowWidth - (MainWindow::lastMouseGlobalPos.x() - e->globalX()), MainWindow::height());
            break;
        case 4:
            MainWindow::resize(MainWindow::lastWindowWidth + (MainWindow::lastMouseGlobalPos.x() - e->globalX()), MainWindow::lastWindowHeight + (MainWindow::lastMouseGlobalPos.y() - e->globalY()));
            if (MainWindow::width() > 566 && MainWindow::height() > 543)
                MainWindow::move(e->globalX(), e->globalY());
            break;
        case 7:
            MainWindow::resize(MainWindow::lastWindowWidth - (MainWindow::lastMouseGlobalPos.x() - e->globalX()), MainWindow::lastWindowHeight + (MainWindow::lastMouseGlobalPos.y() - e->globalY()));
            if (MainWindow::height() > 543)
                MainWindow::move(MainWindow::x(), e->globalY());
            break;
        case 5:
            MainWindow::resize(MainWindow::lastWindowWidth + (MainWindow::lastMouseGlobalPos.x() - e->globalX()), MainWindow::lastWindowHeight - (MainWindow::lastMouseGlobalPos.y() - e->globalY()));
            if (MainWindow::width() > 566)
                MainWindow::move(e->globalX(), MainWindow::y());
            break;
        case 8:
            MainWindow::resize(MainWindow::lastWindowWidth - (MainWindow::lastMouseGlobalPos.x() - e->globalX()), MainWindow::lastWindowHeight - (MainWindow::lastMouseGlobalPos.y() - e->globalY()));
            break;

        }
    }
    else
    if (!MainWindow::moving && !MainWindow::resizing)
    {
        MainWindow::resizingMethod = 0;
        if (e->pos().y() < MainWindow::resizingFrame)
            MainWindow::resizingMethod += 1;
        if (e->pos().y() > MainWindow::size().height() - MainWindow::resizingFrame)
            MainWindow::resizingMethod += 2;
        if (e->pos().x() < MainWindow::resizingFrame)
            MainWindow::resizingMethod += 3;
        if(e->pos().x() > MainWindow::size().width() - MainWindow::resizingFrame)
            MainWindow::resizingMethod += 6;

        switch (MainWindow::resizingMethod)
        {
        case 0:
            MainWindow::setCursor(Qt::ArrowCursor);
            break;
        case 1:
            MainWindow::setCursor(Qt::SizeVerCursor);
            break;
        case 2:
            MainWindow::setCursor(Qt::SizeVerCursor);
            break;
        case 3:
            MainWindow::setCursor(Qt::SizeHorCursor);
            break;
        case 4:
            MainWindow::setCursor(Qt::SizeFDiagCursor);
            break;
        case 5:
            MainWindow::setCursor(Qt::SizeBDiagCursor);
            break;
        case 6:
            MainWindow::setCursor(Qt::SizeHorCursor);
            break;
        case 7:
            MainWindow::setCursor(Qt::SizeBDiagCursor);
            break;
        case 8:
            MainWindow::setCursor(Qt::SizeFDiagCursor);
            break;
        }

    }
    else
    if (MainWindow::moving && !MainWindow::resizing)
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
        if (e->pos().y() <= 50 && e->pos().y() > MainWindow::resizingFrame)
        {
            MainWindow::moving = true;
            MainWindow::lastPoint = e->pos();
        }

        if(MainWindow::resizingMethod)
        {
            resizing = true;
            MainWindow::lastMouseGlobalPos = e->globalPos();
            MainWindow::lastWindowHeight = MainWindow::height();
            MainWindow::lastWindowWidth = MainWindow::width();
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        if (MainWindow::moving)
            MainWindow::moving = false;

        if (MainWindow::resizing)
        {
            MainWindow::resizing = false;
            MainWindow::setCursor(Qt::ArrowCursor);
        }
    }
}

void MainWindow::on_Library_clicked()
{
    if (MainWindow::activeWindow != 1)
    {
        switch (MainWindow::activeWindow)
        {
            case 2:
                ui->Settings->setStyleSheet(MainWindow::MenuButtonsSheets[1]);
                break;
            case 3:
                ui->Synchronization->setStyleSheet(MainWindow::MenuButtonsSheets[2]);
                break;
            default: break;
        }

        MainWindow::activeWindow = 1;
        ui->Library->setStyleSheet(MainWindow::MenuButtonsSheets[4]);
    }
}

void MainWindow::on_Settings_clicked()
{
    if (MainWindow::activeWindow != 2)
    {
        switch (MainWindow::activeWindow)
        {
            case 1:
                ui->Library->setStyleSheet(MainWindow::MenuButtonsSheets[0]);
                break;
            case 3:
                ui->Synchronization->setStyleSheet(MainWindow::MenuButtonsSheets[2]);
                break;
            default: break;
        }
        MainWindow::activeWindow = 2;
        ui->Settings->setStyleSheet(MainWindow::MenuButtonsSheets[5]);
    }
}

void MainWindow::on_Synchronization_clicked()
{
    if (MainWindow::activeWindow != 3)
    {
        switch (MainWindow::activeWindow)
        {
            case 1:
                ui->Library->setStyleSheet(MainWindow::MenuButtonsSheets[0]);
                break;
            case 2:
                ui->Settings->setStyleSheet(MainWindow::MenuButtonsSheets[1]);
                break;
            default: break;
        }

        MainWindow::activeWindow = 3;
        ui->Synchronization->setStyleSheet(MainWindow::MenuButtonsSheets[6]);
    }
}

void MainWindow::on_Logout_clicked()
{
    if (MainWindow::activeWindow != 4)
        ui->Logout->setStyleSheet(MainWindow::MenuButtonsSheets[7]);

    AnswerDialog *answer_window = new AnswerDialog(ui->Logout->mapToGlobal(QPoint(90,0)).x(),ui->Logout->mapToGlobal(QPoint(0,0)).y(),"Fuck!");
    answer_window->show();

    if (answer_window->exec() == QDialog::Accepted)
    {
        ui->Logout->setStyleSheet(MainWindow::MenuButtonsSheets[3]);
        QProcess::startDetached(QApplication::applicationFilePath(), QStringList(), QApplication::applicationDirPath());
        MainWindow::close();
    }
    ui->Logout->setStyleSheet(MainWindow::MenuButtonsSheets[3]);
    delete answer_window;
}


void MainWindow::on_AddBook_clicked()

{
    //ui->Context->clear();
    //ui->line->setStyleSheet(QString::fromUtf8("background-color: rgb(244, 115, 255);"));

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("FB2 Files (*.fb2)"));
    wchar_t * nameOfFile = (wchar_t*)fileName.utf16();                    //костыль, что-то с кодировкой при приведении типов встроенной функцией

    xml_document doc;
    xml_parse_result result = doc.load_file(nameOfFile, encoding_auto);
    //ui->label->setText(result.description());

    xpath_node_set nodes = doc.select_nodes("//section/title/p");

    //QLocale::setDefault(QLocale::Russian);
    //ui->listWidget->setLocale(QLocale::Russian);
    QStringList table_of_contents;
    for(xpath_node node : nodes)
    {
         string a = node.node().text().as_string();
         table_of_contents << node.node().text().as_string();
         std::cout << a << endl;
         //std::cout << a.
          cout<< a;
    }
}


void MainWindow::on_AddFolder_clicked()
{
    QPushButton *button = new QPushButton(this);
    button->setStyleSheet(QString("QPushButton{background-color:rgb(0, 0, 73); border:none;}"));
    button->setMaximumWidth(100);
    button->setMinimumWidth(100);
    button->setMaximumHeight(150);
    button->setMinimumHeight(150);
    ui->LibraryLayout->addWidget(button);

}

void MainWindow::on_TableView_clicked()
{

}



#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_loginwindow.h"

#include "pugiconfig.hpp"
#include "pugixml.hpp"
#include "objectsstyles.h"

#include <QFileDialog>
#include <QLabel>
#include <QKeyEvent>
#include <QProcess>

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


void MainWindow::on_pushButton_clicked()
{
    ui->Context->clear();
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

    ui->Context->addItems(table_of_contents);


}

void MainWindow::on_exit_button_clicked()
{
    exit(0);
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
    if (!moving)
    {
        if (e->pos().y() < resizingFrame)
        {
            MainWindow::setCursor(Qt::SizeVerCursor);
            if (resizing && e->buttons() && Qt::LeftButton)
            {
                MainWindow::setGeometry(MainWindow::x(), e->globalY(), MainWindow::width(), MainWindow::height() + (MainWindow::lastGlobalPos.y() - e->globalY()));
                MainWindow::lastGlobalPos.setY(e->globalY());
                return;
                //cout<<MainWindow::lastGlobalPos.y() - e->globalY()<<endl;
               // MainWindow::lastPoint = e->pos();
                //MainWindow::move(MainWindow::pos().x(), MainWindow::pos().y() - (e->globalY() - MainWindow::lastPoint.y()));
            }
        }
        else if (e->pos().y() > MainWindow::size().height() - resizingFrame)
        {
            MainWindow::setCursor(Qt::SizeVerCursor);
            if (resizing)
            {


            }
        }
        else if (e->pos().x() < resizingFrame)
        {
            MainWindow::setCursor(Qt::SizeHorCursor);
            if (resizing)
            {


            }
        }
        else if (e->pos().x() > MainWindow::size().width() - resizingFrame)
        {
            MainWindow::setCursor(Qt::SizeHorCursor);
            if (resizing)
            {


            }
        }
        else
            MainWindow::setCursor(Qt::ArrowCursor);
    }




    if(e->buttons() && Qt::LeftButton)
        if (moving && !resizing)
        {
            if (!MainWindow::isMaximized())
            {
                move(e->globalX() - MainWindow::lastPoint.x(),  e->globalY() - MainWindow::lastPoint.y());
            }
            else
            {
                prev_geometry.setY(e->globalY());
                MainWindow::normalGeometry() = prev_geometry;
                MainWindow::showNormal();
            }
        }

}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        MainWindow::lastPoint = e->pos();
        MainWindow::lastGlobalPos = e->globalPos();
        if (e->pos().y() <= 50 && e->pos().y() > resizingFrame)
            moving = true;
        if (e->pos().y() < resizingFrame || e->pos().y() > MainWindow::size().height() - resizingFrame || e->pos().x() < resizingFrame || e->pos().x() > MainWindow::size().width() - resizingFrame)
            resizing = true;
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        if (e->pos().y() <= 50 && e->pos().y() > resizingFrame)
        {
            moving = false;
        }

        if (e->pos().y() < resizingFrame*10 || e->pos().y() > MainWindow::size().height() - resizingFrame || e->pos().x() < resizingFrame || e->pos().x() > MainWindow::size().width() - resizingFrame)
        {
            resizing = false;
        }
    }
}

void MainWindow::on_Library_clicked()
{
    if (MainWindow::activeMenuButton != 1)
    {
        MainWindow::activeMenuButton = 1;
        ui->Library->setStyleSheet(MainWindow::MenuButtonsSheets[4]);

        ui->Settings->setStyleSheet(MainWindow::MenuButtonsSheets[1]);

        ui->Synchronization->setStyleSheet(MainWindow::MenuButtonsSheets[2]);

        ui->Logout->setStyleSheet(MainWindow::MenuButtonsSheets[3]);
    }
}

void MainWindow::on_Settings_clicked()
{
    if (MainWindow::activeMenuButton != 2)
    {
        MainWindow::activeMenuButton = 2;

        ui->Library->setStyleSheet(MainWindow::MenuButtonsSheets[0]);

        ui->Settings->setStyleSheet(MainWindow::MenuButtonsSheets[5]);

        ui->Synchronization->setStyleSheet(MainWindow::MenuButtonsSheets[2]);

        ui->Logout->setStyleSheet(MainWindow::MenuButtonsSheets[3]);
    }
}

void MainWindow::on_Synchronization_clicked()
{
    if (MainWindow::activeMenuButton != 3)
    {
        MainWindow::activeMenuButton = 3;
        ui->Library->setStyleSheet(MainWindow::MenuButtonsSheets[0]);

        ui->Settings->setStyleSheet(MainWindow::MenuButtonsSheets[1]);

        ui->Synchronization->setStyleSheet(MainWindow::MenuButtonsSheets[6]);

        ui->Logout->setStyleSheet(MainWindow::MenuButtonsSheets[3]);
    }
}

void MainWindow::on_Logout_clicked()
{
    if (MainWindow::activeMenuButton != 4)
    {
        MainWindow::activeMenuButton = 4;
        ui->Library->setStyleSheet(MainWindow::MenuButtonsSheets[0]);

        ui->Settings->setStyleSheet(MainWindow::MenuButtonsSheets[1]);

        ui->Synchronization->setStyleSheet(MainWindow::MenuButtonsSheets[2]);

        ui->Logout->setStyleSheet(MainWindow::MenuButtonsSheets[7]);
    }
    QProcess::startDetached(QApplication::applicationFilePath(), QStringList(), QApplication::applicationDirPath());
    MainWindow::close();
}

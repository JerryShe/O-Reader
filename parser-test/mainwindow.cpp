#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pugiconfig.hpp"
#include "pugixml.hpp"

#include <QFileDialog>
#include <QLabel>
#include <QKeyEvent>


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
        if (e->pos().y() < 3 || e->pos().y() > MainWindow::size().height() - 3)
            MainWindow::setCursor(Qt::SizeVerCursor);
        else
            if( e->pos().x() < 3 || e->pos().x() > MainWindow::size().width() - 3)
                MainWindow::setCursor(Qt::SizeHorCursor);
            else
                MainWindow::setCursor(Qt::ArrowCursor);
    }


    if((e->buttons() && Qt::LeftButton))
        if ((moving))
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

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
        if (e->pos().y() <= 50 && e->pos().y() > 2)
        {
            MainWindow::lastPoint = e->pos();
            moving = true;
            ui->pushButton->setText("true");
        }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton && moving)
        if (e->pos().y() <= 50)
        {
            moving = false;
            ui->pushButton->setText("false");
        }
}

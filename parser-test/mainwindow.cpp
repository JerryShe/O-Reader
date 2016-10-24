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
    ui->centralWidget=ui->MainPage;

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
    if (MainWindow::geometry() == MainWindow::prev_geometry)
        MainWindow::showMaximized();
    else
    {
        MainWindow::setGeometry(MainWindow::prev_geometry);
    }
}

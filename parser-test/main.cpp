#include "mainwindow.h"
#include <QApplication>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow my_fucking_window;
    my_fucking_window.setWindowFlags(Qt::FramelessWindowHint);

    my_fucking_window.prev_geometry = my_fucking_window.geometry();

    my_fucking_window.show();




    return a.exec();
}

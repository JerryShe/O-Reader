#include "loginwindow.h"
#include "mainwindow.h"
#include <QApplication>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow login_fucking_window;

    login_fucking_window.setWindowFlags(Qt::FramelessWindowHint);
    login_fucking_window.show();


    //login_fucking_window.show();



    return a.exec();
}

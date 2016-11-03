#include "login_window.h"
#include "main_window.h"
#include <QApplication>




int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    LoginWindow login_fucking_window;

    //login_fucking_window.setWindowFlags(Qt::FramelessWindowHint);
    login_fucking_window.setWindowFlags(Qt::CustomizeWindowHint);


    login_fucking_window.show();

    return app.exec();
}

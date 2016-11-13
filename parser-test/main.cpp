#include "login_window.h"
#include <QApplication>




int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    LoginWindow login_window;
    login_window.setWindowFlags(Qt::CustomizeWindowHint);
    login_window.show();

    return app.exec();
}

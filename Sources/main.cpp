#include <window_manager.h>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    WindowManager* windowManager = new WindowManager();

    return app.exec();
}

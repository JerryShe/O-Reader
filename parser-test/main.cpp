#include "login_window.h"
#include <QApplication>
#include <QTranslator>
#include <QUrl>
#include <QDebug>

#if defined(Q_OS_LINUX)
    #define CurrentOS 0
#elif defined(Q_OS_WIN)
    #define CurrentOS 1
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile SettingsFile(QUrl::fromLocalFile("LibraryResources/Settings.conf").toString());
    QString currentLanguage;
    if(SettingsFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QDataStream in(&SettingsFile);
        in>>currentLanguage;
        in>>currentLanguage;
        in>>currentLanguage;
    }
    else
        currentLanguage = "English";
    SettingsFile.close();

    QTranslator* LanguageTranslator = new QTranslator;
    bool done = false;
    if (currentLanguage == "Русский")
        done = LanguageTranslator->load("ru.qm", "LibraryResources/Languages");
    if (currentLanguage == "English")
        done = LanguageTranslator->load("en.qm", "LibraryResources/Languages");
    if (done)
        qApp->installTranslator(LanguageTranslator);

    LoginWindow login_window(LanguageTranslator);

    if (CurrentOS)
        login_window.setWindowFlags(Qt::CustomizeWindowHint);
    else
        login_window.setWindowFlags(Qt::Dialog);

    login_window.show();

    return app.exec();
}

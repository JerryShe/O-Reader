#include "login_window.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile SettingsFile("LibraryResources/Settings.conf");
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
    bool done;
    if (currentLanguage == "Русский")
        done = LanguageTranslator->load("ru.qm", "LibraryResources/Languages");
    if (currentLanguage == "English")
        done = LanguageTranslator->load("en.qm", "LibraryResources/Languages");
    if (done)
        qApp->installTranslator(LanguageTranslator);

    LoginWindow login_window(LanguageTranslator);
    login_window.setWindowFlags(Qt::CustomizeWindowHint);
    login_window.show();

    return app.exec();
}

#include "login_window.h"
#include <QApplication>
#include <QTranslator>
#include <QUrl>
#include <QDebug>

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
        done = LanguageTranslator->load("ru.qm", QUrl::fromLocalFile("LibraryResources/Languages").toString());
    if (currentLanguage == "English")
        done = LanguageTranslator->load("en.qm", QUrl::fromLocalFile("LibraryResources/Languages").toString());
    if (done)
        qApp->installTranslator(LanguageTranslator);

    LoginWindow login_window(LanguageTranslator);
    login_window.setWindowFlags(Qt::CustomizeWindowHint);
    login_window.show();

    return app.exec();
}

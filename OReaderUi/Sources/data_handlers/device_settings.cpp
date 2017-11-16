#include "data_handlers/device_settings.h"

#include <QVector>
#include <QDataStream>
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QApplication>
#include <QDesktopWidget>

#include <QDebug>

DeviceSettingsHandler* DeviceSettingsHandler::getDeviceSettings()
{
    static DeviceSettingsHandler deviceSettings;
    return &deviceSettings;
}


DeviceSettingsHandler::DeviceSettingsHandler()
{
    LastOpenedWindow = 0;

    LibraryRepresentation = false;
    LibraryIconBarSize = 140;
    LibraryIconListSize = 50;

    LibrarySortOrder = false;
    LibrarySortType = 0;

    WindowMaximized = false;
    WindowGeometry = QRect (qApp->desktop()->availableGeometry().width()/6,
                            qApp->desktop()->availableGeometry().height()/6,
                            qApp->desktop()->availableGeometry().width()/1.5,
                            qApp->desktop()->availableGeometry().height()/1.5);
}



DeviceSettingsHandler::~DeviceSettingsHandler()
{

}


bool DeviceSettingsHandler::saveDeviceSettings() const
{
    QString resoursesFolderPath = "LibraryResources";
    if ( ! QDir(resoursesFolderPath).exists()==true)
        QDir().mkdir(resoursesFolderPath);

    QFile SettFile(resoursesFolderPath + "/DeviceSettings.json");

    if(SettFile.open(QIODevice::WriteOnly))
    {
        QJsonObject SettObj;
        SettObj["DeviceSettings"] = this->toJson();

        QJsonDocument SettJson(SettObj);
        SettFile.write(SettJson.toJson());

        SettFile.close();

        qDebug()<<"device settings saved";

    }
    else
    {
        qDebug()<<"save device settings wtf";
    }
    return 1;
}


bool DeviceSettingsHandler::loadDeviceSettings()
{
    QString resoursesFolderPath = "LibraryResources";
    if ( ! QDir(resoursesFolderPath).exists()==true)
        QDir().mkdir(resoursesFolderPath);

    QFile SettingsFile(resoursesFolderPath + "/DeviceSettings.json");

    if(SettingsFile.open(QIODevice::ReadOnly))
    {
        qDebug()<<"device settings loaded";
        QByteArray in = SettingsFile.readAll();

        QJsonDocument SetJson(QJsonDocument::fromJson(in));

        QJsonObject SetObj = SetJson.object();

        if (SetObj.contains("DeviceSettings"))
        {
            SetObj = SetObj["DeviceSettings"].toObject();
            this->fromJson(SetObj);
            SettingsFile.close();
            return 1;
        }
    }

    saveDeviceSettings();
    return 1;
}


QJsonObject DeviceSettingsHandler::toJson()  const
{
    QJsonObject json;

    QJsonObject rectObj;
    rectObj["maximized"] = WindowMaximized;
    rectObj["x"] = WindowGeometry.x();
    rectObj["y"] = WindowGeometry.y();
    rectObj["w"] = WindowGeometry.width();
    rectObj["h"] = WindowGeometry.height();
    json["WindowGeometry"] = rectObj;

    json["LibraryReprezentation"] = LibraryRepresentation;
    json["LibraryIconBarSize"] = LibraryIconBarSize;
    json["LibraryIconListSize"] = LibraryIconListSize;

    json["LibrarySortOrder"] = LibrarySortOrder;
    json["LibrarySortType"] = LibrarySortType;

    return json;
}


void DeviceSettingsHandler::fromJson(const QJsonObject &json)
{
    if (json.contains("LibraryReprezentation"))
        LibraryRepresentation = json["LibraryReprezentation"].toBool();

    if (json.contains("LibraryIconBarSize"))
        LibraryIconBarSize = json["LibraryIconBarSize"].toInt();

    if (json.contains("LibraryIconListSize"))
        LibraryIconListSize = json["LibraryIconListSize"].toInt();

    if (json.contains("LibrarySortType"))
        LibrarySortType = json["LibrarySortType"].toInt();

    if (json.contains("LibrarySortOrder"))
        LibrarySortOrder = json["LibrarySortOrder"].toBool();

    if (json.contains("WindowGeometry"))
    {
        QJsonObject rectObj = json["WindowGeometry"].toObject();

        if (rectObj.contains("maximized"))
            WindowMaximized = rectObj["maximized"].toBool();

        if (rectObj.contains("x"))
            WindowGeometry.setX(rectObj["x"].toInt());
        if (rectObj.contains("y"))
            WindowGeometry.setY(rectObj["y"].toInt());
        if (rectObj.contains("w"))
            WindowGeometry.setWidth(rectObj["w"].toInt());
        if (rectObj.contains("h"))
            WindowGeometry.setHeight(rectObj["h"].toInt());

        if (WindowGeometry == QRect(0,0,0,0))
            WindowGeometry = QRect (qApp->desktop()->width()/6, qApp->desktop()->height()/6, qApp->desktop()->width()/1.5, qApp->desktop()->height()/1.5);
    }
}


bool DeviceSettingsHandler::getLibraryRepresentation() const
{
    return LibraryRepresentation;
}


void DeviceSettingsHandler::setLibraryReprezentation(const bool &val)
{
    LibraryRepresentation = val;
}


int DeviceSettingsHandler::getLibraryBarIconSize() const
{
    return LibraryIconBarSize;
}


int DeviceSettingsHandler::getLibraryListIconSize() const
{
    return LibraryIconListSize;
}


void DeviceSettingsHandler::setLibraryListIconSize(const int &size)
{
    LibraryIconListSize = size;
}


void DeviceSettingsHandler::setLibraryBarIconSize(const int &size)
{
    LibraryIconBarSize = size;
}


void DeviceSettingsHandler::setWindowGeometry(const bool &maximized, const QRect &geometry)
{
    WindowMaximized = maximized;
    WindowGeometry = geometry;
}


bool DeviceSettingsHandler::windowWasMaximized() const
{
    return WindowMaximized;
}


QRect DeviceSettingsHandler::getWindowGeometry() const
{
    return WindowGeometry;
}


int DeviceSettingsHandler::getLastOpenedWindow() const
{
    return LastOpenedWindow;
}


void DeviceSettingsHandler::setLastOpenedWindow(const unsigned int &index)
{
    LastOpenedWindow = index;
}

bool DeviceSettingsHandler::getLibrarySortOrder() const
{
    return LibrarySortOrder;
}

void DeviceSettingsHandler::setLibrarySortOrder(const int &order)
{
    LibrarySortOrder = order;
}

int DeviceSettingsHandler::getLibrarySortType() const
{
    return LibrarySortType;
}

void DeviceSettingsHandler::setLibrarySortType(const int &key)
{
    LibrarySortType = key;
}

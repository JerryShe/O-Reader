#include "device_settings.h"

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


DeviceSettings* DeviceSettings::getDeviceSettings()
{
    static DeviceSettings deviceSettings;
    return &deviceSettings;
}


DeviceSettings::DeviceSettings()
{
    LibraryRepresentation = false;
    LibraryIconBarSize = 140;
    LibraryIconListSize = 50;

    WindowMaximized = false;
    WindowGeometry = QRect (qApp->desktop()->availableGeometry().width()/6,
                            qApp->desktop()->availableGeometry().height()/6,
                            qApp->desktop()->availableGeometry().width()/1.5,
                            qApp->desktop()->availableGeometry().height()/1.5);
}



DeviceSettings::~DeviceSettings()
{

}


bool DeviceSettings::saveDeviceSettings() const
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


bool DeviceSettings::loadDeviceSettings()
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


QJsonObject DeviceSettings::toJson()  const
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

    return json;
}


void DeviceSettings::fromJson(const QJsonObject &json)
{
    if (json.contains("LibraryReprezentation"))
        LibraryRepresentation = json["LibraryReprezentation"].toBool();

    if (json.contains("LibraryIconBarSize"))
        LibraryIconBarSize = json["LibraryIconBarSize"].toInt();

    if (json.contains("LibraryIconListSize"))
        LibraryIconListSize = json["LibraryIconListSize"].toInt();

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


bool DeviceSettings::getLibraryRepresentation() const
{
    return LibraryRepresentation;
}


void DeviceSettings::setLibraryReprezentation(const bool &val)
{
    LibraryRepresentation = val;
}


int DeviceSettings::getLibraryBarIconSize() const
{
    return LibraryIconBarSize;
}


int DeviceSettings::getLibraryListIconSize() const
{
    return LibraryIconListSize;
}


void DeviceSettings::setLibraryListIconSize(const int &size)
{
    LibraryIconListSize = size;
}


void DeviceSettings::setLibraryBarIconSize(const int &size)
{
    LibraryIconBarSize = size;
}


void DeviceSettings::setWindowGeometry(const bool &maximized, const QRect &geometry)
{
    WindowMaximized = maximized;
    WindowGeometry = geometry;
}


bool DeviceSettings::windowWasMaximized() const
{
    return WindowMaximized;
}


QRect DeviceSettings::getWindowGeometry() const
{
    return WindowGeometry;
}

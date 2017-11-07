#ifndef DEVICE_SETTINGS_H
#define DEVICE_SETTINGS_H

#include <QObject>
#include <QRect>
#include <QJsonObject>

class DeviceSettings : public QObject
{
    Q_OBJECT

public:
    static DeviceSettings* getDeviceSettings();


    bool saveDeviceSettings() const;
    bool loadDeviceSettings();

    bool getLibraryRepresentation() const;
    void setLibraryReprezentation(const bool &val);

    int getLibraryBarIconSize() const;
    void setLibraryBarIconSize(const int &size);

    int getLibraryListIconSize() const;
    void setLibraryListIconSize(const int &size);

    void setWindowGeometry(const bool &maximized, const QRect &geometry);
    bool windowWasMaximized() const;
    QRect getWindowGeometry() const;

private:
    DeviceSettings();
    ~DeviceSettings();

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);


    bool LibraryRepresentation;                 // 0 - плитка, 1 - список
    int LibraryIconBarSize;
    int LibraryIconListSize;

    bool WindowMaximized;
    QRect WindowGeometry;
};

#endif // DEVICE_SETTINGS_H

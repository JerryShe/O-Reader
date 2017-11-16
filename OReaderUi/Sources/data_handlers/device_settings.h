#ifndef DEVICE_SETTINGS_H
#define DEVICE_SETTINGS_H

#include <QObject>
#include <QRect>
#include <QJsonObject>

class DeviceSettingsHandler : public QObject
{
    Q_OBJECT

public:
    static DeviceSettingsHandler* getDeviceSettings();


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

    int getLastOpenedWindow() const;
    void setLastOpenedWindow(const unsigned int &index);

    bool getLibrarySortOrder() const;
    void setLibrarySortOrder(const int &order);

    int getLibrarySortType() const;
    void setLibrarySortType(const int &key);

private:
    DeviceSettingsHandler();
    ~DeviceSettingsHandler();

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

    int LastOpenedWindow;

    bool LibraryRepresentation;                 // 0 - плитка, 1 - список
    int LibraryIconBarSize;
    int LibraryIconListSize;

    bool LibrarySortOrder;
    int LibrarySortType;

    bool WindowMaximized;
    QRect WindowGeometry;
};

#endif // DEVICE_SETTINGS_H

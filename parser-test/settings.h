#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

class settings
{
public:
    settings();
    friend QDataStream &operator<<(QDataStream &out, const settings &SettingsElem);
    friend QDataStream &operator>>(QDataStream &out, settings &SettingsElem);

private:
    bool settingsChanged;

    QString InterfaceStyle;

};

#endif // SETTINGS_H

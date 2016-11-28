#include "settings.h"

settings::settings()
{

}


QDataStream &operator<<(QDataStream &out, const settings &SettingsElem)
{
    out<<SettingsElem.InterfaceStyle;
    return out;
}


QDataStream &operator>>(QDataStream &in, settings &SettingsElem)
{
    in>>SettingsElem.InterfaceStyle;
    return in;
}

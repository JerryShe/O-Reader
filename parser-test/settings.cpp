#include "settings.h"

settings::settings()
{

}

Style::Style()
{

}

TextStyleSheet::TextStyleSheet()
{
    FontFamily = "";
    FontSize = 8;
    FontStyle = 0;
    LineSpacing = 1.5;
    TextAlign = 0;
}

TextStyleSheet::TextStyleSheet(QString Font, short Size, short Style, short Spacing, short Align)
    : FontFamily(Font), FontSize(Size), FontStyle(Style), LineSpacing(Spacing), TextAlign(Align){}


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

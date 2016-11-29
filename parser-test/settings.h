#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

struct TextStyleSheet
{
    TextStyleSheet();
    TextStyleSheet(QString Font, short Size, short Style, short Spacing, short Align);

    QString FontFamily;
    short FontSize;          // from 6 to 76
    short FontStyle;         // 00 - нормальный 01 - болд 10 - курсив 11 - болд+курсив
    short LineSpacing;       // from 0,5 to 2
    short TextAlign;         // 0 - justify, 1 - left, 2 - right, 3 - center

    friend &operator<<(QDataStream &out, TextStyleSheet &styleElem);
    friend &operator>>(QDataStream &in, TextStyleSheet &styleElem);
};

struct Style
{
    Style();

    bool BackgroundType;     //1 - color, 0 - image
    QString BackgroundImage;
    bool TextAntiAliasing;
    short ParLeftTopIdent;   //xxyy, xx - left, yy - top
    short TextLeftRightIdent;//xxyy, xx - left, yy - right
    short TextTopBottomIdent;//xxyy, xx - top, yy - bottom

    TextStyleSheet RegularTextStyle;
    TextStyleSheet TitleStyle;
    TextStyleSheet SubtitleStyle;
    TextStyleSheet NoteStyle;
};

class settings
{
public:
    settings();

    friend QDataStream &operator<<(QDataStream &out, const settings &SettingsElem);
    friend QDataStream &operator>>(QDataStream &out, settings &SettingsElem);

private:

    QString InterfaceStyle;
    short Language;

    //QMap <QString, Style> StylesMap;

};

#endif // SETTINGS_H

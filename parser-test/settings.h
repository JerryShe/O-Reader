#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QVector>
#include <QObject>

struct TextStyleSheet
{
    TextStyleSheet();
    TextStyleSheet(QString Font, short Size, short Style, short Spacing, short Align, QString color);

    QString FontFamily;
    short FontSize;          // from 6 to 76
    short FontStyle;         // 00 - нормальный 01 - болд 10 - курсив 11 - болд+курсив
    double LineSpacing;       // from 0,5 to 2
    short TextAlign;         // 0 - justify, 1 - left, 2 - right, 3 - center
    QString TextColor;

    friend QDataStream &operator<<(QDataStream &out, const TextStyleSheet &TextStyleSheetElem);
    friend QDataStream &operator>>(QDataStream &in, TextStyleSheet &TextStyleSheetElem);
};

struct ReadingStyle
{
    ReadingStyle();

    short ColumnCount;
    bool BackgroundType;     //1 - color, 0 - image
    QString BackgroundImage;
    bool TextAntiAliasing;
    short ParLeftTopIdent;   //xxyy, xx - left, yy - top
    short TextLeftRightIdent;//xxyy, xx - left, yy - right

    TextStyleSheet RegularTextStyle;
    TextStyleSheet EmphasizedTextStyle;
    TextStyleSheet TitleStyle;
    TextStyleSheet SubtitleStyle;
    TextStyleSheet NoteStyle;

    friend QDataStream &operator<<(QDataStream &out, const ReadingStyle &ReadingStyleElem);
    friend QDataStream &operator>>(QDataStream &in, ReadingStyle &ReadingStyleElem);
};

class settings : public QObject
{
public:
    settings();
    ~settings();
    void saveSettings();
    void loadSettings();

    QString getInterfaceStyle();
    void setInterfaceStyle(const QString style);

    QString getCurrentLanguage();
    void setLanguage(const QString lang);

    bool getHideTopBar();
    void setHideTopBar(bool n);

    bool getLibraryReprezentation();
    void setLibraryReprezentation(const bool val);

    short getLibraryIconSize();
    void setLibraryIconSize(const short size);

    QString getCurrentTextStyle();
    void setCurrentTextStyle(const QString style);

    QStringList getTextStylesList();
    void saveStyle(const QString name, const ReadingStyle style);

    void removeNamedStyle(QString name);

    ReadingStyle getNamedStyle(const QString name);

    friend QDataStream &operator<<(QDataStream &out, const settings &SettingsElem);
    friend QDataStream &operator>>(QDataStream &out, settings &SettingsElem);

signals:
    void loadDone(){}

private:

    QString InterfaceStyle;
    QString Language;
    bool LibraryReprezentation;
    short LibraryIconBarSize;
    short LibraryIconListSize;
    bool HideTopBar;                 // 1 - показывать всегда, 0 - показывать при наведении

    QStringList TextStylesNames;
    QVector <ReadingStyle> StylesMap;
    QString currentStyle;

};

#endif // SETTINGS_H

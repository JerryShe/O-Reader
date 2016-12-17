#include "settings.h"
#include <QVector>
#include <QDataStream>
#include <QFile>
#include <QDir>

#include <QDebug>

settings::settings()
{}

settings::~settings()
{
    saveSettings();
}

void settings::saveSettings()
{
    QString resoursesFolderPath = "LibraryResources";
    if ( ! QDir(resoursesFolderPath).exists()==true)
        QDir().mkdir(resoursesFolderPath);

    QFile SettingsFile(resoursesFolderPath + "/Settings.conf");

    if(SettingsFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QDataStream out(&SettingsFile);
        out<<*this;
    }
    else
        qDebug()<<"save settings wtf";
    SettingsFile.close();
}

void settings::loadSettings()
{
    QString resoursesFolderPath = "LibraryResources";
    if ( ! QDir(resoursesFolderPath).exists()==true)
        QDir().mkdir(resoursesFolderPath);

    QFile SettingsFile(resoursesFolderPath + "/Settings.conf");

    if(SettingsFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QDataStream in(&SettingsFile);
        in>>*this;
    }
    else
    {
        SettingsFile.open((QIODevice::WriteOnly | QIODevice::Text));
        QDataStream out(&SettingsFile);
        InterfaceStyle = "Red";
        Language = "English";
        LibraryReprezentation = false;
        HideTopBar = false;

        TextStylesNames.push_back("Standart");
        StylesMap.push_back(ReadingStyle());
        currentStyle = "Standart";
        out<<*this;
        return;
    }
    SettingsFile.close();
    emit loadDone();
}

QDataStream &operator<<(QDataStream &out, const settings &SettingsElem)
{
    out<<SettingsElem.LoginToken;
    out<<SettingsElem.InterfaceStyle;
    out<<SettingsElem.Language;
    out<<SettingsElem.LibraryReprezentation;
    out<<SettingsElem.LibraryIconBarSize;
    out<<SettingsElem.LibraryIconListSize;
    out<<SettingsElem.HideTopBar;
    out<<SettingsElem.currentStyle;
    out<<SettingsElem.TextStylesNames;
    out<<SettingsElem.StylesMap;

    return out;
}


QDataStream &operator>>(QDataStream &in, settings &SettingsElem)
{
    in>>SettingsElem.LoginToken;
    in>>SettingsElem.InterfaceStyle;
    in>>SettingsElem.Language;
    in>>SettingsElem.LibraryReprezentation;
    in>>SettingsElem.LibraryIconBarSize;
    in>>SettingsElem.LibraryIconListSize;
    in>>SettingsElem.HideTopBar;
    in>>SettingsElem.currentStyle;
    in>>SettingsElem.TextStylesNames;
    in>>SettingsElem.StylesMap;

    return in;
}


ReadingStyle::ReadingStyle()
{
    ColumnCount = 2;
    BackgroundType = 1;
    BackgroundImage = "#ffffff";
    TextAntiAliasing = false;
    ParLeftTopIdent = 1510;
    TextLeftRightIdent = 1515;    
    TextTopBottomIdent = 1515;
    RegularTextStyle = TextStyleSheet("MS Shell Dlg 2", 10, 0, 1, "Justify", "#000000");
    EmphasizedTextStyle = TextStyleSheet("MS Shell Dlg 2", 10, 2, 1, "Justify", "#000000");
    TitleStyle = TextStyleSheet("MS Shell Dlg 2", 12, 1, 1, "Center", "#000000");
    SubtitleStyle = TextStyleSheet("MS Shell Dlg 2", 10, 3, 1, "Right", "#000000");
    NoteStyle = TextStyleSheet("MS Shell Dlg 2", 8, 0, 1, "Justify", "#000000");
}

QDataStream &operator<<(QDataStream &out, const ReadingStyle &ReadingStyleElem)
{
    out<<ReadingStyleElem.ColumnCount;
    out<<ReadingStyleElem.BackgroundType;
    out<<ReadingStyleElem.BackgroundImage;
    out<<ReadingStyleElem.TextAntiAliasing;
    out<<ReadingStyleElem.ParLeftTopIdent;
    out<<ReadingStyleElem.TextLeftRightIdent;
    out<<ReadingStyleElem.TextTopBottomIdent;
    out<<ReadingStyleElem.RegularTextStyle;
    out<<ReadingStyleElem.EmphasizedTextStyle;
    out<<ReadingStyleElem.TitleStyle;
    out<<ReadingStyleElem.SubtitleStyle;
    out<<ReadingStyleElem.NoteStyle;

    return out;
}

QDataStream &operator>>(QDataStream &in, ReadingStyle &ReadingStyleElem)
{
    in>>ReadingStyleElem.ColumnCount;
    in>>ReadingStyleElem.BackgroundType;
    in>>ReadingStyleElem.BackgroundImage;
    in>>ReadingStyleElem.TextAntiAliasing;
    in>>ReadingStyleElem.ParLeftTopIdent;
    in>>ReadingStyleElem.TextLeftRightIdent;    
    in>>ReadingStyleElem.TextTopBottomIdent;
    in>>ReadingStyleElem.RegularTextStyle;
    in>>ReadingStyleElem.EmphasizedTextStyle;
    in>>ReadingStyleElem.TitleStyle;
    in>>ReadingStyleElem.SubtitleStyle;
    in>>ReadingStyleElem.NoteStyle;

    return in;
}

TextStyleSheet::TextStyleSheet()
{
    FontFamily = "MS Shell Dlg 2";
    FontSize = 8;
    FontStyle = 0;
    LineSpacing = 1.5;
    TextAlign = "Justify";
    TextColor = "#000000";
}

TextStyleSheet::TextStyleSheet(QString Font, short Size, short Style, short Spacing, QString Align, QString color)
    : FontFamily(Font), FontSize(Size), FontStyle(Style), LineSpacing(Spacing), TextAlign(Align), TextColor(color){}

QDataStream &operator <<(QDataStream &out, const TextStyleSheet &TextStyleSheetElem)
{
    out<<TextStyleSheetElem.FontFamily;
    out<<TextStyleSheetElem.FontSize;
    out<<TextStyleSheetElem.FontStyle;
    out<<TextStyleSheetElem.LineSpacing;
    out<<TextStyleSheetElem.TextAlign;
    out<<TextStyleSheetElem.TextColor;

    return out;
}

QDataStream &operator >>(QDataStream &in, TextStyleSheet &TextStyleSheetElem)
{
    in>>TextStyleSheetElem.FontFamily;
    in>>TextStyleSheetElem.FontSize;
    in>>TextStyleSheetElem.FontStyle;
    in>>TextStyleSheetElem.LineSpacing;
    in>>TextStyleSheetElem.TextAlign;
    in>>TextStyleSheetElem.TextColor;

    return in;
}


QString settings::getInterfaceStyle()
{
    return InterfaceStyle;
}

void settings::setInterfaceStyle(const QString style)
{
    InterfaceStyle = style;
}

bool settings::getLibraryReprezentation()
{
    return LibraryReprezentation;
}

void settings::setLibraryReprezentation(const bool val)
{
    LibraryReprezentation = val;
}

short settings::getLibraryIconSize()
{
    return LibraryIconBarSize;
}

/*void settings::setLibraryIconBarSize(short size)
{
    LibraryIconBarSize = size;
}*/

QString settings::getCurrentLanguage()
{
    return Language;
}

void settings::setLanguage(const QString lang)
{
    Language = lang;
}

bool settings::getHideTopBar()
{
    return HideTopBar;
}

void settings::setHideTopBar(bool n)
{
    HideTopBar = n;
}

QString settings::getCurrentTextStyle()
{
    return currentStyle;
}

void settings::setCurrentTextStyle(const QString style)
{
    currentStyle = style;
}

QStringList settings::getTextStylesList()
{
    return TextStylesNames;
}

void settings::setToken(QString token)
{
    LoginToken = token;
}

QString settings::getToken()
{
    return LoginToken;
}

ReadingStyle settings::getNamedStyle(const QString name)
{
    int index = TextStylesNames.indexOf(name);
    if (index != -1)
        return StylesMap.at(index);
    else
        qDebug()<<"style name wtf";
}

ReadingStyle settings::getCurrentTextStyleElem()
{
    return StylesMap.at(TextStylesNames.indexOf(currentStyle));
}

void settings::saveStyle(const QString name, const ReadingStyle style)
{
    if (StylesMap.size() != TextStylesNames.size())
    {
        qDebug()<<"WTF -_-";
        return;
    }
    if (TextStylesNames.indexOf(name) == -1)
    {
        TextStylesNames.push_back(name);
        StylesMap.push_back(style);
    }
    else
        StylesMap[TextStylesNames.indexOf(name)] = style;
}

void settings::removeNamedStyle(QString name)
{
    int index = TextStylesNames.indexOf(name);
    if (index != -1)
    {
        this->TextStylesNames.removeAt(index);
        this->StylesMap.removeAt(index);
    }
    else
    {
        qDebug()<<"delete style wtf";
    }
}

#include "settings.h"
#include <QVector>
#include <QDataStream>
#include <QFile>
#include <QDir>

#include <QDebug>

settings::settings()
{
    textAlignMap.insert(0, "justify");
    textAlignMap.insert(1, "left");
    textAlignMap.insert(2, "right");
    textAlignMap.insert(3, "center");
    loadSettings();
}

settings* settings::getSettings()
{
    static settings ProgramSettings;
    return &ProgramSettings;
}

void settings::setTranslator(QTranslator* translator)
{
    LanguageTranslator = translator;
}

QString settings::getTextAlignName(unsigned short key)
{
    if (textAlignMap.contains(key))
        return textAlignMap[key];
    else
        return "";
}

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
        qDebug()<<"settings saved";
        SettingsFile.close();
    }
    else
        qDebug()<<"save settings wtf";
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
        FKeyForwardPage = Qt::Key_Right;
        SKeyForwardPage = Qt::Key_Space;
        FKeyBackwardPage = Qt::Key_Left;
        SKeyBackwardPage = -1;
        PageTurnByWheel = true;
        PageTurnByTap = false;
        LibraryReprezentation = false;
        HideTopBar = false;

        LibraryReprezentation = false;
        LibraryIconBarSize = 140;
        LibraryIconListSize = 50;

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
    out<<SettingsElem.FKeyForwardPage;
    out<<SettingsElem.SKeyForwardPage;
    out<<SettingsElem.FKeyBackwardPage;
    out<<SettingsElem.SKeyBackwardPage;
    out<<SettingsElem.PageTurnByWheel;
    out<<SettingsElem.PageTurnByTap;
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
    in>>SettingsElem.FKeyForwardPage;
    in>>SettingsElem.SKeyForwardPage;
    in>>SettingsElem.FKeyBackwardPage;
    in>>SettingsElem.SKeyBackwardPage;
    in>>SettingsElem.PageTurnByWheel;
    in>>SettingsElem.PageTurnByTap;
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
    RegularTextStyle = TextStyleSheet("MS Shell Dlg 2", 10, 0, 1, 0, "#000000");
    EmphasizedTextStyle = TextStyleSheet("MS Shell Dlg 2", 10, 2, 1, 0, "#000000");
    TitleStyle = TextStyleSheet("MS Shell Dlg 2", 12, 1, 1, 3, "#000000");
    SubtitleStyle = TextStyleSheet("MS Shell Dlg 2", 10, 3, 1, 2, "#000000");
    NoteStyle = TextStyleSheet("MS Shell Dlg 2", 8, 0, 1, 1, "#000000");
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
    TextAlign = 0;
    TextColor = "#000000";
}

TextStyleSheet::TextStyleSheet(QString Font, unsigned short Size, unsigned short Style, unsigned short Spacing, unsigned short Align, QString color)
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

unsigned short settings::getLibraryBarIconSize()
{
    return LibraryIconBarSize;
}

unsigned short settings::getLibraryListIconSize()
{
    return LibraryIconBarSize;
}

void settings::setLibraryListIconSize(const unsigned short size)
{
    LibraryIconListSize = size;
}

void settings::setLibraryBarIconSize(const unsigned short size)
{
    LibraryIconBarSize = size;
}

QString settings::getCurrentLanguage()
{
    return Language;
}

void settings::setLanguage(const QString lang)
{
    Language = lang;
    bool done;
    if (lang == "Русский")
        done = LanguageTranslator->load("ru.qm", "LibraryResources/Languages");
    if (lang == "English")
        done = LanguageTranslator->load("en.qm", "LibraryResources/Languages");
    if (!done)
    {
        qDebug()<<"error in opening lang-pack";
        return;
    }
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

int settings::getFForwardKey()
{
    return FKeyForwardPage;
}

void settings::setFForwardKey(int key)
{
    FKeyForwardPage = key;
}

int settings::getSForwardKey()
{
    return SKeyForwardPage;
}

void settings::setSForwardKey(int key)
{
    SKeyForwardPage = key;
}

int settings::getFBackwardKey()
{
    return FKeyBackwardPage;
}

void settings::setFBackwardKey(int key)
{
    FKeyBackwardPage = key;
}

int settings::getSBackwardKey()
{
    return SKeyBackwardPage;
}

void settings::setSBackwardKey(int key)
{
    SKeyBackwardPage = key;
}

bool settings::getTurnByWheel()
{
    return PageTurnByWheel;
}

void settings::setTurnByWheel(bool turn)
{
    PageTurnByWheel = turn;
}

bool settings::getTurnByTap()
{
    return PageTurnByTap;
}

void settings::setTurnByTap(bool turn)
{
    PageTurnByTap = turn;
}

ReadingStyle settings::getNamedStyle(const QString name)
{
    int index = TextStylesNames.indexOf(name);
    if (index != -1)
        return StylesMap.at(index);
    else
        qDebug()<<"style name wtf";
    return StylesMap.at(0);
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

    qDebug()<<"settings saved";
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

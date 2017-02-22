#include "settings.h"
#include <QVector>
#include <QDataStream>
#include <QFile>
#include <QDir>

#include <QDebug>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

Settings::Settings()
{
    textAlignMap.insert(0, "justify");
    textAlignMap.insert(1, "left");
    textAlignMap.insert(2, "right");
    textAlignMap.insert(3, "center");
}


Settings* Settings::getSettings()
{
    static Settings ProgramSettings;
    return &ProgramSettings;
}


void Settings::setTranslator(QTranslator* translator)
{
    LanguageTranslator = translator;
}


QString Settings::getTextAlignName(const unsigned short &key)
{
    if (textAlignMap.contains(key))
        return textAlignMap[key];
    else
        return "";
}


Settings::~Settings()
{
    //saveSettings();
}


bool Settings::saveSettings()
{
    QString resoursesFolderPath = "LibraryResources";
    if ( ! QDir(resoursesFolderPath).exists()==true)
        QDir().mkdir(resoursesFolderPath);

    QFile SettFile(resoursesFolderPath + "/Settings.json");

    if(SettFile.open(QIODevice::WriteOnly))
    {
        QJsonObject SettObj;
        SettObj["Settings"] = this->toJson();

        QJsonDocument SettJson(SettObj);
        SettFile.write(SettJson.toJson());

        SettFile.close();

        qDebug()<<"settings saved";

    }
    else
    {
        qDebug()<<"save settings wtf";
    }
    return 1;
}


bool Settings::loadSettings()
{
    QString resoursesFolderPath = "LibraryResources";
    if ( ! QDir(resoursesFolderPath).exists()==true)
        QDir().mkdir(resoursesFolderPath);

    QFile SettingsFile(resoursesFolderPath + "/Settings.json");

    if(SettingsFile.open(QIODevice::ReadOnly))
    {
        qDebug()<<"settings loaded";
        QByteArray in = SettingsFile.readAll();

        QJsonDocument SetJson(QJsonDocument::fromJson(in));

        QJsonObject SetObj = SetJson.object();
        SetObj = SetObj["Settings"].toObject();

        this->fromJson(SetObj);
    }
    else
    {        
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
        TextStyles.push_back(ReadingProfile());
        currentStyle = "Standart";

        saveSettings();

        return 1;
    }
    SettingsFile.close();
    return 1;
}


QJsonObject Settings::toJson()
{
    QJsonObject json;

    json["InterfaceStyle"] = InterfaceStyle;
    json["Language"] = Language;
    json["FKeyForwardPage"] = FKeyForwardPage;
    json["SKeyForwardPage"] = SKeyForwardPage;
    json["FKeyBackwardPage"] =  FKeyBackwardPage;
    json["SKeyBackwardPage"] = SKeyBackwardPage;
    json["PageTurnByWheel"] = PageTurnByWheel;
    json["PageTurnByTap"] = PageTurnByTap;
    json["LibraryReprezentation"] = LibraryReprezentation;
    json["LibraryIconBarSize"] = (int)LibraryIconBarSize;
    json["LibraryIconListSize"] = (int)LibraryIconListSize;
    json["HideTopBar"] = HideTopBar;
    json["currentStyle"] = currentStyle;

    json["TextStylesNames"] = QJsonArray::fromStringList(TextStylesNames);

    QJsonObject Obj;
    for (int i = 0; i < TextStyles.size(); i++)
        Obj[TextStylesNames[i]] = TextStyles[i].toJson();

    json["TextStyles"] = Obj;

    return json;
}

void Settings::fromJson(const QJsonObject &json)
{
    InterfaceStyle = json["InterfaceStyle"].toString();
    Language = json["Language"].toString();
    FKeyForwardPage = json["FKeyForwardPage"].toInt();
    SKeyForwardPage = json["SKeyForwardPage"].toInt();
    FKeyBackwardPage = json["FKeyBackwardPage"].toInt();
    SKeyBackwardPage = json["SKeyBackwardPage"].toInt();
    PageTurnByWheel = json["PageTurnByWheel"].toBool();
    PageTurnByTap = json["PageTurnByTap"].toBool();
    LibraryReprezentation = json["LibraryReprezentation"].toBool();
    LibraryIconBarSize = (unsigned short)json["LibraryIconBarSize"].toInt();
    LibraryIconListSize = (unsigned short)json["LibraryIconListSize"].toInt();
    HideTopBar = json["HideTopBar"].toBool();
    currentStyle = json["currentStyle"].toString();

    TextStylesNames.clear();
    QJsonArray arr = json["TextStylesNames"].toArray();
    foreach (auto i, arr) {
        TextStylesNames.append(i.toString());
    }

    TextStyles.clear();
    QJsonObject Obj = json["TextStyles"].toObject();
    QJsonObject temp;
    for (int i = 0; i < TextStylesNames.size(); i++)
    {
        temp = Obj[TextStylesNames[i]].toObject();
        TextStyles.append(ReadingProfile(temp));
    }

}


ReadingProfile::ReadingProfile()
{
    ColumnCount = 2;
    BackgroundType = 1;
    BackgroundImage = "#ffffff";
    TextAntiAliasing = false;
    ParLeftTopIdent = 1510;
    TextLeftRightIdent = 1515;    
    TextTopBottomIdent = 1515;
    RegularStyle = TextStyleSheet("MS Shell Dlg 2", 10, 0, 1, 0, "#000000");
    EmphasizedStyle = TextStyleSheet("MS Shell Dlg 2", 10, 2, 1, 0, "#000000");
    TitleStyle = TextStyleSheet("MS Shell Dlg 2", 12, 1, 1, 3, "#000000");
    SubtitleStyle = TextStyleSheet("MS Shell Dlg 2", 10, 3, 1, 2, "#000000");
    NoteStyle = TextStyleSheet("MS Shell Dlg 2", 8, 0, 1, 1, "#000000");
}


ReadingProfile::ReadingProfile(QJsonObject &json)
{
    this->fromJson(json);
}


QJsonObject ReadingProfile::toJson()
{
    QJsonObject json;

    json["ColumnCount"] = (int)ColumnCount;
    json["BackgroundType"] = BackgroundType;
    json["BackgroundImage"] = BackgroundImage;
    json["TextAntiAliasing"] = TextAntiAliasing;
    json["ParLeftTopIdent"] = (int)ParLeftTopIdent;
    json["TextLeftRightIdent"] = (int)TextLeftRightIdent;
    json["TextTopBottomIdent"] = (int)TextTopBottomIdent;

    json["RegularTextStyle"] = RegularStyle.toJson();
    json["EmphasizedTextStyle"] = EmphasizedStyle.toJson();
    json["TitleStyle"] = TitleStyle.toJson();
    json["SubtitleStyle"] = SubtitleStyle.toJson();
    json["NoteStyle"] = NoteStyle.toJson();

    return json;
}


void ReadingProfile::fromJson(const QJsonObject &json)
{
    ColumnCount = (unsigned short)json["ColumnCount"].toInt();
    BackgroundType = json["BackgroundType"].toBool();
    BackgroundImage = json["BackgroundImage"].toString();
    TextAntiAliasing = json["TextAntiAliasing"].toBool();
    ParLeftTopIdent = (unsigned short) json["ParLeftTopIdent"].toInt();
    TextLeftRightIdent = (unsigned short)json["TextLeftRightIdent"].toInt();
    TextTopBottomIdent = (unsigned short)json["TextTopBottomIdent"].toInt();

    RegularStyle.fromJson(json["RegularTextStyle"].toObject());
    EmphasizedStyle.fromJson(json["EmphasizedTextStyle"].toObject());
    TitleStyle.fromJson(json["TitleStyle"].toObject());
    SubtitleStyle.fromJson(json["SubtitleStyle"].toObject());
    NoteStyle.fromJson(json["NoteStyle"].toObject());
}


TextStyleSheet::TextStyleSheet()
{
    Family = "MS Shell Dlg 2";
    Size = 8;
    Style = 0;
    LineSpacing = 1.5;
    Align = 0;
    Color = "#000000";
}


TextStyleSheet::TextStyleSheet(const QString &Font,
                               const unsigned short &Size,
                               const unsigned short &Style,
                               const unsigned short &Spacing,
                               const unsigned short &Align,
                               const QString &color)

                               : Family(Font),
                                 Size(Size),
                                 Style(Style),
                                 LineSpacing(Spacing),
                                 Align(Align),
                                 Color(color){}


QJsonObject TextStyleSheet::toJson()
{
    QJsonObject json;

    json["Family"] = Family;
    json["Size"] = (int)Size;
    json["Style"] = (int)Style;
    json["LineSpacing"] = LineSpacing;
    json["Align"] = (int)Align;
    json["Color"] = Color;

    return json;
}


void TextStyleSheet::fromJson(const QJsonObject &json)
{
    Family = json["Family"].toString();
    Size = (unsigned short)json["Size"].toInt();
    Style = (unsigned short)json["Style"].toInt();
    LineSpacing = json["LineSpacing"].toDouble();
    Align = (unsigned short)json["Align"].toInt();
    Color = json["Color"].toString();
}


QString TextStyleSheet::getHTMLStyle()
{
    QString tempHTML =
                       "font-family:'" + Family + "';"
                       "font-size:" + QString::number(Size) + "pt;"
                       "font-weight:" + ((Style%2)? QString("bold"):QString("normal")) + ";"
                       "line-height:" + QString::number(LineSpacing*100) + "%;"
                       "font-style:" + ((Style/2 == 1)?QString("italic"):QString("normal")) + ";"
                       "text-align:" + Settings::getSettings()->getTextAlignName(Align) + ";"
                       "color:" + Color + ";";

    return tempHTML;
}


QString Settings::getInterfaceStyle()
{
    return InterfaceStyle;
}


void Settings::setInterfaceStyle(const QString &style)
{
    InterfaceStyle = style;
}


bool Settings::getLibraryReprezentation()
{
    return LibraryReprezentation;
}


void Settings::setLibraryReprezentation(const bool &val)
{
    LibraryReprezentation = val;
}


unsigned short Settings::getLibraryBarIconSize()
{
    return LibraryIconBarSize;
}


unsigned short Settings::getLibraryListIconSize()
{
    return LibraryIconBarSize;
}


void Settings::setLibraryListIconSize(const unsigned short &size)
{
    LibraryIconListSize = size;
}


void Settings::setLibraryBarIconSize(const unsigned short &size)
{
    LibraryIconBarSize = size;
}


QString Settings::getCurrentLanguage()
{
    return Language;
}


void Settings::setLanguage(const QString &lang)
{
    Language = lang;
    bool done = false;
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


bool Settings::getHideTopBar()
{
    return HideTopBar;
}


void Settings::setHideTopBar(const bool &n)
{
    HideTopBar = n;
}


QString Settings::getCurrentReadProfileName()
{
    return currentStyle;
}


void Settings::setCurrentReadProfile(const QString &style)
{
    currentStyle = style;
}


QStringList Settings::getReadProfilesList()
{
    return TextStylesNames;
}


int Settings::getFForwardKey()
{
    return FKeyForwardPage;
}


void Settings::setFForwardKey(const int &key)
{
    FKeyForwardPage = key;
}


int Settings::getSForwardKey()
{
    return SKeyForwardPage;
}


void Settings::setSForwardKey(const int &key)
{
    SKeyForwardPage = key;
}


int Settings::getFBackwardKey()
{
    return FKeyBackwardPage;
}


void Settings::setFBackwardKey(const int &key)
{
    FKeyBackwardPage = key;
}


int Settings::getSBackwardKey()
{
    return SKeyBackwardPage;
}


void Settings::setSBackwardKey(const int &key)
{
    SKeyBackwardPage = key;
}


bool Settings::getTurnByWheel()
{
    return PageTurnByWheel;
}


void Settings::setTurnByWheel(const bool &turn)
{
    PageTurnByWheel = turn;
}


bool Settings::getTurnByTap()
{
    return PageTurnByTap;
}


void Settings::setTurnByTap(const bool &turn)
{
    PageTurnByTap = turn;
}


ReadingProfile Settings::getNamedReadProfile(const QString name)
{
    int index = TextStylesNames.indexOf(name);
    if (index != -1)
        return TextStyles.at(index);
    else
        qDebug()<<"style name wtf";
    return TextStyles.at(0);
}


ReadingProfile Settings::getCurrentReadProfileElem()
{
    return TextStyles.at(TextStylesNames.indexOf(currentStyle));
}


void Settings::saveReadProfile(const QString &name, const ReadingProfile &style)
{
    if (TextStyles.size() != TextStylesNames.size())
    {
        qDebug()<<"WTF -_-";
        return;
    }
    if (TextStylesNames.indexOf(name) == -1)
    {
        TextStylesNames.push_back(name);
        TextStyles.push_back(style);
    }
    else
        TextStyles[TextStylesNames.indexOf(name)] = style;

    qDebug()<<"style saved";
}


void Settings::removeNamedReadProfile(const QString &name)
{
    int index = TextStylesNames.indexOf(name);
    if (index != -1)
    {
        this->TextStylesNames.removeAt(index);
        this->TextStyles.removeAt(index);
    }
    else
    {
        qDebug()<<"delete style wtf";
    }
}

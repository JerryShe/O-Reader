#include "settings.h"


#include <QVector>
#include <QDataStream>
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <QDebug>


Settings::Settings()
{
    textAlignMap.insert(0, "justify");
    textAlignMap.insert(1, "left");
    textAlignMap.insert(2, "right");
    textAlignMap.insert(3, "center");

    InterfaceStyle = "Red";
    Language = "English";
    FKeyForwardPage = Qt::Key_Right;
    SKeyForwardPage = Qt::Key_Space;
    FKeyBackwardPage = Qt::Key_Left;
    SKeyBackwardPage = -1;
    PageTurnByWheel = true;
    PageTurnByTap = false;
    HideTopBar = false;
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


QString Settings::getTextAlignName(const unsigned short &key) const
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


bool Settings::saveSettings() const
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

        if (SetObj.contains("Settings"))
        {
            SetObj = SetObj["Settings"].toObject();
            this->fromJson(SetObj);
            SettingsFile.close();
            return 1;
        }
    }

    TextStylesNames.append("Standart");
    TextStyles.append(ReadingProfile());
    currentStyle = "Standart";

    saveSettings();
    return 1;
}


QJsonObject Settings::toJson() const
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
    json["HideTopBar"] = HideTopBar;
    json["CurrentStyle"] = currentStyle;

    json["TextStylesNames"] = QJsonArray::fromStringList(TextStylesNames);

    QJsonObject Obj;
    for (int i = 0; i < TextStyles.size(); i++)
        Obj[TextStylesNames[i]] = TextStyles[i].toJson();

    json["TextStyles"] = Obj;

    return json;
}


void Settings::fromJson(const QJsonObject &json)
{
    if (json.contains("InterfaceStyle"))
        InterfaceStyle = json["InterfaceStyle"].toString();

    if (json.contains("Language"))
        Language = json["Language"].toString();

    if (json.contains("FKeyForwardPage"))
        FKeyForwardPage = json["FKeyForwardPage"].toInt();

    if (json.contains("SKeyForwardPage"))
        SKeyForwardPage = json["SKeyForwardPage"].toInt();

    if (json.contains("FKeyBackwardPage"))
        FKeyBackwardPage = json["FKeyBackwardPage"].toInt();

    if (json.contains("SKeyBackwardPage"))
        SKeyBackwardPage = json["SKeyBackwardPage"].toInt();

    if (json.contains("PageTurnByWheel"))
        PageTurnByWheel = json["PageTurnByWheel"].toBool();

    if (json.contains("PageTurnByTap"))
        PageTurnByTap = json["PageTurnByTap"].toBool();

    if (json.contains("HideTopBar"))
        HideTopBar = json["HideTopBar"].toBool();

    TextStylesNames.clear();    
    if (json.contains("TextStylesNames"))
    {
        QJsonArray arr = json["TextStylesNames"].toArray();
        foreach (auto i, arr) {
            TextStylesNames.append(i.toString());
    }
    }

    TextStyles.clear();
    if (json.contains("TextStyles"))
    {
        QJsonObject Obj = json["TextStyles"].toObject();
        QJsonObject temp;
        for (int i = 0; i < TextStylesNames.size(); i++)
        {
            temp = Obj[TextStylesNames[i]].toObject();
            TextStyles.append(ReadingProfile(temp));
        }
    }


    if (json.contains("CurrentStyle"))
        currentStyle = json["CurrentStyle"].toString();
    else
    {
        if (TextStylesNames.size() != 0)
            currentStyle = TextStylesNames[0];
        else
        {
            TextStyles.append(ReadingProfile());
            TextStylesNames.append("Standart");
            currentStyle = "Standart";
        }
    }
}


ReadingProfile::ReadingProfile()
{
    ColumnCount = 2;
    ColumnIndent = 30;
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
    EpigraphStyle = TextStyleSheet("MS Shell Dlg 2", 10, 3, 1, 2, "#000000");
    CiteStyle = TextStyleSheet("MS Shell Dlg 2", 10, 2, 1, 0, "#000000");
    PoemStyle = TextStyleSheet("MS Shell Dlg 2", 10, 2, 1, 0, "#000000");
    NoteStyle = TextStyleSheet("MS Shell Dlg 2", 8, 0, 1, 1, "#000000");
}


ReadingProfile::ReadingProfile(QJsonObject &json)
{
    this->fromJson(json);
}


QJsonObject ReadingProfile::toJson()  const
{
    QJsonObject json;

    json["ColumnCount"] = (int)ColumnCount;
    json["ColumnIndent"] = (int)ColumnIndent;
    json["BackgroundType"] = BackgroundType;
    json["BackgroundImage"] = BackgroundImage;
    json["TextAntiAliasing"] = TextAntiAliasing;
    json["ParLeftTopIdent"] = (int)ParLeftTopIdent;
    json["TextLeftRightIdent"] = (int)TextLeftRightIdent;
    json["TextTopBottomIdent"] = (int)TextTopBottomIdent;

    json["Regular"] = RegularStyle.toJson();
    json["Emphasized"] = EmphasizedStyle.toJson();
    json["Title"] = TitleStyle.toJson();
    json["Subtitle"] = SubtitleStyle.toJson();
    json["Epigraph"] = EpigraphStyle.toJson();
    json["Cite"] = CiteStyle.toJson();
    json["Poem"] = PoemStyle.toJson();
    json["Note"] = NoteStyle.toJson();

    return json;
}


void ReadingProfile::fromJson(const QJsonObject &json)
{
    if (json.contains("ColumnCount"))
        ColumnCount = (unsigned short)json["ColumnCount"].toInt();

    if (json.contains("ColumnIndent"))
        ColumnIndent = (unsigned short)json["ColumnIndent"].toInt();

    if (json.contains("BackgroundType"))
        BackgroundType = json["BackgroundType"].toBool();

    if (json.contains("BackgroundImage"))
        BackgroundImage = json["BackgroundImage"].toString();

    if (json.contains("TextAntiAliasing"))
        TextAntiAliasing = json["TextAntiAliasing"].toBool();

    if (json.contains("ParLeftTopIdent"))
        ParLeftTopIdent = (unsigned short) json["ParLeftTopIdent"].toInt();

    if (json.contains("TextLeftRightIdent"))
        TextLeftRightIdent = (unsigned short)json["TextLeftRightIdent"].toInt();

    if (json.contains("TextTopBottomIdent"))
        TextTopBottomIdent = (unsigned short)json["TextTopBottomIdent"].toInt();


    if (json.contains("Regular"))
        RegularStyle.fromJson(json["Regular"].toObject());

    if (json.contains("Emphasized"))
        EmphasizedStyle.fromJson(json["Emphasized"].toObject());

    if (json.contains("Title"))
        TitleStyle.fromJson(json["Title"].toObject());

    if (json.contains("Subtitle"))
        SubtitleStyle.fromJson(json["Subtitle"].toObject());

    if (json.contains("Epigraph"))
        EpigraphStyle.fromJson(json["Epigraph"].toObject());

    if (json.contains("Cite"))
        CiteStyle.fromJson(json["Cite"].toObject());

    if (json.contains("Poem"))
        PoemStyle.fromJson(json["Poem"].toObject());

    if (json.contains("Note"))
        NoteStyle.fromJson(json["Note"].toObject());
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


QJsonObject TextStyleSheet::toJson() const
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
    if (json.contains("Family"))
        Family = json["Family"].toString();

    if (json.contains("Size"))
        Size = (unsigned short)json["Size"].toInt();

    if (json.contains("Style"))
        Style = (unsigned short)json["Style"].toInt();

    if (json.contains("LineSpacing"))
        LineSpacing = json["LineSpacing"].toDouble();

    if (json.contains("Align"))
        Align = (unsigned short)json["Align"].toInt();

    if (json.contains("Color"))
        Color = json["Color"].toString();
}


QString TextStyleSheet::getHTMLStyle() const
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


QString Settings::getCurrentLanguage() const
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


bool Settings::getHideTopBar() const
{
    return HideTopBar;
}


void Settings::setHideTopBar(const bool &n)
{
    HideTopBar = n;
}


QString Settings::getCurrentReadProfileName() const
{
    return currentStyle;
}


void Settings::setCurrentReadProfile(const QString &style)
{
    currentStyle = style;
}


QStringList Settings::getReadProfilesList() const
{
    return TextStylesNames;
}


int Settings::getFForwardKey() const
{
    return FKeyForwardPage;
}


void Settings::setFForwardKey(const int &key)
{
    FKeyForwardPage = key;
}


int Settings::getSForwardKey() const
{
    return SKeyForwardPage;
}


void Settings::setSForwardKey(const int &key)
{
    SKeyForwardPage = key;
}


int Settings::getFBackwardKey() const
{
    return FKeyBackwardPage;
}


void Settings::setFBackwardKey(const int &key)
{
    FKeyBackwardPage = key;
}


int Settings::getSBackwardKey() const
{
    return SKeyBackwardPage;
}


void Settings::setSBackwardKey(const int &key)
{
    SKeyBackwardPage = key;
}


bool Settings::getTurnByWheel() const
{
    return PageTurnByWheel;
}


void Settings::setTurnByWheel(const bool &turn)
{
    PageTurnByWheel = turn;
}


bool Settings::getTurnByTap() const
{
    return PageTurnByTap;
}


void Settings::setTurnByTap(const bool &turn)
{
    PageTurnByTap = turn;
}


ReadingProfile Settings::getNamedReadProfile(const QString name) const
{
    int index = TextStylesNames.indexOf(name);
    if (index != -1)
        return TextStyles.at(index);
    else
        qDebug()<<"style name wtf";
    return TextStyles.at(0);
}


ReadingProfile Settings::getCurrentReadProfile() const
{
    return TextStyles.at(TextStylesNames.indexOf(currentStyle));
}


void Settings::saveReadProfile(const QString &name, const ReadingProfile &style)
{
    if (TextStyles.size() != TextStylesNames.size())
        return;

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

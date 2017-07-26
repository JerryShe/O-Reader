#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QVector>
#include <QObject>
#include <QMap>
#include <QTranslator>
#include <QRect>
#include <QJsonObject>


struct TextStyleSheet
{
    TextStyleSheet();
    TextStyleSheet(const QString &Font,
                   const unsigned short &Size,
                   const unsigned short &Style,
                   const unsigned short &Spacing,
                   const unsigned short &Align,
                   const QString &color);

    QString Family;
    unsigned short Size;          // from 6 to 76
    unsigned short Style;         // 00 - нормальный 01 - болд 10 - курсив 11 - болд+курсив
    double LineSpacing;       // from 0,5 to 2
    unsigned short Align;         // 0 - justify, 1 - left, 2 - right, 3 - center
    QString Color;

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

    QString getHTMLStyle(const int &scale = 0) const;
};


struct ReadingProfile
{
    ReadingProfile();
    ReadingProfile(QJsonObject &json);

    unsigned short ColumnCount;
    unsigned short ColumnIndent;
    bool BackgroundType;     //1 - color, 0 - image
    QString BackgroundImage;
    bool TextAntiAliasing;
    unsigned short ParLeftTopIdent;   //xxyy, xx - left, yy - top
    unsigned short TextLeftRightIdent;//xxyy, xx - left, yy - right
    unsigned short TextTopBottomIdent;//xxyy, xx - top, yy - bottom

    TextStyleSheet RegularStyle;
    TextStyleSheet EmphasizedStyle;
    TextStyleSheet TitleStyle;
    TextStyleSheet SubtitleStyle;
    TextStyleSheet EpigraphStyle;
    TextStyleSheet CiteStyle;
    TextStyleSheet PoemStyle;
    TextStyleSheet NoteStyle;

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);
};


class Settings : public QObject
{
    Q_OBJECT

public:
    static Settings* getSettings();


    void setTranslator(QTranslator* translator);

    bool saveSettings() const;
    bool loadSettings();

    QString getInterfaceStyle();
    void setInterfaceStyle(const QString &style);

    QString getCurrentLanguage() const;
    void setLanguage(const QString &lang);

    bool getHideTopBar() const;
    void setHideTopBar(const bool &n);

    int getFForwardKey() const;
    void setFForwardKey(const int &key);
    int getSForwardKey() const;
    void setSForwardKey(const int &key);
    int getFBackwardKey() const;
    void setFBackwardKey(const int &key);
    int getSBackwardKey() const;
    void setSBackwardKey(const int &key);

    bool getTurnByWheel() const;
    void setTurnByWheel(const bool &turn);

    bool getTurnByTap() const;
    void setTurnByTap(const bool &turn);


    QString getCurrentReadProfileName() const;
    void setCurrentReadProfile(const QString &style);

    QStringList getReadProfilesList() const;
    void saveReadProfile(const QString &name, const ReadingProfile &style);

    void removeNamedReadProfile(const QString &name);

    ReadingProfile getNamedReadProfile(const QString name) const;
    ReadingProfile getCurrentReadProfile() const;

    QString getTextAlignName(const unsigned short &key) const;

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

private:
    Settings();
    ~Settings();


    QString InterfaceStyle;
    QString Language;
    QTranslator* LanguageTranslator;

    int FKeyForwardPage;
    int SKeyForwardPage;
    int FKeyBackwardPage;
    int SKeyBackwardPage;
    bool PageTurnByWheel;
    bool PageTurnByTap;


    bool HideTopBar;                               // 1 - показывать всегда, 0 - показывать при наведении

    QStringList TextStylesNames;
    QVector <ReadingProfile> TextStyles;
    QString currentStyle;

    QMap <unsigned short, QString> textAlignMap;
};

#endif // SETTINGS_H

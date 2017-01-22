#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QVector>
#include <QObject>
#include <QMap>
#include <QTranslator>

struct TextStyleSheet
{
    TextStyleSheet();
    TextStyleSheet(QString Font, unsigned short Size, unsigned short Style, unsigned short Spacing, unsigned short Align, QString color);

    QString FontFamily;
    unsigned short FontSize;          // from 6 to 76
    unsigned short FontStyle;         // 00 - нормальный 01 - болд 10 - курсив 11 - болд+курсив
    double LineSpacing;       // from 0,5 to 2
    unsigned short TextAlign;         // 0 - justify, 1 - left, 2 - right, 3 - center
    QString TextColor;

    friend QDataStream &operator<<(QDataStream &out, const TextStyleSheet &TextStyleSheetElem);
    friend QDataStream &operator>>(QDataStream &in, TextStyleSheet &TextStyleSheetElem);
};

struct ReadingStyle
{
    ReadingStyle();

    unsigned short ColumnCount;
    bool BackgroundType;     //1 - color, 0 - image
    QString BackgroundImage;
    bool TextAntiAliasing;
    unsigned short ParLeftTopIdent;   //xxyy, xx - left, yy - top
    unsigned short TextLeftRightIdent;//xxyy, xx - left, yy - right
    unsigned short TextTopBottomIdent;//xxyy, xx - top, yy - bottom

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
    settings(QTranslator* translator);
    ~settings();
    void saveSettings();
    void loadSettings();

    QString getInterfaceStyle();
    void setInterfaceStyle(const QString style);

    QString getCurrentLanguage();
    void setLanguage(const QString lang);

    bool getHideTopBar();
    void setHideTopBar(bool n);

    int getFForwardKey();
    void setFForwardKey(int key);
    int getSForwardKey();
    void setSForwardKey(int key);
    int getFBackwardKey();
    void setFBackwardKey(int key);
    int getSBackwardKey();
    void setSBackwardKey(int key);
    bool getTurnByWheel();
    void setTurnByWheel(bool turn);

    bool getLibraryReprezentation();
    void setLibraryReprezentation(const bool val);

    unsigned short getLibraryBarIconSize();
    void setLibraryBarIconSize(const unsigned short size);

    unsigned short getLibraryListIconSize();
    void setLibraryListIconSize(const unsigned short size);

    QString getCurrentTextStyle();
    void setCurrentTextStyle(const QString style);

    QStringList getTextStylesList();
    void saveStyle(const QString name, const ReadingStyle style);

    void setToken(QString token);
    QString getToken();

    void removeNamedStyle(QString name);

    ReadingStyle getNamedStyle(const QString name);
    ReadingStyle getCurrentTextStyleElem();

    QString getTextAlignName(unsigned short key);

    friend QDataStream &operator<<(QDataStream &out, const settings &SettingsElem);
    friend QDataStream &operator>>(QDataStream &out, settings &SettingsElem);

signals:
    void loadDone(){}

private:
    QString LoginToken;
    QString UserEmail;
    QString UserPassword;

    QString InterfaceStyle;
    QString Language;
    QTranslator* LanguageTranslator;

    int FKeyForwardPage;
    int SKeyForwardPage;
    int FKeyBackwardPage;
    int SKeyBackwardPage;
    bool PageTurnByWheel;

    bool LibraryReprezentation;      // 0 - плитка, 1 - список
    unsigned short LibraryIconBarSize;
    unsigned short LibraryIconListSize;
    bool HideTopBar;                 // 1 - показывать всегда, 0 - показывать при наведении

    QStringList TextStylesNames;
    QVector <ReadingStyle> StylesMap;
    QString currentStyle;

    QMap <unsigned short, QString> textAlignMap;
};

#endif // SETTINGS_H

#ifndef FB2TEXTPARSER_H
#define FB2TEXTPARSER_H

#include <QStringList>
#include <books.h>
#include <settings.h>

#include <QStack>
#include <QTextStream>



class FB2TextParser : public QObject
{
    Q_OBJECT

public:
    FB2TextParser(Book boo, settings* PSettings, int width, int height);
    ~FB2TextParser();

public:
    void setPageGeometry(const int width, const int height);

    void parseBookText();

    float getProgress();

    QString getPageForward();
    QString getPageBackward();

public slots:
    QString updatePage(const int width, const int height);
    QString updateSettings();

private:
    QStringList splitTextToWords(QString temp);
    QTextStream* doc;

    void setHTMLinf();
    void setFontMap();
    void setLinespaceMap();

    int getWordWidth(QString word);
    int getWordHeight();

    int getSpaceWidth();
    int getLinespaceMap();

    void applyTag();
    bool applyWord();
    bool parseTag();
    void takeTag();

    void extractTag(QString tagBeg, QString tagEnd);

    void debugSave(QString HTMLPage);

    QStringList bookText;
    unsigned int pageWidth;
    unsigned int pageHeight;

    QStringList Columns;

    unsigned int pageBegin;

    long long currentBStrNum,
              currentTextPos,
              currentEStrNum,
              strCount;

    int currentColumn;
    int currentWordPos;

    unsigned int wordWidth, wordHeight;
    unsigned int currentWidth, currentHeight;
    unsigned short stringStep;
    unsigned int stringHeight;


    bool tagType;  // 0 - open, 1 - close
    bool parseDirection;    // 0 - forward, 1 - backward

    QString columnTale;
    QString word, tag;

    Book book;
    settings *ProgramSettings;
    ReadingStyle CurStyle;

    QString PageHTMLHeader;
    QString PageHTMLBottom;
    QString PageHTMLSep;

    QStack <QString> tagStack;
    QStack <QString> beginTagStack;
    QMap <QString, QFontMetrics*> fontMap;
    QMap <QString, double> linespaceMap;
};

#endif // FB2TEXTPARSER_H

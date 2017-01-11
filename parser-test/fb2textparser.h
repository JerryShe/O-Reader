#ifndef FB2TEXTPARSER_H
#define FB2TEXTPARSER_H

#include <QStringList>
#include <books.h>
#include <settings.h>

#include <QStack>


class FB2TextParser : public QObject
{
    Q_OBJECT

public:
    FB2TextParser(Book boo, settings* PSettings, int width, int height);
    ~FB2TextParser();

public:
    void setPageGeometry(int width, int height);

    void parseBookText();

    QString getPageFrom();
    QString getPageTo();
    QString updatePage();


public slots:
    void setHTMLinf();
    void setFontMap();
    void setSpacesWidth();
    void setLinespaceMap();

private:
    int getWordWidth(QString word);
    int getWordHeight(QString word);

    int getSpaceWidth();
    int getLinespaceMap();


    QStringList bookText;
    int pageWidth;
    int pageHeight;

    QStringList Columns;
    int currentWidth;
    int currentHeight;

    int currentBStrNum;
    int currentEStrNum;

    int strCount;

    QString columnTale;

    Book book;
    settings *ProgramSettings;
    ReadingStyle CurStyle;

    QString PageHTMLHeader;
    QString PageHTMLBottom;
    QString PageHTMLSep;

    QStack <QString> tagStack;
    QMap <QString, QFontMetrics*> fontMap;
    QMap <QString, int> spacesMap;
    QMap <QString, double> linespaceMap;
};

#endif // FB2TEXTPARSER_H

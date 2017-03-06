#ifndef FB2TEXTPAGINATOR_H
#define FB2TEXTPAGINATOR_H

#include <QStringList>
#include "books.h"
#include "settings.h"

#include <QStack>
#include <QTextStream>



class FB2TextPaginator : public QObject
{
    Q_OBJECT

public:
    FB2TextPaginator();
    QString startParser(Book *OpeningBook, const int &Pwidth, const int &Pheight);
    ~FB2TextPaginator();

public:
    void setPageGeometry(const int &width, const int &height);
    void parseBookText();
    float getProgress();

    QString getPageForward();
    QString getPageBackward();

    QStringList getBookContentTable();
    long long getCurrentSectionIndex();

public slots:
    QString updatePage(const int &width, const int &height);
    QString updateSettings(const int &width, const int &height);
    QString goToSection(const int &sectionIndex);

private:
    QStringList splitTextToWords(QString temp);
    void createTableOfContents();

    QTextStream* doc;

    void setHTMLinf();
    void setFontMap();
    void setLinespaceMap();

    int getWordWidth(const QString &word);
    int getWordHeight();

    int getSpaceWidth();
    int getLinespaceMap();

    void applyTag();
    bool applyWord();
    int parseTag();
    void findTagsTail();

    void debugSave(const QString &HTMLPage);



    QStringList bookText;
    unsigned int columnWidth, columnHeight;

    QStringList Columns;
    QString HTMLPage;

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

    bool beginParagrafTail, ParagrafTail;

    QString columnTail;
    QString word, tag;



    Book *book;
    Settings *ProgramSettings;
    ReadingProfile CurProfile;

    QString PageHTMLHeader, PageHTMLBottom, PageHTMLSep;

    QStack <QString> tagStack;
    QStack <QString> beginTagStack;

    QMap <QString, QFontMetrics*> fontMap;
    QMap <QString, double> linespaceMap;

    QStringList TableOfContentsText;
    QVector <long long> TableOfContentsIndexes;

};

#endif // FB2TEXTPAGINATOR_H

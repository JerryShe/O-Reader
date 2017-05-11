#ifndef FB2TEXTPAGINATOR_H
#define FB2TEXTPAGINATOR_H


#include "books.h"
#include "settings.h"
#include "tagsresolver.h"
#include "bookimagetable.h"

#include <QStringList>
#include <QStack>



class XMLTextPaginator : public QObject
{
    Q_OBJECT

public:
    XMLTextPaginator();
    QString startParser(Book *OpeningBook, const int &Pwidth, const int &Pheight);
    ~XMLTextPaginator();

public:
    void setPageGeometry(const int &width, const int &height);
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
    void setHTMLinf();
    void setFontMap();
    void setLinespaceMap();

    int getWordWidth(const QString &word);
    int getWordHeight();
    int getWordHeightFor(QString name);

    int getSpaceWidth();
    int getLinespaceMap();

    void applyTag();
    bool applyWord();

    void commitTag();
    void commitWord();

    void doStep(int direction);

    int parseTag();    
    void findTagsTail();

    void placeImage();

    void preparePage(bool direction);
    void createHTMLPage();

    void debugSave(const QString &HTMLPage);

    QStringList bookText;
    unsigned int columnWidth, columnHeight;

    QVector <QStringList> Columns;

    int tagsLineCount;
    bool tagsLineDirection;         /// 0 - open, 1 - close
    int lastLineSize;

    QString HTMLPage;

    long long currentBStrNum,
                 currentTextPos,
                 currentEStrNum,
                 strCount;

    int currentColumn;

    unsigned int wordWidth, wordHeight;
    unsigned int currentWidth, currentHeight;
    unsigned int stringHeight;


    bool tagType;                       /// 0 - open, 1 - close
    bool parseDirection;               /// 0 - forward, 1 - backward

    bool beginParagrafTail, ParagrafTail;

    QString columnTail;
    QString word, tag;


    Book *book;
    Settings *ProgramSettings;
    ReadingProfile CurProfile;

    TagsResolver *Resolver;

    QString PageHTMLHeader, PageHTMLBottom, PageHTMLSep;

    QStack <QString> tagStack;
    QStack <QString> beginTagStack;


    QMap <QString, QFontMetrics*> fontMap;
    QMap <QString, double> linespaceMap;

    QStringList TableOfContentsText;
    QVector <long long> TableOfContentsIndexes;

    BookImageTable* ImageTable;
    QString HTMLImage;
    int HTMLImageSize;
};

#endif // FB2TEXTPAGINATOR_H

#ifndef FB2TEXTPAGINATOR_H
#define FB2TEXTPAGINATOR_H


#include "books.h"
#include "tagsresolver.h"
#include "book_image_table.h"
#include "paginatorhelper.h"

#include <QStringList>
#include <QStack>
#include<QTreeWidgetItem>



class XMLTextPaginator : public QObject
{
    Q_OBJECT

public:
    XMLTextPaginator(QObject* parent);
    QString startParser(Book *OpeningBook, const int &Pwidth, const int &Pheight);
    ~XMLTextPaginator();

    void setPageGeometry(const int &width, const int &height);
    float getProgress();

    QString getPageForward();
    QString getPageBackward();

    QTreeWidgetItem* getBookContentTable();
    long long getCurrentSectionIndex();

public slots:
    QString resizePage(const int &width, const int &height);
    QString updateSettings(const int &width, const int &height);
    QString goToSection(const long long sectionIndex);

    QString getPageNotes(const int &viewWidth);


signals:
    void notesAvailable();


private:
    int getWordWidth();
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
    unsigned short ColumnCount;
    unsigned short TextLeftRightIdent, TextTopBottomIdent;
    unsigned short ParLeftTopIdent;

    unsigned int wordWidth, wordHeight;
    unsigned int currentWidth, currentHeight;
    unsigned int stringHeight;


    bool tagType;                       /// 0 - open, 1 - close
    bool parseDirection;               /// 0 - forward, 1 - backward

    bool beginParagrafTail, ParagrafTail;

    QString columnTail;
    QString word, tag;


    Book *book;

    TagsResolver *Resolver;
    PaginatorHelper *Helper;

    QString PageHTMLStyles;
    QString PageHTMLHeader, PageHTMLBottom, PageHTMLSep;

    QStack <QString> tagStack;
    QStack <QString> beginTagStack;


    QHash <QString, QFontMetrics*> fontsMetrics;
    QHash <QString, double> fontsLinespaces;

    QTreeWidgetItem* TableOfContents;

    BookImageTable* ImageTable;
    QString HTMLImage;
    int HTMLImageSize;

    QHash <QString, QStringList> notesTable;

    QStringList PageNotes;
};

#endif // FB2TEXTPAGINATOR_H

#ifndef XML_TEXT_PAGINATOR_H
#define XML_TEXT_PAGINATOR_H


#include "books.h"
#include "tags_resolver.h"
#include "book_image_table.h"
#include "paginator_helper.h"
#include "xml_text_searcher.h"

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
    float getProgress() const;

    QTreeWidgetItem* getBookContentTable() const;

public slots:
    QString resizePage(const int &width, const int &height);
    QString updateSettings(const int &width, const int &height);
    QString refreshPage();

    QString goToPosition(const BookPosition &pos);
    QString goToSection(const long long sectionIndex);  
    QString goToBookmark(const int &index);
    QString goToNote(const int &index);

    QString getPageNote(const QString &ID, const int &viewWidth) const;

    QString getPageForward();
    QString getPageBackward();

    QString rescaleText(const bool &inc);

    QVector<BookNote> searchStart(const QString &key, const bool &caseSensitivity, const bool &punctuation, const int &previewSize);

    bool addBookmark() const;
    bool addBooknote(const QString &note) const;

    QString getTextStyles();

signals:
    void currentSearchStep(QString step);

private:    
    int tag_p();
    int tag_br();
    int tag_section();
    int tag_a();
    int tag_img();

    BookPosition getCurrentPosition() const;

    int getWordWidth() const;
    int getWordHeight() const;
    int getWordHeightFor(QString name) const;

    int getSpaceWidth() const;
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

    void debugSave(const QString &HTMLPage) const;


    /////////////////////////////////////////////////////////////////////////////////////////////

    QHash <int, int(XMLTextPaginator::*)()> TagParseFunctions;

    QStringList bookText;
    unsigned int columnWidth, columnHeight;

    QVector <QStringList> Columns;

    int tagsLineCount;
    bool tagsLineDirection;         /// 0 - open, 1 - close
    int lastLineSize;

    QString HTMLPage;

    long long pageBeginTextPos,
                 currentTextPos,
                 pageEndTextPos;

    int currentColumn;
    unsigned short ColumnCount, ColumnIndent;
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

    /////////////////////////////////////////////////////////////////////////////////////////////

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
};

#endif // XML_TEXT_PAGINATOR_H

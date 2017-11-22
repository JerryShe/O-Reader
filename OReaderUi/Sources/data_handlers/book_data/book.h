#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QVector>
#include <QPair>
#include <QDateTime>
#include <QJsonObject>
#include <QDomDocument>
#include <QStack>
#include <QImage>

#include "book_elems.h"


class Book
{
public:
    enum BookFormat
    {
        FB2 = 1,
        EPUB
    };

    enum BookContainsImages
    {
        UNKNOWN = -1,
        YES = 0,
        NO
    };

    Book();
    Book(const QJsonObject &BookJson);

    QString getFileName() const;
    bool isZipped();
    QString getZippedFileName() const;
    BookFormat getFormat() const;
    QString getIndex() const;
    QString getCodec() const;
    qint64 getAdditionalTime() const;


    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);


    QByteArray getFB2BookByteArray(bool &result);
    QDomDocument *getFB2BookDomDoc(bool &result);


    double getProgressProcent() const;
    QStack<QString> getProgressTagStack() const;

    void setProgress(const long long &progress, const bool &paragrafTail, const QStack<QString> &tagStack, const double &procent);
    BookPosition getProgress() const;

    bool addBookmark(const BookPosition &position);
    QVector <BookPosition> getBookmarks() const;
    BookPosition getBookmarkAt(const int &index) const;

    bool addBooknote(const BookPosition &position, const QString &note);
    QVector<BookNote> getBooknotes() const;
    BookNote getBooknoteAt(const int &index) const;


    QString getAuthorName() const;
    QString getTitle() const;
    QStringList getAnnotation() const;
    QStringList getGenres() const;
    QString getSeries() const;
    QString getLanguage() const;

    bool haveCoverImage() const;
    QImage getCover() const;
    void setCover(const QImage cover, const QString format);

    BookContainsImages getContainsImages() const;
    void setContainsImages(const BookContainsImages contain);

    bool getFullInfoWasLoaded() const;

private:
    BookFormat Format;
    QString File;
    QString ZippedFile;
    QString Index;
    QString Codec;    
    qint64 AdditionTime;
    BookContainsImages ContainsImages;

    QString Cover;
    QString CoverType;

    BookPosition LastBookProgress;
    double ProgressProcent = 0;

    QVector <BookPosition> Bookmarks;
    QVector <BookNote> Booknotes;


    BookTitleInfo TitleInfo;

    bool fullInfoWasLoaded;
    BookTitleInfo SrcTitleInfo;
    BookDocumentInfo DocumentInfo;
    BookPublishInfo PublishInfo;


    friend class BookCreator;
};

#endif // BOOK_H

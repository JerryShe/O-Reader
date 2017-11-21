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
    QString getHTMLCover() const;

    BookContainsImages getContainsImages() const;
    void setContainsImages(const BookContainsImages contain);

private:
    BookFormat Format;
    QString File;
    QString ZippedFile;
    QString Index;
    QString Codec;    

    QString Title;
    QString AuthorFirstName;
    QString AuthorMiddleName;
    QString AuthorLastName;
    QPair <QString, int> Series;
    QStringList Genres;
    QStringList Annotation;
    QString Language;
    QString SourceLanguage;
    qint64 AddittionTime;
    QString CoverType;
    QString Cover;
    BookContainsImages ContainsImages;            /// -1 - unknown, 0 - nope, 1 - yepe

    BookPosition lastBookProgress;
    double ProgressProcent = 0;

    QVector <BookPosition> Bookmarks;
    QVector <BookNote> Booknotes;

    friend class BookCreator;
};

#endif // BOOK_H

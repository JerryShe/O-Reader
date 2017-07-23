#ifndef BOOKBAR_H
#define BOOKBAR_H

#include <QString>
#include <QVector>
#include <QPair>
#include <QDateTime>
#include <QDataStream>
#include <QIcon>
#include <QJsonObject>
#include <QDomDocument>
#include <QStack>

#include "genresmap.h"


struct BookPosition
{
    BookPosition(const long long &position, const QStack<QString> &tagsStack, const bool &tail);
    BookPosition();
    BookPosition(const QJsonObject &json);

    virtual QJsonObject toJson() const;
    virtual void fromJson(const QJsonObject &json);

    long long TextPos;
    QStack <QString> PrevTags;
    bool ParagrafTail;
};


struct BookNote: public BookPosition
{
    BookNote();
    BookNote(const long long &position, const QStack<QString> &tagsStack, const bool &tail, QString note);
    BookNote(const BookPosition &position, const QString &note);
    BookNote(const QJsonObject &json);

    virtual QJsonObject toJson() const;
    virtual void fromJson(const QJsonObject &json);

    QString Note;
};



class Book
{
public:
    Book(bool &result, const QString &FileName, GenresMap *Gmap);
    Book(bool &result, const QString &zipFileName, const QString &fileName, const QByteArray byArr, GenresMap *Gmap);

    Book(const QJsonObject &BookJson);
    Book(){}


    QString getFileName() const;
    QString getZippedFileName() const;
    void setFile(const QString &file);

    bool isZipped();

    int getFormat() const;
    void setFormat(const int format);

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

    QDomDocument* getFB2BookDomDoc(bool &result);
    QByteArray getFB2BookByteArray(bool &result);

    long long getProgressPosition() const;
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

    QImage getCover() const;
    bool haveCoverImage() const;
    QString getHTMLCover() const;

    void setIndex(const int &index);
    unsigned int getIndex() const;

    QStringList getAnnotation() const;
    QStringList getGenres() const;
    QString getSeries() const;
    QString getLanguage() const;

    QString getCodec() const;
    void setCodec(const QString &Codec);

    int getContainImages();
    void setContainImages(const int &contain);


private:
    bool loadFB2(QDomDocument *doc, GenresMap *Gmap);
    bool loadEPub(QString fileName);


    int Format;                            /// 1 - FB2, 2 - EPub
    QString File;
    QString ZippedFile;
    unsigned int Index;
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
    QDateTime AddittionTime;
    QString CoverType;
    QString Cover;
    int ContainImages;            /// -1 - unknown, 0 - nope, 1 - yepe

    BookPosition lastBookProgress;
    double ProgressProcent = 0;

    QVector <BookPosition> Bookmarks;
    QVector <BookNote> Booknotes;
};

#endif // BOOKBAR_H

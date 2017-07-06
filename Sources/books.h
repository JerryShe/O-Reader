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

    long long TextPos;
    QStack <QString> PrevTags;
    bool ParagrafTail;
};



class Book
{
public:
    Book(bool &result, const QString &FileName, GenresMap *Gmap);
    Book(bool &result, const QString &zipFileName, const QString &fileName, const QByteArray byArr, GenresMap *Gmap);

    Book(const QJsonObject &BookJson);
    Book(){}

    void writeToConsole();

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

    long long getProgressPosition() const;
    double getProgressProcent() const;
    QStack<QString> getProgressTagStack() const;

    void setProgress(const long long &progress, const bool &paragrafTail, const QStack<QString> &tagStack, const double &procent);
    BookPosition getProgress() const;

    QString getCodec() const;
    void setCodec(const QString &Codec);

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
    double ProgressProcent = 0;
    QString CoverType;
    QString Cover;

    BookPosition lastBookProgress;

};

#endif // BOOKBAR_H

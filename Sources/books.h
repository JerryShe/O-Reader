#ifndef BOOKBAR_H
#define BOOKBAR_H

#include <QString>
#include <QVector>
#include <QPair>
#include <QDateTime>
#include <QDataStream>
#include <QIcon>

#include "genresmap.h"
#include <QJsonObject>

class Book
{
public:
    Book(bool &result, const QString &FileName, GenresMap *Gmap);
    Book(const QJsonObject &BookJson);
    Book(){}

    void writeToConsole();

    QString getAuthorName();
    QString getTitle();

    QImage getCover();
    bool haveCoverImage();
    QString getHTMLCover();

    void setBookIndex(const int &index);
    unsigned int getBookIndex();

    QStringList getAnnotation();
    QStringList getGenres();
    QString getSeries();
    QString getLanguage();

    long long getBookProgress();
    double getBookProgressPocent();
    QStringList getBookProgressTagStack();
    void setBookProgress(const long long &progress, const double &procent, const QStringList &tagStack);

    QString getBookCodec();
    void setBookCodec(const QString &Codec);

    QString getFile();
    void setFile(const QString &file);

    int getFormat();
    void setFormat(const int format);

    QJsonObject toJson();
    void fromJson(const QJsonObject &json);

private:
    bool loadFB2(QString fileName, GenresMap *Gmap);
    bool loadEPub(QString fileName);


    int Format;                            /// 1 - FB2, 2 - EPub
    QString File;
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
    long long Progress = 0;
    double ProgressProcent = 0;
    QStringList ProgressTagStack;
    QString CoverType;
    QString Cover;
};

#endif // BOOKBAR_H

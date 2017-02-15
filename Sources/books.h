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
    Book(bool &result, QString FileName, GenresMap *Gmap);
    Book(QJsonObject &BookJson);
    Book(){}

    void writeToConsole();

    QString getAuthorName();
    QString getTitle();
    QImage getCover();
    void setBookIndex(const int index);
    unsigned int getBookIndex();

    QStringList getAnnotation();
    QStringList getGenres();
    QString getSeries();
    QString getLanguage();
    long long getBookProgress();
    double getBookProgressPocent();
    QStringList getBookProgressTagStack();
    void setBookProgress(const long long progress, const double procent, QStringList tagStack);

    QString getBookCodec();
    void setBookCodec(QString Codec);
    QString File;

    QJsonObject getJson();

private:

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

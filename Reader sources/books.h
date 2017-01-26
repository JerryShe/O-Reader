#ifndef BOOKBAR_H
#define BOOKBAR_H

#include <QString>
#include <QVector>
#include <QPair>
#include <QDateTime>
#include <QDataStream>
#include <QIcon>

#include <genresmap.h>

class Book
{
public:
    Book(bool &result, QString FileName, GenresMap *Gmap);
    Book(){}
    friend QDataStream &operator<<(QDataStream &out, const Book &BookElem);
    friend QDataStream &operator>>(QDataStream &out, Book &BookElem);
    void writeToConsole();

    QString getAuthorName();
    QString getTitle();
    QImage getCover();
    void setBookIndex(const int index);
    int getBookIndex();

    QStringList getAnnotation();
    QStringList getGenres();
    QString getSeries();
    QString getLanguage();
    long long getBookProgress();
    float getBookProgressPocent();
    QStringList getBookProgressTagStack();
    void setBookProgress(const long long progress,double procent, QStringList tagStack);

    QString getBookCodec();
    void setBookCodec(QString BookCodec);
    QString File;

private:

    int BookIndex;
    QString BookCodec;

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
    float ProgressProcent = 0;
    QStringList ProgressTagStack;
    QString CoverType;
    QString Cover;
};

#endif // BOOKBAR_H

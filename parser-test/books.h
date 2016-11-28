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
    Book(QString FileName, GenresMap *Gmap);
    Book(){}
    friend QDataStream &operator<<(QDataStream &out, const Book &BookElem);
    friend QDataStream &operator>>(QDataStream &out, Book &BookElem);
    void writeToConsole();

    QString getAuthorName();
    QString getTitle();
    QImage getCover();
    void setBookIndex(int index);
    int getBookIndex();

    QStringList getAnnotation();
    QStringList getGenres();
    QString getSeries();
    QString getLanguage();
    int getBookProgress();

    QString File;

private:

    int BookIndex;
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
    double BookProgress = 0;
    QString CoverType;
    QString Cover;
};

#endif // BOOKBAR_H

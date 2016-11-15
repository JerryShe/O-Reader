#ifndef BOOKBAR_H
#define BOOKBAR_H

#include <QString>
#include <QVector>
#include <QPair>
#include <QDateTime>
#include <QDataStream>


class Book
{
public:
    Book(QString FileName);
    Book(){}
    friend QDataStream &operator<<(QDataStream &out, const Book &BookElem);
    friend QDataStream &operator>>(QDataStream &out, Book &BookElem);
    void writeToConsole();

    QString File;
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
    QByteArray Image;



};

#endif // BOOKBAR_H

#ifndef BOOKBAR_H
#define BOOKBAR_H

#include <QString>
#include <QVector>
#include <QPair>
#include <QDateTime>


class Book
{
public:
    Book(QString FileName);
    Book(){}
    void writeToFile();
    void readFromFile();

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

    QByteArray Image;
    QDateTime AddittionTime;
    double BookProgress = 0;


};

#endif // BOOKBAR_H

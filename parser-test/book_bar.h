#ifndef BOOKBAR_H
#define BOOKBAR_H

#include <QPushButton>
#include <QString>
#include <QVector>
#include <QPair>
#include <QDateTime>


class BookBar : public QPushButton
{
    Q_OBJECT

public:
    BookBar(QString FileName);
    QWidget getBarWidget();

    QString File;
    QString Title;
    QPair <QString, QString> Author;
    QPair <QString, int> Series;
    QVector <QString> Genres;
    QString Description;

    QByteArray Image;
    QDateTime DateOfPublication;
    QDateTime AddittionTime;
    double BookProgress;


};

#endif // BOOKBAR_H

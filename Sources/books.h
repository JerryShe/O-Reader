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
#include <QDomDocument>

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

    long long getProgress() const;
    double getProgressProcent();
    QStringList getProgressTagStack() const;
    void setProgress(const long long &progress, const double &procent, const QStringList &tagStack);

    QString getCodec() const;
    void setCodec(const QString &Codec);

    QString getFileName() const;
    QString getZippedFileName() const;
    void setFile(const QString &file);

    int getFormat() const;
    void setFormat(const int format);

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

private:
    bool loadFB2(QDomDocument &doc, GenresMap *Gmap);
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
    long long Progress = 0;
    double ProgressProcent = 0;
    QStringList ProgressTagStack;
    QString CoverType;
    QString Cover;
};

#endif // BOOKBAR_H

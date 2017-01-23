#include "books.h"
#include "QFile"
#include "QDomDocument"
#include <iostream>
#include <QDataStream>
#include <QImage>
#include <QIcon>
#include "genresmap.h"

#include <qdebug.h>

using namespace std;

Book::Book(QString fileName, GenresMap *Gmap)
{
    Book::File = fileName;

    Book::Progress = 0;

    QFile bookFile(fileName);
    if (bookFile.open(QIODevice::ReadOnly))
    {
        QDomDocument doc;
        if (doc.setContent(&bookFile))
        {
            bookFile.close();

            if (doc.namedItem("FictionBook").nodeName().isNull())
            {
                ///выдать эксепшн - это не фикшн бук
            }

            QDomNodeList childs = doc.childNodes();
            for (int i = 0; i < childs.size(); i++)
                if (childs.at(i).isProcessingInstruction())
                {
                    QString data = childs.at(i).toProcessingInstruction().data();
                    int j = data.indexOf("encoding");
                    if (j != -1)
                    {
                        j = data.indexOf("'", j);
                        for (j += 1; j < data.size() && j < data.indexOf("'", j); j++)
                            BookCodec += data[j];
                    }
                    break;
                }

            //файл книги
            Book::File = fileName;

            QDomNode titleInfo = doc.elementsByTagName("title-info").item(0);
            if (titleInfo.isNull())
            {
                ///выдать эксепшн - не найден title-info
            }

            //название книги
            if (! titleInfo.namedItem("book-title").isNull())
                Book::Title = titleInfo.namedItem("book-title").toElement().text();

            //имя автора
            QDomNode author = titleInfo.namedItem("author");
            if (!author.namedItem("first-name").isNull())
                Book::AuthorFirstName = author.namedItem("first-name").toElement().text();
            if (!author.namedItem("middle-name").isNull())
                Book::AuthorMiddleName = author.namedItem("middle-name").toElement().text();
            if (!author.namedItem("last-name").isNull())
                Book::AuthorLastName = author.namedItem("last-name").toElement().text();

            //жанры
            QDomNodeList nodeList = doc.elementsByTagName("genre");
            for (int i = 0; i < nodeList.length(); ++i)
                Book::Genres << Gmap->getGenreFromMap( nodeList.item(i).toElement().text() );

            //языки
            if (! titleInfo.namedItem("lang").isNull())
                Book::Language = titleInfo.namedItem("lang").toElement().text();

            if (! titleInfo.namedItem("src-lang").isNull())
                Book::SourceLanguage = titleInfo.namedItem("src-lang").toElement().text();

            //аннотация
            if (! titleInfo.namedItem("annotation").isNull())
            {
                nodeList = titleInfo.namedItem("annotation").childNodes();
                for (int i = 0; i < nodeList.size(); ++i)
                    Book::Annotation<<nodeList.item(i).toElement().text();
            }

            //книжная серия
            if (! titleInfo.namedItem("sequence").isNull())
            {
                Book::Series.first = titleInfo.namedItem("sequence").toElement().attribute("name", "");
                Book::Series.second = titleInfo.namedItem("sequence").toElement().attribute("number", "").toInt();
            }


            //дата добавления
            Book::AddittionTime = QDateTime::currentDateTime();


            //изображения
            if (!titleInfo.namedItem("coverpage").isNull())
            {
                QString coverName = titleInfo.namedItem("coverpage").namedItem("image").toElement().attribute("l:href", "");
                if (coverName.isEmpty())
                    coverName = titleInfo.namedItem("coverpage").namedItem("image").toElement().attribute("xlink:href", "");

                if (coverName.isEmpty())
                    CoverType = "noImage";
                else
                {
                    if (coverName.at(0) == '#')
                        coverName = coverName.right(coverName.size() - coverName.indexOf('#') - 1);

                    nodeList = doc.elementsByTagName("binary");
                    for (int i = 0; i < nodeList.size(); i++)
                    {
                        if (nodeList.at(i).toElement().attribute("id") == coverName)
                        {
                            CoverType = nodeList.at(i).toElement().attribute("content-type");

                            Cover = nodeList.at(i).toElement().text();

                            for (int i = 0; i < Cover.size(); i++)
                                if (Cover.at(i) == '\r' && Cover.at(i+1) == '\n')
                                {
                                    Cover.replace(i, 2, " ");
                                    i++;
                                }
                            break;
                        }
                    }
                }
            }
            else
                CoverType = "noImage";
        }
    }
}

void Book::writeToConsole()
{
    qDebug()<<Book::File;
    qDebug()<<Book::BookCodec;
    qDebug()<<Book::BookIndex;
    qDebug()<<Book::Title;
    qDebug()<<Book::AuthorFirstName;
    qDebug()<<Book::AuthorMiddleName;
    qDebug()<<Book::AuthorLastName;
    qDebug()<<Book::Annotation;
    qDebug()<<Book::SourceLanguage;
    qDebug()<<Book::Language;
    qDebug()<<Book::Genres;
    qDebug()<<Book::Series;
    qDebug()<<Book::AddittionTime;
}

QDataStream &operator <<(QDataStream &out, const Book &BookElem)
{
    out<<BookElem.File;
    out<<BookElem.BookCodec;
    out<<BookElem.Title;
    out<<BookElem.AuthorFirstName;
    out<<BookElem.AuthorMiddleName;
    out<<BookElem.AuthorLastName;
    out<<BookElem.Series.first;
    out<<BookElem.Series.second;
    out<<BookElem.Genres;
    out<<BookElem.Annotation;
    out<<BookElem.Language;
    out<<BookElem.SourceLanguage;
    out<<BookElem.AddittionTime;
    out<<BookElem.Progress;
    out<<BookElem.ProgressTagStack;
    out<<BookElem.ProgressProcent;
    out<<BookElem.CoverType;
    out<<BookElem.Cover;

    return out;
}

QDataStream &operator >> (QDataStream &in, Book &BookElem)
{
    in>>BookElem.File;
    in>>BookElem.BookCodec;
    in>>BookElem.Title;
    in>>BookElem.AuthorFirstName;
    in>>BookElem.AuthorMiddleName;
    in>>BookElem.AuthorLastName;
    in>>BookElem.Series.first;
    in>>BookElem.Series.second;
    in>>BookElem.Genres;
    in>>BookElem.Annotation;
    in>>BookElem.Language;
    in>>BookElem.SourceLanguage;
    in>>BookElem.AddittionTime;
    in>>BookElem.Progress;
    in>>BookElem.ProgressTagStack;
    in>>BookElem.ProgressProcent;
    in>>BookElem.CoverType;
    in>>BookElem.Cover;

    return in;
}

QString Book::getAuthorName()
{
        return AuthorFirstName + ' ' + AuthorLastName;
}

QString Book::getTitle()
{
    return Title;
}

QImage Book::getCover()
{
    QImage tempImage;
    if (CoverType != "noImage")
    {
        QByteArray BinaryCover = QByteArray::fromBase64(Cover.toUtf8());

        if (CoverType == "image/jpeg")
            tempImage = QImage::fromData(BinaryCover, "JPEG");
        if (CoverType == "image/jpg")
            tempImage = QImage::fromData(BinaryCover, "JPG");
        if (CoverType == "image/png")
            tempImage = QImage::fromData(BinaryCover, "PNG");
    }
    else
        tempImage = QImage(":/noImage/noImage.png");

    if (tempImage.size().width() > 200)
        tempImage = tempImage.scaledToWidth(200);
    if (tempImage.size().height() > 300)
        tempImage = tempImage.scaledToHeight(300);

    return tempImage;
}

void Book::setBookIndex(int index)
{
    BookIndex = index;
}

int Book::getBookIndex()
{
    return BookIndex;
}

QStringList Book::getAnnotation()
{
    return Annotation;
}

QStringList Book::getGenres()
{
    return Genres;
}

QString Book::getLanguage()
{
    return Language;
}

long long Book::getBookProgress()
{
    return Progress;
}

QStringList Book::getBookProgressTagStack()
{
    return ProgressTagStack;
}

float Book::getBookProgressPocent()
{
    return ProgressProcent;
}

void Book::setBookProgress(const long long progress, double procent, QStringList tagStack)
{
    Progress = progress;
    ProgressProcent = procent;
    ProgressTagStack = tagStack;
}

QString Book::getSeries()
{
    if (Series.second)
        return Series.first + ' ' + QString::number(Series.second);
    else
        return Series.first;
}

QString Book::getBookCodec()
{
    return BookCodec;
}
void Book::setBookCodec(QString codec)
{
    BookCodec = codec;
}

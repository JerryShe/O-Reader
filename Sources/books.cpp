#include "books.h"
#include <QFile>
#include <QDomDocument>
#include <QDataStream>
#include <QImage>
#include <QIcon>
#include <QUrl>
#include <QBuffer>
#include "genresmap.h"
#include "synchronization.h"

#include <qdebug.h>

using namespace std;

Book::Book(bool &result, QString fileName, GenresMap *Gmap)
{
    CoverType = "noImage";
    File = fileName;

    Progress = 0;

    QFile bookFile(fileName);
    if (bookFile.open(QIODevice::ReadOnly))
    {
        QDomDocument doc;
        if (doc.setContent(&bookFile))
        {
            bookFile.close();

            if (doc.namedItem("FictionBook").nodeName().isNull())
            {
                result = false;
                return;
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
            if (BookCodec == "")
            {
                result = false;
                return;
            }

            //файл книги
            File = fileName;

            QDomNode titleInfo = doc.elementsByTagName("title-info").item(0);
            if (titleInfo.isNull())
            {
                ///выдать сообщение - не найден title-info
            }

            //название книги
            if (! titleInfo.namedItem("book-title").isNull())
                Title = titleInfo.namedItem("book-title").toElement().text();

            //имя автора
            QDomNode author = titleInfo.namedItem("author");
            if (!author.namedItem("first-name").isNull())
                AuthorFirstName = author.namedItem("first-name").toElement().text();
            if (!author.namedItem("middle-name").isNull())
                AuthorMiddleName = author.namedItem("middle-name").toElement().text();
            if (!author.namedItem("last-name").isNull())
                AuthorLastName = author.namedItem("last-name").toElement().text();

            //жанры
            QDomNodeList nodeList = doc.elementsByTagName("genre");
            for (int i = 0; i < nodeList.length(); ++i)
                Genres << Gmap->getGenreFromMap( nodeList.item(i).toElement().text() );

            //языки
            if (! titleInfo.namedItem("lang").isNull())
                Language = titleInfo.namedItem("lang").toElement().text();

            if (! titleInfo.namedItem("src-lang").isNull())
                SourceLanguage = titleInfo.namedItem("src-lang").toElement().text();

            //аннотация
            if (! titleInfo.namedItem("annotation").isNull())
            {
                nodeList = titleInfo.namedItem("annotation").childNodes();
                for (int i = 0; i < nodeList.size(); ++i)
                    Annotation<<nodeList.item(i).toElement().text();
            }

            //книжная серия
            if (! titleInfo.namedItem("sequence").isNull())
            {
                Series.first = titleInfo.namedItem("sequence").toElement().attribute("name", "");
                Series.second = titleInfo.namedItem("sequence").toElement().attribute("number", "").toInt();
            }


            //дата добавления
            AddittionTime = QDateTime::currentDateTime();


            //изображения
            if (!titleInfo.namedItem("coverpage").isNull())
            {
                QString coverName = titleInfo.namedItem("coverpage").namedItem("image").toElement().attribute("l:href", "");
                if (coverName.isEmpty())
                {
                    coverName = titleInfo.namedItem("coverpage").namedItem("image").toElement().attribute("xlink:href", "");
                    if (coverName.isEmpty())
                    {
                        CoverType = "noImage";
                        return;
                    }
                }

                if (coverName.at(0) == '#')
                    coverName = coverName.right(coverName.size() - 1);

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

                QImage tempImage;
                QByteArray BinaryCover = QByteArray::fromBase64(Cover.toUtf8());

                if (CoverType == "image/jpeg" || CoverType == "image/jpg")
                    tempImage = QImage::fromData(BinaryCover, "JPG");
                if (CoverType == "image/png")
                    tempImage = QImage::fromData(BinaryCover, "PNG");

                if (tempImage.height() > 750 || tempImage.width() > 600)
                {
                    if (tempImage.height() > 750)
                        tempImage.scaledToHeight(750);
                    else
                        tempImage.scaledToWidth(600);

                    QByteArray ba;
                    QBuffer bu(&ba);

                    if (CoverType == "image/jpeg" || CoverType == "image/jpg")
                        tempImage.save(&bu, "JPG");
                    if (CoverType == "image/png")
                        tempImage.save(&bu, "PNG");

                    Cover = ba.toBase64();
                }
            }
            else
                CoverType = "noImage";
        }
        else
        {
            result = false;
            bookFile.close();
        }
    }
    else
        result = false;
}

void Book::writeToConsole()
{
    qDebug()<<File;
    qDebug()<<BookCodec;
    qDebug()<<BookIndex;
    qDebug()<<Title;
    qDebug()<<AuthorFirstName;
    qDebug()<<AuthorMiddleName;
    qDebug()<<AuthorLastName;
    qDebug()<<Annotation;
    qDebug()<<SourceLanguage;
    qDebug()<<Language;
    qDebug()<<Genres;
    qDebug()<<Series;
    qDebug()<<AddittionTime;
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

        if (CoverType == "image/jpeg" || CoverType == "image/jpg")
            tempImage = QImage::fromData(BinaryCover, "JPG");
        if (CoverType == "image/png")
            tempImage = QImage::fromData(BinaryCover, "PNG");
    }
    else
        tempImage = QImage(":/Images/noImage.png");

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
    Synchronization::getSynchronization()->addAction(UActions::UpdateProgress, File, Progress);
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

#include "book_creator.h"

#include <QFile>
#include <QFileInfo>
#include <QBuffer>
#include <QMimeDatabase>
#include <QMimeType>
#include <QImage>
#include <QCryptographicHash>


BookCreator::BookCreator(QObject* parent) : QObject(parent)
{

}


Book BookCreator::createFB2Book(bool &result, const QString &fileName)
{
    Book newBook;

    newBook.File = fileName;

    QFile bookFile(fileName);
    if (bookFile.open(QIODevice::ReadOnly))
    {
        QDomDocument* doc = new QDomDocument();
        if (doc->setContent(&bookFile))
        {
            bookFile.close();
            result = loadFB2(doc, newBook);
        }
        else
            result = false;

        delete doc;
        bookFile.close();
    }
    else
        result = false;

    return newBook;
}


Book BookCreator::createFB2ZippedBook(bool &result, const QString &zipFileName, const QString &fileName, const QByteArray byArr)
{
    Book newBook;

    newBook.File = zipFileName;
    newBook.ZippedFile = fileName;


    QDomDocument* doc = new QDomDocument();
    if (doc->setContent(byArr))
        result = loadFB2(doc, newBook);
    else
        result = false;

    delete doc;
    return newBook;
}


Book BookCreator::createEPUBBook(bool &result, const QString &fileName)
{

}


bool BookCreator::loadFB2(QDomDocument *doc, Book &newBook)
{
    newBook.CoverType = "noImage";
    newBook.Format = Book::BookFormat::FB2;

    if (doc->namedItem("FictionBook").nodeName().isNull())
        return false;

    QDomNodeList childs = doc->childNodes();
    for (int i = 0; i < childs.size(); i++)
        if (childs.at(i).isProcessingInstruction())
        {
            QString data = childs.at(i).toProcessingInstruction().data();
            int j = data.indexOf("encoding");
            if (j != -1)
            {
                j = data.indexOf("'", j);
                for (j += 1; j < data.size() && j < data.indexOf("'", j); j++)
                    newBook.Codec += data[j];
            }
            break;
        }
    if (newBook.Codec == "")
        return false;

    QDomNode titleInfo = doc->elementsByTagName("title-info").item(0);
    if (titleInfo.isNull())
    {
        ///выдать сообщение - не найден title-info
    }

    //название книги
    if (! titleInfo.namedItem("book-title").isNull())
        newBook.Title = titleInfo.namedItem("book-title").toElement().text();

    //имя автора
    QDomNode author = titleInfo.namedItem("author");
    if (!author.namedItem("first-name").isNull())
        newBook.AuthorFirstName = author.namedItem("first-name").toElement().text();
    if (!author.namedItem("middle-name").isNull())
        newBook.AuthorMiddleName = author.namedItem("middle-name").toElement().text();
    if (!author.namedItem("last-name").isNull())
        newBook.AuthorLastName = author.namedItem("last-name").toElement().text();

    //жанры
    QDomNodeList nodeList = doc->elementsByTagName("genre");
    for (int i = 0; i < nodeList.length(); ++i)
        newBook.Genres << genres.getFB2Genre( nodeList.item(i).toElement().text() );

    //языки
    if (! titleInfo.namedItem("lang").isNull())
        newBook.Language = titleInfo.namedItem("lang").toElement().text();

    if (! titleInfo.namedItem("src-lang").isNull())
        newBook.SourceLanguage = titleInfo.namedItem("src-lang").toElement().text();

    //аннотация
    if (! titleInfo.namedItem("annotation").isNull())
    {
        nodeList = titleInfo.namedItem("annotation").childNodes();
        for (int i = 0; i < nodeList.size(); ++i)
            newBook.Annotation<<nodeList.item(i).toElement().text();
    }

    //книжная серия
    if (! titleInfo.namedItem("sequence").isNull())
    {
        newBook.Series.first = titleInfo.namedItem("sequence").toElement().attribute("name", "");
        newBook.Series.second = titleInfo.namedItem("sequence").toElement().attribute("number", "").toInt();
    }


    //дата добавления
    newBook.AddittionTime = QDateTime::currentMSecsSinceEpoch();


    //изображения
    if (!titleInfo.namedItem("coverpage").isNull())
    {
        QString coverName = titleInfo.namedItem("coverpage").namedItem("image").toElement().attribute("l:href", "");
        if (coverName.isEmpty())
        {
            coverName = titleInfo.namedItem("coverpage").namedItem("image").toElement().attribute("xlink:href", "");
            if (coverName.isEmpty())
            {
                newBook.CoverType = "noImage";
                return true;
            }
        }

        if (coverName.at(0) == '#')
            coverName = coverName.right(coverName.size() - 1);

        nodeList = doc->elementsByTagName("binary");
        for (int i = 0; i < nodeList.size(); i++)
        {
            if (nodeList.at(i).toElement().attribute("id") == coverName)
            {
                newBook.CoverType = nodeList.at(i).toElement().attribute("content-type");
                newBook.Cover = nodeList.at(i).toElement().text();

                for (int i = 0; i < newBook.Cover.size(); i++)
                    if (newBook.Cover.at(i) == '\r' && newBook.Cover.at(i+1) == '\n')
                    {
                        newBook.Cover.replace(i, 2, " ");
                        i++;
                    }
                break;
            }
        }

        QImage tempImage;
        QByteArray BinaryCover = QByteArray::fromBase64(newBook.Cover.toUtf8());


        QMimeDatabase data;
        newBook.CoverType = data.mimeTypeForData(BinaryCover).preferredSuffix().toUpper();

        std::string str = newBook.CoverType.toStdString();
        const char* p = str.c_str();

        tempImage = QImage::fromData(BinaryCover, p);


        if (tempImage.height() > 750 || tempImage.width() > 1000)
            tempImage.scaled(750, 1000, Qt::KeepAspectRatio, Qt::SmoothTransformation);


        QByteArray ba;
        QBuffer bu(&ba);

        tempImage.save(&bu, p);

        newBook.Cover = ba.toBase64();
    }
    else
        newBook.CoverType = "noImage";

    newBook.Index = createFB2BookHash(doc->toByteArray());

    return true;
}


bool BookCreator::loadEPub()
{
    return false;
}


QString BookCreator::createFB2BookHash(const QByteArray &book)
{
    QByteArray sum = QCryptographicHash::hash(book, QCryptographicHash::Md5).toHex();
    return QString(sum);
}

#include "book_creator.h"

#include <QFile>
#include <QFileInfo>
#include <QImage>
#include <QCryptographicHash>
#include <QMimeDatabase>
#include <QMimeType>


BookCreator::BookCreator(QObject* parent) : QObject(parent)
{

}


void BookCreator::loadBookFullInfo(Book *book)
{
    bool result = true;
    QDomDocument* doc = book->getFB2BookDomDoc(result);
    if (result)
    {
        QDomNode description = doc->elementsByTagName("description").item(0);
        if (description.isNull())
            return;

        //src-title-info
        QDomNode srcTitleInfo = description.namedItem("src-title-info");
        if (!srcTitleInfo.isNull())
            parseFB2TitleInfo(srcTitleInfo, book->SrcTitleInfo);

        //document-info
        QDomNode documentInfo = description.namedItem("document-info");
        if (!documentInfo.isNull())
            parseFB2DocumentInfo(documentInfo, book->DocumentInfo);

        //publish-info
        QDomNode publishInfo = description.namedItem("publish-info");
        if (!publishInfo.isNull())
            parseFB2PublishInfo(publishInfo, book->PublishInfo);
    }

    book->fullInfoWasLoaded = true;
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

    newBook.Index = createFB2BookHash(doc->toByteArray());
    newBook.AddittionTime = QDateTime::currentMSecsSinceEpoch();


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

    QDomNode description = doc->elementsByTagName("description").item(0);
    if (description.isNull())
        return false;

    //title-info
    QDomNode titleInfo = description.namedItem("title-info");
    if (!titleInfo.isNull())
        parseFB2TitleInfo(titleInfo, newBook.TitleInfo);


    //images
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

        QString base64Cover;
        QDomNodeList nodeList = doc->elementsByTagName("binary");
        for (int i = 0; i < nodeList.size(); i++)
        {
            if (nodeList.at(i).toElement().attribute("id") == coverName)
            {
                base64Cover = nodeList.at(i).toElement().text();
                base64Cover.replace("\r\n", " ");
                break;
            }
        }

        QByteArray cover = QByteArray::fromBase64(base64Cover.toUtf8());

        QMimeDatabase data;
        QString format = data.mimeTypeForData(cover).preferredSuffix().toUpper();

        newBook.setCover(QImage::fromData(cover, format.toStdString().c_str()), format);
    }
    else
        newBook.CoverType = "noImage";

    return true;
}


void BookCreator::parseFB2TitleInfo(const QDomNode &titleInfo, BookTitleInfo &title)
{
    //genres
    QDomNodeList nodeList = titleInfo.toElement().elementsByTagName("genre");
    for (int i = 0; i < nodeList.length(); ++i)
        title.Genres << FB2GenresMap.getFB2Genre(nodeList.item(i).toElement().text() );

    //title
    if (!titleInfo.namedItem("book-title").isNull())
        title.Title = titleInfo.namedItem("book-title").toElement().text();

    //author
    QDomNode author = titleInfo.namedItem("author");
    if (!author.isNull())
        parseFB2PersonInfo(author, title.Author);

    //languages
    if (!titleInfo.namedItem("lang").isNull())
        title.Language = titleInfo.namedItem("lang").toElement().text();
    if (!titleInfo.namedItem("src-lang").isNull())
        title.SourceLanguage = titleInfo.namedItem("src-lang").toElement().text();

    //translator
    QDomNode translator = titleInfo.namedItem("translator");
    if (!translator.isNull())
        parseFB2PersonInfo(translator, title.Translator);

    //keywords
    if (!titleInfo.namedItem("keywords").isNull())
        title.Keywords = titleInfo.namedItem("keywords").toElement().text();

    //date of writing
    if (!titleInfo.namedItem("date").isNull())
        title.DateOfWriting = titleInfo.namedItem("date").toElement().text();


    //annotation
    if (!titleInfo.namedItem("annotation").isNull())
    {
        QDomNodeList nodeList = titleInfo.namedItem("annotation").childNodes();
        for (int i = 0; i < nodeList.size(); ++i)
            title.Annotation<<nodeList.item(i).toElement().text();
    }

    //series
    if (! titleInfo.namedItem("sequence").isNull())
    {
        title.Series.first = titleInfo.namedItem("sequence").toElement().attribute("name", "");
        title.Series.second = titleInfo.namedItem("sequence").toElement().attribute("number", "").toInt();
    }
}


void BookCreator::parseFB2PersonInfo(const QDomNode &personInfo, BookPerson &person)
{
    if (!personInfo.namedItem("first-name").isNull())
        person.FirstName = personInfo.namedItem("first-name").toElement().text();
    if (!personInfo.namedItem("middle-name").isNull())
        person.MiddleName = personInfo.namedItem("middle-name").toElement().text();
    if (!personInfo.namedItem("last-name").isNull())
        person.LastName = personInfo.namedItem("last-name").toElement().text();
    if (!personInfo.namedItem("nickname").isNull())
        person.Nickname = personInfo.namedItem("nickname").toElement().text();
    if (!personInfo.namedItem("home-page").isNull())
        person.HomePageUrl = personInfo.namedItem("home-page").toElement().text();
    if (!personInfo.namedItem("email").isNull())
        person.Email = personInfo.namedItem("email").toElement().text();
}


void BookCreator::parseFB2DocumentInfo(const QDomNode &documentInfo, BookDocumentInfo &info)
{
    QDomNode author = documentInfo.namedItem("author");
    if (!author.isNull())
        parseFB2PersonInfo(author, info.DocumentCreator);

    if (!documentInfo.namedItem("program-used").isNull())
        info.ProgramUsed = documentInfo.namedItem("program-used").toElement().text();

    if (!documentInfo.namedItem("date").isNull())
        info.CreationDate = documentInfo.namedItem("date").toElement().text();

    if (!documentInfo.namedItem("src-url").isNull())
        info.SrcUrl = documentInfo.namedItem("src-url").toElement().text();

    if (!documentInfo.namedItem("src-ocr").isNull())
        info.SrcOrl = documentInfo.namedItem("src-ocr").toElement().text();
}


void BookCreator::parseFB2PublishInfo(const QDomNode &publishInfo, BookPublishInfo &info)
{
    if (!publishInfo.namedItem("book-name").isNull())
        info.PublishBookName = publishInfo.namedItem("book-name").toElement().text();

    if (!publishInfo.namedItem("publisher").isNull())
        info.Publisher = publishInfo.namedItem("publisher").toElement().text();

    if (!publishInfo.namedItem("city").isNull())
        info.PublishCity = publishInfo.namedItem("city").toElement().text();

    if (!publishInfo.namedItem("year").isNull())
        info.PublishYear = publishInfo.namedItem("year").toElement().text();

    if (!publishInfo.namedItem("isbn").isNull())
        info.ISBN = publishInfo.namedItem("isbn").toElement().text();
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

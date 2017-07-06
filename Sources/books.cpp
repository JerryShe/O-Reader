#include "books.h"
#include <QFile>
#include <QDomDocument>
#include <QDataStream>
#include <QImage>
#include <QIcon>
#include <QUrl>
#include <QBuffer>

#include <QJsonArray>
#include <QJsonValue>

#include "genresmap.h"
#include "synchronization.h"

#include <QDebug>
#include <QFileInfo>

#include <QMimeType>
#include <QMimeDatabase>

#include <QtGui/private/qzipreader_p.h>


BookPosition::BookPosition(const long long &position, const QStack<QString> &tagsStack, const bool &tail)
{
    TextPos = position;
    PrevTags = tagsStack;
    ParagrafTail = tail;
}


BookPosition::BookPosition()
{
    TextPos = -1;
    ParagrafTail = false;
}


BookPosition::BookPosition(const QJsonObject &json)
{
    this->fromJson(json);
}


QJsonObject BookPosition::toJson() const
{
    QJsonObject json;

    json["TextPosition"] = QString::number(TextPos);

    QStringList temp;
    for(int i = 0; i < PrevTags.size(); i++)
        temp.append(PrevTags[i]);
    json["PrevTags"] = QJsonArray::fromStringList(temp);

    json["ParagrafTail"] = ParagrafTail;

    return json;
}


void BookPosition::fromJson(const QJsonObject &json)
{
    if (json.contains("TextPosition"))
        TextPos = json["TextPosition"].toString().toLongLong();

    if (json.contains("PrevTags"))
    {
        PrevTags.clear();
        QJsonArray tempArr = json["PrevTags"].toArray();
        for (int i = 0; i < tempArr.size(); i++)
            PrevTags.append(tempArr[i].toString());
    }

    if (json.contains("ParagrafTail"))
        ParagrafTail = json["ParagrafTail"].toBool();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Book::Book(bool &result, const QString &fileName, GenresMap *Gmap)
{
    File = fileName;
    ProgressProcent = 0;

    QFileInfo fileInfo(fileName);
    QString fileFormat = fileInfo.suffix();

    if (QString::compare(fileFormat, "fb2", Qt::CaseInsensitive) == 0)
    {
        QFile bookFile(fileName);
        if (bookFile.open(QIODevice::ReadOnly))
        {
            QDomDocument* doc = new QDomDocument();
            if (doc->setContent(&bookFile))
            {
                bookFile.close();
                result = loadFB2(doc, Gmap);
            }
            else
                result = false;

            delete doc;
        }
        else
            result = false;

        bookFile.close();
    }
    else if (QString::compare(fileFormat, "epub", Qt::CaseInsensitive) == 0)
    {

        result = loadEPub(fileName);

    }
}


//for zipped fb2
Book::Book(bool &result, const QString &zipFileName, const QString &fileName, const QByteArray byArr, GenresMap *Gmap)
{
    File = zipFileName;
    ZippedFile = fileName;


    QDomDocument *doc = new QDomDocument();
    if (doc->setContent(byArr))
        result = loadFB2(doc, Gmap);
    else
        result = false;

    delete doc;
}


QDomDocument* Book::getFB2BookDomDoc(bool &result)
{
    if (Format != 1)
    {
        result = false;
        return 0;
    }

    if (ZippedFile.isEmpty())
    {
        QFile bookFile(File);
        if (bookFile.open(QIODevice::ReadOnly))
        {
            QDomDocument* doc = new QDomDocument();
            if (doc->setContent(&bookFile))
            {
                bookFile.close();
                result = true;
                return doc;
            }
            bookFile.close();
        }
    }
    else
    {
        QZipReader zip(File);
        if (zip.exists())
        {
            QByteArray byteArr = zip.fileData(ZippedFile);
            QDomDocument* doc = new QDomDocument();
            if (doc->setContent(byteArr))
            {
                result = true;
                return doc;
            }
        }
    }

    result = false;
    return 0;
}


QByteArray Book::getFB2BookByteArray(bool &result)
{
    if (Format != 1)
    {
        result = false;
        return 0;
    }


    if (ZippedFile.isEmpty())
    {
        QFile* bookFile= new QFile(File);
        if (bookFile->open(QIODevice::ReadOnly))
        {
            QByteArray byteArr = bookFile->readAll();
            bookFile->close();
            result = true;
            return byteArr;
        }
    }
    else
    {
        QZipReader zip(File);
        if (zip.exists())
        {
            QByteArray byteArr = zip.fileData(ZippedFile);
            result = true;
            return byteArr;
        }
    }

    result = false;
    return 0;
}


bool Book::loadFB2(QDomDocument *doc, GenresMap *Gmap)
{
    CoverType = "noImage";
    Format = 1;

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
                    Codec += data[j];
            }
            break;
        }
    if (Codec == "")
        return false;

    QDomNode titleInfo = doc->elementsByTagName("title-info").item(0);
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
    QDomNodeList nodeList = doc->elementsByTagName("genre");
    for (int i = 0; i < nodeList.length(); ++i)
        Genres << Gmap->getFB2Genre( nodeList.item(i).toElement().text() );

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


        QMimeDatabase data;
        CoverType = data.mimeTypeForData(BinaryCover).preferredSuffix().toUpper();

        std::string str = CoverType.toStdString();
        const char* p = str.c_str();

        tempImage = QImage::fromData(BinaryCover, p);


        if (tempImage.height() > 750 || tempImage.width() > 1000)
            tempImage.scaled(750, 1000, Qt::KeepAspectRatio, Qt::SmoothTransformation);


        QByteArray ba;
        QBuffer bu(&ba);

        tempImage.save(&bu, p);

        Cover = ba.toBase64();
    }
    else
        CoverType = "noImage";

    return true;
}


bool Book::loadEPub(QString fileName)
{
    Format = 2;

    return false;
}


Book::Book(const QJsonObject &json)
{
    this->fromJson(json);
}


void Book::writeToConsole()
{
    qDebug()<<File;
    qDebug()<<Codec;
    qDebug()<<Index;
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


void Book::fromJson(const QJsonObject &json)
{
    QJsonArray tempArr;
    Genres.clear();
    Annotation.clear();
    lastBookProgress.PrevTags.clear();

    if (json.contains("Format"))
        Format = json["Format"].toInt();

    if (json.contains("File"))
        File = json["File"].toString();

    if (json.contains("ZippedFile"))
        ZippedFile = json["ZippedFile"].toString();

    if (json.contains("Index"))
        Index = (unsigned int)json["Index"].toInt();

    if (json.contains("Codec"))
        Codec = json["Codec"].toString();

    if (json.contains("Title"))
        Title = json["Title"].toString();

    if (json.contains("AuthorFirstName"))
        AuthorFirstName = json["AuthorFirstName"].toString();

    if (json.contains("AuthorMiddleName"))
        AuthorMiddleName = json["AuthorMiddleName"].toString();

    if (json.contains("AuthorLastName"))
        AuthorLastName = json["AuthorLastName"].toString();

    if (json.contains("SeriesFirst"))
        Series.first = json["SeriesFirst"].toString();

    if (json.contains("SeriesSecond"))
        Series.second = json["SeriesSecond"].toInt();

    if (json.contains("Genres"))
    {
        tempArr = json["Genres"].toArray();
        foreach (auto i, tempArr) {
            Genres.append(i.toString());
        }
    }

    if (json.contains("Annotation"))
    {
        tempArr = json["Annotation"].toArray();
        foreach (auto i, tempArr) {
            Annotation.append(i.toString());
        }
    }

    if (json.contains("Language"))
        Language = json["Language"].toString();

    if (json.contains("SourceLanguage"))
        SourceLanguage = json["SourceLanguage"].toString();

    if (json.contains("AddittionTime"))
        AddittionTime = QDateTime::fromString(json["AddittionTime"].toString());

    if (json.contains("CoverType"))
        CoverType = json["CoverType"].toString();

    if (json.contains("Cover"))
        Cover = json["Cover"].toString();

    if (json.contains("LastPosition"))
        lastBookProgress.fromJson(json["LastPosition"].toObject());

    if (json.contains("ProgressProcent"))
        ProgressProcent = json["ProgressProcent"].toDouble();


    if (json.contains("Bookmarks"))
    {
        tempArr = json["Bookmarks"].toArray();
        for (int i = 0; i < tempArr.size(); i++)
            Bookmarks.append(BookPosition(tempArr[i].toObject()));
    }


    if (json.contains("Booknotes"))
    {
        tempArr = json["Bookmarks"].toArray();
        for (int i = 0; i < tempArr.size(); i++)
            Booknotes.append( QPair<BookPosition, QString> (BookPosition(tempArr[i].toObject()), tempArr[i].toObject()["Note"].toString()));
    }
}


QJsonObject Book::toJson() const
{
    QJsonObject json;

    json["Format"] = Format;
    json["File"] = File;
    json["ZippedFile"] = ZippedFile;
    json["Index"] = (int)Index;
    json["Codec"] = Codec;
    json["Title"] = Title;
    json["AuthorFirstName"] = AuthorFirstName;
    json["AuthorMiddleName"] = AuthorMiddleName;
    json["AuthorLastName"] = AuthorLastName;
    json["SeriesFirst"] = Series.first;
    json["SeriesSecond"] = QString::number(Series.second);

    json["Genres"] = QJsonArray::fromStringList(Genres);

    json["Annotation"] = QJsonArray::fromStringList(Annotation);

    json["Language"] = Language;
    json["SourceLanguage"] = SourceLanguage;
    json["AddittionTime"] = AddittionTime.toString();

    json["LastPosition"] = lastBookProgress.toJson();

    json["ProgressProcent"] = ProgressProcent;
    json["CoverType"] = CoverType;
    json["Cover"] = Cover;


    QJsonArray bookmarksArr;
    for (int i = 0; i < Bookmarks.size(); i++)
        bookmarksArr.append(Bookmarks[i].toJson());
    json["Bookmarks"] = bookmarksArr;

    QJsonArray booknotesArr;
    for (int i = 0; i < Booknotes.size(); i++)
    {
        QJsonObject tempObj = Booknotes[i].first.toJson();
        tempObj["Note"] = Booknotes[i].second;
        booknotesArr.append(tempObj);
    }
    json["Booknotes"] = booknotesArr;

    return json;
}


QString Book::getAuthorName() const
{
    return AuthorFirstName + ' ' + AuthorLastName;
}


QString Book::getTitle() const
{
    return Title;
}


QImage Book::getCover() const
{
    QImage tempImage;

    if (Format == 1)
    {
        if (CoverType != "noImage")
        {
            QByteArray BinaryCover = QByteArray::fromBase64(Cover.toUtf8());

            QMimeDatabase data;
            QString type = data.mimeTypeForData(BinaryCover).preferredSuffix().toUpper();

            std::string str = type.toStdString();
            const char* p = str.c_str();

            tempImage = QImage::fromData(BinaryCover, p);
        }
        else
            tempImage = QImage(":/Images/noImage.png");

        if (tempImage.size().width() > 200)
            tempImage = tempImage.scaledToWidth(200);
        if (tempImage.size().height() > 300)
            tempImage = tempImage.scaledToHeight(300);
    }
    else if (Format == 2)
    {
        /// create epub image
    }

    return tempImage;
}


bool Book::haveCoverImage() const
{
    if (CoverType == "noImage")
        return false;
    return true;
}


QString Book::getHTMLCover() const
{
    if (CoverType != "noImage")
        return Cover;
    return "";
}


void Book::setIndex(const int &index)
{
    Index = index;
}


unsigned int Book::getIndex() const
{
    return Index;
}


QStringList Book::getAnnotation() const
{
    return Annotation;
}


QStringList Book::getGenres() const
{
    return Genres;
}


QString Book::getLanguage() const
{
    return Language;
}


long long Book::getProgressPosition() const
{
    return lastBookProgress.TextPos;
}


QStack <QString> Book::getProgressTagStack() const
{
    return lastBookProgress.PrevTags;
}


double Book::getProgressProcent() const
{
    return ProgressProcent;
}


void Book::setProgress(const long long &progress, const bool &paragrafTail, const QStack <QString> &tagStack, const double &procent)
{
    lastBookProgress.TextPos = progress;
    lastBookProgress.ParagrafTail = paragrafTail;
    lastBookProgress.PrevTags = tagStack;

    ProgressProcent = procent;

    //TODO: в синхронизацию кидать структуру и процент
    //Synchronization::getSynchronization()->addAction(UActions::UpdateProgress, File, Progress);
}


BookPosition Book::getProgress() const
{
    return lastBookProgress;
}


QString Book::getSeries() const
{
    if (Series.second)
        return Series.first + ' ' + QString::number(Series.second);
    else
        return Series.first;
}


QString Book::getCodec() const
{
    return Codec;
}


void Book::setCodec(const QString &codec)
{
    Codec = codec;
}


QString Book::getFileName() const
{
    return File;
}


QString Book::getZippedFileName() const
{
    return ZippedFile;
}


bool Book::isZipped()
{
   if (ZippedFile.isEmpty())
       return false;
   return true;
}


void Book::setFile(const QString &file)
{
    File = file;
}


int Book::getFormat()  const
{
    return Format;
}


void Book::setFormat(const int format)
{
    Format = format;
}


bool Book::addBookmark(const BookPosition &position)
{
    int i = 0;
    for (; i < Bookmarks.size(); i++)
    {
        if (position.TextPos > Bookmarks[i].TextPos)
            break;
        else if (position.TextPos == Bookmarks[i].TextPos)
            return false;
    }

    if (i == Bookmarks.size())
        Bookmarks.append(position);
    else
        Bookmarks.insert(i, position);

    return true;
}


QVector <BookPosition> Book::getBookmarks() const
{
    return Bookmarks;
}


bool Book::addBooknote(const BookPosition &position, const QString &note)
{
    int i = 0;
    for (; i < Booknotes.size(); i++)
    {
        if (position.TextPos > Booknotes[i].first.TextPos)
            break;
        else if (position.TextPos == Booknotes[i].first.TextPos)
            return false;
    }

    if (i == Booknotes.size())
        Booknotes.append(QPair <BookPosition, QString> (position, note));
    else
        Booknotes.insert(i, QPair <BookPosition, QString> (position, note));

    return true;
}


QVector <QPair <BookPosition, QString>> Book::getBooknotes() const
{
    return Booknotes;
}

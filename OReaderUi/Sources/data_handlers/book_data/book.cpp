#include <QDomDocument>
#include <QImage>
#include <QJsonArray>
#include <QJsonValue>
#include <QMimeDatabase>
#include <QMimeType>
#include <QtGui/private/qzipreader_p.h>

#include "book.h"
#include "synchronization.h"

#include <QDebug>


Book::Book()
{
    ProgressProcent = 0;
    ContainImages = -1;
}


Book::Book(const QJsonObject &json)
{
    ProgressProcent = 0;
    ContainImages = -1;

    this->fromJson(json);
}


void Book::fromJson(const QJsonObject &json)
{
    QJsonArray tempArr;
    Genres.clear();
    Annotation.clear();
    lastBookProgress.PrevTags.clear();

    if (json.contains("Format"))
        Format = static_cast <BookFormat> (json["Format"].toInt());

    if (json.contains("File"))
        File = json["File"].toString();

    if (json.contains("ZippedFile"))
        ZippedFile = json["ZippedFile"].toString();

    if (json.contains("Index"))
        Index = json["Index"].toString();

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

    if (json.contains("Images"))
        ContainImages = json["Images"].toInt();


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
            Booknotes.append( BookNote(BookPosition(tempArr[i].toObject()), tempArr[i].toObject()["Note"].toString()));
    }
}


QDomDocument* Book::getFB2BookDomDoc(bool &result)
{
    if (Format == BookFormat::FB2)
    {
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
    }

    result = false;
    return 0;
}


QByteArray Book::getFB2BookByteArray(bool &result)
{
    if (Format == BookFormat::FB2)
    {
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
    }

    result = false;
    return 0;
}


QJsonObject Book::toJson() const
{
    QJsonObject json;

    json["Format"] = (int)Format;
    json["File"] = File;
    json["ZippedFile"] = ZippedFile;
    json["Index"] = Index;
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
    json["Images"] = ContainImages;


    QJsonArray bookmarksArr;
    for (int i = 0; i < Bookmarks.size(); i++)
        bookmarksArr.append(Bookmarks[i].toJson());
    json["Bookmarks"] = bookmarksArr;

    QJsonArray booknotesArr;
    for (int i = 0; i < Booknotes.size(); i++)
        booknotesArr.append(Booknotes[i].toJson());
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

    if (Format == FB2)
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
    else if (Format == EPUB)
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


void Book::setIndex(const QString index)
{
    Index = index;
}


QString Book::getIndex() const
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


long long Book::getTextPosition() const
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


Book::BookFormat Book::getFormat()  const
{
    return Format;
}


int Book::getContainImages()
{
    return ContainImages;
}


void Book::setContainImages(const int &contain)
{
    ContainImages = contain;
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


BookPosition Book::getBookmarkAt(const int &index) const
{
    if (Bookmarks.size() > index && index >= 0)
        return Bookmarks[index];
    return BookPosition();
}


bool Book::addBooknote(const BookPosition &position, const QString &note)
{
    int i = 0;
    for (; i < Booknotes.size(); i++)
    {
        if (position.TextPos > Booknotes[i].TextPos)
            break;
        else if (position.TextPos == Booknotes[i].TextPos)
            return false;
    }

    if (i == Booknotes.size())
        Booknotes.append(BookNote(position, note));
    else
        Booknotes.insert(i, BookNote(position, note));

    return true;
}


QVector <BookNote> Book::getBooknotes() const
{
    return Booknotes;
}


BookNote Book::getBooknoteAt(const int &index) const
{
    if (Booknotes.size() > index && index >= 0)
        return Booknotes[index];
    return BookNote();
}

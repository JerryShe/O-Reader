#include <QDomDocument>
#include <QImage>
#include <QJsonArray>
#include <QJsonValue>
#include <QtGui/private/qzipreader_p.h>
#include <QBuffer>

#include "book.h"
#include "synchronization.h"

#include <QDebug>


Book::Book()
{
    ProgressProcent = 0;
    fullInfoWasLoaded = false;
    ContainsImages = BookContainsImages::UNKNOWN;
}


Book::Book(const QJsonObject &json)
{
    ProgressProcent = 0;
    fullInfoWasLoaded = false;
    ContainsImages = BookContainsImages::UNKNOWN;

    this->fromJson(json);
}


QJsonObject Book::toJson() const
{
    QJsonObject json;

    json["Index"] = Index;
    json["Format"] = (int)Format;
    json["File"] = File;
    json["ZippedFile"] = ZippedFile;
    json["Codec"] = Codec;
    json["AdditionTime"] = QString::number(AdditionTime);
    json["CoverType"] = CoverType;
    json["Cover"] = Cover;

    json["LastPosition"] = LastBookProgress.toJson();
    json["ProgressProcent"] = ProgressProcent;

    json["Images"] = (int)ContainsImages;

    json["TitleInfo"] = TitleInfo.toJson();


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


void Book::fromJson(const QJsonObject &json)
{
    QJsonArray tempArr;

    if (json.contains("Index"))
        Index = json["Index"].toString();

    if (json.contains("Format"))
        Format = static_cast <BookFormat> (json["Format"].toInt());

    if (json.contains("File"))
        File = json["File"].toString();

    if (json.contains("ZippedFile"))
        ZippedFile = json["ZippedFile"].toString();

    if (json.contains("Codec"))
        Codec = json["Codec"].toString();

    if (json.contains("TitleInfo"))
        TitleInfo.fromJson(json["TitleInfo"].toObject());

    if (json.contains("AdditionTime"))
        AdditionTime = json["AdditionTime"].toString().toULongLong();

    if (json.contains("CoverType"))
        CoverType = json["CoverType"].toString();

    if (json.contains("Cover"))
        Cover = json["Cover"].toString();

    if (json.contains("Images"))
        ContainsImages = static_cast <BookContainsImages> (json["Images"].toInt());


    if (json.contains("LastPosition"))
        LastBookProgress.fromJson(json["LastPosition"].toObject());

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


QString Book::getAuthorName() const
{
    return TitleInfo.Author.FirstName + " " + TitleInfo.Author.LastName;
}


QString Book::getTitle() const
{
    return TitleInfo.Title;
}


qint64 Book::getAdditionalTime() const
{
    return AdditionTime;
}


QImage Book::getCover() const
{
    QImage tempImage;

    if (CoverType != "noImage")
    {
        QByteArray BinaryCover = QByteArray::fromBase64(Cover.toUtf8());

        const char* p = CoverType.toStdString().c_str();

        tempImage = QImage::fromData(BinaryCover, p);
    }
    else
        tempImage = QImage(":/Images/noImage.png");

    if (tempImage.size().width() > 250)
        tempImage = tempImage.scaledToWidth(250);
    if (tempImage.size().height() > 350)
        tempImage = tempImage.scaledToHeight(350);

    return tempImage;
}


void Book::setCover(const QImage cover, const QString format)
{
    CoverType = format;

    if (cover.height() > 500 || cover.width() > 750)
        cover.scaled(750, 1000, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QByteArray ba;
    QBuffer bu(&ba);

    cover.save(&bu, format.toStdString().c_str());

    Cover = ba.toBase64();
}


bool Book::haveCoverImage() const
{
    if (CoverType == "noImage")
        return false;
    return true;
}


QString Book::getIndex() const
{
    return Index;
}


QStringList Book::getAnnotation() const
{
    return TitleInfo.Annotation;
}


QStringList Book::getGenres() const
{
    return TitleInfo.Genres;
}


QString Book::getLanguage() const
{
    return TitleInfo.Language;
}


QStack <QString> Book::getProgressTagStack() const
{
    return LastBookProgress.PrevTags;
}


double Book::getProgressProcent() const
{
    return ProgressProcent;
}


void Book::setProgress(const long long &progress, const bool &paragrafTail, const QStack <QString> &tagStack, const double &procent)
{
    LastBookProgress.TextPos = progress;
    LastBookProgress.ParagrafTail = paragrafTail;
    LastBookProgress.PrevTags = tagStack;

    ProgressProcent = procent;

    //Synchronization::getSynchronization()->addAction(UActions::UpdateProgress, File, Progress);
}


BookPosition Book::getProgress() const
{
    return LastBookProgress;
}


QString Book::getSeries() const
{
    if (TitleInfo.Series.second)
        return TitleInfo.Series.first + ' ' + QString::number(TitleInfo.Series.second);
    else
        return TitleInfo.Series.first;
}


QString Book::getCodec() const
{
    return Codec;
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


Book::BookContainsImages Book::getContainsImages() const
{
    return ContainsImages;
}


void Book::setContainsImages(const BookContainsImages contain)
{
    ContainsImages = contain;
}


bool Book::getFullInfoWasLoaded() const
{
    return fullInfoWasLoaded;
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

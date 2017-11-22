#include "book_elems.h"

#include <QJsonObject>
#include <QJsonArray>

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



BookNote::BookNote()
{}


BookNote::BookNote(const long long &position, const QStack<QString> &tagsStack, const bool &tail, QString note)
{
    TextPos = position;
    PrevTags = tagsStack;
    ParagrafTail = tail;
    Note = note;
}


BookNote::BookNote(const BookPosition &position, const QString &note)
{
    TextPos = position.TextPos;
    PrevTags = position.PrevTags;
    ParagrafTail = position.ParagrafTail;
    Note = note;
}


BookNote::BookNote(const QJsonObject &json)
{
    fromJson(json);
}


void BookNote::fromJson(const QJsonObject &json)
{
    if (json.contains("Note"))
        Note = json["Note"].toString();
    BookPosition::fromJson(json);
}


QJsonObject BookNote::toJson() const
{
    QJsonObject json = BookPosition::toJson();
    json["Note"] = Note;

    return json;
}


QJsonObject BookTitleInfo::toJson() const
{
    QJsonObject json;

    json["Title"] = Title;

    QJsonArray authors;
    for (int i = 0; i < Authors.size(); ++i)
        authors.append(Authors[i].toJson());
    json["Authors"] = authors;

    json["SeriesFirst"] = Series.first;
    json["SeriesSecond"] = QString::number(Series.second);

    json["Genres"] = QJsonArray::fromStringList(Genres);

    json["Annotation"] = QJsonArray::fromStringList(Annotation);

    json["Language"] = Language;
    json["SourceLanguage"] = SourceLanguage;

    return json;
}


void BookTitleInfo::fromJson(const QJsonObject &json)
{
    QJsonArray tempArr;

    if (json.contains("Title"))
        Title = json["Title"].toString();

    if (json.contains("Authors"))
    {
        QJsonArray authors = json["Authors"].toArray();
        foreach (auto person, authors) {
            BookPerson author;
            author.fromJson(person.toObject());
            Authors.append(author);
        }
    }

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
}


QJsonObject BookPerson::toJson() const
{
    QJsonObject json;
    json["FirstName"] = FirstName;
    json["MiddleName"] = MiddleName;
    json["LastName"] = LastName;
    return json;
}


void BookPerson::fromJson(const QJsonObject &json)
{
    if (json.contains("FirstName"))
        FirstName = json["FirstName"].toString();

    if (json.contains("MiddleName"))
        MiddleName = json["MiddleName"].toString();

    if (json.contains("LastName"))
        LastName = json["LastName"].toString();
}

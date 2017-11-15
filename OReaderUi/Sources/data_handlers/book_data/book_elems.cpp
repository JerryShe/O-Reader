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

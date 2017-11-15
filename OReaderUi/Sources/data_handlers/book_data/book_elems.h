#ifndef BOOK_ELMS_H
#define BOOK_ELMS_H

#include <QStack>
#include <QJsonObject>

struct BookPosition
{
    BookPosition(const long long &position, const QStack<QString> &tagsStack, const bool &tail);
    BookPosition();
    BookPosition(const QJsonObject &json);

    virtual QJsonObject toJson() const;
    virtual void fromJson(const QJsonObject &json);

    long long TextPos;
    QStack <QString> PrevTags;
    bool ParagrafTail;
};


struct BookNote: public BookPosition
{
    BookNote();
    BookNote(const long long &position, const QStack<QString> &tagsStack, const bool &tail, QString note);
    BookNote(const BookPosition &position, const QString &note);
    BookNote(const QJsonObject &json);

    virtual QJsonObject toJson() const;
    virtual void fromJson(const QJsonObject &json);

    QString Note;
};

#endif // BOOK_ELMS_H

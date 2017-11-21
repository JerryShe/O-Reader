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




struct BookPerson
{
    QString FirstName;
    QString MiddleName;
    QString LastName;
    QString Nickname;
    QString HomePageUrl;
    QString Email;
};


struct BookTitleInfo
{
   BookPerson Author;
   QString Title;

   QPair <QString, int> Series;
   QStringList Genres;
   QStringList Annotation;
   QString Language;
   QString SourceLanguage;

   QString Keywords;
   QString DateOfWriting;

   BookPerson Translator;


   QJsonObject toJson() const;
   void fromJson(const QJsonObject &json);
};


struct BookDocumentInfo
{
    BookPerson DocumentCreator;
    QString ProgramUsed;
    QString CreationDate;
    QString SrcUrl;
    QString SrcOrl;
};


struct BookPublishInfo
{
    QString PublishBookName;
    QString Publisher;
    QString PublishCity;
    QString PublishYear;
    QString ISBN;
};

#endif // BOOK_ELMS_H

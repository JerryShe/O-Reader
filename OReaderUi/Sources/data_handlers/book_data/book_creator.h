#ifndef BOOK_CREATOR_H
#define BOOK_CREATOR_H

#include <QObject>
#include <QDomDocument>

#include "book.h"
#include "book_elems.h"
#include "genres_map.h"


class BookCreator : public QObject
{
    Q_OBJECT

public:
    BookCreator(QObject* parent = nullptr);

    void loadBookFullInfo(Book *book);

    Book createFB2Book(bool &result, const QString &fileName);
    Book createFB2ZippedBook(bool &result, const QString &zipFileName, const QString &fileName, const QByteArray byArr);
    Book createEPUBBook(bool &result, const QString &fileName);

private:
    GenresMap FB2GenresMap;

    bool loadFB2(QDomDocument *doc, Book &newBook);
    bool loadEPub();


    void parseFB2TitleInfo(const QDomNode &titleInfo, BookTitleInfo &title);
    void parseFB2PersonInfo(const QDomNode &personInfo, BookPerson &person);
    void parseFB2DocumentInfo(const QDomNode &documentInfo, BookDocumentInfo &info);
    void parseFB2PublishInfo(const QDomNode &publishInfo, BookPublishInfo &info);


    QString createFB2BookHash(const QByteArray &book);
};

#endif // BOOK_CREATOR_H

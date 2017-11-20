#ifndef BOOK_CREATOR_H
#define BOOK_CREATOR_H

#include <QObject>
#include <QDomDocument>

#include "book.h"
#include "genres_map.h"


class BookCreator : public QObject
{
    Q_OBJECT

public:
    BookCreator(QObject* parent = nullptr);

    Book createFB2Book(bool &result, const QString &fileName);
    Book createFB2ZippedBook(bool &result, const QString &zipFileName, const QString &fileName, const QByteArray byArr);
    Book createEPUBBook(bool &result, const QString &fileName);

private:
    GenresMap genres;

    bool loadFB2(QDomDocument *doc, Book &newBook);
    bool loadEPub();

    QString createFB2BookHash(const QByteArray &book);
};

#endif // BOOK_CREATOR_H

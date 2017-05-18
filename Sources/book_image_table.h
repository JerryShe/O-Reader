#ifndef BOOK_IMAGETABLE_H
#define BOOK_IMAGETABLE_H


#include <QHash>
#include <QImage>

#include <books.h>

class BookImageTable
{
public:
    BookImageTable();
    BookImageTable(Book *book);
    ~BookImageTable();

    void addImage(QString name, QString img, QString format);

    bool contains(QString imgName);

    QPair<QString, unsigned int> getHTMLImage(QString name, int freeHeight, int pageWidth, int pageHeight);

    QVector<QImage> getBookImages();

private:
    void createFromFB2(Book* book);
    void createFromEPub(Book* book);

    QHash <QString, QImage> ImageMap;
};

#endif // BOOK_IMAGETABLE_H

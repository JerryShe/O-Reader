#ifndef BOOKIMAGETABLE_H
#define BOOKIMAGETABLE_H

#include <QHash>
#include <QImage>

#include "data_handlers/book.h"

class BookImageTable
{
public:
    BookImageTable();
    BookImageTable(Book *book);
    ~BookImageTable();

    void addImage(QString name, QString img, QString format);

    bool contains(QString imgName) const;

    QPair<QString, unsigned int> getHTMLImage(QString name, int freeHeight, int pageWidth, int pageHeight) const;

    QVector<QImage> getBookImages() const;

private:
    void createFromFB2(Book* book);
    void createFromEPub(Book* book);

    QHash <QString, QImage> ImageMap;
};

#endif // BOOKIMAGETABLE_H

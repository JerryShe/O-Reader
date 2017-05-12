#ifndef BOOKIMAGETABLE_H
#define BOOKIMAGETABLE_H


#include <QHash>
#include <QImage>

class BookImageTable
{
public:
    BookImageTable();
    ~BookImageTable();

    void addImage(QString name, QString img, QString format);
    bool contains(QString imgName);
    QPair<QString, unsigned int> getImage(QString name, int freeHeight, int pageWidth, int pageHeight);

private:
    QHash <QString, QImage> ImageMap;
};

#endif // BOOKIMAGETABLE_H

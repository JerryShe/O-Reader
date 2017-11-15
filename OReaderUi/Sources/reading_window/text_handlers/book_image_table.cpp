#include"reading_window/text_handlers/book_image_table.h"

#include <QBuffer>
#include <QDomDocument>
#include <QMimeType>
#include <QMimeDatabase>
#include <QFile>
#include <QtGui/private/qzipreader_p.h>

#include <QDebug>


BookImageTable::BookImageTable()
{
    qDebug()<<"create BookImageTable";
}


BookImageTable::BookImageTable(Book *book)
{
    if (book->getFormat() == Book::BookFormat::FB2)
        createFromFB2(book);
    else if (book->getFormat() == Book::BookFormat::EPUB)
        createFromEPub(book);
    qDebug()<<"create BookImageTable";
}


BookImageTable::~BookImageTable()
{
    qDebug()<<"delete BookImageTable";
}


void BookImageTable::createFromEPub(Book *book)
{

}


void BookImageTable::createFromFB2(Book *book)
{
    bool result;
    QDomDocument* doc = book->getFB2BookDomDoc(result);

    if (!result)
        return;


    QDomNodeList nodeList = doc->elementsByTagName("binary");
    for (int i = 0; i < nodeList.size(); i++)
    {
        QString name = nodeList.at(i).toElement().attribute("id");
        QString image = nodeList.at(i).toElement().text();

        QByteArray BinaryCover = QByteArray::fromBase64(image.toUtf8());

        QMimeDatabase data;
        if (!data.mimeTypeForData(BinaryCover).name().contains("image"))
            continue;

        QString type = data.mimeTypeForData(BinaryCover).preferredSuffix().toUpper();

        addImage(name, image, type);
    }
}


void BookImageTable::addImage(QString name, QString img, QString format)
{
    QImage tempImage;
    QByteArray BinaryCover = QByteArray::fromBase64(img.toUtf8());

    std::string str = format.toStdString();
    const char* p = str.c_str();

    tempImage = QImage::fromData(BinaryCover, p);

    if (!ImageMap.contains(name))
        ImageMap.insert(name, tempImage);
}


bool BookImageTable::contains(QString imgName) const
{
    return ImageMap.contains(imgName);
}


QPair <QString, unsigned int> BookImageTable::getHTMLImage(QString name, int freeHeight, int pageWidth, int pageHeight) const
{
    if (!ImageMap.contains(name))
        return QPair<QString, int> ("", 0);


    QImage image = ImageMap[name];

    if (image.height() > freeHeight)
    {
        if (image.height() >= freeHeight*2)
            image = image.scaled(pageWidth, pageHeight, Qt::KeepAspectRatio);
        else
            image = image.scaled(pageWidth, freeHeight, Qt::KeepAspectRatio);
    }
    else if (image.width() > pageWidth)
        image = image.scaled(pageWidth, freeHeight, Qt::KeepAspectRatio);


    QString base64;
    base64 = "<p class='image'><img src=\"data:image/png;base64,";

    QByteArray ba;
    QBuffer bu(&ba);
    image.save(&bu, "PNG");

    base64 += ba.toBase64();

    base64 += "\" width = \"" + QString::number(image.width()) +
            "\" height = \"" + QString::number(image.height()) + "\"/></p>";


    return QPair <QString, unsigned int> (base64, image.height());
}


QVector <QImage> BookImageTable::getBookImages() const
{
    QVector <QImage> ImageList;
    foreach (QImage img, ImageMap) {
        ImageList.append(img);
    }

    return ImageList;
}

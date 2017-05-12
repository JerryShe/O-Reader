#include "bookimagetable.h"

#include <QBuffer>

#include <QDebug>

BookImageTable::BookImageTable()
{
    qDebug()<<"create BookImageTable";
}


BookImageTable::~BookImageTable()
{
    qDebug()<<"delete BookImageTable";
}


void BookImageTable::addImage(QString name, QString img, QString format)
{
    QImage tempImage;
    QByteArray BinaryCover = QByteArray::fromBase64(img.toUtf8());

    if (format == "jpeg" || format == "jpg")
        tempImage = QImage::fromData(BinaryCover, "JPG");
    if (format == "png")
        tempImage = QImage::fromData(BinaryCover, "PNG");

    if (!ImageMap.contains(name))
        ImageMap.insert(name, tempImage);
}


bool BookImageTable::contains(QString imgName)
{
    return ImageMap.contains(imgName);
}


QPair <QString, unsigned int> BookImageTable::getImage(QString name, int freeHeight, int pageWidth, int pageHeight)
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

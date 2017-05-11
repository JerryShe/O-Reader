#include "xmltextparser.h"

#include <QFile>
#include <QDebug>



QString parseTagAttribute(QString tag, QString attr)
{
    int namePosBegin = tag.indexOf(attr);
    if (namePosBegin == -1)
        return QString();

    namePosBegin = tag.indexOf("\"", namePosBegin);
    if (namePosBegin == -1)
        return QString();

    int namePosEnd = tag.indexOf("\"", namePosBegin + 1);
    if (namePosEnd == -1)
        return QString();

    return tag.mid(namePosBegin + 1, namePosEnd - namePosBegin - 1);
}



XMLTextParser::XMLTextParser(Book *openingBook)
{
    book = openingBook;
    ImageTable = new BookImageTable();

    if (book->getFormat() == 1)
    {
        parseFB2();
        createFB2TableOfContents();
    }
    else if (book->getFormat() == 2)
    {
        parseEPub();
        createEPubImageTable();
        createEPubTableOfContents();
    }
}


QStringList XMLTextParser::getText()
{
    return bookText;
}


QStringList XMLTextParser::getTableOfContentsText()
{
    return TableOfContentsText;
}


QVector <long long> XMLTextParser::getTableOfContentsIndexes()
{
    return TableOfContentsIndexes;
}


BookImageTable *XMLTextParser::getImageTable()
{
    return ImageTable;
}


QStringList XMLTextParser::splitTextToWords(QString temp)
{
    QStringList tempList;
    tempList.append(temp);

    for (int i = 0; i < tempList.size(); i++)
    {
        int pos = tempList[i].indexOf("<");
        if (pos != -1)
        {
            tempList.append(tempList[i].right(tempList[i].size() - pos));
            tempList[i] = tempList[i].left(pos);
            i++;
        }

        if (tempList[i][0] == '<')
        {
            pos = tempList[i].indexOf(">");
            if (pos == -1)
            {
                do
                {
                    doc->operator>>(temp);
                    tempList[i].append(" " + temp);
                }
                while (temp.indexOf(">") == -1);
            }

            if (pos != tempList[i].size() - 1)
            {
                tempList.append(tempList[i].right(tempList[i].size() - pos - 1));
                tempList[i] = tempList[i].left(pos + 1);
            }
        }
        else
        {
            int pos = tempList[i].indexOf("-");
            if (pos != -1 && pos != tempList[i].size() - 1)
            {
                QStringList newTemp = tempList[i].split("-");
                if (newTemp.size() > 1)
                {
                    for (int j = 0; j < newTemp.size() - 1; j++)
                        newTemp[j] += "-";

                    tempList.removeAt(i);

                    for (int j = 0; j < newTemp.size(); j++)
                        tempList.insert(i++, newTemp[j]);
                }
            }
        }
    }

    return tempList;
}


void XMLTextParser::parseFB2()
{
    QFile bookFile(book->getFile());
    QString coverName;


    if (bookFile.open(QIODevice::ReadOnly))
    {
        doc = new QTextStream(&bookFile);
        doc->setCodec(book->getBookCodec().toStdString().c_str());

        QString temp;

        do
        {
            doc->operator >> (temp);

            int coverPos = temp.indexOf("<coverpage>");
            if (coverPos != -1)
            {
                if (temp.indexOf("</coverpage>", coverPos+12) == -1)
                {
                    do
                    {
                        coverName += temp;
                        doc->operator >> (temp);
                    }
                    while ((temp.indexOf("</coverpage>") == -1 && temp.indexOf("<body>") == -1) && !doc->atEnd());
                    coverName += temp;
                }

                temp = coverName.right(coverName.size() - coverName.indexOf("</coverpage>") - 12);
                coverName = parseTagAttribute(coverName, "href");
                coverName.remove(0,1);
            }
        }
        while(temp.indexOf("<body>") == -1 && !doc->atEnd());

        temp = temp.remove(0, temp.indexOf("<body>") + 6);
        bookText.append(splitTextToWords(temp));


        while(!doc->atEnd())
        {
            doc->operator >>(temp);
            if (temp.indexOf("<binary") != -1)
            {
                bookText.append(splitTextToWords(temp.left(temp.indexOf("<binary"))));

                createFB2ImageTable(temp);
                break;
            }
            else
            {
                bookText.append(splitTextToWords(temp));
            }
        }
        bookFile.close();
    }
    else
    {
        qDebug()<<"невозможно открыть файл книги";
    }

    qDebug()<<"cover "<<coverName;
    if (book->haveCoverImage() && ImageTable->contains(coverName))
        bookText.prepend("<image l:href=\"#" + coverName + "\"/>");


    delete doc;
}


void XMLTextParser::createFB2ImageTable(QString htmlTail)
{
    QString base64 = htmlTail.right(htmlTail.size() - htmlTail.indexOf("<binary") - 7);
    QString temp;

    do
    {
        doc->operator >>(temp);

        if (temp.indexOf("</binary>") == -1)
        {
            base64 += temp;
            continue;
        }
        else
        {
            QString image;
            QString imageFormat;
            QString imageName;


            int binPos = temp.indexOf("</binary>");
            base64 += " " + temp.left(binPos);

            temp = temp.right(temp.size() - binPos);

            imageName = parseTagAttribute(base64, "id");


            int imageFormatBegin = base64.indexOf("image/") + 6;
            int imageFormatEnd = base64.indexOf("\"", imageFormatBegin);

            imageFormat = base64.mid(imageFormatBegin, imageFormatEnd - imageFormatBegin);


            int base64Begin = base64.indexOf(">", imageFormatEnd) + 1;

            image += base64.mid(base64Begin, base64.size() - base64Begin);


            ImageTable->addImage(imageName, image, imageFormat);

            base64.clear();
        }
    }
    while (temp.indexOf("</FictionBook>") == -1 && !doc->atEnd());
}


void XMLTextParser::createFB2TableOfContents()
{
    for (long long i = 0; i < bookText.size(); i++)
        if (bookText[i] == "<section>")
        {
            if (bookText[++i] == "<TitleText>")
            {
                long long pos;
                QString text;
                for (pos = i + 1; pos < bookText.size() && bookText[pos][0] == '<'; pos++);
                for (; pos < bookText.size() && bookText[pos] != "</TitleText>"; pos++)
                    if (bookText[pos][0] != '<')
                        text += bookText[pos] + " ";
                TableOfContentsText.append(text);
                TableOfContentsIndexes.append(i);
                i = pos;
            }
        }
}


void XMLTextParser::parseEPub()
{

}


void XMLTextParser::createEPubImageTable()
{

}


void XMLTextParser::createEPubTableOfContents()
{

}

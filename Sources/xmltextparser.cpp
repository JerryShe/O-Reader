#include "xmltextparser.h"

#include <QFile>
#include <QDebug>



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

                int nameBegin = coverName.indexOf("href");
                nameBegin = coverName.indexOf("\"", nameBegin);
                int nameEnd = coverName.indexOf("\"", nameBegin + 1);

                temp = coverName.right(coverName.size() - coverName.indexOf("</coverpage>") - 12);
                coverName = coverName.mid(nameBegin + 2, nameEnd - nameBegin - 2);
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
    //if (book->haveCoverImage() && ImageTable->contains(coverName))
        //bookText.prepend("<section> <image l:href=\"#" + ImageTable[coverName] + "</section>");


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


            int namePosBegin = base64.indexOf("id");
            namePosBegin = base64.indexOf("\"", namePosBegin);
            int namePosEnd = base64.indexOf("\"", namePosBegin + 1);

            imageName = base64.mid(namePosBegin + 1, namePosEnd - namePosBegin - 1);


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

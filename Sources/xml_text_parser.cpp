#include "xml_text_parser.h"

#include <QFile>
#include <QDebug>

#include <fb2_parser.h>


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


QStringList splitTextToWords(QString temp)
{
    QStringList tempList;
    tempList.append(temp);
    for (int i = 0; i < tempList.size(); i++)
    {
        int pos = tempList[i].indexOf("<");
        if (pos > 0)
        {
            tempList.append(tempList[i].right(tempList[i].size() - pos));
            tempList[i] = tempList[i].left(pos);
            i++;
        }

        if (tempList[i][0] == '<')
        {
            pos = tempList[i].indexOf(">");
            if (pos == -1)
                break;

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

    for (int i = 0; i < tempList.size(); i++)
        if (tempList[i].isEmpty())
            tempList.removeAt(i);

    return tempList;
}


XMLTextParser::XMLTextParser(Book *openingBook)
{
    if (openingBook->getFormat() == 1)
    {
        FB2Parser parser(openingBook, bookText, ImageTable, TableOfContents, notesTable);
    }
    else if (openingBook->getFormat() == 2)
    {

    }
}


QStringList XMLTextParser::getText() const
{
    return bookText;
}


QTreeWidgetItem* XMLTextParser::getTableOfContents() const
{
    return TableOfContents;
}


BookImageTable *XMLTextParser::getImageTable() const
{
    return ImageTable;
}


QHash <QString, QStringList> XMLTextParser::getNotesTable() const
{
    return notesTable;
}

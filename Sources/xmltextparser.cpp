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

    if (book->getFormat() == 1)
    {
        parseFB2();
        createFB2TableOfContents();
        createFB2NotesTable();
    }
    else if (book->getFormat() == 2)
    {
        parseEPub();
        createEPubTableOfContents();
    }

    ImageTable = new BookImageTable(openingBook);

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


QStringList XMLTextParser::splitTextToWords(QString temp) const
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

    for (int i = 0; i < tempList.size(); i++)
        if (tempList[i].isEmpty())
            tempList.removeAt(i);

    return tempList;
}


void XMLTextParser::parseFB2()
{
    QFile bookFile(book->getFileName());
    QString coverName;


    if (bookFile.open(QIODevice::ReadOnly))
    {
        doc = new QTextStream(&bookFile);
        doc->setCodec(book->getCodec().toStdString().c_str());

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
        while(temp.indexOf("<body") == -1 && !doc->atEnd());

        temp = temp.remove(0, temp.indexOf("<body"));
        bookText.append(splitTextToWords(temp));


        while(!doc->atEnd())
        {
            doc->operator >>(temp);

            if (temp.indexOf("<binary") != -1)
            {
                bookText.append(splitTextToWords(temp.left(temp.indexOf("<binary"))));
                break;
            }
            else
                bookText.append(splitTextToWords(temp));
        }
        bookFile.close();
    }
    else
    {
        qDebug()<<"невозможно открыть файл книги";
    }

    qDebug()<<"cover "<<coverName;
    if (book->haveCoverImage())
        bookText.prepend("<image l:href=\"#" + coverName + "\"/>");

    delete doc;
}


void XMLTextParser::createFB2NotesTable()
{
    int notesPos;

    for (notesPos = 0; notesPos < bookText.size(); notesPos++)
    {
        if (bookText[notesPos][0] == "<")
            if (bookText[notesPos].indexOf("<body") != -1)
            {
                if (parseTagAttribute(bookText[notesPos], "name") == "notes")
                    break;
            }
    }

    if (notesPos != 0 && notesPos != bookText.size())
    {
        for (int i = notesPos; i < bookText.size(); i++)
        {
            if (bookText[i] == "</body>")
                break;

            if (bookText[notesPos][0] == "<")
                if (bookText[i].indexOf("<section") != -1)
                {
                    QString noteID = parseTagAttribute(bookText[i], "id");
                    if (!noteID.isEmpty())
                    {
                        QStringList noteText;
                        for (i = i + 1; i < bookText.size(); i++)
                        {
                            if (bookText[i].indexOf("</section") == -1)
                                noteText.append(bookText[i]);
                            else
                                break;
                        }

                        notesTable.insert(noteID, noteText);
                    }
                }
        }
    }
}


void XMLTextParser::createFB2TableOfContents()
{
    TableOfContents = new QTreeWidgetItem(0);
    QTreeWidgetItem* curItem = TableOfContents;

    for (long long i = 0; i < bookText.size(); i++)
    {
        if (bookText[i] == "<section>")
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(curItem);
            item->setWhatsThis(0,QString::number(i));

            curItem->addChild(item);
            curItem = item;
            QString text;

            for (; i < bookText.size(); i++)
                if (bookText[i] == "<title>" || bookText[i] == "</section>")
                    break;

            if (bookText[i] == "<title>")
            {
                i++;

                for (i = i+1; i < bookText.size(); i++)
                {
                    if (bookText[i][0] != '<')
                        text += bookText[i] + " ";
                    else
                    {
                        if (bookText[i] == "</p>")
                            text += '\n';
                        else if (bookText[i] == "</title>" || bookText[i] == "</section>")
                            break;
                    }
                }

                if (text[text.size() - 1] == '\n')
                    text.remove(text.size() - 1, 1);

                curItem->setText(0, text);
            }
        }

        if (bookText[i] == "</section>")
        {
            if (curItem->parent() != 0)
                curItem = curItem->parent();
        }

        if (bookText[i] == "</body>")
            break;
    }


}


void XMLTextParser::parseEPub()
{

}


void XMLTextParser::createEPubTableOfContents()
{

}

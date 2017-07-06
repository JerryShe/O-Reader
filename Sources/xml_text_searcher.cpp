#include "xml_text_searcher.h"
#include <QString>
#include <QRegExp>

#include <QDebug>



XMLTextSearcher::XMLTextSearcher(const int &bookFormat)
{
    resolver = new TagsResolver(this, bookFormat);
    qDebug()<<"create text searcher";
}


XMLTextSearcher::~XMLTextSearcher()
{
    qDebug()<<"delete text searcher";
    for (int i = 0; i < results.size(); i++)
        delete results[i];
}


void XMLTextSearcher::setStartData(const BookPosition &position)
{
    startPos = position;
}


BookPosition XMLTextSearcher::getStartData() const
{
    return startPos;
}


void XMLTextSearcher::start(const QStringList &bookText, const QString searchKey)
{
    if (!searchKey.size())
        return;

    QStringList key = searchKey.split(" ");

    for (int i = 0; i < key.size(); i++)
    {
        int pos = key[i].indexOf("-");
        if (pos != -1 && pos != key[i].size() - 1)
        {
            QStringList newTemp = key[i].split("-");
            if (newTemp.size() > 1)
            {
                for (int j = 0; j < newTemp.size() - 1; j++)
                    newTemp[j] += "-";

                key.removeAt(i);

                for (int j = 0; j < newTemp.size(); j++)
                    key.insert(i++, newTemp[j]);
            }
        }
    }

    qDebug()<<"new search: "<<key;

    int pos = 0;

    QStack <QString> tags;
    tags.push("Text");
    bool tail;

    QRegExp regExp("[?!.;,:-    \n*&%#@'\"+-()^/\\s]");

    for (long long i = 0; i < bookText.size(); i++)
    {
        if (bookText[i][0] == '<')
        {
            tagInfo TagInf = resolver->getTag(bookText[i]);
            if (TagInf.index == -1)
                continue;

            if (TagInf.index < 31)
            {
                if (tags.back() == TagInf.html)
                    tags.pop();
                else
                    tags.push(TagInf.html);
            }


            if (TagInf.html == "p")
            {
                if (TagInf.type == false)
                    tail = true;
                else
                    tail = false;
            }
        }
        else
        {
            QString text = bookText[i];
            QString keyText = key[pos];

            text.remove(regExp);
            keyText.remove(regExp);

            if (keyText.isEmpty() || text.isEmpty())
                continue;

            if (text.compare(keyText, Qt::CaseInsensitive) == 0)
            {
                pos++;
                if (pos >= key.size())
                {
                    BookPosition* res = new BookPosition(i - key.size() + 1, tags, tail);
                    results.push_back(res);
                    pos = 0;
                }
            }
            else
                pos = 0;
        }
    }
}


int XMLTextSearcher::getResultCount() const
{
    return results.size();
}


int XMLTextSearcher::getResultFrom(const long long &position) const
{
    for (int i = 0; i < results.size(); i++)
        if (position < results[i]->TextPos)
            return i;

    if (results.size())
        return results.size() - 1;
    else
        return -1;
}


BookPosition *XMLTextSearcher::getResultAt(const int &index) const
{
    if (index >= 0 && index < results.size())
        return results[index];

    return 0;
}

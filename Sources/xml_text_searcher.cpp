#include "xml_text_searcher.h"

#include <QStringList>
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
}


void XMLTextSearcher::commitTag(QStack <QString> &tags, const tagInfo &TagInf)
{
    if (!tags.isEmpty() && TagInf.index < 31)
    {
        if (tags.last() == TagInf.html)
            tags.pop();
        else
            tags.push(TagInf.html);
    }
}


void XMLTextSearcher::checkP(const tagInfo &TagInf, const bool &type, bool &paragrafTail)
{
    if (TagInf.html == "p")
    {
        if (TagInf.type == type)
            paragrafTail = true;
        else
            paragrafTail = false;
    }
}


void XMLTextSearcher::start(const QStringList &bookText, const QString searchKey, const bool &caseSensitive, const bool &punctuation, const int &previewSize)
{
    if (!searchKey.size())
        return;

    PreviewSize = previewSize;

    QString::SplitBehavior splitMode;

    if (punctuation)
        splitMode = QString::KeepEmptyParts;
    else
        splitMode = QString::SkipEmptyParts;

    QStringList key = searchKey.split(" ", splitMode);


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
    Qt::CaseSensitivity sensitivity;
    if (caseSensitive)
        sensitivity = Qt::CaseSensitive;
    else
        sensitivity = Qt::CaseInsensitive;

    for (long long i = 0; i < bookText.size(); i++)
    {
        if (bookText[i][0] == '<')
        {
            tagInfo TagInf = resolver->getTag(bookText[i]);
            if (TagInf.index == -1)
                continue;

            commitTag(tags, TagInf);
            checkP(TagInf, false, tail);
        }
        else
        {
            QString text = bookText[i];
            QString keyText = key[pos];

            if (!punctuation)
            {
                text.remove(regExp);
                keyText.remove(regExp);
            }

            if (keyText.isEmpty() || text.isEmpty())
                continue;

            if (text.compare(keyText, sensitivity) == 0)
            {
                pos++;
                if (pos >= key.size())
                {
                    BookPosition res(i - key.size() + 1, tags, tail);
                    results.push_back(BookNote(res, createPreview(res, i, bookText)));
                    pos = 0;
                }
            }
            else
                pos = 0;
        }
    }
}


QString XMLTextSearcher::createPreview(const BookPosition &pos, const long long &textPos, const QStringList &bookText)
{
    int wordCount = 0;
    QStack <QString> previewTags = pos.PrevTags;
    bool previewTail = pos.ParagrafTail;
    long long prevStart;

    for (prevStart = pos.TextPos; prevStart > 0 && wordCount <= (PreviewSize-1)/2; prevStart--)
    {
        if (bookText[prevStart][0] == '<')
        {
            tagInfo TagInf = resolver->getTag(bookText[prevStart]);
            if (TagInf.index == -1 || TagInf.index == 31 || TagInf.index == 32 || TagInf.index == 40)
                continue;

            if (TagInf.index < 5)
                break;


            commitTag(previewTags, TagInf);
            checkP(TagInf, true, previewTail);
        }
        else
            wordCount++;
    }

    QString preview = "<body>";

    for (int j = 0; j < previewTags.size(); j++)
        preview.append("<" + previewTags[j] + ">");

    if (previewTail && bookText[prevStart + 1][0] != "–" && bookText[prevStart + 1][0] != '-')
        preview.append("... ");

    wordCount = 0;


    for (long long j = prevStart + 1; j < bookText.size() && wordCount <= PreviewSize; j++)
    {
        if (j == pos.TextPos)
            preview.append("<mark>");

        if (bookText[j][0] == '<')
        {
            tagInfo TagInf = resolver->getTag(bookText[j]);
            if (TagInf.index == -1 || TagInf.index == 31 || TagInf.index == 32 || TagInf.index == 40)
                continue;

            if (TagInf.index < 5)
            {
                prevStart++;
                break;
            }

            commitTag(previewTags, TagInf);

            if (TagInf.type == false)
                preview.append("<" + TagInf.html + ">");
            else
                preview.append("</" + TagInf.html + ">");

            checkP(TagInf, false, previewTail);
        }
        else
        {
            if (bookText[j].right(1) != "-" || bookText[j].size() == 1)
                preview.append(bookText[j] + " ");
            else
                preview.append(bookText[j]);

            wordCount++;
        }

        if (j == textPos)
            preview.append("</mark>");
    }


    if (previewTail)
        preview.append("...");

    for (int j = previewTags.size() - 1; j >= 0; j--)
        preview.append("</" + previewTags[j] + ">");

    preview.append("</body>");

    return preview;
}


QVector<BookNote> XMLTextSearcher::getResults()
{
    return results;
}


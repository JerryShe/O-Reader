#include "tagsresolver.h"

#include <QDebug>

tagInfo::tagInfo()
{
    index = -1;
}

tagInfo::tagInfo(bool t, char i, QString s)
{
    type = t;
    index = i;
    html = s;
}



TagsResolver::TagsResolver(QObject * parent, int format)
{
    setParent(parent);

    switch (format) {
    case 1:
        createFB2map();
        break;
    case 2:
        createEPUBmap();
        break;
    default:
        break;
    }
}


TagsResolver::~TagsResolver()
{

}


void TagsResolver::createFB2map()
{
    TagMap.clear();

    TagMap.insert("title", tagInfo(0, 1, "TitleText"));
    TagMap.insert("epigraph", tagInfo(0, 2, "epigraph"));
    TagMap.insert("annotation", tagInfo(0, 3, "annotation"));
    TagMap.insert("subtitle", tagInfo(0, 4, "subtitle"));


    TagMap.insert("strong", tagInfo(0, 10, "strong"));
    TagMap.insert("emphasis", tagInfo(0, 11, "emphasis"));
    TagMap.insert("strikethrough", tagInfo(0, 12, "strike"));
    TagMap.insert("text-author", tagInfo(0, 13, "cite"));
    TagMap.insert("cite", tagInfo(0, 14, "cite"));
    TagMap.insert("sub", tagInfo(0, 15, "sub"));
    TagMap.insert("sup", tagInfo(0, 16, "sup"));    


    TagMap.insert("poem", tagInfo(0, 20, "poem"));
    TagMap.insert("stanza", tagInfo(0, -1, ""));
    TagMap.insert("v", tagInfo(0, 22, "p"));


    TagMap.insert("p", tagInfo(0, 30, "p"));
    TagMap.insert("body", tagInfo(0, 31, "body"));
    TagMap.insert("section", tagInfo(0, 32, "section"));
    TagMap.insert("empty-line", tagInfo(0, 33, "br/"));


    TagMap.insert("image", tagInfo(0, 40, "img"));
    TagMap.insert("a", tagInfo(0, 41, "a"));
}


void TagsResolver::createEPUBmap()
{
    TagMap.clear();

}



tagInfo TagsResolver::getTag(QString tagStr)
{
    int lpos = tagStr.indexOf("<");
    int rpos = tagStr.indexOf(">", lpos);

    QString tagTail;
    int tailPos = tagStr.indexOf(" ");

    if(tailPos != -1)
    {
        tagTail = tagStr.right(tagStr.size() - tailPos);
        tagTail.remove(tagTail.size() - 1, 1);
        tagStr = tagStr.left(tailPos);
    }

    bool TagType;

    if (lpos != -1 && rpos != -1)
    {
        if (tagStr[lpos+1] == '/')
        {
            TagType = true;
            tagStr = tagStr.mid(lpos + 2, rpos - lpos - 2);
        }
        else
        {
            TagType = false;
            tagStr = tagStr.mid(lpos + 1, rpos - lpos - 1);
        }
    }
    else
        return tagInfo();

    if (TagMap.contains(tagStr))
    {
        tagInfo temp = TagMap[tagStr];
        temp.type = TagType;

        if (!tagTail.isEmpty())
            temp.html += tagTail;

        return temp;
    }
    else
        return tagInfo();
}

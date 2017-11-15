#ifndef TAGS_RESOLVER_H
#define TAGS_RESOLVER_H

#include <QHash>
#include <QObject>

struct tagInfo
{
    bool type;
    char index;
    QString html;

    tagInfo();
    tagInfo(bool t, char i, QString s);
};

/*  Tag types
 * первое значение:  0 - тег имеет только открытый вариант
 *                           1 - тег имеет как закрытый, так и открытый вариант
 *
 * 1 -1 - unknown tag
 *
 * 1 1 - title
 * 1 2 - epigraph
 * 1 3 - annotation
 * 1 4 - subtitle
 *
 * 1 10 - strong
 * 1 11 - emphasis
 * 1 12 - strikethrough text
 * 1 13 - text-author
 * 1 14 - cite
 * 1 15 - sub
 * 1 16 - sup
 *
 * 1 20 - poem
 * 0 33 - stanza
 * 1 30 - (v) poem line
 *
 * 1 30 - paragraph
 * 1 31 - body
 * 1 32 - section
 * 0 33 - empty line
 *
 * 0 40 - image
 * 1 41 - link
 */


class TagsResolver : public QObject
{
public:
    TagsResolver(QObject * parent, int format);
    ~TagsResolver();

    tagInfo getTag(QString tagStr) const;          // return tag type and correct html tag

private:
    void createFB2map();
    void createEPUBmap();

    QHash <QString, tagInfo> TagMap;
};



#endif // TAGS_RESOLVER_H

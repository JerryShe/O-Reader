#ifndef TEXTTAGCLASS_H
#define TEXTTAGCLASS_H

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
 *
 * 0 -1 - unknown tag
 *
 * 0 1 - title begin
 * 1 1 - title end
 * 0 2 - epigraph begin
 * 1 2 - epigraph end
 * 0 3 - annotation begin
 * 1 3 - annotation end
 * 0 4 - subtitle begin
 * 1 4 - subtitle end
 *
 * 0 10 - strong begin
 * 1 10 - strong end
 * 0 11 - emphasis begin
 * 1 11 - emphasis end
 * 0 12 - strikethrough text begin
 * 1 12 - strikethrough text end
 * 0 13 - text-author begin
 * 1 13 - text-author end
 * 0 14 - cite begin
 * 1 14 - cite end
 * 0 15 - sub begin
 * 1 15 - sub end
 * 0 16 - sup begin
 * 1 16 - sup end
 *
 * 0 20 - poem begin
 * 1 20 - poem end
 * 0 -1 - stanza
 * 0 22 - (v) poem line begin
 * 1 22 - (v) poem line end
 *
 * 0 30 - paragraph begin
 * 1 30 - paragraph end
 * 0 31 - body begin
 * 1 31 - body end
 * 0 32 - section begin
 * 1 32 - section end

 * 0 33 - empty line
 *
 * 0 40 - image
 * 0 41 - link begin
 * 1 41 - link end
 */



/* Format index
 * 1 - FB2
 * 2 - EPub
 */


class TagsResolver : public QObject
{
public:
    TagsResolver(QObject * parent, int format);
    ~TagsResolver();

    tagInfo getTag(QString tagStr);          // return tag type and correct html tag

private:
    void createFB2map();
    void createEPUBmap();

    QHash <QString, tagInfo> TagMap;
};



#endif // TEXTTAGCLASS_H

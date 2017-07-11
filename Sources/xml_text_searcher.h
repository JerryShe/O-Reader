#ifndef XML_TEXT_SEARCHER_H
#define XML_TEXT_SEARCHER_H

#include <QObject>
#include <QVector>
#include <QStack>

#include "books.h"
#include "tags_resolver.h"



class XMLTextSearcher : public QObject
{
    Q_OBJECT
public:
    explicit XMLTextSearcher(const int &bookFormat);
    ~XMLTextSearcher();

public slots:
    void start(const QStringList &bookText, const QString searchKey);
    QVector <QPair<BookPosition, QString>> getResults();

private:
    QString createPreview(const BookPosition &pos, const long long &textPos, const QStringList &bookText);

    void commitTag(QStack<QString> &tags, const tagInfo &TagInf);
    void checkP(const tagInfo &TagInf, const bool &type, bool &paragrafTail);

    QVector <QPair<BookPosition, QString>> results;

    TagsResolver* resolver;

    bool parTail;

};

#endif // XML_TEXT_SEARCHER_H

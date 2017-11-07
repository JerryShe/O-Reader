#ifndef XML_TEXT_SEARCHER_H
#define XML_TEXT_SEARCHER_H

#include <QObject>
#include <QVector>
#include <QStack>

#include "data_handlers/book.h"
#include "reading_window/text_handlers/xml/paginator/tags_resolver.h"


class XMLTextSearcher : public QObject
{
    Q_OBJECT
public:
    explicit XMLTextSearcher(const int &bookFormat);
    ~XMLTextSearcher();

public slots:
    void start(const QStringList &bookText, const QString searchKey, const bool &caseSensitive, const bool &punctuation, const int &previewSize);
    QVector <BookNote> getResults();

private:
    QString createPreview(const BookPosition &pos, const long long &textPos, const QStringList &bookText);

    void commitTag(QStack<QString> &tags, const tagInfo &TagInf);
    void checkP(const tagInfo &TagInf, const bool &type, bool &paragrafTail);

    QVector <BookNote> results;

    TagsResolver* resolver;

    int PreviewSize;
};

#endif // XML_TEXT_SEARCHER_H

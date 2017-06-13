#ifndef XML_TEXT_SEARCHER_H
#define XML_TEXT_SEARCHER_H

#include <QObject>
#include <QVector>
#include <QStack>

#include <tags_resolver.h>

struct SearchResult
{
    SearchResult(const long long &position, const QStack<QString> &tagsStack, const bool &tail);

    long long pos;
    QStack <QString> tags;
    bool paragrafTail;
};


class XMLTextSearcher : public QObject
{
    Q_OBJECT
public:
    explicit XMLTextSearcher(const int &bookFormat);
    ~XMLTextSearcher();

public slots:
    void start(const QStringList &bookText, const QString searchKey);

    int getResultCount() const;

    SearchResult* getResultAt(const int &index) const;
    int getResultFrom(const long long &position) const;
    int getResultBefore(const long long &position) const;

private:
    QVector <SearchResult*> results;

    TagsResolver* resolver;
};

#endif // XML_TEXT_SEARCHER_H

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

    void setStartData(const QStack<QString> &stack, const long long &pos, const bool &parTail);
    BookPosition getStartData() const;


    int getResultCount() const;

    BookPosition* getResultAt(const int &index) const;
    int getResultFrom(const long long &position) const;

private:
    QVector <BookPosition*> results;

    TagsResolver* resolver;

    QStack <QString> startStack;
    long long startPos;
    bool paragrafTail;
};

#endif // XML_TEXT_SEARCHER_H

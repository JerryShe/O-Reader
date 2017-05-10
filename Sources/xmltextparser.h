#ifndef XMLTEXTPARSER_H
#define XMLTEXTPARSER_H

#include "books.h"
#include "bookimagetable.h"

#include <QObject>
#include <QTextStream>
#include <QImage>


class XMLTextParser
{
public:
    XMLTextParser(Book *openingBook);

    QStringList getText();
    QStringList getTableOfContentsText();
    QVector <long long> getTableOfContentsIndexes();

    BookImageTable* getImageTable();

private:
    void parseFB2();
    void createFB2TableOfContents();
    void createFB2ImageTable(QString htmlTail);

    void parseEPub();
    void createEPubTableOfContents();
    void createEPubImageTable();


    QTextStream* doc;
    QStringList splitTextToWords(QString temp);

    Book *book;

    QStringList TableOfContentsText;
    QVector <long long> TableOfContentsIndexes;

    BookImageTable* ImageTable;

    QStringList bookText;
};

#endif // XMLTEXTPARSER_H

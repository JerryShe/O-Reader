#ifndef XMLTEXTPARSER_H
#define XMLTEXTPARSER_H

#include "books.h"
#include "book_image_table.h"

#include <QObject>
#include <QTextStream>
#include <QImage>
#include <QHash>
#include <QTreeWidgetItem>



QString parseTagAttribute(QString tag, QString attr);
QStringList splitTextToWords(QString temp);


class XMLTextParser
{
public:
    XMLTextParser(Book *openingBook);

    QStringList getText() const;
    QTreeWidgetItem* getTableOfContents() const;

    BookImageTable* getImageTable() const;
    QHash <QString, QStringList> getNotesTable() const;

private:
    QTreeWidgetItem* TableOfContents;
    BookImageTable* ImageTable;
    QStringList bookText;
    QHash <QString, QStringList> notesTable;
};

#endif // XMLTEXTPARSER_H

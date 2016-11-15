#include "books.h"
#include "QFile"
#include "QDomDocument"
#include <iostream>


#include <qdebug.h>

using namespace std;

Book::Book(QString fileName)
{
    Book::File = fileName;

    QFile bookFile(fileName);
    if (bookFile.open(QIODevice::ReadOnly))
    {
        QDomDocument doc;
        if (doc.setContent(&bookFile))
        {
            bookFile.close();

            if (doc.namedItem("FictionBook").nodeName().isNull())
            {
                ///выдать эксепшн - это не фанкшн бук
            }

            //файл книги
            Book::File = fileName;


            QDomNode titleInfo = doc.elementsByTagName("title-info").item(0);
            if (titleInfo.isNull())
            {
                ///выдать эксепшн - не найден title-info
            }

            //название книги
            if (! titleInfo.namedItem("book-title").isNull())
                Book::Title = titleInfo.namedItem("book-title").toElement().text();

            //имя автора
            QDomNode author = titleInfo.namedItem("author");
            if (!author.namedItem("first-name").isNull())
                Book::AuthorFirstName = author.namedItem("first-name").toElement().text();
            if (!author.namedItem("middle-name").isNull())
                Book::AuthorMiddleName = author.namedItem("middle-name").toElement().text();
            if (!author.namedItem("last-name").isNull())
                Book::AuthorLastName = author.namedItem("last-name").toElement().text();

            //жанры
            QDomNodeList nodeList = doc.elementsByTagName("genre");
            for (int i = 0; i < nodeList.length(); ++i)
                Book::Genres<<nodeList.item(i).toElement().text();

            //языки
            if (! titleInfo.namedItem("lang").isNull())
                Book::Language = titleInfo.namedItem("lang").toElement().text();

            if (! titleInfo.namedItem("src-lang").isNull())
                Book::SourceLanguage = titleInfo.namedItem("src-lang").toElement().text();

            //аннотация
            if (! titleInfo.namedItem("annotation").isNull())
            {
                nodeList = titleInfo.namedItem("annotation").childNodes();
                for (int i = 0; i < nodeList.size(); ++i)
                    Book::Annotation<<nodeList.item(i).toElement().text();
            }

            //книжная серия
            if (! titleInfo.namedItem("sequence").isNull())
            {
                Book::Series.first = titleInfo.namedItem("sequence").toElement().attribute("name", "");
                Book::Series.second = titleInfo.namedItem("sequence").toElement().attribute("number", "").toInt();
            }

            //дата добавления
            Book::AddittionTime = QDateTime::currentDateTime();


            qDebug()<<Book::File  ;
            qDebug()<<Book::Title  ;
            qDebug()<<Book::AuthorFirstName  ;
            qDebug()<<Book::AuthorMiddleName  ;
            qDebug()<<Book::AuthorLastName  ;
            qDebug()<<Book::Annotation  ;
            qDebug()<<Book::SourceLanguage  ;
            qDebug()<<Book::Language  ;
            qDebug()<<Book::Genres  ;
            qDebug()<<Book::Series  ;
            qDebug()<<Book::AddittionTime  ;

        }
    }
}

void Book::readFromFile()
{}

void Book::writeToFile()
{}





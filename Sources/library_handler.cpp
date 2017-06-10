#include "library_handler.h"

#include <QDirIterator>
#include <QDebug>

#include <QJsonDocument>
#include <QJsonArray>


LibraryHandler* LibraryHandler::getLibraryHandler()
{
    static LibraryHandler LibHandler;
    return &LibHandler;
}


LibraryHandler::LibraryHandler()
{
    resoursesFolderPath = "LibraryResources";
    libraryView = 0;
    UserActions = Synchronization::getSynchronization();
    currentBookIndex = 0;
    filesMask << "*.fb2" << "*.zip" << "*.epub";
    needRefresh = true;
}


LibraryHandler::~LibraryHandler()
{}


void LibraryHandler::setLibraryWidget(LibraryView* lbWidget)
{
    qDebug()<<"set lib widget";
    libraryView = lbWidget;
    needRefresh = true;
    refreshLibrary();
}


bool LibraryHandler::loadBookList()
{
    QFile LibFile(resoursesFolderPath + "/BookList.json");

    if(!LibFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to Create File" << endl;

        ///оповещение - невозможно открыть файл библиотеки
        return 0;
    }

    QByteArray in = LibFile.readAll();

    QJsonDocument LibJson(QJsonDocument::fromJson(in));

    QJsonObject LibObj = LibJson.object();
    this->fromJson(LibObj);

    needRefresh = true;

    LibFile.close();
    qDebug()<<bookList.size()<<"books loaded";

    return 1;
}


bool LibraryHandler::saveBookList() const
{
    QFile LibFile(resoursesFolderPath + "/BookList.json");

    if(!LibFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Failed to Create Book File";
        ///оповещение - невозможно открыть файл библиотеки
        return 0;
    }

    QJsonDocument LibJson(this->toJson());
    LibFile.write(LibJson.toJson());

    LibFile.close();

    qDebug()<<bookList.size()<<"books saved";
    return 1;
}


QJsonObject LibraryHandler::toJson() const
{
    QJsonObject json;
    QJsonArray LibArray;

    for (int i = 0; i < bookList.size(); i++)
        LibArray.append(bookList[i].toJson());

    json["Library"] = LibArray;

    return json;
}


void LibraryHandler::fromJson(const QJsonObject &json)
{
    QJsonArray LibArray = json["Library"].toArray();
    QJsonObject temp;

    for (int i = 0; i < LibArray.size(); i++)
    {
        temp = LibArray[i].toObject();
        bookList.append(Book(temp));

        if (libraryView != 0)
            libraryView->addItem(&bookList.back());
    }
}


void LibraryHandler::deleteBooks(QVector<unsigned int> deletedItemsIndexes)
{
    qDebug()<<"deleting books";
    for (int i = 0; i < deletedItemsIndexes.size(); i++)
    {
        for (int j = 0; j < bookList.size(); j++)
        {
            if (bookList[j].getIndex() == deletedItemsIndexes.at(i))
            {
                UserActions->addAction(UActions::DeleteBook, bookList[j].getFileName());
                bookList.remove(j);
                break;
            }
        }
    }

    if (deletedItemsIndexes.size())
    {
        saveBookList();
        UserActions->saveLog();
        refreshLibrary();
    }
}


void LibraryHandler::AddBooks(const QStringList &fileList)
{
    emit showLoadImage("");

    qDebug()<<"adding books";
    if (!fileList.size())
        return;

    GenresMap *Gmap = new GenresMap();

    for (int i = 0; i < fileList.size(); i++)
        openNewBook(fileList[i], Gmap);

    UserActions->saveLog();
    saveBookList();
    delete Gmap;

    emit hideLoadImage();
}


void LibraryHandler::AddFolder(const QString &path)
{
    if (path.isEmpty())
        return;

    QStringList fileList;

    QDirIterator it(path, filesMask, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
        fileList << it.next();
    if (!fileList.size())
        return;

    AddBooks(fileList);
}


int LibraryHandler::getFileTipe(const QString &fileName) const
{
    QFileInfo fileInfo(fileName);
    QString format = fileInfo.suffix();

    if (format.compare("zip", Qt::CaseInsensitive) == 0)
        return 3;
    if (format.compare("fb2", Qt::CaseInsensitive) == 0)
        return 1;
    if (format.compare("epub", Qt::CaseInsensitive) == 0)
        return 2;

    return 0;
}


void LibraryHandler::openNewBook(const QString &file, GenresMap *Gmap)
{
    for (int j = 0; j < bookList.size(); j++)
    {
        if (file == bookList[j].getFileName())
        {
            /// оповещение - такая книга уже есть
            return;
        }
    }

    int format = getFileTipe(file);

    if (format != 0 && format != 3)
    {
        bool result = true;
        Book boo(result, file, Gmap);
        if (!result)
        {
            /// оповещение - невозможно открыть как книгу
            qDebug()<<"Invalid file!";
            return;
        }

        boo.setIndex(++currentBookIndex);
        bookList.push_back(boo);

        UserActions->addAction(UActions::AddBook, file);
        if (libraryView != 0)
        {
            libraryView->addItem(&boo);
            libraryView->reset();
        }
    }
    if (format == 3)
    {
        qDebug()<<"zip!";
    }
}


void LibraryHandler::deleteBook(const unsigned int &index)
{
    if (libraryView != 0)
        libraryView->deleteBook(index);
    for (int i = 0; i < bookList.size(); i++)
        if (bookList[i].getIndex() == index)
        {
            UserActions->addAction(UActions::DeleteBook, bookList[i].getFileName());
            bookList.remove(i);
            break;
        }
}


bool AuthorComparator(Book &boo1, Book &boo2)
{
    if (boo1.getAuthorName() <= boo2.getAuthorName())
        return true;
    else
        return false;
}

bool TitleComparator(Book &boo1, Book & boo2)
{
    if (boo1.getTitle() <= boo2.getTitle())
        return true;
    else
        return false;
}


void LibraryHandler::sortBooks(const QString &mode)
{
    if (libraryView == 0)
        return;

    libraryView->clear();

    if (mode == QObject::tr("Date"))
    {
        for (int i = 0; i < bookList.size(); i++)
            libraryView->addItem(&bookList[i]);

        return;
    }
    if (mode == QObject::tr("Author"))
    {
        QVector <Book> indexVector = bookList;
        qSort(indexVector.begin(), indexVector.end(), &AuthorComparator);

        for (int i = 0; i < indexVector.size(); i++)
            libraryView->addItem(&indexVector[i]);

        return;
    }
    if (mode == QObject::tr("Title"))
    {
        QVector <Book> indexVector = bookList;
        qSort(indexVector.begin(), indexVector.end(), &TitleComparator);

        for (int i = 0; i < indexVector.size(); i++)
            libraryView->addItem(&indexVector[i]);

        return;
    }
}


void LibraryHandler::findBooks(const QString &token, const QString &mode)
{
    if (libraryView == 0)
        return;

    if (!token.isEmpty())
    {
        libraryView->clear();
        needRefresh = true;

        if (mode == QObject::tr("Title"))
        {
            for (int i = 0; i < bookList.size(); i++)
                if (bookList[i].getTitle().indexOf(token, 0, Qt::CaseInsensitive) != -1)
                    libraryView->addItem(&bookList[i]);

            return;
        }

        if (mode == QObject::tr("Author"))
        {
            for (int i = 0; i < bookList.size(); i++)
                if (bookList[i].getAuthorName().indexOf(token, 0, Qt::CaseInsensitive) != -1)
                    libraryView->addItem(&bookList[i]);

            return;
        }

        if (mode == QObject::tr("Series"))
        {
            for (int i = 0; i < bookList.size(); i++)
                if (bookList[i].getSeries().indexOf(token, 0, Qt::CaseInsensitive) != -1)
                    libraryView->addItem(&bookList[i]);

            return;
        }
    }
}


Book* LibraryHandler::getBookByIndex(const unsigned int &index)
{
    int i;
    for (i = 0; i < bookList.size(); i++)
        if (bookList[i].getIndex() == index)
            break;

    if (i == bookList.size())
        return 0;

    return &bookList[i];
}


Book* LibraryHandler::getLastOpenedBook()
{
    unsigned int index = UserActions->getLastOpenedBookIndex();
    if (index == 0)
        return 0;

    return getBookByIndex(index);
}


void LibraryHandler::refreshLibrary()
{
    if (needRefresh == true && libraryView != 0)
    {
        qDebug()<<"refreshing library representation";

        libraryView->clear();
        needRefresh = false;
        for (int i = 0; i < bookList.size(); i++)
            libraryView->addItem(&bookList[i]);
    }
}

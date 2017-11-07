#include "data_handlers/library_handler.h"

#include <QDirIterator>
#include <QJsonDocument>
#include <QJsonArray>
#include <QtGui/private/qzipreader_p.h>

#include <QDebug>

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
}


LibraryHandler::~LibraryHandler()
{}


void LibraryHandler::setLibraryWidget(LibraryView* lbWidget)
{
    qDebug()<<"set lib widget";
    libraryView = lbWidget;
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

    for (int i = 0; i < bookList.size(); i++)
        if (currentBookIndex < bookList[i].getIndex())
            currentBookIndex = bookList[i].getIndex();

    LibFile.close();
    qDebug()<<bookList.size()<<"books loaded";

    QVector <Book*> losted = findMissingBooks();
    if (losted.size())
        emit lostBooks(losted);

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
    if (!json.contains("Library"))
        return;

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


QVector <Book*> LibraryHandler::findMissingBooks()
{
    QVector <Book*> missBooks;
    for (int i = 0; i < bookList.size(); i++)
    {
        QFileInfo file(bookList[i].getFileName());

        if (!file.isFile())
            missBooks.append(&bookList[i]);
        else
            if (bookList[i].isZipped())
            {
                QZipReader zip(bookList[i].getFileName());
                if (zip.exists())
                {
                    bool res = false;
                    foreach (QZipReader::FileInfo info, zip.fileInfoList())
                    {
                        if(info.filePath == bookList[i].getZippedFileName())
                        {
                            res = true;
                            break;
                        }
                    }

                    if (!res)
                        missBooks.append(&bookList[i]);
                }
                else
                    missBooks.append(&bookList[i]);
            }
    }

    return missBooks;
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


    //TODO: проверка корректности пути

    while (it.hasNext())
        fileList << it.next();

    if (fileList.size() == 0)
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


    if (format == 1 || format == 2)
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
    else if (format == 3)
    {
        QZipReader zip(file);
        if (zip.exists())
        {
            foreach (QZipReader::FileInfo info, zip.fileInfoList())
            {
                if(info.isFile)
                {
                    QString zippedFile = info.filePath;
                    QFileInfo info (zippedFile);
                    if (info.suffix().compare("fb2", Qt::CaseInsensitive) == 0)
                    {
                        QByteArray byteBook = zip.fileData(zippedFile);
                        bool result = true;
                        Book boo (result, file, zippedFile, byteBook, Gmap);

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
                }
            }
        }
    }
    else
        return;
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


void LibraryHandler::sortBooks(const QString &mode, bool direction)
{
    if (libraryView == 0)
        return;

    libraryView->setSort(mode, direction);
}


void LibraryHandler::findBooks(const QString &token, const QString &mode)
{
    if (libraryView == 0)
        return;

    QVariant key(token);

    if (!token.isEmpty())
        libraryView->setFilter(mode, key);
}


void LibraryHandler::clearFind()
{
    libraryView->setFilter(tr("Title"), "");
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
    if (libraryView != 0)
    {
        qDebug()<<"refreshing library representation";

        libraryView->clear();
        for (int i = 0; i < bookList.size(); i++)
            libraryView->addItem(&bookList[i]);
    }
}

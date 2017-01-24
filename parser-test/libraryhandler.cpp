#include "libraryhandler.h"
#include <QDirIterator>
#include <QDebug>


LibraryHandler::LibraryHandler(MainWindow* MWindow)
{
    window = MWindow;
    currentBookIndex = 0;
    filesMask<<"*.fb2"<<"*.zip";
}

void LibraryHandler::deleteBooks(QVector<int> deletedItemsIndexes)
{
    for (int i = 0; i < deletedItemsIndexes.size(); i++)
    {
        for (int j = 0; j < bookList.size(); j++)
        {
            if (bookList[j].getBookIndex() == deletedItemsIndexes.at(i))
            {
                window->UserActions->addAction(UActions::DeleteBook, bookList.at(j).File, 0);
                bookList.remove(j);
                break;
            }
        }
    }
    if (deletedItemsIndexes.size())
        saveBookList();
}

void LibraryHandler::AddBooks(const QStringList fileList)
{
    if (!fileList.size())
        return;

    GenresMap *Gmap = new GenresMap();

    for (int i = 0; i < fileList.size(); i++)
        openNewBooks(fileList[i], Gmap);

    delete Gmap;
    saveBookList();
}


void LibraryHandler::AddFolder(QString path)
{
    QStringList fileList;

    if (path.isEmpty())
        return;

    QDirIterator it(path, filesMask, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
        fileList << it.next();

    if (!fileList.size())
        return;

    GenresMap *Gmap = new GenresMap();

    for (int i = 0; i < fileList.size(); ++i)
        openNewBooks(fileList[i], Gmap);

    saveBookList();
    delete Gmap;
}


void LibraryHandler::loadBookList()
{
    QFile bookFileList(window->resoursesFolderPath + "/BookList.lb");

    if(bookFileList.open(QIODevice::ReadOnly | QIODevice::Text ))
        qDebug() << "File Has Been Created" << endl;
    else
    {
        qDebug() << "Failed to Create File" << endl;
        ///оповещение - невозможно открыть или создать файл библиотеки
        return;
    }

    QDataStream in(&bookFileList);
    Book temp;
    while (!in.atEnd())
    {
        in>>temp;
        temp.setBookIndex(currentBookIndex++);
        bookList.push_back(temp);
        window->LibraryLayout->addItem(temp.getBookIndex(), temp.getAuthorName(), temp.getTitle(), temp.getCover());
    }
    bookFileList.close();
}


void LibraryHandler::saveBookList()
{
    QFile bookFileList(window->resoursesFolderPath + "/BookList.lb");

    if(bookFileList.open(QIODevice::WriteOnly | QIODevice::Text ))
    {
        qDebug() << "Book File Has Been Created" << endl;
    }
    else
    {
        qDebug() << "Failed to Create Book File" << endl;
        ///оповещение - невозможно открыть или создать файл библиотеки
        return;
    }

    QDataStream out(&bookFileList);
    for (int i = 0; i < bookList.size(); i++)
        out<<bookList[i];

    bookFileList.close();
    window->UserActions->saveLog();
}


QString LibraryHandler::getFileTipe(const QString fileName)
{
    QString tipe;
    for (int i = 1; i <= 4; i++)
        tipe.push_front(fileName[fileName.length()-i]);

    if (tipe == ".zip" || tipe == ".ZIP")
        return "zip";
    if (tipe == ".FB2" || tipe == ".fb2")
        return "fb2";
    return "unknown format!";
}


void LibraryHandler::openNewBooks(const QString file, GenresMap *Gmap)
{
    for (int j = 0; j < bookList.size(); j++)
    {
        if (file == bookList.at(j).File)
        {
            /// оповещение - такая книга уже есть
            return;
        }
    }

    QString tipe = getFileTipe(file);

    if (tipe == "fb2")
    {
        bool result;
        Book boo(result, file, Gmap);
        if (!result)
            return;

        boo.setBookIndex(currentBookIndex++);
        bookList.push_back(boo);

        window->UserActions->addAction(UActions::AddBook, file, 0);
        window->LibraryLayout->addItem(boo.getBookIndex(), boo.getAuthorName(), boo.getTitle(), boo.getCover());
    }
    if (tipe == "zip")
    {
        qDebug()<<"zip!";
    }
}

void LibraryHandler::deleteBook(const int index)
{
    window->LibraryLayout->deleteBook(index);
    for (int i = 0; i < bookList.size(); i++)
        if (bookList[i].getBookIndex() == index)
        {
            window->UserActions->addAction(UActions::DeleteBook, bookList.at(i).File, 0);
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

void LibraryHandler::sortBooks(const QString mode)
{
    if (mode == QObject::tr("Date"))
    {
        window->LibraryLayout->clear();
        for (int i = 0; i < bookList.size(); i++)
            window->LibraryLayout->addItem(bookList[i].getBookIndex(), bookList[i].getAuthorName(), bookList[i].getTitle(), bookList[i].getCover());
        return;
    }
    if (mode == QObject::tr("Author"))
    {

        QVector <Book> indexVector = bookList;
        qSort(indexVector.begin(), indexVector.end(), &AuthorComparator);
        window->LibraryLayout->clear();
        for (int i = 0; i < indexVector.size(); i++)
            window->LibraryLayout->addItem(indexVector[i].getBookIndex(), indexVector[i].getAuthorName(), indexVector[i].getTitle(), indexVector[i].getCover());
        return;
    }
    if (mode == QObject::tr("Title"))
    {
        window->LibraryLayout->clear();
        QVector <Book> indexVector = bookList;
        qSort(indexVector.begin(), indexVector.end(), TitleComparator);
        window->LibraryLayout->clear();
        for (int i = 0; i < indexVector.size(); i++)
            window->LibraryLayout->addItem(indexVector[i].getBookIndex(), indexVector[i].getAuthorName(), indexVector[i].getTitle(), indexVector[i].getCover());
        return;
    }
}


void LibraryHandler::findBooks(QString token, QString mode)
{
    if (token != "")
    {
        needRefresh = true;
        window->LibraryLayout->clear();
        if (mode == QObject::tr("Title"))
        {
            for (int i = 0; i < bookList.size(); i++)
                if (bookList[i].getTitle().indexOf(token, 0, Qt::CaseInsensitive) != -1)
                    window->LibraryLayout->addItem(bookList[i].getBookIndex(), bookList[i].getAuthorName(), bookList[i].getTitle(), bookList[i].getCover());
            return;
        }
        if (mode == QObject::tr("Author"))
        {
            for (int i = 0; i < bookList.size(); i++)
                if (bookList[i].getAuthorName().indexOf(token, 0, Qt::CaseInsensitive) != -1)
                    window->LibraryLayout->addItem(bookList[i].getBookIndex(), bookList[i].getAuthorName(), bookList[i].getTitle(), bookList[i].getCover());
            return;
        }
        if (mode == QObject::tr("Series"))
        {
            for (int i = 0; i < bookList.size(); i++)
                if (bookList[i].getSeries().indexOf(token, 0, Qt::CaseInsensitive) != -1)
                    window->LibraryLayout->addItem(bookList[i].getBookIndex(), bookList[i].getAuthorName(), bookList[i].getTitle(), bookList[i].getCover());
            return;
        }
    }
    else
        return;
}

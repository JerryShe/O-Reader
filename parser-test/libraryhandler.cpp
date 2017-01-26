#include "libraryhandler.h"
#include <QDirIterator>
#include <QDebug>


LibraryHandler::LibraryHandler(librarylayout *LWidget)
{
    resoursesFolderPath = "LibraryResources";
    LibraryWidget = LWidget;
    UserActions = Synchronization::getSynchronization();;
    currentBookIndex = 0;
    filesMask<<"*.fb2";
}

LibraryHandler::~LibraryHandler()
{
    saveBookList();
}

void LibraryHandler::deleteBooks(QVector<int> deletedItemsIndexes)
{
    for (int i = 0; i < deletedItemsIndexes.size(); i++)
    {
        for (int j = 0; j < bookList.size(); j++)
        {
            if (bookList[j].getBookIndex() == deletedItemsIndexes.at(i))
            {
                UserActions->addAction(UActions::DeleteBook, bookList.at(j).File);
                bookList.remove(j);
                break;
            }
        }
    }
    if (deletedItemsIndexes.size())
    {
        saveBookList();
        UserActions->saveLog();
        RefreshLibrary();
    }
}

void LibraryHandler::AddBooks(const QStringList fileList)
{
    if (!fileList.size())
        return;

    GenresMap *Gmap = new GenresMap();

    for (int i = 0; i < fileList.size(); i++)
        openNewBook(fileList[i], Gmap);

    UserActions->saveLog();
    saveBookList();
    delete Gmap;
}


void LibraryHandler::AddFolder(QString path)
{
    if (path.isEmpty())
        return;

    QStringList fileList;

    QDirIterator it(path, filesMask, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
        fileList << it.next();
    if (!fileList.size())
        return;

    GenresMap *Gmap = new GenresMap();

    for (int i = 0; i < fileList.size(); ++i)
        openNewBook(fileList[i], Gmap);

    saveBookList();
    UserActions->saveLog();
    delete Gmap;
}


void LibraryHandler::loadBookList()
{
    QFile bookFileList(resoursesFolderPath + "/BookList.lb");

    if(bookFileList.open(QIODevice::ReadOnly | QIODevice::Text ))
        qDebug() << "File Has Been Opened" << endl;
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
        LibraryWidget->addItem(temp.getBookIndex(), temp.getAuthorName(), temp.getTitle(), temp.getCover());
    }
    bookFileList.close();
}


void LibraryHandler::saveBookList()
{
    QFile bookFileList(resoursesFolderPath + "/BookList.lb");

    if(bookFileList.open(QIODevice::WriteOnly | QIODevice::Text ))
    {
        qDebug() << "Book File Has Been Opened" << endl;
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

    qDebug()<<"books saved";
    bookFileList.close();
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


void LibraryHandler::openNewBook(const QString file, GenresMap *Gmap)
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
        bool result = true;
        Book boo(result, file, Gmap);
        if (!result)
        {
            /// оповещение - невозможно открыть как fb2
            qDebug()<<"Invalid FB2 file!";
            return;
        }

        boo.setBookIndex(currentBookIndex++);
        bookList.push_back(boo);

        UserActions->addAction(UActions::AddBook, file);
        LibraryWidget->addItem(boo.getBookIndex(), boo.getAuthorName(), boo.getTitle(), boo.getCover());
    }
    if (tipe == "zip")
    {
        qDebug()<<"zip!";
    }
}

void LibraryHandler::deleteBook(const int index)
{
    LibraryWidget->deleteBook(index);
    for (int i = 0; i < bookList.size(); i++)
        if (bookList[i].getBookIndex() == index)
        {
            UserActions->addAction(UActions::DeleteBook, bookList.at(i).File);
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
        LibraryWidget->clear();
        for (int i = 0; i < bookList.size(); i++)
            LibraryWidget->addItem(bookList[i].getBookIndex(), bookList[i].getAuthorName(), bookList[i].getTitle(), bookList[i].getCover());
        return;
    }
    if (mode == QObject::tr("Author"))
    {

        QVector <Book> indexVector = bookList;
        qSort(indexVector.begin(), indexVector.end(), &AuthorComparator);
        LibraryWidget->clear();
        for (int i = 0; i < indexVector.size(); i++)
            LibraryWidget->addItem(indexVector[i].getBookIndex(), indexVector[i].getAuthorName(), indexVector[i].getTitle(), indexVector[i].getCover());
        return;
    }
    if (mode == QObject::tr("Title"))
    {
        LibraryWidget->clear();
        QVector <Book> indexVector = bookList;
        qSort(indexVector.begin(), indexVector.end(), TitleComparator);
        LibraryWidget->clear();
        for (int i = 0; i < indexVector.size(); i++)
            LibraryWidget->addItem(indexVector[i].getBookIndex(), indexVector[i].getAuthorName(), indexVector[i].getTitle(), indexVector[i].getCover());
        return;
    }
}


void LibraryHandler::findBooks(QString token, QString mode)
{
    if (token != "")
    {
        needRefresh = true;
        LibraryWidget->clear();
        if (mode == QObject::tr("Title"))
        {
            for (int i = 0; i < bookList.size(); i++)
                if (bookList[i].getTitle().indexOf(token, 0, Qt::CaseInsensitive) != -1)
                    LibraryWidget->addItem(bookList[i].getBookIndex(), bookList[i].getAuthorName(), bookList[i].getTitle(), bookList[i].getCover());
            return;
        }
        if (mode == QObject::tr("Author"))
        {
            for (int i = 0; i < bookList.size(); i++)
                if (bookList[i].getAuthorName().indexOf(token, 0, Qt::CaseInsensitive) != -1)
                    LibraryWidget->addItem(bookList[i].getBookIndex(), bookList[i].getAuthorName(), bookList[i].getTitle(), bookList[i].getCover());
            return;
        }
        if (mode == QObject::tr("Series"))
        {
            for (int i = 0; i < bookList.size(); i++)
                if (bookList[i].getSeries().indexOf(token, 0, Qt::CaseInsensitive) != -1)
                    LibraryWidget->addItem(bookList[i].getBookIndex(), bookList[i].getAuthorName(), bookList[i].getTitle(), bookList[i].getCover());
            return;
        }
    }
}

Book* LibraryHandler::getBookByIndex(int index)
{
    int i;
    for (i = 0; i < bookList.size(); i++)
        if (bookList[i].getBookIndex() == index)
            break;
    return &bookList[i];
}

void LibraryHandler::RefreshLibrary()
{
    if (needRefresh == true)
    {
        LibraryWidget->clear();
        needRefresh = false;
        for (int i = 0; i < bookList.size(); i++)
            LibraryWidget->addItem(bookList[i].getBookIndex(), bookList[i].getAuthorName(), bookList[i].getTitle(), bookList[i].getCover());
    }
}

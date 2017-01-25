#ifndef LIBRARYHANDLER_H
#define LIBRARYHANDLER_H

#include <QString>
#include <QObject>
#include <library_layout.h>
#include <synchronization.h>
#include "genresmap.h"
#include "books.h"


class LibraryHandler: public QObject
{
    Q_OBJECT

public:
    LibraryHandler(librarylayout* LWidget);

public slots:
    void AddBooks(const QStringList fileList);
    void AddFolder(const QString path);
    void deleteBook(const int index);
    void deleteBooks(QVector <int> deletedItemsIndexes);

    void openNewBooks(const QString fileList, GenresMap *Gmap);
    QString getFileTipe(const QString fileName);

    void findBooks(QString key, QString mode);

    Book* getBookByIndex(int index);

    void RefreshLibrary();

    void loadBookList();
    void saveBookList();

    void sortBooks(const QString mode);

private:
    librarylayout* LibraryWidget;
    Synchronization* UserActions;
    QString resoursesFolderPath;
    bool needRefresh = false;
    QStringList filesMask;
    QVector <Book> bookList;
    int currentBookIndex;
};

#endif // LIBRARYHANDLER_H

#ifndef LIBRARYHANDLER_H
#define LIBRARYHANDLER_H

#include <QString>
#include <QObject>
#include "library.h"
#include "synchronization.h"
#include "genresmap.h"
#include "books.h"

#include <QJsonObject>

class LibraryHandler: public QObject
{
    Q_OBJECT

public:
    static LibraryHandler* getLibraryHandler();


public slots:
    void setLibraryWidget(Library *lbWidget);

    void AddBooks(const QStringList &fileList);
    void AddFolder(const QString &path);
    void deleteBook(const unsigned int &index);
    void deleteBooks(QVector <unsigned int> deletedItemsIndexes);

    void openNewBook(const QString &fileList, GenresMap *Gmap);

    void findBooks(const QString &key, const QString &mode);

    Book* getBookByIndex(const unsigned int &index);

    void refreshLibrary();

    bool loadBookList();
    bool saveBookList();

    QJsonObject toJson();
    void fromJson(const QJsonObject &json);

    Book* getLastOpenedBook();

    void sortBooks(const QString &mode);

private:
    int getFileTipe(const QString &fileName);           /// 0 - unknown, 1 - FB2, 2 - EPub, 3 - zip


    LibraryHandler();
    ~LibraryHandler();

    Library* LibraryView;

    Synchronization* UserActions;

    QString resoursesFolderPath;

    bool needRefresh;

    QStringList filesMask;

    QVector <Book> bookList;
    unsigned int currentBookIndex;
};

#endif // LIBRARYHANDLER_H

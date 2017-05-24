#ifndef LIBRARYHANDLER_H
#define LIBRARYHANDLER_H

#include <QString>
#include <QObject>
#include "library_view.h"
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
    void setLibraryWidget(LibraryView *lbWidget);

    void AddBooks(const QStringList &fileList);
    void AddFolder(const QString &path);
    void deleteBook(const unsigned int &index);
    void deleteBooks(QVector <unsigned int> deletedItemsIndexes);

    void openNewBook(const QString &fileList, GenresMap *Gmap);

    void findBooks(const QString &key, const QString &mode);

    Book* getBookByIndex(const unsigned int &index);

    void refreshLibrary();

    bool loadBookList();
    bool saveBookList() const;

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

    Book* getLastOpenedBook();

    void sortBooks(const QString &mode);


signals:
    void showLoadImage(QString gifFile);
    void hideLoadImage();

private:
    int getFileTipe(const QString &fileName) const;           /// 0 - unknown, 1 - FB2, 2 - EPub, 3 - zip


    LibraryHandler();
    ~LibraryHandler();

    LibraryView* libraryView;

    Synchronization* UserActions;

    QString resoursesFolderPath;

    bool needRefresh;

    QStringList filesMask;

    QVector <Book> bookList;
    unsigned int currentBookIndex;
};

#endif // LIBRARYHANDLER_H

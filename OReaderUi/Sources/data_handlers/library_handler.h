#ifndef LIBRARYHANDLER_H
#define LIBRARYHANDLER_H

#include "main_window/library/library_view/library_view.h"
#include "data_handlers/synchronization.h"
#include "data_handlers/genresmap.h"
#include "data_handlers/book.h"

#include <QString>
#include <QObject>
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
    void clearFind();

    Book* getBookByIndex(const unsigned int &index);

    void refreshLibrary();

    bool loadBookList();
    bool saveBookList() const;

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

    Book* getLastOpenedBook();

    void sortBooks(const QString &mode, bool direction = false);

    QVector <Book*> findMissingBooks();

signals:
    void showLoadImage(QString gifFile);
    void hideLoadImage();
    void lostBooks(QVector <Book*>);

private:
    int getFileTipe(const QString &fileName) const;           /// 0 - unknown, 1 - FB2, 2 - EPub, 3 - zip


    LibraryHandler();
    ~LibraryHandler();

    LibraryView* libraryView;

    Synchronization* UserActions;

    QString resoursesFolderPath;

    QStringList filesMask;

    QVector <Book> bookList;
    unsigned int currentBookIndex;
};

#endif // LIBRARYHANDLER_H

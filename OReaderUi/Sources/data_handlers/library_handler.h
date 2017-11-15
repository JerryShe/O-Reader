#ifndef LIBRARYHANDLER_H
#define LIBRARYHANDLER_H

#include "library_view.h"
#include "synchronization.h"
#include "book.h"
#include "book_creator.h"

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

    void openNewBook(const QString &fileList);

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
    void addBookToLib(Book &book);

    LibraryHandler();
    ~LibraryHandler();

    LibraryView* libraryView;

    Synchronization* UserActions;

    BookCreator* bookCreator;

    QString resoursesFolderPath;

    QStringList filesMask;

    QHash <unsigned int, Book> bookTable;
    unsigned int currentBookIndex;
};

#endif // LIBRARYHANDLER_H

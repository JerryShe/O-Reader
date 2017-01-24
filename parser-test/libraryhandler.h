#ifndef LIBRARYHANDLER_H
#define LIBRARYHANDLER_H

#include <QString>
#include <QObject>
#include "main_window.h"
#include "ui_mainwindow.h"

class MainWindow;

class LibraryHandler: public QObject
{
    Q_OBJECT

public:
    LibraryHandler(MainWindow* MWindow);

public slots:
    void AddBooks(const QStringList fileList);
    void AddFolder(const QString path);
    void deleteBook(const int index);
    void deleteBooks(QVector <int> deletedItemsIndexes);

    void openNewBooks(const QString fileList, GenresMap *Gmap);
    QString getFileTipe(const QString fileName);

    void findBooks(QString key, QString mode);

    void loadBookList();
    void saveBookList();

    void sortBooks(const QString mode);

public:
    bool needRefresh = false;
    QStringList filesMask;
    QVector <Book> bookList;
    int currentBookIndex;

private:
    MainWindow * window;
};

#endif // LIBRARYHANDLER_H

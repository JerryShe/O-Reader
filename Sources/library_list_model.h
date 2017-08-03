#ifndef LIBRARY_LIST_MODEL_H
#define LIBRARY_LIST_MODEL_H

#include <QAbstractListModel>

#include "books.h"


enum BookInf
{
    Index = 100,
    CoverImage,
    AuthorName,
    Title,
    Progress,
    Series
};


struct BookData
{
    QVariant cover;
    QVariant author;
    QVariant title;
    QVariant index;
    QVariant progress;
    QVariant series;

    BookData(Book* book);
    BookData();
};


class LibraryListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    LibraryListModel(QObject* parent = 0);
    LibraryListModel(QVector <Book> &bookList, QObject *parent);

    ~LibraryListModel();

    QVariant data(const QModelIndex &index, int role) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);

    int rowCount(const QModelIndex &parent) const;
    int rowCount() const;

    void removeRow(int row);

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;


    void addBook(Book* book);

    void deleteBookByIndex(const unsigned int &index);
    void deleteBooksByIndexes(const QVector<unsigned int> &indexes);

    void clear();


private:
    QVector <BookData> bookVector;
    Qt::ItemDataRole DisplayRole;

};

#endif // LIBRARY_LIST_MODEL_H

#ifndef LIBRARY_MODEL_H
#define LIBRARY_MODEL_H

#include <QAbstractListModel>
#include <QStyledItemDelegate>

#include "books.h"


enum BookInf
{
    Index = 100,
    CoverImage,
    AuthorName,
    Title,
    Progress
};


struct BookData
{
    QVariant cover;
    QVariant author;
    QVariant title;
    QVariant index;
    QVariant progress;

    BookData(Book* book);
    BookData();
};


class LibraryModel : public QAbstractListModel
{
    Q_OBJECT

public:
    LibraryModel(QObject* parent);
    LibraryModel(QVector <Book> &bookList, QObject *parent);

    ~LibraryModel();

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



class LibraryListDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    LibraryListDelegate();
    ~LibraryListDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index ) const;


    void setListViewMode(const bool flag);
    bool listViewMode() const;

    void setItemsColors(const QColor &norm, const QColor &sel, const QColor &hov, const QColor &hovSel);

private:
    void paintListViewItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index, const QRect &rect) const;
    void paintIconViewItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index, const QRect &rect) const;

    void drawBookStatus(const QPoint &pos, const double &progress, QPainter *painter, const QRect &rect) const;

    void drawBackground(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect) const;


    QFont font;
    QFontMetrics* fm;
    bool viewMode;      //0 - icon, 1 - list

    QColor normal;
    QColor selected;
    QColor hover;
    QColor hoverSelected;
};

#endif // LIBRARY_MODEL_H

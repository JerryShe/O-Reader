#include "library_list_model.h"

#include <QVariant>
#include <QPixmap>

#include <QDebug>


BookData::BookData(Book* book)
{
    cover = QVariant(QPixmap::fromImage(book->getCover()));
    author = QVariant(book->getAuthorName());
    title = QVariant(book->getTitle());
    index = QVariant(book->getIndex());
    progress = QVariant(book->getProgressProcent());
    series = QVariant(book->getSeries());
    additionTime = QVariant(book->getAdditionalTime());
}


BookData::BookData()
{}


LibraryListModel::LibraryListModel(QObject* parent) : QAbstractListModel(parent)
{}


LibraryListModel::LibraryListModel(QVector<Book> &bookList, QObject *parent) : QAbstractListModel(parent)
{
    for (int i = 0; i < bookList.size(); i++)
        addBook(&bookList[i]);
}


LibraryListModel::~LibraryListModel()
{
    qDebug()<<"delete LibraryModel";
    bookVector.clear();
}


QVariant LibraryListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() && index.row() < bookVector.size())
        return QVariant();

    switch (role)
    {
    case BookInf::Index:
        return bookVector[index.row()].index;
    case BookInf::CoverImage:
        return bookVector[index.row()].cover;
    case BookInf::AuthorName:
        return bookVector[index.row()].author;
    case BookInf::Title:
        return bookVector[index.row()].title;
    case BookInf::Progress:
        return bookVector[index.row()].progress;
    case BookInf::Series:
        return bookVector[index.row()].series;
    case BookInf::AdditionDate:
        return bookVector[index.row()].additionTime;

    default:
        return QVariant();
    }
}


bool LibraryListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(value)

    if (index.isValid())
    {
        if (role == Qt::DisplayRole)
            return true;
    }
    return false;
}


int LibraryListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return bookVector.size();
}


int LibraryListModel::rowCount() const
{
    return bookVector.size();
}


void LibraryListModel::removeRow(int row)
{
    if (row >= 0 && row < bookVector.size())
        bookVector.removeAt(row);
}


QVariant LibraryListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section)
    Q_UNUSED(orientation)
    Q_UNUSED(role)

    return QVariant();
}


Qt::ItemFlags LibraryListModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractListModel::flags(index);
    return index.isValid() ? (flags | Qt::ItemIsEditable) : flags;
}


void LibraryListModel::addBook(Book* book)
{
    beginInsertRows(QModelIndex(), 0, 0);
    bookVector.prepend(BookData(book));
    endInsertRows();
}


void LibraryListModel::deleteBookByIndex(const QString &index)
{
    for (int i = 0; i < bookVector.size(); i++)
        if (bookVector[i].index.toString() == index)
        {
            beginRemoveRows(QModelIndex(), i, i);
            bookVector.removeAt(i);
            endRemoveRows();
            break;
        }
}


void LibraryListModel::deleteBooksByIndexes(const QVector<QString> &indexes)
{
    for (int i = 0; i < indexes.size(); i++)
        deleteBookByIndex(indexes[i]);
}


void LibraryListModel::clear()
{
    bookVector.clear();
}

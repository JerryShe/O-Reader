#include "library_list_proxy_model.h"

#include <QDebug>


LibraryListProxyModel::LibraryListProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent), sortType(0), sortDirection(false)
{
    invalidateFilter();
    qDebug()<<"create library proxy model";
}


LibraryListProxyModel::~LibraryListProxyModel()
{
    qDebug()<<"delete library proxy model";
}


void LibraryListProxyModel::setFilter(BookInf role, QVariant value)
{
    curFilter = role;
    curFilterVal = value;
    invalidateFilter();
}


void LibraryListProxyModel::setSort(const int &type, const bool &direction)
{
    sortType = type;
    sortDirection = direction;
}


bool LibraryListProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    switch (curFilter)
    {
    case BookInf::AuthorName:
    {
        if (!curFilterVal.toString().isEmpty())
            return sourceModel()->index(sourceRow, 0, sourceParent).
                    data(BookInf::AuthorName).toString().contains(curFilterVal.toString(), Qt::CaseInsensitive);
        else
            return true;
    }
    case BookInf::Title:
    {
        if (!curFilterVal.toString().isEmpty())
            return sourceModel()->index(sourceRow, 0, sourceParent).
                    data(BookInf::Title).toString().contains(curFilterVal.toString(), Qt::CaseInsensitive);
        else
            return true;
    }
    case BookInf::Series:
    {
        if (!curFilterVal.toString().isEmpty())
            return sourceModel()->index(sourceRow, 0, sourceParent).
                    data(BookInf::Series).toString().contains(curFilterVal.toString(), Qt::CaseInsensitive);
        else
            return true;
    }
    default:
        return true;
    }
}


bool LibraryListProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    bool answ = false;

    switch (sortType)
    {
    case 0:
        answ = (left.data(BookInf::Index).toInt() < right.data(BookInf::Index).toInt()); /// index
        break;

    case 1:
        answ = (left.data(BookInf::AuthorName).toString() < right.data(BookInf::AuthorName).toString());
        break;

    case 2:
        answ = (left.data(BookInf::Title).toString() < right.data(BookInf::Title).toString());
        break;

    case 3:
        answ = (left.data(BookInf::Progress).toDouble() < right.data(BookInf::Progress).toDouble());
        break;

    default:
        break;
    }

    if (sortDirection)
        answ = !answ;

    return answ;
}

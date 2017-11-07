#ifndef LIBRARY_LIST_PROXY_MODEL_H
#define LIBRARY_LIST_PROXY_MODEL_H

#include <QSortFilterProxyModel>

#include "main_window/library/library_view/library_list_model.h"


class LibraryListProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    LibraryListProxyModel(QObject *parent = 0);
    ~LibraryListProxyModel();

    void setFilter(BookInf role, QVariant value = 0);
    void setSort(const int &type, const bool &direction);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    BookInf curFilter;
    QVariant curFilterVal;

    int sortType;  /// 0 - date, 1 - author, 2 - title, 3 - progress
    bool sortDirection;
};


#endif // LIBRARY_LIST_PROXY_MODEL_H

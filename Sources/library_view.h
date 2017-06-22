#ifndef LIBRARY_VIEW_H
#define LIBRARY_VIEW_H


#include <QGridLayout>
#include <QListView>
#include <QStandardItemModel>

#include "settings.h"
#include "books.h"
#include "library_list_model.h"
#include "library_list_delegate.h"
#include "library_list_proxy_model.h"

#include <QPersistentModelIndex>


class LibraryView : public QListView
{
    Q_OBJECT

public:
    LibraryView(QWidget *widget = 0);
    ~LibraryView();

    void addItem(Book *book);
    QVector <unsigned int> deleteSelectedItems();
    void deleteBook(const unsigned int &index);
    void setSettingsData();

    int getSelectedItemsCount();

    void groupBy(const QString &mode);

public slots:
    void changeViewMod();
    void iconUpscale();
    void iconDownscale();

    void clear();

    void setSort(const QString &type, const bool &direction);
    void setFilter(const QString &type, const QVariant &role);

signals:
    void showBookPage(unsigned int index);

private slots:
    void showSelectedItem(const QModelIndex &mIndex);

private:
    LibraryListModel* BookModel;
    LibraryListProxyModel* BookProxyModel;
    LibraryListDelegate* delegate;

    Settings* ProgramSettings;

    unsigned short IconBarSize;
    unsigned short IconListSize;
};

#endif // LIBRARY_VIEW_H

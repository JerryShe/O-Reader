#ifndef LIBRARY_VIEW_H
#define LIBRARY_VIEW_H

#include "device_settings.h"
#include "book.h"
#include "library_list_model.h"
#include "library_list_delegate.h"
#include "library_list_proxy_model.h"

#include <QGridLayout>
#include <QListView>
#include <QStandardItemModel>


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
    bool getLibraryRepresentation() const;

    void groupBy(const QString &mode);

public slots:
    void changeViewMod();

    void setBookIconSize(const int &size);
    int getBookIconSize() const;

    void clear();

    void setSort(const QString &type, const bool &direction);
    void setFilter(const QString &type, const QVariant &key);

signals:
    void showBookPage(unsigned int index);

private slots:
    void showSelectedItem(const QModelIndex &mIndex);

private:
    LibraryListModel* BookModel;
    LibraryListProxyModel* BookProxyModel;
    LibraryListDelegate* delegate;

    DeviceSettings* deviceSettings;

    int IconBarSize;
    int IconListSize;
};

#endif // LIBRARY_VIEW_H

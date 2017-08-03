#include "library_view.h"
#include "styles.h"

#include <QGridLayout>
#include <QPair>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QCoreApplication>
#include <QScrollBar>
#include <QScroller>

#include "settings.h"



LibraryView::LibraryView(QWidget *widget) : QListView(widget)
{
    qRegisterMetaType<QList<QPersistentModelIndex> >("QList<QPersistentModelIndex>");
    qRegisterMetaType<QAbstractItemModel::LayoutChangeHint>("QAbstractItemModel::LayoutChangeHint");

    qDebug()<<"create LibraryView";

    setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
    setResizeMode(QListView::Adjust);

    setAttribute(Qt::WA_AcceptTouchEvents);
    verticalScrollBar()->setSingleStep(30);

    if (QTouchDevice::devices().size())
        QScroller::grabGesture(viewport(), QScroller::LeftMouseButtonGesture);

    BookModel = new LibraryListModel(this);
    BookProxyModel = new LibraryListProxyModel();
    delegate = new LibraryListDelegate(this);

    setSettingsData();

    this->setItemDelegate(delegate);
    BookProxyModel->setSourceModel(BookModel);


    this->setModel(BookProxyModel);
    BookProxyModel->setDynamicSortFilter(true);
    BookProxyModel->sort(0);

    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setDragDropMode(QAbstractItemView::NoDragDrop);

    connect(this, SIGNAL(activated(QModelIndex)), SLOT(showSelectedItem(QModelIndex)));
    this->show();
}


LibraryView::~LibraryView()
{
    qDebug()<<"delete LibraryView";
}


void LibraryView::showSelectedItem(const QModelIndex &mIndex)
{
   if (!mIndex.isValid())
      return;

   emit(showBookPage(mIndex.data(BookInf::Index).toInt()));
}


void LibraryView::addItem(Book *book)
{
    BookModel->addBook(book);
    BookProxyModel->invalidate();
    this->repaint();
}


void LibraryView::changeViewMod()
{
    if (viewMode() == QListView::IconMode)
    {
        setViewMode(QListView::ListMode);
        delegate->setListViewMode(true);

        setIconSize(QSize(IconListSize,IconListSize));
        setGridSize(QSize(IconListSize, IconListSize));

        deviceSettings->setLibraryReprezentation(true);
    }
    else
    {
        setViewMode(QListView::IconMode);
        delegate->setListViewMode(false);

        setIconSize(QSize(IconBarSize, IconBarSize + 70));
        setGridSize(QSize(IconBarSize, IconBarSize + 70));

        deviceSettings->setLibraryReprezentation(false);
    }
    verticalScrollBar()->setSingleStep(30);
}


void LibraryView::setBookIconSize(const int &size)
{
    if (viewMode() == QListView::IconMode)
    {
        IconBarSize = size;
        deviceSettings->setLibraryBarIconSize(size);

        setGridSize(QSize(size, size + 70));
        setIconSize(QSize(size, size + 70));
    }
    else
    {
        IconListSize = size;
        deviceSettings->setLibraryListIconSize(size);

        setGridSize(QSize(size, size));
        setIconSize(QSize(size, size));
    }
}


int LibraryView::getBookIconSize() const
{
    if (viewMode() == QListView::ListMode)
        return IconListSize;
    return IconBarSize;
}


QVector<unsigned int> LibraryView::deleteSelectedItems()
{
    qDebug()<<"delete books";

    QVector <unsigned int> deletedItems;

    QModelIndexList SelectedItems = selectionModel()->selectedIndexes();

    for (int i = 0; i < SelectedItems.size(); i++)
        deletedItems.push_back(SelectedItems.at(i).data(BookInf::Index).toInt());

    for (int i = 0; i < deletedItems.size(); i++)
        BookModel->deleteBookByIndex(deletedItems[i]);

    return deletedItems;
}


void LibraryView::deleteBook(const unsigned int &index)
{
    qDebug()<<"delete "<<index;
    BookModel->deleteBookByIndex(index);

    BookProxyModel->invalidate();
}


int LibraryView::getSelectedItemsCount()
{
    return selectionModel()->selectedIndexes().size();
}


void LibraryView::clear()
{
    BookModel->clear();
}


void LibraryView::groupBy(const QString &mode)
{

}


void LibraryView::setSort(const QString &type, const bool &direction)
{
    if (type == tr("Date"))
        BookProxyModel->setSort(0, direction);
    else if (type == tr("Author"))
        BookProxyModel->setSort(1, direction);
    else if (type == tr("Title"))
        BookProxyModel->setSort(2, direction);
    else if (type == tr("Progress"))
        BookProxyModel->setSort(3, direction);

    BookProxyModel->invalidate();
}


void LibraryView::setFilter(const QString &type, const QVariant &key)
{
    if (type == tr("Title"))
        BookProxyModel->setFilter(BookInf::Title, key);
    else if (type == tr("Author"))
        BookProxyModel->setFilter(BookInf::AuthorName, key);
    else if (type == tr("Series"))
        BookProxyModel->setFilter(BookInf::Series, key);

    BookProxyModel->invalidate();
}


void LibraryView::setSettingsData()
{
    deviceSettings = DeviceSettings::getDeviceSettings();

    QString ListViewStyle[1];
    setLibraryStyle(ListViewStyle, Settings::getSettings()->getInterfaceStyle());
    setStyleSheet(ListViewStyle[0]);

    IconBarSize = deviceSettings->getLibraryBarIconSize();
    IconListSize = deviceSettings->getLibraryListIconSize();

    if (deviceSettings->getLibraryRepresentation())
    {
        setViewMode(QListView::ListMode);
        delegate->setListViewMode(true);
        setIconSize(QSize(IconListSize, IconListSize));
        setGridSize(QSize(IconListSize, IconListSize));
    }
    else
    {
        setViewMode(QListView::IconMode);
        delegate->setListViewMode(false);
        setIconSize(QSize(IconBarSize, IconBarSize + 70));
        setGridSize(QSize(IconBarSize, IconBarSize + 70));
    }
}


bool LibraryView::getLibraryRepresentation() const
{
    if (viewMode() == QListView::ListMode)
        return true;
    return false;
}

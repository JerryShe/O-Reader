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




LibraryView::LibraryView(QWidget *widget)
{
    qRegisterMetaType<QList<QPersistentModelIndex> >("QList<QPersistentModelIndex>");
    qRegisterMetaType<QAbstractItemModel::LayoutChangeHint>("QAbstractItemModel::LayoutChangeHint");


    setParent(widget);

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
    qDebug()<<"create LibraryView";
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
        setGridSize(QSize(IconListSize + 5, IconListSize+ 5));
        setViewMode(QListView::ListMode);
        delegate->setListViewMode(true);
        setIconSize(QSize(IconListSize + 5,IconListSize + 5));
        ProgramSettings->setLibraryReprezentation(true);
    }
    else
    {
        setGridSize(QSize(IconBarSize - 10, IconBarSize + 60));
        setViewMode(QListView::IconMode);
        delegate->setListViewMode(false);
        setIconSize(QSize(IconBarSize - 10, IconBarSize + 60));
        ProgramSettings->setLibraryReprezentation(false);
    }
    verticalScrollBar()->setSingleStep(30);
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


void LibraryView::setFilter(const QString &type, const QVariant &role)
{
    if (type == tr("Title"))
        BookProxyModel->setFilter(BookInf::Title, role);
    else if (type == tr("Author"))
        BookProxyModel->setFilter(BookInf::AuthorName, role);

    BookProxyModel->invalidate();
}


void LibraryView::iconUpscale()
{
    if (viewMode() == QListView::IconMode)
    {
        if (IconBarSize < 260)
        {
            IconBarSize+=30;
            setGridSize(QSize(IconBarSize - 10, IconBarSize + 60));
            setIconSize(QSize(IconBarSize - 10, IconBarSize + 60));
            ProgramSettings->setLibraryBarIconSize(IconBarSize);
        }
    }
    else
    {
        if (IconListSize < 200)
        {
            IconListSize+=10;
            setGridSize(QSize(IconListSize + 5,IconListSize + 5));
            setIconSize(QSize(IconListSize + 5,IconListSize + 5));
            ProgramSettings->setLibraryListIconSize(IconListSize);
        }
    }
}


void LibraryView::iconDownscale()
{
    if (viewMode() == QListView::IconMode)
    {
        if (IconBarSize > 110)
        {
            IconBarSize-=30;
            setGridSize(QSize(IconBarSize - 10, IconBarSize + 60));
            setIconSize(QSize(IconBarSize - 10, IconBarSize + 60));
            ProgramSettings->setLibraryBarIconSize(IconBarSize);
        }
    }
    else
    {
        if (IconListSize > 30)
        {
            IconListSize-=10;
            setGridSize(QSize(IconListSize + 5, IconListSize + 5));
            setIconSize(QSize(IconListSize + 5,IconListSize + 5));
            ProgramSettings->setLibraryListIconSize(IconListSize);
        }
    }
}


void LibraryView::setSettingsData()
{
    ProgramSettings = Settings::getSettings();

    QString ListViewStyle[1];
    setLibraryStyle (ListViewStyle, ProgramSettings->getInterfaceStyle());
    setStyleSheet(ListViewStyle[0]);

    IconBarSize = ProgramSettings->getLibraryBarIconSize();
    IconListSize = ProgramSettings->getLibraryListIconSize();

    if (IconBarSize < 80 || IconBarSize > 280)
        IconBarSize = 140;
    if (IconListSize < 20 || IconBarSize > 210)
        IconListSize = 50;

    if (ProgramSettings->getLibraryReprezentation())
    {
        setGridSize(QSize(IconListSize + 5, IconListSize + 5));
        setViewMode(QListView::ListMode);
        delegate->setListViewMode(true);
        setIconSize(QSize(IconListSize + 5, IconListSize + 5));
    }
    else
    {
        setGridSize(QSize(IconBarSize - 10, IconBarSize + 60));
        setViewMode(QListView::IconMode);
        delegate->setListViewMode(false);
        setIconSize(QSize(IconBarSize - 10, IconBarSize + 60));
    }

    QColor normal;
    QColor selected;
    QColor hover;
    QColor hoverSelected;

    getLibraryStyleColors(normal, selected, hover, hoverSelected);
    delegate->setItemsColors(normal, selected, hover, hoverSelected);
}

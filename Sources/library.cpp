#include "library.h"
#include "styles.h"

#include <QGridLayout>
#include <QPair>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QCoreApplication>

Library::Library(QWidget *widget)
{
    setParent(widget);

    setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
    setResizeMode(QListView::Adjust);

    ListSize = 2;
    itemCount = 0;

    BookModel = new QStandardItemModel(ListSize,ListSize);
    setModel(BookModel);

    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setDragDropMode(QAbstractItemView::NoDragDrop);

    connect(this, SIGNAL(activated(QModelIndex)), SLOT(showSelectedItem(QModelIndex)));
}


Library::~Library()
{
    delete BookModel;
}


void Library::showSelectedItem(const QModelIndex &mIndex)
{
   if (!mIndex.isValid())
      return;

   emit(showBookPage(mIndex.data(Qt::WhatsThisRole).toInt()));
}


void Library::addItem(const unsigned int &BookIndex, const QString &name, const QString &title, const QImage &cover)
{
    BookModel->setRowCount(itemCount+1);

    QIcon coverIcon = QIcon(QPixmap::fromImage(cover));

    QModelIndex index = BookModel->index(itemCount++,0);
    BookModel->setData(index, name + '\n' + title, Qt::DisplayRole);
    BookModel->setData(index, name + '\n' + title, Qt::ToolTipRole);
    BookModel->setData(index, BookIndex, Qt::WhatsThisRole);
    BookModel->setData(index, coverIcon, Qt::DecorationRole);

    QCoreApplication::processEvents();
}


void Library::changeViewMod()
{
    if (viewMode() == QListView::IconMode)
    {
        setGridSize(QSize(IconListSize+5,IconListSize + 5));
        setViewMode(QListView::ListMode);
        setIconSize(QSize(IconListSize,IconListSize));
        ProgramSettings->setLibraryReprezentation(true);
    }
    else
    {
        setGridSize(QSize(IconBarSize - 10,IconBarSize + 60));
        setViewMode(QListView::IconMode);
        setIconSize(QSize(IconBarSize,IconBarSize));
        ProgramSettings->setLibraryReprezentation(false);
    }
}

QVector<unsigned int> Library::deleteItems()
{
    QVector <unsigned int> deletedItems;

    QModelIndexList SelectedItems = selectionModel()->selectedIndexes();
    for (int i = 0; i < SelectedItems.size(); i++)
        deletedItems.push_back(SelectedItems.at(i).data(Qt::WhatsThisRole).toInt());

    while(SelectedItems.size())
    {
        BookModel->removeRow(SelectedItems.first().row());
        SelectedItems = selectionModel()->selectedIndexes();
    }

    itemCount = itemCount - deletedItems.size();
    if (!BookModel->rowCount())
        clear();
    return deletedItems;
}


void Library::deleteBook(const unsigned int &index)
{
    int i;
    for (i = 0; i < BookModel->rowCount(); i++)
        if (BookModel->item(i,0)->data(Qt::WhatsThisRole) == index)
            break;

    BookModel->removeRow(i);
}


int Library::getSelectedItemsCount()
{
    return selectionModel()->selectedIndexes().size();
}


void Library::clear()
{
    QStandardItemModel* temp = BookModel;
    BookModel = new QStandardItemModel(ListSize,ListSize);

    setModel(BookModel);
    itemCount = 0;
    temp->clear();
    delete temp;
}


void Library::groupBy(const QString &mode)
{

}


void Library::iconUpscale()
{
    if (viewMode() == QListView::IconMode)
    {
        if (IconBarSize < 260)
        {
            IconBarSize+=30;
            setGridSize(QSize(IconBarSize - 10, IconBarSize + 60));
            setIconSize(QSize(IconBarSize,IconBarSize));
            ProgramSettings->setLibraryBarIconSize(IconBarSize);
        }
    }
    else
    {
        if (IconListSize < 200)
        {
            IconListSize+=10;
            setGridSize(QSize(IconListSize + 5,IconListSize + 5));
            setIconSize(QSize(IconListSize,IconListSize));
            ProgramSettings->setLibraryListIconSize(IconListSize);
        }
    }
}


void Library::iconDownscale()
{
    if (viewMode() == QListView::IconMode)
    {
        if (IconBarSize > 110)
        {
            IconBarSize-=30;
            setGridSize(QSize(IconBarSize - 10, IconBarSize + 60));
            setIconSize(QSize(IconBarSize,IconBarSize));
            ProgramSettings->setLibraryBarIconSize(IconBarSize);
        }
    }
    else
    {
        if (IconListSize > 30)
        {
            IconListSize-=10;
            setGridSize(QSize(IconListSize + 5,IconListSize + 5));
            setIconSize(QSize(IconListSize,IconListSize));
            ProgramSettings->setLibraryListIconSize(IconListSize);
        }
    }
}


void Library::setSettingsData()
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
        setGridSize(QSize(IconListSize+5,IconListSize + 5));
        setViewMode(QListView::ListMode);
        setIconSize(QSize(IconListSize,IconListSize));
    }
    else
    {
        setGridSize(QSize(IconBarSize - 10,IconBarSize + 60));
        setViewMode(QListView::IconMode);
        setIconSize(QSize(IconBarSize,IconBarSize));
    }
}

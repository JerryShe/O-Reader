#include "library.h"
#include "styles.h"

#include <QGridLayout>
#include <QPair>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QCoreApplication>

library::library(QWidget *widget)
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

library::~library()
{
    delete BookModel;
}

void library::showSelectedItem(QModelIndex mIndex)
{
   if (!mIndex.isValid())
      return;

   emit(showBookPage(mIndex.data(Qt::WhatsThisRole).toInt()));
}


void library::addItem(unsigned int BookIndex, QString name, QString title, QImage cover)
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


void library::changeViewMod()
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

QVector<unsigned int> library::deleteItems()
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

void library::deleteBook(unsigned int index)
{
    int i;
    for (i = 0; i < BookModel->rowCount(); i++)
        if (BookModel->item(i,0)->data(Qt::WhatsThisRole) == index)
            break;

    BookModel->removeRow(i);
}

int library::getSelectedItemsCount()
{
    return selectionModel()->selectedIndexes().size();
}

void library::clear()
{
    QStandardItemModel* temp = BookModel;
    BookModel = new QStandardItemModel(ListSize,ListSize);

    setModel(BookModel);
    itemCount = 0;
    temp->clear();
    delete temp;
}

void library::groupBy(QString mode)
{

}

void library::iconUpscale()
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

void library::iconDownscale()
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

void library::setSettingsData()
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

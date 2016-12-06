#include "library_layout.h"
#include "styles.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QPair>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>

librarylayout::librarylayout(QWidget *widget)
{
    libraryGridLayout = new QGridLayout(this);

    BookListView = new QListView();

    BookListView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
    BookListView->setResizeMode(QListView::Adjust);

    ListSize = 2;
    itemCount = 0;
    BookModel = new QStandardItemModel(ListSize,ListSize);
    BookListView->setModel(BookModel);

    IconBarSize = 140;
    IconListSize = 50;

    BookListView->setViewMode(QListView::IconMode);
    BookListView->setIconSize(QSize(IconBarSize,IconBarSize));
    BookListView->setGridSize(QSize(IconBarSize - 10,IconBarSize + 60));

    BookListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    BookListView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    BookListView->setDragDropMode(QAbstractItemView::NoDragDrop);

    QString ListViewStyle[1];
    setLibraryStyle (ListViewStyle, "Red");
    BookListView->setStyleSheet(ListViewStyle[0]);

    connect(BookListView, SIGNAL(doubleClicked(QModelIndex)), SLOT(showSelectedItem(QModelIndex)));

    librarylayout::setLayout(libraryGridLayout);
    libraryGridLayout->addWidget(BookListView, 0, 0);
    libraryGridLayout->setContentsMargins(20,20,0,0);
    BookListView->show();
}

librarylayout::~librarylayout()
{
    delete libraryGridLayout;
    delete BookListView;
    delete BookModel;
}

void librarylayout::showSelectedItem(QModelIndex mIndex)
{
   if (!mIndex.isValid())
      return;

   emit(showBookPage(mIndex.data(Qt::WhatsThisRole).toInt()));
}


void librarylayout::addItem(int BookIndex, QString name, QString title, QImage cover)
{
    BookModel->setRowCount(itemCount+1);

    QIcon coverIcon = QIcon(QPixmap::fromImage(cover));

    QModelIndex index = BookModel->index(itemCount++,0);
    BookModel->setData(index, name + '\n' + title, Qt::DisplayRole);
    BookModel->setData(index, name + '\n' + title, Qt::ToolTipRole);
    BookModel->setData(index, BookIndex, Qt::WhatsThisRole);
    BookModel->setData(index, coverIcon, Qt::DecorationRole);
}


void librarylayout::changeViewMod()
{
    if (BookListView->viewMode() == QListView::IconMode)
    {
        BookListView->setGridSize(QSize(IconListSize+5,IconListSize + 5));
        BookListView->setViewMode(QListView::ListMode);
        BookListView->setIconSize(QSize(IconListSize,IconListSize));
    }
    else
    {
        BookListView->setGridSize(QSize(IconBarSize - 10,IconBarSize + 60));
        BookListView->setViewMode(QListView::IconMode);
        BookListView->setIconSize(QSize(IconBarSize,IconBarSize));
    }
}

QVector <int> librarylayout::deleteItems()
{
    QVector <int> deletedItems;

    QModelIndexList SelectedItems = BookListView->selectionModel()->selectedIndexes();
    for (int i = 0; i < SelectedItems.size(); i++)
        deletedItems.push_back(SelectedItems.at(i).data(Qt::WhatsThisRole).toInt());

    while(SelectedItems.size())
    {
        BookModel->removeRow(SelectedItems.first().row());
        SelectedItems = BookListView->selectionModel()->selectedIndexes();
    }
    return deletedItems;
}

void librarylayout::sortBy(int mode)
{

}

void librarylayout::groupBy(int mode)
{

}

void librarylayout::findItems(QString str, int mode)
{

}

void librarylayout::iconUpscale()
{
    if (BookListView->viewMode() == QListView::IconMode)
    {
        if (IconBarSize < 260)
        {
            IconBarSize+=30;
            BookListView->setGridSize(QSize(IconBarSize - 10, IconBarSize + 60));
            BookListView->setIconSize(QSize(IconBarSize,IconBarSize));
        }
    }
    else
    {
        if (IconListSize < 200)
        {
            IconListSize+=10;
            BookListView->setGridSize(QSize(IconListSize + 5,IconListSize + 5));
            BookListView->setIconSize(QSize(IconListSize,IconListSize));
        }
    }
}

void librarylayout::iconDownscale()
{
    if (BookListView->viewMode() == QListView::IconMode)
    {
        if (IconBarSize > 110)
        {
            IconBarSize-=30;
            BookListView->setGridSize(QSize(IconBarSize - 10, IconBarSize + 60));
            BookListView->setIconSize(QSize(IconBarSize,IconBarSize));
        }
    }
    else
    {
        if (IconListSize > 30)
        {
            IconListSize-=10;
            BookListView->setGridSize(QSize(IconListSize + 5,IconListSize + 5));
            BookListView->setIconSize(QSize(IconListSize,IconListSize));
        }
    }
}

void librarylayout::setSettingsData()
{

}

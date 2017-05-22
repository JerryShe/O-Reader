#include "library_view.h"
#include "styles.h"

#include <QGridLayout>
#include <QPair>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QCoreApplication>


LibraryView::LibraryView(QWidget *widget)
{
    setParent(widget);

    setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
    setResizeMode(QListView::Adjust);

    setAttribute(Qt::WA_AcceptTouchEvents);

    BookModel = new LibraryModel(this);

    delegate = new LibraryListDelegate();
    setSettingsData();
    this->setItemDelegate(delegate);


    setModel(BookModel);

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
    delete delegate;
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
    this->reset();
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

    if (!BookModel->rowCount())
        clear();

    return deletedItems;
}


void LibraryView::deleteBook(const unsigned int &index)
{
    qDebug()<<"delete "<<index;
    BookModel->deleteBookByIndex(index);
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

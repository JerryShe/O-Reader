#include "reading_search_widget.h"
#include "ui_reading_search_widget.h"

#include "settings.h"
#include "styles.h"
#include "reading_search_results_delegate.h"

#include <QTouchDevice>
#include <QScroller>

#include <QDebug>


void ReadingSearchWidget::setStyle()
{
    QString styles[2];
    setExitButtonStyle(styles, Settings::getSettings()->getInterfaceStyle());
    ui->ExitButton->setStyleSheet(styles[0]);

    ui->ResultsView->setStyleSheet("QTreeView"
                                   "{background-color:rgb(150, 0, 60);"
                                   "color: white;"
                                   "font-size:16px;"
                                   "outline: 0px;"
                                   "border:none;}"

                                   " QTreeView::item:has-children:hover, QTreeView::item:has-children:selected"
                                   " {background-color:rgb(140, 0, 40);}"

                                   " QTreeView::item:!has-children"
                                   " {border: 4px solid white;"
                                   "margin-top:5px;"
                                   "margin-bottom:5px;"
                                   "min-height:30px;}"

                                   " QTreeView::item:!has-children:hover"
                                   "{border: 4px solid rgb(100,0,30);}"

                                   " QTreeView::item:!has-children:selected"
                                   "{border: 4px solid rgb(151,151,227);}"

                                   " QTreeView::item:!has-children:selected:hover"
                                   "{border: 4px solid rgb(130,130,195);}"

                                   "QTreeView::branch:has-children:closed{"
                                   "background-image: url(:/Images/LightArrowVertOpen.png);"
                                   "background-repeat: no-repeat;"
                                   "background-position: center center;}"

                                   "QTreeView::branch:has-children:open{"
                                   "background-repeat: no-repeat;"
                                   "background-position: center center;"
                                   "background-image: url(:/Images/LightArrowOpen.png)}");
}


ReadingSearchWidget::ReadingSearchWidget(QTreeWidgetItem* item, const long long &pos, const QString &styles, QWidget *parent):
    QWidget(parent),
    Contents(item),
    CurrentPos(pos),
    ui(new Ui::ReadingSearchWidget)

{
    qDebug()<<"create SearchWidget";
    ui->setupUi(this);

    connect(ui->ExitButton, SIGNAL(clicked(bool)), this, SIGNAL(searchClosed()));
    connect(ui->SearchKey, SIGNAL(returnPressed()), this, SLOT(on_StartSearch_clicked()));

    setStyle();  
    ResultsModel = 0;

    ReadingSearchResultsDelegate *delegate = new ReadingSearchResultsDelegate(this);
    delegate->setTextStyles(styles);
    ui->ResultsView->setItemDelegate(delegate);

    if (QTouchDevice::devices().size())
    {
        QScroller::grabGesture(ui->ResultsView->viewport(), QScroller::LeftMouseButtonGesture);
        ui->ResultsView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    }

    connect(ui->ResultsView, &QTreeView::doubleClicked, [this](const QModelIndex &index){
        qDebug()<<index.data(Qt::UserRole + 2).toString();
    });

    ui->SearchKey->setFocus();
}


ReadingSearchWidget::~ReadingSearchWidget()
{
    qDebug()<<"delete SearchWidget";
    delete ui;
}


void ReadingSearchWidget::runSearch(const QString &searchKey)
{
    ui->SearchKey->setText(searchKey);
    ui->SearchType->setCurrentIndex(2);
    on_StartSearch_clicked();
}


void ReadingSearchWidget::clearResults()
{
    if (ResultsModel != 0)
    {
        ResultsModel->clear();
        delete ResultsModel;
    }

    ResultsModel = new QStandardItemModel(this);
    ResultsRoot = ResultsModel->invisibleRootItem();
    ResultsRoot->setData(QVariant(0), Qt::UserRole);

    ui->ResultsView->setModel(ResultsModel);

    TreeElems.clear();
    TreeElems.insert(0, ResultsRoot);

    CurSearchResult = 0;

    ui->ResultsCount->clear();
}


void ReadingSearchWidget::setSearchResults(const QVector<BookNote> results)
{    
    if (results.size() == 0)
    {
        ui->ResultsCount->setText("Nothing found");
        return;
    }

    SearchResults = results;
    ui->ResultsCount->setText(QString::number(SearchResults.size()));

    lastStepContentsItem = Contents;
    createResultsTree(Contents);
    if(CurSearchResult != SearchResults.size())
        addResultsToLast();

    showCurrentResult();
}


void ReadingSearchWidget::createResultsTree(QTreeWidgetItem *item)
{
    if(CurSearchResult >= SearchResults.size())
        return;

    if (SearchResults[CurSearchResult].TextPos <= item->whatsThis(0).toLongLong())
    {
        addResultToTree(lastStepContentsItem);
        CurSearchResult++;
        createResultsTree(item);
    }
    else
    {
        lastStepContentsItem = item;
        for (int i = 0; i < item->childCount(); i++)
            createResultsTree(item->child(i));
    }
}


void ReadingSearchWidget::addResultsToLast()
{
    for (;CurSearchResult < SearchResults.size(); CurSearchResult++)
         addResultToTree(lastStepContentsItem);
}


void ReadingSearchWidget::addResultToTree(const QTreeWidgetItem* item)
{
    if (!TreeElems.contains(item->whatsThis(0).toLongLong()))
        addBranchFor(item);

    QStandardItem* newItem = new QStandardItem();

    newItem->setData(QVariant(1), Qt::UserRole);
    newItem->setData(QVariant(SearchResults[CurSearchResult].Note), Qt::UserRole + 2);
    newItem->setData(QVariant(CurSearchResult), Qt::UserRole + 1);

    TreeElems[item->whatsThis(0).toLongLong()]->appendRow(newItem);
}


void ReadingSearchWidget::addBranchFor(const QTreeWidgetItem* item)
{
    if (!TreeElems.contains(item->parent()->whatsThis(0).toLongLong()))
        addBranchFor(item->parent());

    QStandardItem* newItem = new QStandardItem(item->text(0));
    newItem->setData(QVariant(0), Qt::UserRole);
    TreeElems.insert(item->whatsThis(0).toLongLong(), newItem);
    TreeElems[item->parent()->whatsThis(0).toLongLong()]->appendRow(newItem);
}


void ReadingSearchWidget::showCurrentResult()
{
    QStandardItem* item = ResultsRoot;

    switch (ui->SearchType->currentIndex()) {
    case 0:
    {
        while(item->hasChildren())
            item = item->child(0,0);
        break;
    }
    case 1:
    {
        while (item->hasChildren())
            item = item->child(item->rowCount() - 1, 0);
        break;
    }
    case 2:
    {
        long long lastKey = 0;

        for (int i = 0;i < TreeElems.size(); i++)
            if (TreeElems.keys()[i] <= CurrentPos && TreeElems.keys()[i] > lastKey)
                lastKey = TreeElems.keys()[i];

        QStandardItem* rootItem = TreeElems[lastKey];
        for (int i = 0; i < rootItem->rowCount(); i++)
            if (SearchResults[rootItem->child(i, 0)->data(Qt::UserRole + 1).toLongLong()].TextPos > CurrentPos)
            {
                item = rootItem->child(i, 0);
                break;
            }

        break;
    }
    default:
        return;
    }

    ui->ResultsView->collapseAll();

    //lol-bug
    ui->ResultsView->scrollTo(item->index(), QAbstractItemView::EnsureVisible);
    ui->ResultsView->scrollTo(item->index(), QAbstractItemView::EnsureVisible);

    ui->ResultsView->selectionModel()->select(item->index(), QItemSelectionModel::SelectCurrent);
}


void ReadingSearchWidget::on_StartSearch_clicked()
{
    if (!ui->SearchKey->text().isEmpty())
    {
        clearResults();
        emit startSearch(ui->SearchKey->text(), ui->CaseSensitive->isChecked(), ui->Punctuation->isChecked(), ui->PreviewSize->value());
        connect(ui->SearchType, SIGNAL(activated(int)), this, SLOT(showCurrentResult()));
    }
}


void ReadingSearchWidget::on_GoToSelected_clicked()
{
    if (ui->ResultsView->selectionModel() != 0)
        if (ui->ResultsView->selectionModel()->selectedIndexes().size() != 0)
            if (ui->ResultsView->selectionModel()->selectedIndexes().first().data(Qt::UserRole).toInt() == 1)
            {
                emit goTo(SearchResults[ui->ResultsView->selectionModel()->selectedIndexes().first().data(Qt::UserRole + 1).toInt()]);
                emit searchClosed();
            }
}


void ReadingSearchWidget::on_Expand_clicked()
{
    ui->ResultsView->expandAll();
}


void ReadingSearchWidget::on_Collapse_clicked()
{
    ui->ResultsView->collapseAll();
}

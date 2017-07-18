#ifndef READING_SEARCH_WIDGET_H
#define READING_SEARCH_WIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTextDocument>

#include "books.h"


namespace Ui {
class ReadingSearchWidget;
}

class ReadingSearchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReadingSearchWidget(QTreeWidgetItem* item, const long long &pos, const QString &Styles, QWidget *parent = 0);
    ~ReadingSearchWidget();

public slots:
    void setSearchResults(const QVector<BookNote> results);

signals:
    void goTo(BookPosition pos);
    void startSearch(const QString &token, const bool &caseSensitivity, const bool &punctuation);
    void searchClosed();

private slots:
    void createResultsTree(QTreeWidgetItem *item);
    void addResultToTree(const QTreeWidgetItem* item);
    void addResultsToLast();
    void addBranchFor(const QTreeWidgetItem* item);

    void on_StartSearch_clicked();
    void on_GoToSelected_clicked();

    void clearResults();

    void setStyle();


    void on_Expand_clicked();

    void on_Collapse_clicked();

private:
    QTreeWidgetItem *Contents;
    QTreeWidgetItem *lastStepContentsItem;

    QStandardItemModel *ResultsModel;
    QStandardItem* ResultsRoot;

    QVector<BookNote> SearchResults;
    int CurSearchResult;
    QHash <long long, QStandardItem*> TreeElems;

    long long CurrentPos;

    Ui::ReadingSearchWidget *ui;
};

#endif // READING_SEARCH_WIDGET_H

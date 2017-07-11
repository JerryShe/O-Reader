#ifndef READING_SEARCH_WIDGET_H
#define READING_SEARCH_WIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "books.h"

namespace Ui {
class ReadingSearchWidget;
}

class ReadingSearchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReadingSearchWidget(QWidget *parent = 0);
    ~ReadingSearchWidget();

public slots:
    void setBookData(QTreeWidgetItem* item, const long long &pos);
    void setSearchResult(const QVector<QPair<BookPosition, QString>> &results);

signals:
    void goTo(BookPosition pos);
    void startSearch(const QString &token, const QString &searchType);
    void searchClosed();

private slots:
    void on_StartSearch_clicked();

private:
    void setStyle();

    QTreeWidgetItem *Contents;
    QVector<QPair<BookPosition, QString>> SearchResults;
    long long CurrentPos;

    Ui::ReadingSearchWidget *ui;
};

#endif // READING_SEARCH_WIDGET_H

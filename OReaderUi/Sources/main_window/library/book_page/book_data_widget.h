#ifndef BOOK_DATA_WIDGET_H
#define BOOK_DATA_WIDGET_H

#include <QWidget>

#include "book.h"

namespace Ui {
class BookDataWidget;
}

class BookDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BookDataWidget(QWidget *parent = 0);
    ~BookDataWidget();

    void setBook(Book* openedBook);
    void resetData();

signals:
    void showBookPage();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_CloseData_clicked();

    void on_ChangeCover_clicked();

    void on_EditData_clicked();

private:
    Ui::BookDataWidget *ui;

    Book* book;
};

#endif // BOOK_DATA_WIDGET_H

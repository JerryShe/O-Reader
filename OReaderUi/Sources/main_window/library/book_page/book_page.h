#ifndef BOOK_PAGE_H
#define BOOK_PAGE_H

#include <QMainWindow>

#include "book.h"

namespace Ui {
class BookPage;
}

class BookPage : public QWidget
{
    Q_OBJECT

public:
    explicit BookPage(QWidget *parent = 0);
    ~BookPage();

    void setBook(Book* showingBook);
    void resetData();

private slots:
    void on_startReading_clicked();
    void on_deleteBook_clicked();

    void showBookPage();

    void on_ShowIllustrations_clicked();

    void on_ShowBookData_clicked();

signals:
    void startReading(QString index);
    void deleteBook(QString index);
    void closeBookPage();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    void setStyle(QString Style);

    Ui::BookPage *ui;

    Book* book;

    int curImage;
};

#endif // BOOK_PAGE_H

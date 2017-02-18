#ifndef BOOK_PAGE_H
#define BOOK_PAGE_H

#include <QMainWindow>
#include "books.h"

namespace Ui {
class BookPage;
}

class BookPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit BookPage(Book *book, const QString &Style, QWidget *parent = 0);
    ~BookPage();
    void readBook();

private slots:
    void on_startReading_clicked();
    void on_deleteBook_clicked();

signals:
    void startReading(unsigned int index);
    void deleteBook(unsigned int index);

private:
    void setStyle(QString Style);
    Ui::BookPage *ui;
    unsigned int BookIndex;
    QString style;
};

#endif // BOOK_PAGE_H

#ifndef BOOK_PAGE_H
#define BOOK_PAGE_H

#include <QMainWindow>
#include <books.h>

namespace Ui {
class BookPage;
}

class BookPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit BookPage(Book book, QString Style, QWidget *parent = 0);
    ~BookPage();
    void readBook();

private slots:
    void on_exit_button_clicked();

private:
    void setStyle(QString Style);
    Ui::BookPage *ui;
};

#endif // BOOK_PAGE_H

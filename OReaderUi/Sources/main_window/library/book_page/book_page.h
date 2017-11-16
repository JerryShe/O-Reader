#ifndef BOOK_PAGE_H
#define BOOK_PAGE_H

#include <QMainWindow>

#include "book.h"

namespace Ui {
class BookPage;
}

class BookPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit BookPage(Book *boo, QWidget *parent = 0);
    ~BookPage();
    void readBook();

private slots:
    void on_startReading_clicked();
    void on_deleteBook_clicked();

    void on_ShowIllustrations_clicked();
    void on_PrevIllustration_clicked();
    void on_CloseIllustrations_clicked();
    void on_NextIllustration_clicked();

signals:
    void startReading(QString index);
    void deleteBook(QString index);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    void setStyle(QString Style);

    void showIllustrationAt(const int i);

    Ui::BookPage *ui;

    Book* book;
    QVector <QImage> images;

    int curImage;
};

#endif // BOOK_PAGE_H

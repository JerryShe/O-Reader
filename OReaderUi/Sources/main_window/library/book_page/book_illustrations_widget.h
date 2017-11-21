#ifndef BOOK_ILLUSTRATIONS_WIDGET_H
#define BOOK_ILLUSTRATIONS_WIDGET_H

#include <QWidget>
#include <QImage>

#include "book.h"
#include "book_image_table.h"


namespace Ui {
class BookIllustrationsWidget;
}

class BookIllustrationsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BookIllustrationsWidget(QWidget *parent = 0);
    ~BookIllustrationsWidget();

    void setBook(Book* book);
    bool imagesLoaded() const;

    void resetData();

signals:
    void showBookPage();

private slots:
    void on_PrevIllustration_clicked();
    void on_NextIllustration_clicked();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    void showIllustrationAt(const int i);


    Ui::BookIllustrationsWidget *ui;

    QVector <QImage> images;
    int curImage;
};

#endif // BOOK_ILLUSTRATIONS_WIDGET_H

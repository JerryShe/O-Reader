#ifndef BOOK_WIDGET_H
#define BOOK_WIDGET_H

#include <QWidget>
#include <books.h>


#include <QState>

namespace Ui {
class BookWidget;
}

class BookWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BookWidget(QWidget *parent = 0);
    ~BookWidget();

private slots:
    void on_ShowButton_clicked();
    void on_ReadButton_clicked();
    void on_PageButton_clicked();

    void hideWidget();
    void showWidget();

    void setStyle();

signals:
    void showBookPage(unsigned int index);
    void startReading(unsigned int index);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    Ui::BookWidget *ui;

    QState *s1;
    QState *s2;

    unsigned int BookIndex;
    QPixmap Cover;
};

#endif // BOOK_WIDGET_H

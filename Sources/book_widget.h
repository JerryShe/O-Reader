#ifndef BOOK_WIDGET_H
#define BOOK_WIDGET_H

#include <QWidget>
#include <books.h>

#include <QStateMachine>
#include <QPropertyAnimation>
#include <QSignalTransition>

namespace Ui {
class BookWidget;
}

class BookWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BookWidget(QWidget *parent = 0);
    ~BookWidget();

public slots:
    void hideWidget();
    void showWidget();

private slots:
    void on_ReadButton_clicked();
    void on_PageButton_clicked();

    void setStyle();

signals:
    void showBookPage(unsigned int index);
    void startReading(unsigned int index);

    void showButtonClicked();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    Ui::BookWidget *ui;

    unsigned int BookIndex;
    QPixmap Cover;

    QStateMachine *machine;
    QPropertyAnimation *animation;
    QState *s1;
    QState *s2;

    QSignalTransition *transition1;
    QSignalTransition *transition2;
};

#endif // BOOK_WIDGET_H

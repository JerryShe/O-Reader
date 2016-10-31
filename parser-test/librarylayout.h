#ifndef LIBRARYLAYOUT_H
#define LIBRARYLAYOUT_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>

class librarylayout : public QWidget
{
    Q_OBJECT
public:
    explicit librarylayout(QWidget *widget);
    void addWidget(QWidget* widget);
private:

    void setColumnsAndMargins();

    QGridLayout* gridLayout;
    int row;
    int column;
    int max_columns;
    int windowSize;

    QScrollArea* scrollArea;
    QWidget *content = NULL;
};

#endif // LIBRARYLAYOUT_H

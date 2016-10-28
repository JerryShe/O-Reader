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
    explicit librarylayout(QWidget *parent = 0);
    void addWidget(QWidget* widget);
private:
    QVBoxLayout* baseLayout;
    QVector<QHBoxLayout*> layoutInNow;
    bool needNewLayout;
    QGridLayout* layout;
    int row;
    int column;
    QScrollArea* area;
};

#endif // LIBRARYLAYOUT_H

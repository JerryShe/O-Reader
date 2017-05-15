#ifndef LIBRARY_H
#define LIBRARY_H


#include <QGridLayout>
#include <QListView>
#include <QStandardItemModel>

#include "settings.h"
#include "books.h"


class Library : public QListView
{
    Q_OBJECT

public:
    Library(QWidget *widget = 0);
    ~Library();

    void addItem(Book *book);
    QVector <unsigned int> deleteItems();
    void deleteBook(const unsigned int &index);
    void setSettingsData();

    void changeViewMod();
    void iconUpscale();
    void iconDownscale();

    int getSelectedItemsCount();

    void clear();
    void groupBy(const QString &mode);

signals:
    void showBookPage(unsigned int index);

private slots:
    void showSelectedItem(const QModelIndex &mIndex);

private:
     QStandardItemModel* BookModel;

    Settings* ProgramSettings;

    unsigned short IconBarSize;
    unsigned short IconListSize;
    int ListSize;
    int itemCount;
};

#endif // LIBRARY_H

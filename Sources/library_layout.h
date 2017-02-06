#ifndef LIBRARYLAYOUT_H
#define LIBRARYLAYOUT_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QListView>
#include <QStandardItemModel>
#include "settings.h"



class librarylayout : public QWidget
{
    Q_OBJECT

public:
    librarylayout(QWidget *widget = 0);
    ~librarylayout();

    void addItem(int BookIndex, QString name, QString title, QImage cover);
    QVector <int> deleteItems();
    void deleteBook(int index);
    void setSettingsData();

    void setStyle(QString libraryStyle[]);
    void changeViewMod();
    void iconUpscale();
    void iconDownscale();

    int getSelectedItemsCount();

    void clear();
    void groupBy(QString mode);

signals:
    void showBookPage(int index);

private slots:
    void showSelectedItem(QModelIndex mIndex);

private:
    QGridLayout* libraryGridLayout;
    QListView* BookListView;
    QStandardItemModel* BookModel;

    settings* ProgramSettings;

    unsigned short IconBarSize;
    unsigned short IconListSize;
    int ListSize;
    int itemCount;
};

#endif // LIBRARYLAYOUT_H

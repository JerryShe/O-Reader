#ifndef LIBRARY_H
#define LIBRARY_H


#include <QGridLayout>
#include <QListView>
#include <QStandardItemModel>
#include "settings.h"



class library : public QListView
{
    Q_OBJECT

public:
    library(QWidget *widget = 0);
    ~library();

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
     QStandardItemModel* BookModel;

    settings* ProgramSettings;

    unsigned short IconBarSize;
    unsigned short IconListSize;
    int ListSize;
    int itemCount;
};

#endif // LIBRARY_H

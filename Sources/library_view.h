#ifndef LIBRARY_VIEW_H
#define LIBRARY_VIEW_H


#include <QGridLayout>
#include <QListView>
#include <QStandardItemModel>

#include "settings.h"
#include "books.h"
#include "library_model.h"



class LibraryView : public QListView
{
    Q_OBJECT

public:
    LibraryView(QWidget *widget = 0);
    ~LibraryView();

    void addItem(Book *book);
    QVector <unsigned int> deleteSelectedItems();
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
    LibraryModel* BookModel;
    LibraryListDelegate* delegate;

    Settings* ProgramSettings;

    unsigned short IconBarSize;
    unsigned short IconListSize;
};

#endif // LIBRARY_VIEW_H

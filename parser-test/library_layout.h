#ifndef LIBRARYLAYOUT_H
#define LIBRARYLAYOUT_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QMainWindow>
#include <QListView>
#include <QStandardItemModel>



class librarylayout : public QWidget
{
    Q_OBJECT

public:
    explicit librarylayout(QWidget *Parent=0);
    ~librarylayout();

    void addItem(int BookIndex, QString name, QString title, QImage cover);
    QVector <int> deleteItems();
    void setSettingsData();

    void setStyle(QString libraryStyle[]);
    void changeViewMod();
    void iconUpscale();
    void iconDownscale();

    void sortBy(int mode);
    void groupBy(int mode);
    void findItems(QString str, int mode);

signals:
    void showBookPage(int index);

private slots:
    void showSelectedItem(QModelIndex mIndex);

private:
    QGridLayout *libraryGridLayout;

    QListView *BookListView;
    QStandardItemModel *BookModel;

    int IconBarSize;
    int IconListSize;
    int ListSize;
    int itemCount;
};

#endif // LIBRARYLAYOUT_H

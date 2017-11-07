#ifndef LIBRARY_LIST_DELEGATE_H
#define LIBRARY_LIST_DELEGATE_H

#include <QStyledItemDelegate>


class LibraryListDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit LibraryListDelegate(QObject* parent = 0);
    ~LibraryListDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index ) const;

    void setListViewMode(const bool flag);
    bool listViewMode() const;

private:
    void paintListViewItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index, const QRect &rect) const;
    void paintIconViewItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index, const QRect &rect) const;

    void drawBookStatus(const QPoint &pos, const double &progress, QPainter *painter) const;


    QFont font;
    QFontMetrics* fm;
    bool viewMode;      //0 - icon, 1 - list
};

#endif // LIBRARY_LIST_DELEGATE_H

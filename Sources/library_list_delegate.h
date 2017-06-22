#ifndef LIBRARY_LIST_DELEGATE_H
#define LIBRARY_LIST_DELEGATE_H

#include <QStyledItemDelegate>


class LibraryListDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    LibraryListDelegate(QObject* parent = 0);
    ~LibraryListDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index ) const;


    void setListViewMode(const bool flag);
    bool listViewMode() const;

    void setItemsColors(const QColor &norm, const QColor &sel, const QColor &hov, const QColor &hovSel);

private:
    void paintListViewItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index, const QRect &rect) const;
    void paintIconViewItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index, const QRect &rect) const;

    void drawBookStatus(const QPoint &pos, const double &progress, QPainter *painter) const;

    void drawBackground(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect) const;


    QFont font;
    QFontMetrics* fm;
    bool viewMode;      //0 - icon, 1 - list

    QColor normal;
    QColor selected;
    QColor hover;
    QColor hoverSelected;
};

#endif // LIBRARY_LIST_DELEGATE_H

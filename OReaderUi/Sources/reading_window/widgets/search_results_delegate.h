#ifndef SEARCH_RESULTS_DELEGATE_H
#define SEARCH_RESULTS_DELEGATE_H

#include <QStyledItemDelegate>
#include <QTextDocument>

#include "data_handlers/settings_handler.h"

class SearchResultsDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit SearchResultsDelegate(QObject *parent = 0);
    ~SearchResultsDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index ) const;

    void setTextStyles(const QString &styles);

private:
    void drawTextBackground(QPainter *painter, const QStyleOptionViewItem &option) const;

    bool textBackgroundType;
    QString textBackground;
    QImage* textBackgroundImage;

    QTextDocument *ResultPreview;
    QString TextStyles;

};

#endif // SEARCH_RESULTS_DELEGATE_H

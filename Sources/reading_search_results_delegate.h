#ifndef READING_SEARCH_RESULTS_DELEGATE_H
#define READING_SEARCH_RESULTS_DELEGATE_H

#include <QStyledItemDelegate>
#include <QTextDocument>

#include "settings.h"

class ReadingSearchResultsDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ReadingSearchResultsDelegate(QObject *parent = 0);
    ~ReadingSearchResultsDelegate();

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

#endif // READING_SEARCH_RESULTS_DELEGATE_H

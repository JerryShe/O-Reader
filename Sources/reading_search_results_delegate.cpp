#include "reading_search_results_delegate.h"

#include <QPainter>
#include <QAbstractTextDocumentLayout>
#include <QApplication>
#include <QLabel>

#include <QDebug>

ReadingSearchResultsDelegate::ReadingSearchResultsDelegate(QObject *parent): QStyledItemDelegate(parent)
{
    ResultPreview = new QTextDocument(this);
    ResultPreview->setDocumentMargin(9);

    textBackgroundType = Settings::getSettings()->getCurrentReadProfile().BackgroundType;
    textBackground = Settings::getSettings()->getCurrentReadProfile().BackgroundImage;

    if (!textBackgroundType)
        textBackgroundImage = new QImage(textBackground);
}


ReadingSearchResultsDelegate::~ReadingSearchResultsDelegate()
{
    if (!textBackgroundType)
        delete textBackgroundImage;
}


void ReadingSearchResultsDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if (index.data(Qt::UserRole).toInt() == 1)
    {
        ResultPreview->setTextWidth(option.rect.width());
        ResultPreview->setHtml(TextStyles + "<body>" + index.data(Qt::UserRole + 2).toString() + "<body>");

        QAbstractTextDocumentLayout::PaintContext context;
        context.palette = option.palette;

        painter->save();

        QStyledItemDelegate::paint(painter, option, index);
        drawTextBackground(painter, option);

        QAbstractTextDocumentLayout* layout = ResultPreview->documentLayout();
        painter->translate(option.rect.x(), option.rect.y() + 5);
        layout->draw(painter, context);

        painter->restore();
    }
    else if (index.data(Qt::UserRole).toInt() == 0)
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
}


void ReadingSearchResultsDelegate::drawTextBackground(QPainter *painter, const QStyleOptionViewItem &option) const
{
    QRect textRect = option.rect;
    textRect.setTopLeft(textRect.topLeft() + QPoint(4,9));
    textRect.setBottomRight(textRect.bottomRight() - QPoint(4,9));

    if (textBackgroundType)
    {
        painter->fillRect(textRect, QColor(textBackground));
    }
    else
    {
        QRect imageRect = textRect;
        imageRect.moveTo(0,0);
        painter->drawImage(textRect, *textBackgroundImage, imageRect);
    }
}


QSize ReadingSearchResultsDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    if (index.data(Qt::UserRole).toInt() == 0)
        return QStyledItemDelegate::sizeHint(option, index);

    ResultPreview->setTextWidth(1000);
    ResultPreview->setHtml(TextStyles + "<body>" + index.data(Qt::UserRole + 2).toString() + "<body>");
    return ResultPreview->size().toSize();
}


void ReadingSearchResultsDelegate::setTextStyles(const QString &styles)
{
    TextStyles = styles;
}

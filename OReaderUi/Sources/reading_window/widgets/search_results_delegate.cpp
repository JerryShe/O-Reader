#include "reading_window/widgets/search_results_delegate.h"

#include <QPainter>
#include <QAbstractTextDocumentLayout>
#include <QApplication>
#include <QLabel>

#include <QDebug>

SearchResultsDelegate::SearchResultsDelegate(QObject *parent): QStyledItemDelegate(parent)
{
    ResultPreview = new QTextDocument(this);
    ResultPreview->setDocumentMargin(9);

    textBackgroundType = SettingsHandler::getSettings()->getCurrentReadProfile().BackgroundType;
    textBackground = SettingsHandler::getSettings()->getCurrentReadProfile().BackgroundImage;

    if (!textBackgroundType)
        textBackgroundImage = new QImage(textBackground);
}


SearchResultsDelegate::~SearchResultsDelegate()
{
    if (!textBackgroundType)
        delete textBackgroundImage;
}


void SearchResultsDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if (index.data(Qt::UserRole).toInt() == 1)
    {
        ResultPreview->setTextWidth(option.rect.width());
        ResultPreview->setHtml(TextStyles + index.data(Qt::UserRole + 2).toString());

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


void SearchResultsDelegate::drawTextBackground(QPainter *painter, const QStyleOptionViewItem &option) const
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


QSize SearchResultsDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    if (index.data(Qt::UserRole).toInt() == 0)
        return QStyledItemDelegate::sizeHint(option, index);

    ResultPreview->setTextWidth(1000);
    ResultPreview->setHtml(TextStyles + index.data(Qt::UserRole + 2).toString());
    return ResultPreview->size().toSize() + QSize(4,13);
}


void SearchResultsDelegate::setTextStyles(const QString &styles)
{
    TextStyles = styles;
}

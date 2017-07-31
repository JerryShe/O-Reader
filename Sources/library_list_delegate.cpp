#include "library_list_delegate.h"

#include <QApplication>
#include <QPainter>
#include <QBrush>
#include <QPalette>
#include <QVariant>

#include "library_list_model.h"


#include <QDebug>



LibraryListDelegate::LibraryListDelegate(QObject* parent) : QStyledItemDelegate(parent)
{
    font = qApp->font();
    font.setPixelSize(12);
    font.setBold(true);
    fm = new QFontMetrics(font);

    viewMode = false;
    qDebug()<<"create delegate";
}


LibraryListDelegate::~LibraryListDelegate()
{
    qDebug()<<"delete LibraryDelegate";
    delete fm;
}


void LibraryListDelegate::setListViewMode(const bool flag)
{
    viewMode = flag;
}


bool LibraryListDelegate::listViewMode() const
{
    return viewMode;
}


void LibraryListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    //painter->setRenderHints(QPainter::Antialiasing| QPainter::TextAntialiasing);

    QRect rect = option.rect;
    rect.setHeight(option.decorationSize.height());

    //TODO: костыль или не костыль, вот в чем вопрос...
    QStyledItemDelegate::paint(painter, option, index);


    if (!viewMode)
        paintIconViewItem(painter, option, index, rect);
    else
        paintListViewItem(painter, option, index, rect);

    painter->restore();
}


void LibraryListDelegate::paintListViewItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index, const QRect &rect) const
{
    QPixmap BookCover = qvariant_cast<QPixmap>(index.data(BookInf::CoverImage));
    QString AuthorName = qvariant_cast<QString>(index.data(BookInf::AuthorName));
    QString Title = qvariant_cast<QString>(index.data(BookInf::Title));

    if (!BookCover.isNull())
    {
        BookCover = BookCover.scaled(option.decorationSize.width() - 10, rect.height() - 10, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter->drawPixmap(rect.x() + 5 + (option.decorationSize.width() - BookCover.width())/2, rect.y() + (option.decorationSize.height() - BookCover.height())/2, BookCover);
    }

    QRect authorRect = rect;
    authorRect.setLeft(rect.x() + option.decorationSize.width() + 5);
    authorRect.setBottom(rect.y() + rect.height()/2 - 5);

    QRect titleRect = rect;
    titleRect.setLeft(rect.x() + option.decorationSize.width() + 5);
    titleRect.setTop(rect.y() + rect.height()/2 + 5);


    painter->setFont(font);
    painter->drawText(authorRect, Qt::AlignBottom	 | Qt::AlignLeft, AuthorName);
    painter->drawText(titleRect, Qt::AlignLeft | Qt::AlignTop, Title);

    QPoint progressPos(rect.x() + 5 + (option.decorationSize.width() + BookCover.width())/2, rect.y() + (rect.height() - BookCover.height())/2);
    drawBookStatus(progressPos, qvariant_cast<double>(index.data(BookInf::Progress)), painter);
}


void LibraryListDelegate::paintIconViewItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index, const QRect &rect) const
{
    QPixmap BookCover = qvariant_cast<QPixmap>(index.data(BookInf::CoverImage));
    QString AuthorName = qvariant_cast<QString>(index.data(BookInf::AuthorName));
    QString Title = qvariant_cast<QString>(index.data(BookInf::Title));

    if (!BookCover.isNull())
    {
        BookCover = BookCover.scaled(rect.width() - 10, rect.height() - (fm->height())*2 - 25, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter->drawPixmap(rect.x() + (rect.width() - BookCover.width())/2 , rect.y()+5, BookCover);
    }

    AuthorName = fm->elidedText(AuthorName, Qt::ElideRight, rect.width() - 10);
    Title = fm->elidedText(Title, Qt::ElideRight, rect.width() - 10);

    QRect titleRect = rect;
    titleRect.setBottom(titleRect.bottom() - 10);
    titleRect.setTop(titleRect.bottom() - fm->height());

    QRect authorRect = rect;
    authorRect.setBottom(titleRect.top() - 5);
    authorRect.setTop(authorRect.bottom() - fm->height());


    painter->setFont(font);
    painter->drawText(authorRect, Qt::AlignHCenter, AuthorName);
    painter->drawText(titleRect, Qt::AlignHCenter, Title);

    QPoint progressPos(rect.x() + (rect.width() + BookCover.width())/2, rect.y() + 5);
    drawBookStatus(progressPos, qvariant_cast<double>(index.data(BookInf::Progress)), painter);
}


void LibraryListDelegate::drawBookStatus(const QPoint &pos, const double &progress, QPainter *painter) const
{
    if (pos.x() == 0)
        return;


    double a = 0, b = 0;

    if (progress <= 50)
        a = 1 - (progress/50.0);
    else
        b = (progress/50.0) - 1;

    if (progress < 0 || progress > 100)
        a = b = 0;


    QColor color = QColor::fromRgb(200*a, 200*b, 200 - 200*(b+a));
    painter->setBrush(QBrush(color, Qt::SolidPattern));
    QColor penColor(0,0,0,0);
    painter->setPen(penColor);
    painter->drawRect(pos.x() - 5, pos.y() - 5, 10, 10);
}


QSize LibraryListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    return(QSize(option.rect.width(), option.decorationSize.height()));
}

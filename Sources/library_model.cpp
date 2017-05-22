#include "library_model.h"
#include <QPainter>
#include <QApplication>
#include <QVariant>
#include <QBrush>
#include <QPalette>

#include <QDebug>


BookData::BookData(Book* book)
{
    cover = QVariant(QPixmap::fromImage(book->getCover()));
    author = QVariant(book->getAuthorName());
    title = QVariant(book->getTitle());
    index = QVariant(book->getIndex());
    progress = QVariant(book->getProgressProcent());
}


BookData::BookData()
{

}


LibraryModel::LibraryModel(QObject* parent = 0) : QAbstractListModel(parent)
{}


LibraryModel::LibraryModel(QVector<Book> &bookList, QObject *parent) : QAbstractListModel(parent)
{
    for (int i = 0; i < bookList.size(); i++)
        addBook(&bookList[i]);
}


LibraryModel::~LibraryModel()
{
    qDebug()<<"delete LibraryModel";
    bookVector.clear();
}


QVariant LibraryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role)
    {
    case BookInf::Index:
        return bookVector[index.row()].index;
    case BookInf::CoverImage:
        return bookVector[index.row()].cover;
    case BookInf::AuthorName:
        return bookVector[index.row()].author;
    case BookInf::Title:
        return bookVector[index.row()].title;
    case BookInf::Progress:
        return bookVector[index.row()].progress;

    default:
        return QVariant();
    }
}


bool LibraryModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid())
    {
        if (role == Qt::DisplayRole)
            return true;
    }
    return false;
}


int LibraryModel::rowCount(const QModelIndex &parent) const
{
    return bookVector.size();
}


int LibraryModel::rowCount() const
{
    return bookVector.size();
}


void LibraryModel::removeRow(int row)
{
    if (row >= 0 && row < bookVector.size())
        bookVector.removeAt(row);
}


QVariant LibraryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
        return QVariant();
}


Qt::ItemFlags LibraryModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractListModel::flags(index);
    return index.isValid() ?
                (flags | Qt::ItemIsEditable) :
                flags;
}


void LibraryModel::addBook(Book* book)
{
    bookVector.prepend(BookData(book));
}


void LibraryModel::deleteBookByIndex(const unsigned int &index)
{
    for (int i = 0; i < bookVector.size(); i++)
        if (bookVector[i].index.toUInt()== index)
        {
            bookVector.removeAt(i);
            break;
        }
}


void LibraryModel::deleteBooksByIndexes(const QVector<unsigned int> &indexes)
{
    for (int i = 0; i < indexes.size(); i++)
        deleteBookByIndex(indexes[i]);
}


void LibraryModel::clear()
{
    bookVector.clear();
}






LibraryListDelegate::LibraryListDelegate()
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


void LibraryListDelegate::setItemsColors(const QColor &norm, const QColor &sel, const QColor &hov, const QColor &hovSel)
{
    normal = norm;
    selected = sel;
    hover = hov;
    hoverSelected = hovSel;
}


void LibraryListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    QRect rect = option.rect;
    rect.setHeight(option.decorationSize.height());

    drawBackground(painter, option, rect);

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
    drawBookStatus(progressPos, qvariant_cast<double>(index.data(BookInf::Progress)), painter, rect);
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
    drawBookStatus(progressPos, qvariant_cast<double>(index.data(BookInf::Progress)), painter, rect);
}


void LibraryListDelegate::drawBookStatus(const QPoint &pos, const double &progress, QPainter *painter, const QRect &rect) const
{
    if (pos.x() == 0)
        return;

    double a = 0, b = 0;

    if (progress <= 50)
        a = 1 - (progress/50.0);
    else
        b = (progress/50.0) - 1;


    QColor color = QColor::fromRgb(200*a, 200*b, 200 - 200*(b+a));
    painter->setBrush(QBrush(color, Qt::SolidPattern));
    QColor penColor(0,0,0);
    painter->setPen(penColor);
    painter->drawEllipse(pos.x() - 5, pos.y() - 5, 10, 10);
}


void LibraryListDelegate::drawBackground(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect) const
{
    if (option.state & QStyle::State_MouseOver)
    {
        if (option.state & QStyle::State_Selected)
            painter->fillRect(rect, QBrush(hoverSelected));
        else
            painter->fillRect(rect, QBrush(hover));
    }
    else if (option.state & QStyle::State_Selected)
        painter->fillRect(rect, QBrush(selected));
}


QSize LibraryListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    return(option.rect.size());
}


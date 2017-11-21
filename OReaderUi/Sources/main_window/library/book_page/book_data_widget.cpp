#include "book_data_widget.h"
#include "ui_book_data_widget.h"

#include <QKeyEvent>
#include <QFileDialog>
#include <QImageReader>

BookDataWidget::BookDataWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookDataWidget)
{
    ui->setupUi(this);

    this->installEventFilter(this);
    this->setFocusPolicy(Qt::StrongFocus);
}


BookDataWidget::~BookDataWidget()
{
    delete ui;
}


void BookDataWidget::setBook(Book *openedBook)
{
    book = openedBook;

    ui->_File->setText(book->getFileName() + (book->isZipped() ? "  :  " + book->getZippedFileName() : ""));
    ui->_Codec->setText(book->getCodec());
    ui->_MD5->setText(book->getIndex());
    ui->_Time->setText(QDateTime::fromMSecsSinceEpoch(book->getAdditionalTime()).toString("dd.MM.yyyy - HH:mm:ss"));

    if (book->getFormat() == Book::BookFormat::FB2)
        ui->_Format->setText("FB2");
    else if(book->getFormat() == Book::BookFormat::EPUB)
        ui->_Format->setText("EPUB");

    QPixmap cover = QPixmap::fromImage(book->getCover());
    ui->_Cover->setFixedSize(cover.size());
    ui->_Cover->setPixmap(cover);


    ui->_AuthorName->setText(book->getAuthorName());
    ui->_Title->setText(book->getTitle());
    ui->_Language->setText(book->getLanguage());
    ui->_Series->setText(book->getSeries());
    ui->_SeriesNumber->setText(book->getSeries());
}


void BookDataWidget::resetData()
{
    book = nullptr;
}


bool BookDataWidget::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched)

    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *KeyEvent = static_cast<QKeyEvent*>(event);
        if (KeyEvent->key() == Qt::Key_Escape)
            emit showBookPage();
    }
    else if (event->type() == QEvent::LanguageChange)
        ui->retranslateUi(this);

    return true;
}


void BookDataWidget::on_CloseData_clicked()
{
    emit showBookPage();
}


void BookDataWidget::on_ChangeCover_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, QObject::tr("Open files"), "", tr("Image file (*.jpg *.jpeg *.png)"));
    QImage newCover(file);

    ///заглушка
    book->setCover(newCover, QImageReader::imageFormat(file));

    QPixmap cover = QPixmap::fromImage(book->getCover());
    ui->_Cover->setFixedSize(cover.size());
    ui->_Cover->setPixmap(cover);
}


void BookDataWidget::on_EditData_clicked()
{

}

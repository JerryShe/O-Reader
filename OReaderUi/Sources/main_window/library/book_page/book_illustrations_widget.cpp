#include "book_illustrations_widget.h"
#include "ui_book_illustrations_widget.h"

#include <QKeyEvent>


BookIllustrationsWidget::BookIllustrationsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookIllustrationsWidget)
{
    ui->setupUi(this);

    curImage = 0;

    connect(ui->CloseIllustrations, SIGNAL(clicked(bool)), this, SIGNAL(showBookPage()));

    this->installEventFilter(this);
    this->setFocusPolicy(Qt::StrongFocus);
}


BookIllustrationsWidget::~BookIllustrationsWidget()
{
    delete ui;
}


void BookIllustrationsWidget::setBook(Book *book)
{
    Book::BookContainsImages existing = book->getContainsImages();

    if (existing != Book::BookContainsImages::NO)
    {
        BookImageTable imageTable(book);
        images = imageTable.getBookImages();

        this->show();
        showIllustrationAt(curImage);
        this->hide();
    }
    ui->TitleLabel->setText(book->getAuthorName() + " - " + book->getTitle());
}


bool BookIllustrationsWidget::imagesLoaded() const
{
    return images.size() > 0;
}


void BookIllustrationsWidget::resetData()
{
    images.clear();
    curImage = 0;
}


void BookIllustrationsWidget::on_PrevIllustration_clicked()
{
    if (curImage > 0 && curImage <= images.size())
        curImage--;
    else
        curImage = images.size() - 1;

    showIllustrationAt(curImage);
}


void BookIllustrationsWidget::on_NextIllustration_clicked()
{
    if (curImage >= 0 && curImage < images.size()-1)
        curImage++;
    else
        curImage = 0;
    showIllustrationAt(curImage);
}

bool BookIllustrationsWidget::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched)

    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *KeyEvent = static_cast<QKeyEvent*>(event);

        if (KeyEvent->key() == Qt::Key_Left)
            on_PrevIllustration_clicked();
        else if (KeyEvent->key() == Qt::Key_Right)
            on_NextIllustration_clicked();
        else if (KeyEvent->key() == Qt::Key_Escape)
            emit showBookPage();
    }
    else if (event->type() == QEvent::LanguageChange)
        ui->retranslateUi(this);

    return true;
}


void BookIllustrationsWidget::showIllustrationAt(const int i)
{
    if (i >= images.size() || i < 0)
        return;

    QImage img = images[i];
    if (img.width() > ui->IllustrationLabel->width() || img.height() > ui->IllustrationLabel->height())
        img = img.scaled(ui->IllustrationLabel->width(), ui->IllustrationLabel->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QPixmap pixmap = QPixmap::fromImage(img);
    ui->IllustrationLabel->setPixmap(pixmap);

    ui->ImageCounter->setText(QString::number(i+1) + "/" + QString::number(images.size()));
}

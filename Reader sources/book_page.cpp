#include "book_page.h"
#include "ui_book_page.h"

#include "styles.h"
#include "books.h"
#include "reading_window.h"

void BookPage::setStyle(QString Style)
{
    QString PageStyles[7];

    setBookPageStyle(PageStyles, Style);

    BookPage::setStyleSheet(PageStyles[0]);

    ui->startReading->setStyleSheet(PageStyles[1]);
    ui->deleteBook->setStyleSheet(PageStyles[4]);
    ui->leftLine->setStyleSheet(PageStyles[5]);
    ui->leftLine_2->setStyleSheet(PageStyles[5]);

    ui->author->setStyleSheet(PageStyles[2]);
    ui->genres->setStyleSheet(PageStyles[2]);
    ui->title->setStyleSheet(PageStyles[2]);
    ui->series->setStyleSheet(PageStyles[2]);
    ui->BookProgress->setStyleSheet(PageStyles[2]);
    ui->annotation->setStyleSheet(PageStyles[3]);

    setExitButtonStyle(PageStyles, Style);
    ui->exit_button->setStyleSheet(PageStyles[0]);
}

BookPage::BookPage(Book* book, QString Style, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BookPage)
{
    setAttribute(Qt::WA_DeleteOnClose);

    BookIndex = book->getBookIndex();
    ui->setupUi(this);
    setStyle(Style);
    style = Style;

    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(Qt::Popup);

    this->setGeometry(parent->x() + 180, parent->y() + 100, parent->width() - 270, parent->height() - 200);

    QStringList list = book->getAnnotation();
    QString temp = "     ";
    for (int i = 0; i < list.size(); i++)
        if (list[i] != "")
        {
            QString a = list.at(i);
            a = a.trimmed();
            if (a != "")
                temp += a + '\n' + "     ";
        }

    ui->annotation->setText(temp);
    ui->annotation->setReadOnly(true);
    ui->annotation->setAlignment(Qt::AlignJustify);

    QPixmap cover = QPixmap::fromImage(book->getCover());
    ui->Image->setMaximumSize(cover.size());
    ui->Image->setMinimumSize(cover.size());
    ui->Image->setPixmap(cover);

    int textWidth = this->width() - ui->BookData->contentsMargins().left() - ui->BookData->contentsMargins().right()
            - ui->Image->width() - ui->ImageBlock->contentsMargins().left() - ui->ImageBlock->contentsMargins().right()
            - ui->startReading->width() - ui->VerticalButtonBlock->contentsMargins().right() - 2;

    QFontMetrics metrics(ui->author->font());
    ui->author->setText(metrics.elidedText(book->getAuthorName(), Qt::ElideRight, textWidth));

    metrics = QFontMetrics(ui->title->font());
    ui->title->setText(metrics.elidedText(book->getTitle(), Qt::ElideRight, textWidth));

    metrics = QFontMetrics(ui->series->font());
    ui->series->setText(metrics.elidedText(book->getSeries(), Qt::ElideRight, textWidth));

    ui->BookProgress->setText(QString::number(floor(book->getBookProgressPocent()*10)/10) + "%");

    list = book->getGenres();
    temp = list[0];
    for (int i = 1; i < list.size(); i++)
        temp += ", " + list[i];

    metrics = QFontMetrics(ui->genres->font());
    ui->genres->setText(metrics.elidedText(temp, Qt::ElideRight, textWidth));
    connect(ui->exit_button, SIGNAL(clicked(bool)), this, SLOT(close()));

    show();
}

BookPage::~BookPage()
{
    delete ui;
}

void BookPage::on_startReading_clicked()
{
    this->hide();
    emit startReading(BookIndex);
    this->close();
}

void BookPage::on_deleteBook_clicked()
{
    AnswerDialog *answer_window = new AnswerDialog(ui->deleteBook->mapToGlobal(QPoint(- 300, ui->exit_button->height())),
                                                   QObject::tr("Delete book?"),
                                                   style,
                                                   this);
    answer_window->show();

    if (answer_window->exec() == QDialog::Accepted)
    {
        emit deleteBook(BookIndex);
        delete answer_window;
        this->close();
    }
    else
        delete answer_window;
}

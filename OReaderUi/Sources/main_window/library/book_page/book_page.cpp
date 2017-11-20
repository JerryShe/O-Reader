#include "book_page.h"
#include "ui_book_page.h"
#include "book.h"
#include "settings_handler.h"
#include "answer_dialog.h"
#include "book_image_table.h"

#include "styles.h"

#include <QKeyEvent>

#include <QDebug>

void BookPage::setStyle(QString Style)
{
    QString PageStyles[8];

    setBookPageStyle(PageStyles, Style);

    BookPage::setStyleSheet(PageStyles[0]);

    ui->startReading->setStyleSheet(PageStyles[1]);
    ui->deleteBook->setStyleSheet(PageStyles[4]);
    ui->leftLine->setStyleSheet(PageStyles[5]);

    ui->author->setStyleSheet(PageStyles[2]);
    ui->genres->setStyleSheet(PageStyles[2]);
    ui->title->setStyleSheet(PageStyles[2]);
    ui->series->setStyleSheet(PageStyles[2]);
    ui->BookProgress->setStyleSheet(PageStyles[2]);
    ui->annotation->setStyleSheet(PageStyles[3]);

    ui->ImageCounter->setStyleSheet(PageStyles[2]);

    ui->NextIllustration->setStyleSheet(PageStyles[6]);
    ui->PrevIllustration->setStyleSheet(PageStyles[7]);

    setExitButtonStyle(PageStyles, Style);
    ui->exit_button->setStyleSheet(PageStyles[0]);
    ui->CloseIllustrations->setStyleSheet(PageStyles[0]);
}


BookPage::BookPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookPage)
{
    ui->setupUi(this);
}


BookPage::~BookPage()
{
    qDebug()<<"delete BookPage";
    delete ui;
}

void BookPage::setBook(Book *showingbook)
{
    book = showingbook;

    ui->stackedWidget->setCurrentWidget(ui->BookWidget);

    setStyle(SettingsHandler::getSettings()->getInterfaceStyle());

    ui->author->setWordWrap(true);
    ui->title->setWordWrap(true);

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
    ui->CoverImage->setFixedSize(cover.size());
    ui->CoverImage->setPixmap(cover);

    QFontMetrics metrics(ui->author->font());
    ui->author->setText(metrics.elidedText(book->getAuthorName(), Qt::ElideRight, ui->author->width()));

    metrics = QFontMetrics(ui->title->font());
    ui->title->setText(metrics.elidedText(book->getTitle(), Qt::ElideRight, ui->title->width()));

    metrics = QFontMetrics(ui->series->font());
    ui->series->setText(metrics.elidedText(tr("Серия") + book->getSeries(), Qt::ElideRight, ui->series->width()));

    ui->BookProgress->setText(QString::number(floor(book->getProgressProcent()*10)/10) + "%");

    list = book->getGenres();
    temp = list[0];
    for (int i = 1; i < list.size(); i++)
        temp += ", " + list[i];

    metrics = QFontMetrics(ui->genres->font());
    ui->genres->setText(metrics.elidedText(tr("Жанр: ") + temp, Qt::ElideRight, ui->genres->width()));


    connect(ui->exit_button, SIGNAL(clicked(bool)), this, SIGNAL(closeBookPage()));


    //illustrations
    switch (book->getContainImages())
    {
        case Book::BookContainsImages::UNKNOWN:
        {
            BookImageTable imageTable(book);
            images = imageTable.getBookImages();

            if (images.size() == 0)
            {
                ui->ShowIllustrations->setEnabled(false);
                book->setContainImages(Book::BookContainsImages::NO);
            }
            else
                book->setContainImages(Book::BookContainsImages::YES);

            break;
        }
        case Book::BookContainsImages::YES:
        {
            break;
        }
        case Book::BookContainsImages::NO:
        {
            ui->ShowIllustrations->setEnabled(false);
            break;
        }
    }


    this->installEventFilter(this);
    ui->IllustrationsWidget->installEventFilter(this);
}


void BookPage::resetData()
{
    book = nullptr;
    images.clear();
    curImage = 0;

    ui->annotation->clear();
    ui->author->clear();
    ui->BookProgress->clear();
    ui->genres->clear();
    ui->CoverImage->clear();
    ui->series->clear();
    ui->title->clear();
}


void BookPage::on_startReading_clicked()
{
    emit startReading(book->getIndex());
}


void BookPage::on_deleteBook_clicked()
{
    AnswerDialog *answer_window = new AnswerDialog(ui->deleteBook->mapToGlobal(QPoint(ui->deleteBook->width() - 300, ui->deleteBook->height() - 70)),
                                                   QObject::tr("Delete book?"),
                                                   this);
    answer_window->show();

    if (answer_window->exec() == QDialog::Accepted)
    {
        emit deleteBook(book->getIndex());
        this->close();
    }
}


void BookPage::on_ShowIllustrations_clicked()
{
    if (book->getContainImages() == Book::BookContainsImages::YES)
    {
        if (images.size() == 0)
        {
            BookImageTable imageTable(book);
            images = imageTable.getBookImages();
        }

        curImage = 0;
        showIllustrationAt(curImage);

        ui->stackedWidget->setCurrentWidget(ui->IllustrationsWidget);
    }
}


void BookPage::showIllustrationAt(const int i)
{
    if (i >= images.size() || i < 0)
        return;

    QImage img = images[i];
    if (img.width() > this->width() || img.height() > this->height() - 70)
        img = img.scaled(this->width(), this->height() - 70, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->IllustrationLabel->setFixedSize(img.size());

    QPixmap pixmap = QPixmap::fromImage(img);
    ui->IllustrationLabel->setPixmap(pixmap);

    ui->ImageCounter->setText(QString::number(i+1) + "/" + QString::number(images.size()));
}


void BookPage::on_PrevIllustration_clicked()
{
    if (curImage > 0 && curImage <= images.size())
        curImage--;
    else
        curImage = images.size() - 1;

    showIllustrationAt(curImage);
}


void BookPage::on_CloseIllustrations_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->BookWidget);
}


void BookPage::on_NextIllustration_clicked()
{
    if (curImage >= 0 && curImage < images.size()-1)
        curImage++;
    else
        curImage = 0;
    showIllustrationAt(curImage);
}


bool BookPage::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj)

    if (ui->stackedWidget->currentWidget() == ui->IllustrationsWidget)
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent *KeyEvent = static_cast<QKeyEvent*>(event);

            if (KeyEvent->key() == Qt::Key_Left)
                on_PrevIllustration_clicked();
            else if (KeyEvent->key() == Qt::Key_Right)
                on_NextIllustration_clicked();
            else if (KeyEvent->key() == Qt::Key_Escape)
            {
                ui->stackedWidget->setCurrentWidget(ui->BookWidget);
                return true;
            }
        }
    }
    else
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent *KeyEvent = static_cast<QKeyEvent*>(event);
            if (KeyEvent->key() == Qt::Key_Escape)
                this->close();
        }
    }

    return false;
}

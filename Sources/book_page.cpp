#include "book_page.h"
#include "ui_book_page.h"

#include "styles.h"
#include "books.h"
#include "settings.h"
#include "answer_dialog.h"
#include "book_image_table.h"

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
    ui->leftLine_2->setStyleSheet(PageStyles[5]);

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


BookPage::BookPage(Book *boo, QWidget *parent) :
    //QMainWindow(parent),
    ui(new Ui::BookPage)
{
    setAttribute(Qt::WA_DeleteOnClose);

    book = boo;
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->BookWidget);

    setStyle(Settings::getSettings()->getInterfaceStyle());

    setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setWindowFlags(Qt::Popup);

    this->setGeometry(parent->mapToGlobal(QPoint(180, 0)).x(), parent->mapToGlobal(QPoint(0, 100)).y(), parent->width() - 270, parent->height() - 200);

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
    ui->Image->setFixedSize(cover.size());
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

    ui->BookProgress->setText(QString::number(floor(book->getProgressProcent()*10)/10) + "%");

    list = book->getGenres();
    temp = list[0];
    for (int i = 1; i < list.size(); i++)
        temp += ", " + list[i];

    metrics = QFontMetrics(ui->genres->font());
    ui->genres->setText(metrics.elidedText(temp, Qt::ElideRight, textWidth));


    connect(ui->exit_button, SIGNAL(clicked(bool)), this, SLOT(close()));


    //illustrations
    BookImageTable imageTable(book);
    images = imageTable.getBookImages();

    if (images.size() == 0)
        ui->ShowIllustrations->setEnabled(false);


    this->installEventFilter(this);
    ui->IllustrationsWidget->installEventFilter(this);

    show();
}


BookPage::~BookPage()
{
    qDebug()<<"delete BookPage";
    delete ui;
}


void BookPage::on_startReading_clicked()
{
    this->hide();
    emit startReading(book->getIndex());
    this->close();
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
        delete answer_window;
        this->close();
    }
    else
        delete answer_window;
}


void BookPage::on_ShowIllustrations_clicked()
{
    curImage = 0;
    showIllustrationAt(curImage);

    ui->stackedWidget->setCurrentWidget(ui->IllustrationsWidget);
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

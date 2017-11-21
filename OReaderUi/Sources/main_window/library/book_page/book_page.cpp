#include "book_page.h"
#include "ui_book_page.h"
#include "settings_handler.h"
#include "answer_dialog.h"

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

    ui->author->setStyleSheet(PageStyles[2]);
    ui->genres->setStyleSheet(PageStyles[2]);
    ui->title->setStyleSheet(PageStyles[2]);
    ui->series->setStyleSheet(PageStyles[2]);
    ui->BookProgress->setStyleSheet(PageStyles[2]);
    ui->annotation->setStyleSheet(PageStyles[3]);
}


BookPage::BookPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookPage)
{
    ui->setupUi(this);

    ui->author->setWordWrap(true);
    ui->title->setWordWrap(true);

    ui->annotation->setReadOnly(true);
    ui->annotation->setAlignment(Qt::AlignJustify);

    connect(ui->IllustrationsWidgetPage, SIGNAL(showBookPage()), this, SLOT(showBookPage()));
    connect(ui->BookDataWidgetPage, SIGNAL(showBookPage()), this, SLOT(showBookPage()));

    connect(ui->exit_button, SIGNAL(clicked(bool)), this, SIGNAL(closeBookPage()));

    setStyle(SettingsHandler::getSettings()->getInterfaceStyle());

    this->installEventFilter(this);
    this->setFocusPolicy(Qt::StrongFocus);
}


BookPage::~BookPage()
{
    qDebug()<<"delete BookPage";
    delete ui;
}


void BookPage::setBook(Book *showingBook)
{
    if (showingBook == nullptr)
        return;

    book = showingBook;

    ui->stackedWidget->setCurrentWidget(ui->BookWidgetPage);

    QStringList list = book->getAnnotation();
    QString temp = "     ";
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i] != "")
        {
            QString a = list.at(i);
            a = a.trimmed();
            if (a != "")
                temp += a + '\n' + "     ";
        }
    }

    ui->annotation->setText(temp);

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



    if (book->getContainsImages() == Book::BookContainsImages::UNKNOWN)
        ui->IllustrationsWidgetPage->setBook(showingBook);

    if (book->getContainsImages() == Book::BookContainsImages::NO)
        ui->ShowIllustrations->setEnabled(false);

    ui->BookDataWidgetPage->setBook(book);
}


void BookPage::resetData()
{
    book = nullptr;
    curImage = 0;

    ui->annotation->clear();
    ui->author->clear();
    ui->BookProgress->clear();
    ui->genres->clear();
    ui->CoverImage->clear();
    ui->series->clear();
    ui->title->clear();

    ui->IllustrationsWidgetPage->resetData();
    ui->BookDataWidgetPage->resetData();
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
        emit closeBookPage();
    }
}


void BookPage::showBookPage()
{
    ui->stackedWidget->setCurrentWidget(ui->BookWidgetPage);
}


bool BookPage::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj)

    if (ui->stackedWidget->currentWidget() == ui->BookWidgetPage)
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent *KeyEvent = static_cast<QKeyEvent*>(event);
            if (KeyEvent->key() == Qt::Key_Escape)
                emit closeBookPage();
        }
    }
    else if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }

    return false;
}


void BookPage::on_ShowIllustrations_clicked()
{
    if (book->getContainsImages() == Book::BookContainsImages::YES)
    {
        if (!ui->IllustrationsWidgetPage->imagesLoaded())
            ui->IllustrationsWidgetPage->setBook(book);

        ui->stackedWidget->setCurrentWidget(ui->IllustrationsWidgetPage);
    }
}


void BookPage::on_ShowBookData_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->BookDataWidgetPage);
}

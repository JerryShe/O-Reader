#include "book_widget.h"
#include "ui_book_widget.h"

#include "settings.h"
#include "library_handler.h"

#include "styles.h"

#include <QStateMachine>
#include <QPropertyAnimation>
#include <QSignalTransition>


void BookWidget::setStyle()
{
    QString curStyle = Settings::getSettings()->getInterfaceStyle();
    QString styles[4];

    setLastBookWidgetStyle(styles, curStyle);

    setStyleSheet(styles[0]);
    ui->ReadButton->setStyleSheet(styles[1]);
    ui->PageButton->setStyleSheet(styles[2]);
    ui->ShowButton->setStyleSheet(styles[3]);
}

BookWidget::BookWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookWidget)
{
    ui->setupUi(this);
    setStyle();

    Book* book = LibraryHandler::getLibraryHandler()->getLastOpenedBook();

    if (book == 0)
        this->close();

    BookIndex = book->getBookIndex();

    ui->Author->setText(book->getAuthorName());

    ui->BookProgress->setText(QString::number(floor(book->getBookProgressPocent()*10)/10) + "%");

    ui->Title->setText(book->getTitle());

    this->show();

    Cover = QPixmap::fromImage(book->getCover());
    Cover = Cover.scaledToWidth(ui->ImageLabel->maximumWidth());
    ui->ImageLabel->resize(ui->ImageLabel->width(), Cover.height());
    ui->ImageLabel->setPixmap(Cover);

    this->hideWidget();

    this->parentWidget()->installEventFilter(this);
}

bool BookWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Resize)
    {
        this->resize(this->width(), this->parentWidget()->height() - 30);

        if (ui->ImageLabel->height() < Cover.height())
            ui->ImageLabel->setPixmap(Cover.scaledToHeight(ui->ImageLabel->height()));
    }
    return false;
}

BookWidget::~BookWidget()
{
    delete ui;
}

void BookWidget::on_ShowButton_clicked()
{
    if (ui->LastBookLayout->isHidden())
        this->showWidget();
    else
        this->hideWidget();
}

void BookWidget::showWidget()
{
    this->resize(235, this->height());
    ui->LastBookLayout->show();

}

void BookWidget::hideWidget()
{
    ui->LastBookLayout->hide();
    this->resize(15, this->height());
}

void BookWidget::on_ReadButton_clicked()
{
    this->hideWidget();
    emit startReading(BookIndex);
}

void BookWidget::on_PageButton_clicked()
{
    this->hideWidget();
    emit showBookPage(BookIndex);
}

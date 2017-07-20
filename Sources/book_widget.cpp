#include "book_widget.h"
#include "ui_book_widget.h"

#include "settings.h"
#include "library_handler.h"

#include "styles.h"

#include <QStateMachine>
#include <QPropertyAnimation>
#include <QSignalTransition>

#include <QMouseEvent>


void BookWidget::setStyle()
{
    QString curStyle = Settings::getSettings()->getInterfaceStyle();
    QString styles[4];

    setLastBookWidgetStyle(styles, curStyle);

    setStyleSheet(styles[0]);
    this->setStyleSheet(styles[0]);
    ui->ReadButton->setStyleSheet(styles[1]);
    ui->PageButton->setStyleSheet(styles[2]);
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

    BookIndex = book->getIndex();

    ui->Author->setText(book->getAuthorName());

    ui->BookProgress->setText(QString::number(floor(book->getProgressProcent()*10)/10) + "%");

    ui->Title->setText(book->getTitle());

    this->show();

    machine = new QStateMachine(this);
    s1 = new QState(machine);
    s2 = new QState(machine);

    animation = new QPropertyAnimation(this, "pos");

    animation->setDuration(100);

    s2->assignProperty(this, "pos", QPoint(- this->width(), 30));
    s1->assignProperty(this, "pos", QPoint(25, 30));


    transition1 = s1->addTransition(this, SIGNAL(showButtonClicked()), s2);
    transition2 = s2->addTransition(this, SIGNAL(showButtonClicked()), s1);


    transition1->addAnimation(animation);
    transition2->addAnimation(animation);
    machine->setInitialState(s1);
    machine->start();


    Cover = QPixmap::fromImage(book->getCover());
    Cover = Cover.scaledToWidth(ui->ImageLabel->maximumWidth());
    ui->ImageLabel->resize(ui->ImageLabel->width(), Cover.height());
    ui->ImageLabel->setPixmap(Cover);

    this->parentWidget()->installEventFilter(this);
}


bool BookWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Resize)
    {
        this->resize(this->width(), this->parentWidget()->height() - 30);
        this->move(25, 30);

        if (ui->ImageLabel->height() < Cover.height())
            ui->ImageLabel->setPixmap(Cover.scaledToHeight(ui->ImageLabel->height()));
    }
    return false;
}


BookWidget::~BookWidget()
{
    delete ui;
}


void BookWidget::showWidget()
{
    if (machine->configuration().contains(s2))
        emit showButtonClicked();
}


void BookWidget::hideWidget()
{
    if (machine->configuration().contains(s1))
        emit showButtonClicked();
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


unsigned int BookWidget::getBookIndex()
{
    return BookIndex;
}

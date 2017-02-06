#include "booktableofcontents.h"
#include "ui_booktableofcontents.h"
#include "styles.h"


void BookTableOfContents::setWindowStyle(QString style)
{
    QString windowStyle[2];
    setReaderTableOfContents(windowStyle, style);
    ui->TableOfContents->setStyleSheet(windowStyle[0]);
    ui->Close->setStyleSheet(windowStyle[1]);
    ui->GoTo->setStyleSheet(windowStyle[1]);
}

BookTableOfContents::BookTableOfContents(QString style, QStringList contentList, int currentPos, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookTableOfContents)
{
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    setWindowStyle(style);
    ui->TableOfContents->addItems(contentList);
    ui->TableOfContents->setCurrentRow(currentPos);
    connect(ui->Close, SIGNAL(clicked()), this, SLOT(reject()));
}

BookTableOfContents::~BookTableOfContents()
{
    delete ui;
}

void BookTableOfContents::on_GoTo_clicked()
{
    emit goToSection(ui->TableOfContents->currentRow());
}

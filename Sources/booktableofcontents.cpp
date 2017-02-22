#include "booktableofcontents.h"
#include "ui_booktableofcontents.h"
#include "styles.h"


void BookTableOfContents::setStyle(const QString &style)
{
    QString windowStyle[2];
    setReaderTableOfContents(windowStyle, style);
    ui->TableOfContents->setStyleSheet(windowStyle[0]);
    ui->Close->setStyleSheet(windowStyle[1]);
    ui->GoTo->setStyleSheet(windowStyle[1]);
}

BookTableOfContents::BookTableOfContents(const QString &style, const QStringList &contentList, const int &currentPos, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookTableOfContents)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    ui->setupUi(this);
    setStyle(style);
    ui->TableOfContents->addItems(contentList);
    ui->TableOfContents->setCurrentRow(currentPos);

    connect(ui->Close, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->GoTo, &QPushButton::clicked, [this](){emit goToSection(ui->TableOfContents->currentRow());});
}

BookTableOfContents::~BookTableOfContents()
{
    delete ui;
}

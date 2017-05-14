#include "booktableofcontents.h"
#include "ui_booktableofcontents.h"
#include "styles.h"

#include <QDebug>
#include <QTreeWidgetItem>


void BookTableOfContents::setStyle(const QString &style)
{
    QString windowStyle[2];
    setReaderTableOfContents(windowStyle, style);
    ui->TableOfContents->setStyleSheet(windowStyle[0]);
    ui->Close->setStyleSheet(windowStyle[1]);
    ui->GoTo->setStyleSheet(windowStyle[1]);
}

BookTableOfContents::BookTableOfContents(const QString &style, QTreeWidgetItem *content, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookTableOfContents)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    ui->setupUi(this);
    setStyle(style);

    ui->TableOfContents->addTopLevelItem(content);
    ui->TableOfContents->setRootIndex(ui->TableOfContents->model()->index(0,0,QModelIndex()));

    connect(ui->Close, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->GoTo, &QPushButton::clicked, [this](){
        if (ui->TableOfContents->selectedItems().size())
            emit goToSection(ui->TableOfContents->selectedItems().first()->whatsThis(0).toLongLong());});
}

BookTableOfContents::~BookTableOfContents()
{
    qDebug()<<"delete table of contents";
    delete ui;
}

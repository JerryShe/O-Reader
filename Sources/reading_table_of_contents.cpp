#include "reading_table_of_contents.h"
#include "ui_reading_table_of_contents.h"
#include "styles.h"

#include <QDebug>
#include <QTreeWidgetItem>

#include <QScroller>
#include <QTouchDevice>

#include <settings.h>

void ReadingTableOfContents::setStyle()
{
    QString windowStyle[2];
    setReaderTableOfContents(windowStyle, Settings::getSettings()->getInterfaceStyle());
    ui->TableOfContents->setStyleSheet(windowStyle[0]);
    ui->Close->setStyleSheet(windowStyle[1]);
    ui->GoTo->setStyleSheet(windowStyle[1]);
}


ReadingTableOfContents::ReadingTableOfContents(QTreeWidgetItem *content, const long long &pos, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReadingTableOfContents)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    setStyle();

    ui->TableOfContents->addTopLevelItem(content);
    ui->TableOfContents->setRootIndex(ui->TableOfContents->model()->index(0,0,QModelIndex()));

    curSection = content;
    curPos = pos;
    getCurrentSection(curSection);
    ui->TableOfContents->setCurrentItem(curSection);

    connect(ui->Close, SIGNAL(clicked()), this, SLOT(reject()));

    connect(ui->GoTo, &QPushButton::clicked, [this](){
        if (ui->TableOfContents->selectedItems().size())
            emit goToSection(ui->TableOfContents->selectedItems().first()->whatsThis(0).toLongLong());});


    if (QTouchDevice::devices().size())
    {
        QScroller::grabGesture(ui->TableOfContents->viewport(), QScroller::LeftMouseButtonGesture);
        ui->TableOfContents->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    }

    qDebug()<<"create table of contents";
}


void ReadingTableOfContents::getCurrentSection(QTreeWidgetItem* item)
{
    if (curPos > item->whatsThis(0).toLongLong())
    {
        curSection = item;
        for (int i = 0; i < item->childCount(); i++)
            getCurrentSection(item->child(i));
    }
}


ReadingTableOfContents::~ReadingTableOfContents()
{
    qDebug()<<"delete table of contents";
    delete ui;
}

#include "reading_window/widgets/table_of_contents_widget.h"
#include "ui_table_of_contents_widget.h"
#include "data_handlers/settings_handler.h"

#include "styles.h"

#include <QTreeWidgetItem>
#include <QScroller>
#include <QTouchDevice>

#include <QDebug>


void TableOfContentsWidget::setStyle()
{
    QString windowStyle[2];
    setReaderTableOfContents(windowStyle, SettingsHandler::getSettings()->getInterfaceStyle());
    ui->TableOfContents->setStyleSheet(windowStyle[0]);
    ui->Close->setStyleSheet(windowStyle[1]);
    ui->GoTo->setStyleSheet(windowStyle[1]);
}


TableOfContentsWidget::TableOfContentsWidget(QTreeWidgetItem *content, const long long &pos, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableOfContentsWidget)
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


void TableOfContentsWidget::getCurrentSection(QTreeWidgetItem* item)
{
    if (curPos > item->whatsThis(0).toLongLong())
    {
        curSection = item;
        for (int i = 0; i < item->childCount(); i++)
            getCurrentSection(item->child(i));
    }
}


TableOfContentsWidget::~TableOfContentsWidget()
{
    qDebug()<<"delete table of contents";
    delete ui;
}

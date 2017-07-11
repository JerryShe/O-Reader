#include "reading_search_widget.h"
#include "ui_reading_search_widget.h"

#include "settings.h"
#include "styles.h"

#include <QPushButton>

#include <QDebug>


void ReadingSearchWidget::setStyle()
{
    QString styles[2];
    setExitButtonStyle(styles, Settings::getSettings()->getInterfaceStyle());
    ui->ExitButton->setStyleSheet(styles[0]);

    setBackgroundWindowColor(styles, Settings::getSettings()->getInterfaceStyle());

    this->setStyleSheet("background-color:rgb(150, 0, 60); color:white;}");

}

ReadingSearchWidget::ReadingSearchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReadingSearchWidget)
{
    qDebug()<<"create SearchWidget";
    ui->setupUi(this);

    connect(ui->ExitButton, SIGNAL(clicked(bool)), this, SIGNAL(searchClosed()));
    setStyle();
}


ReadingSearchWidget::~ReadingSearchWidget()
{
    qDebug()<<"delete SearchWidget";
    delete ui;
}


void ReadingSearchWidget::setBookData(QTreeWidgetItem* item, const long long &pos)
{
    Contents = item;
    CurrentPos = pos;
}


void ReadingSearchWidget::setSearchResult(const QVector<QPair<BookPosition, QString>> &results)
{
    SearchResults = results;
}


void ReadingSearchWidget::on_StartSearch_clicked()
{

}

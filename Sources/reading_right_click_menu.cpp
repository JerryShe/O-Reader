#include "reading_right_click_menu.h"
#include "ui_reading_right_click_menu.h"

#include <QDebug>

void ReadingRightClickMenu::setStyle()
{
    this->setStyleSheet("ReadingRightClickMenu{"
                        "border:0px;"
                        "background-color:rgb(150, 0, 60);}");

    QString kostil = "QPushButton"
                     "{background-color: rgb(162, 0, 70);"
                     "border:none;"
                     "color:white;}"
                     "QPushButton:hover"
                     "{background-color:rgb(147, 0, 60);}";

    ui->Copy->setStyleSheet(kostil);
    ui->FindSelected->setStyleSheet(kostil);
    ui->GoogleSearch->setStyleSheet(kostil);
    ui->GoogleTranslate->setStyleSheet(kostil);
    ui->Note->setStyleSheet(kostil);
    ui->OpenSearch->setStyleSheet(kostil);
    ui->OpenSettings->setStyleSheet(kostil);
    ui->Selection->setStyleSheet(kostil);
    ui->TextSizeMinus->setStyleSheet(kostil);
    ui->TextSizePlus->setStyleSheet(kostil);
    ui->TextSizeLabel->setStyleSheet("QLabel{background-color: rgb(162, 0, 70);color:white;}");
}


ReadingRightClickMenu::ReadingRightClickMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReadingRightClickMenu)
{
    ui->setupUi(this);

    connect(ui->OpenSearch, SIGNAL(clicked(bool)), this, SIGNAL(openSearch()));
    connect(ui->OpenSettings, SIGNAL(clicked(bool)), this, SIGNAL(openSettings()));
    connect(ui->TextSizeMinus, &QPushButton::clicked, [this](){
        emit rescaleText(false);
    });
    connect(ui->TextSizePlus, &QPushButton::clicked, [this](){
        emit rescaleText(true);
    });

    setStyle();
}


ReadingRightClickMenu::~ReadingRightClickMenu()
{
    delete ui;
}


void ReadingRightClickMenu::setState(const int &state)
{
    ui->Note->hide();

    if (state != 2)
    {
        ui->FindSelected->hide();
        ui->GoogleSearch->hide();
        ui->GoogleTranslate->hide();
        ui->Copy->hide();
        ui->Note->hide();

        this->setFixedHeight(120);
    }
    else
    {
        connect(ui->Copy, SIGNAL(clicked(bool)), this, SIGNAL(copySelected()));
        connect(ui->FindSelected, SIGNAL(clicked(bool)), this, SIGNAL(findSelected()));
        connect(ui->GoogleSearch, SIGNAL(clicked(bool)), this, SIGNAL(findGoogle()));
        connect(ui->GoogleTranslate, SIGNAL(clicked(bool)), this, SIGNAL(translateGoogle()));
        connect(ui->Note, SIGNAL(clicked(bool)), this, SIGNAL(createNote()));

        this->setFixedHeight(240);
    }

    if (state != 0)
    {
        connect(ui->Selection, SIGNAL(clicked(bool)), this, SIGNAL(disableSelect()));
        ui->Selection->setText(tr("Disable text selection"));
    }
    else
    {
        connect(ui->Selection, SIGNAL(clicked(bool)), this, SIGNAL(enableSelect()));
    }
}

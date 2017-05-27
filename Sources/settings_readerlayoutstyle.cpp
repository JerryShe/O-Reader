#include "settings_readerlayoutstyle.h"
#include "ui_settings_readerlayoutstyle.h"

#include <QListView>
#include <QColorDialog>

#include <QScroller>
#include <QTouchDevice>

Settings_ReaderLayoutStyle::Settings_ReaderLayoutStyle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings_ReaderLayoutStyle)
{
    ui->setupUi(this);
    ui->StyleWidget->hide();

    ui->NameBox->setView(new QListView());
    ui->SizeBox->setView(new QListView());
    ui->TextStyleBox->setView(new QListView());
    ui->LineSpacingBox->setView(new QListView());
    ui->AlignmentBox->setView(new QListView());

    connect(ui->NameBox, SIGNAL(activated(QString)), this, SIGNAL(settingsUpdate()));
    connect(ui->SizeBox, SIGNAL(activated(QString)), this, SIGNAL(settingsUpdate()));
    connect(ui->TextStyleBox, SIGNAL(activated(QString)), this, SIGNAL(settingsUpdate()));
    connect(ui->LineSpacingBox, SIGNAL(activated(QString)), this, SIGNAL(settingsUpdate()));
    connect(ui->AlignmentBox, SIGNAL(activated(QString)), this, SIGNAL(settingsUpdate()));


    if (QTouchDevice::devices().size())
    {
        QScroller::grabGesture(ui->NameBox->view()->viewport(), QScroller::LeftMouseButtonGesture);
        ui->NameBox->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        QScroller::grabGesture(ui->SizeBox->view()->viewport(), QScroller::LeftMouseButtonGesture);
        ui->SizeBox->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        QScroller::grabGesture(ui->TextStyleBox->view()->viewport(), QScroller::LeftMouseButtonGesture);
        ui->TextStyleBox->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        QScroller::grabGesture(ui->LineSpacingBox->view()->viewport(), QScroller::LeftMouseButtonGesture);
        ui->LineSpacingBox->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        QScroller::grabGesture(ui->AlignmentBox->view()->viewport(), QScroller::LeftMouseButtonGesture);
        ui->AlignmentBox->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    }


    for(double i = 1; i <= 2.5; i += 0.1)
        ui->LineSpacingBox->addItem(QString::number(i));
}


Settings_ReaderLayoutStyle::~Settings_ReaderLayoutStyle()
{
    delete ui;
}


void Settings_ReaderLayoutStyle::on_ColorBox_clicked()
{
    QColor Color = QColorDialog::getColor();
    if (!Color.isValid())
        return;
    ui->ColorBox->setStyleSheet("QPushButton{border:none;background-color:" + Color.name() + "; "
                                     "color:" + QColor(255 - Color.red(), 255 - Color.green(), 255 - Color.blue()).name() + ";}");
    ui->ColorBox->setText(Color.name());

    emit settingsUpdate();
}


void Settings_ReaderLayoutStyle::on_ShowButton_clicked()
{
    if (ui->StyleWidget->isHidden())
        ui->StyleWidget->show();
    else
        ui->StyleWidget->hide();
}


QString Settings_ReaderLayoutStyle::getHTMLStyle()
{
    QString tempHTML = "font-family:'" + ui->NameBox->currentText() + "';"
                                 "font-size:" + ui->SizeBox->currentText() + "pt;"
                                 "font-weight:" + ((ui->TextStyleBox->currentIndex()%2)?"900":"100") + ";"
                                 "line-height:" + QString::number(ui->LineSpacingBox->currentText().toDouble()*100) + ";"
                                 "font-style:" + ((ui->TextStyleBox->currentIndex()/2 == 1)?QString("italic"):QString("normal")) + ";"
                                 "text-align:" + Settings::getSettings()->getTextAlignName(ui->AlignmentBox->currentIndex()) + ";"
                                 "color:" + ui->ColorBox->text() + ";";

    return tempHTML;
}


void Settings_ReaderLayoutStyle::setStyleName(const QString &name)
{
    ui->ShowButton->setText(name);
}


void Settings_ReaderLayoutStyle::setStyleData(const TextStyleSheet &style)
{
    ui->NameBox->setCurrentFont(style.Family);
    ui->SizeBox->setCurrentText(QString::number(style.Size));
    ui->TextStyleBox->setCurrentIndex(style.Style);
    ui->LineSpacingBox->setCurrentText(QString::number(style.LineSpacing));
    ui->AlignmentBox->setCurrentIndex(style.Align);
    ui->ColorBox->setStyleSheet("QPushButton{border:none;background-color:" + style.Color + "; "
            "color:" + QColor(255 - QColor(style.Color).red(), 255 - QColor(style.Color).green(),
                              255 - QColor(style.Color).blue()).name() + ";}");
    ui->ColorBox->setText(style.Color);
}


TextStyleSheet Settings_ReaderLayoutStyle::getStyleData()
{
    TextStyleSheet tempStyle;

    tempStyle.Family = ui->NameBox->currentText();
    tempStyle.Size = ui->SizeBox->currentText().toShort();
    tempStyle.Style = ui->TextStyleBox->currentIndex();
    tempStyle.LineSpacing = ui->LineSpacingBox->currentText().toDouble();
    tempStyle.Align = ui->AlignmentBox->currentIndex();
    tempStyle.Color = ui->ColorBox->text();

    return tempStyle;
}

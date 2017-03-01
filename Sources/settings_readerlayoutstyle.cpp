#include "settings_readerlayoutstyle.h"
#include "ui_settings_readerlayoutstyle.h"

#include <QListView>
#include <QColorDialog>


Settings_ReaderLayoutStyle::Settings_ReaderLayoutStyle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings_ReaderLayoutStyle)
{
    ui->setupUi(this);
    ui->StyleWidget->hide();

    ui->NameBox->setView(new QListView());
    ui->SizeBox->setView(new QListView());
    ui->StyleBox->setView(new QListView());
    ui->LineSpacingBox->setView(new QListView());
    ui->AlignmentBox->setView(new QListView());

    connect(ui->NameBox, SIGNAL(activated(QString)), this, SIGNAL(settingsUpdate()));
    connect(ui->SizeBox, SIGNAL(activated(QString)), this, SIGNAL(settingsUpdate()));
    connect(ui->StyleBox, SIGNAL(activated(QString)), this, SIGNAL(settingsUpdate()));
    connect(ui->LineSpacingBox, SIGNAL(activated(QString)), this, SIGNAL(settingsUpdate()));
    connect(ui->AlignmentBox, SIGNAL(activated(QString)), this, SIGNAL(settingsUpdate()));

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
                                 "font-weight:" + ((ui->StyleBox->currentIndex()%2)?"900":"100") + ";"
                                 "line-height:" + QString::number(ui->LineSpacingBox->currentText().toDouble()*100) + ";"
                                 "font-style:" + ((ui->StyleBox->currentIndex()/2 == 1)?QString("italic"):QString("normal")) + ";"
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
    ui->StyleBox->setCurrentIndex(style.Style);
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
    tempStyle.Style = ui->StyleBox->currentIndex();
    tempStyle.LineSpacing = ui->LineSpacingBox->currentText().toDouble();
    tempStyle.Align = ui->AlignmentBox->currentIndex();
    tempStyle.Color = ui->ColorBox->text();

    return tempStyle;
}
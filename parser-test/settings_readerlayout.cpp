#include "settings_readerlayout.h"
#include "ui_settings_readerlayout.h"
#include "settings.h"
#include <QColorDialog>
#include <QDebug>

Settings_ReaderLayout::Settings_ReaderLayout(QWidget *parent) : QFrame(parent), ui(new Ui::Settings_ReaderLayout)
{
    ui->setupUi(this);

    ui->_OverallSettingsWidget->hide();
    ui->_RegularSettingsWidget->hide();
    ui->_EmphasizedSettingsWidget->hide();
    ui->_TitleSettingsWidget->hide();
    ui->_SubtitleSettingsWidget->hide();
    ui->_NoteSettingsWidget->hide();

    for(double i = 0.5; i <= 2.0; i += 0.1)
    {
        ui->RegularLineSpacingBox->addItem(QString::number(i));
        ui->TitleLineSpacingBox->addItem(QString::number(i));
        ui->SubtitleLineSpacingBox->addItem(QString::number(i));
        ui->NoteLineSpacingBox->addItem(QString::number(i));
        ui->EmphasizedLineSpacingBox->addItem(QString::number(i));
    }

    connect(ui->BackgroundImageBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->BackgroundTypeBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->TextAntiAliasingBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->ParagraphLeftIdentBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->ParagraphTopIdentBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->TextLeftIdentBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->TextRightIdentBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));

    connect(ui->RegularNameBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->RegularSizeBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->RegularStyleBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->RegularLineSpacingBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->RegularAlignmentBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));

    connect(ui->EmphasizedNameBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->EmphasizedSizeBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->EmphasizedStyleBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->EmphasizedLineSpacingBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->EmphasizedAlignmentBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));

    connect(ui->TitleNameBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->TitleSizeBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->TitleStyleBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->TitleLineSpacingBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->TitleAlignmentBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));

    connect(ui->SubtitleNameBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->SubtitleSizeBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->SubtitleStyleBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->SubtitleLineSpacingBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->SubtitleAlignmentBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));

    connect(ui->NoteNameBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->NoteSizeBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->NoteStyleBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->NoteLineSpacingBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->NoteAlignmentBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));

}

void Settings_ReaderLayout::updateTextBox()
{

    QString htEx = "<style type='text/css'>"
       "p{"
            "margin-top:" + ui->ParagraphTopIdentBox->currentText() + "px;"
            "margin-bottom:10px;"
            "margin-left:" + ui->TextLeftIdentBox->currentText() + "px;"
            "margin-right:" + ui->TextRightIdentBox->currentText() + "px;}"

       "TitleText{"
            "font-family:'" + ui->TitleNameBox->currentText() + "';"
            "font-size:" + ui->TitleSizeBox->currentText() + "pt;"
            "font-weight:" + QString::number(1000*(ui->TitleStyleBox->currentIndex()%2)) + ";"
            "line-height:" + QString::number(ui->TitleLineSpacingBox->currentText().toDouble()*100) + ";"
            "font-style:" + ((ui->TitleStyleBox->currentIndex()/2 == 1)?QString("italic"):QString("normal")) + ";"
            "text-align:" + ui->TitleAlignmentBox->currentText() + ";"
            "color:" + ui->TitleColorBox->text() + ";"
            "text-indent:" + ui->ParagraphLeftIdentBox->currentText() + "px;}"

       "SubtitleText{"
            "font-family:'" + ui->SubtitleNameBox->currentText() + "';"
            "font-size:" + ui->SubtitleSizeBox->currentText() + "pt;"
            "font-weight:" + QString::number(1000*(ui->SubtitleStyleBox->currentIndex()%2)) + ";"
            "line-height:" + QString::number(ui->SubtitleLineSpacingBox->currentText().toDouble()*100) + ";"
            "font-style:" + ((ui->SubtitleStyleBox->currentIndex()/2 == 1)?QString("italic"):QString("normal")) + ";"
            "text-align:" + ui->SubtitleAlignmentBox->currentText() + ";"
            "color:" + ui->SubtitleColorBox->text() + ";"
            "text-indent:" + ui->ParagraphLeftIdentBox->currentText() + "px;}"

       "Text{"
            "font-family:'" + ui->RegularNameBox->currentText() + "';"
            "font-size:" + ui->RegularSizeBox->currentText() + "pt;"
            "font-weight:" + QString::number(1000*(ui->RegularStyleBox->currentIndex()%2)) + ";"
            "line-height:" + QString::number(ui->RegularLineSpacingBox->currentText().toDouble()*100) + ";"
            "font-style:" + ((ui->RegularStyleBox->currentIndex()/2 == 1)?QString("italic"):QString("normal")) + ";"
            "text-align:" + ui->RegularAlignmentBox->currentText() + ";"
            "color:" + ui->RegularColorBox->text() + ";"
            "text-indent:" + ui->ParagraphLeftIdentBox->currentText() + "px;}"

       "Emphasis{"
            "font-family:'" + ui->EmphasizedNameBox->currentText() + "';"
            "font-size:" + ui->EmphasizedSizeBox->currentText() + "pt;"
            "font-weight:" + QString::number(1000*(ui->EmphasizedStyleBox->currentIndex()%2)) + ";"
            "line-height:" + QString::number(ui->EmphasizedLineSpacingBox->currentText().toDouble()*100) + ";"
            "font-style:" + ((ui->EmphasizedStyleBox->currentIndex()/2 == 1)?QString("italic"):QString("normal")) + ";"
            "text-align:" + ui->EmphasizedAlignmentBox->currentText() + ";"
            "color:" + ui->EmphasizedColorBox->text() + ";"
            "text-indent:" + ui->ParagraphLeftIdentBox->currentText() + "px;}"

       "Note{"
            "font-family:'" + ui->NoteNameBox->currentText() + "';"
            "font-size:" + ui->NoteSizeBox->currentText() + "pt;"
            "font-weight:" + QString::number(1000*(ui->NoteStyleBox->currentIndex()%2)) + ";"
            "line-height:" + QString::number(ui->NoteLineSpacingBox->currentText().toDouble()*100) + ";"
            "font-style:" + ((ui->NoteStyleBox->currentIndex()/2 == 1)?QString("italic"):QString("normal")) + ";"
            "text-align:" + ui->NoteAlignmentBox->currentText() + ";"
            "color:" + ui->NoteColorBox->text() + ";"
            "text-indent:" + ui->ParagraphLeftIdentBox->currentText() + "px;}"

    "</style> <body align = 'justify' bgcolor='" + ui->BackgroundColorBox->text() + "'>"
    "<TitleText>"
    "<p>Гарри Гаррисон</p>"
    "<p>«Новые приключения Стальной Крысы»</p>"
    "</TitleText>"
    "<SubtitleText>"
    "<p>Мойре и Тодду, чьи любящая помощь и поддержка позволили этой книге появиться на свет.</p>"
    "</SubtitleText>"
    "<Text>"
    "<p>Стояла заветная пора дня, посягать на которую — святотатство, один из редчайших моментов в жизни, когда все идет без сучка без задоринки. Откинувшись на спинку кресла, я включил стерео размером с комнату — сабвуферы с локомотив, пищалки, от которых зубы ноют, — и воздух напоила благодать токатты и фуги И. С. Баха.</p>"
    "<p>Моя ладонь ласкала стакан только что налитого трехсотлетнего, драгоценного бурбона, охлажденного кубиками миллионолетнего льда, доставленного с одной из внешних планет. Просто идеально! Благодушно улыбнувшись, я поднес стакан к губам.</p>"
    "<p>И тут в рай вторглось нечто чуждое, будто пульсирующая зубная боль или чуть слышный комариный зуд. С могучим Бахом схлестнулось тоненькое треньканье. Чувствуя, как губы искажает оскал, я коснулся регулятора громкости, и великий орган жалобно захлебнулся молчанием. И дверной звонок прозвучал вполне отчетливо.</p>"
    "</Text> <Emphasis><p>Динь-динь…</p></Emphasis>"
    "</body>";

    ui->TextExample->setHtml(htEx);
}

void Settings_ReaderLayout::setStyleData(const ReadingStyle style)
{
    ui->BackgroundTypeBox->setCurrentIndex(style.BackgroundType);
    if (ui->BackgroundTypeBox->currentIndex() == true)
    {
        ui->BackgroundColor->show();
        ui->BackgroundColorBox->show();
        ui->BackgroundColorBox->setStyleSheet("QPushButton{border:none;background-color:" + style.BackgroundImage + "; "
                "color:" + QColor(255 - QColor(style.BackgroundImage).red(), 255 - QColor(style.BackgroundImage).green(),
                                  255 - QColor(style.BackgroundImage).blue()).name() + ";}");
        ui->BackgroundColorBox->setText(style.BackgroundImage);
        ui->BackgroundImage->hide();
        ui->BackgroundImageBox->hide();
    }
    else
    {
        ui->BackgroundColor->hide();
        ui->BackgroundColorBox->hide();
        ui->BackgroundImage->show();
        ui->BackgroundImageBox->setCurrentText(style.BackgroundImage);
        ui->BackgroundImageBox->show();
    }

    ui->ColumnNumberBox->setCurrentText(QString::number(style.ColumnCount));
    ui->TextAntiAliasingBox->setCurrentIndex(style.TextAntiAliasing);
    ui->ParagraphLeftIdentBox->setCurrentText(QString::number(style.ParLeftTopIdent/100));
    ui->ParagraphTopIdentBox->setCurrentText(QString::number(style.ParLeftTopIdent%100));
    ui->TextLeftIdentBox->setCurrentText(QString::number(style.TextLeftRightIdent/100));
    ui->TextRightIdentBox->setCurrentText(QString::number(style.TextLeftRightIdent%100));

    ui->RegularNameBox->setCurrentFont(style.RegularTextStyle.FontFamily);
    ui->RegularSizeBox->setCurrentText(QString::number(style.RegularTextStyle.FontSize));
    ui->RegularStyleBox->setCurrentIndex(style.RegularTextStyle.FontStyle);
    ui->RegularLineSpacingBox->setCurrentText(QString::number(style.RegularTextStyle.LineSpacing));
    ui->RegularAlignmentBox->setCurrentIndex(style.RegularTextStyle.TextAlign);
    ui->RegularColorBox->setStyleSheet("QPushButton{border:none;background-color:" + style.RegularTextStyle.TextColor + "; "
            "color:" + QColor(255 - QColor(style.RegularTextStyle.TextColor).red(), 255 - QColor(style.RegularTextStyle.TextColor).green(),
                              255 - QColor(style.RegularTextStyle.TextColor).blue()).name() + ";}");
    ui->RegularColorBox->setText(style.RegularTextStyle.TextColor);

    ui->EmphasizedNameBox->setCurrentFont(style.EmphasizedTextStyle.FontFamily);
    ui->EmphasizedSizeBox->setCurrentText(QString::number(style.EmphasizedTextStyle.FontSize));
    ui->EmphasizedStyleBox->setCurrentIndex(style.EmphasizedTextStyle.FontStyle);
    ui->EmphasizedLineSpacingBox->setCurrentText(QString::number(style.EmphasizedTextStyle.LineSpacing));
    ui->EmphasizedAlignmentBox->setCurrentIndex(style.EmphasizedTextStyle.TextAlign);
    ui->EmphasizedColorBox->setStyleSheet("QPushButton{border:none;background-color:" + style.EmphasizedTextStyle.TextColor + "; "
            "color:" + QColor(255 - QColor(style.EmphasizedTextStyle.TextColor).red(), 255 - QColor(style.EmphasizedTextStyle.TextColor).green(),
                              255 - QColor(style.EmphasizedTextStyle.TextColor).blue()).name() + ";}");
    ui->EmphasizedColorBox->setText(style.EmphasizedTextStyle.TextColor);

    ui->TitleNameBox->setCurrentFont(style.TitleStyle.FontFamily);
    ui->TitleSizeBox->setCurrentText(QString::number(style.TitleStyle.FontSize));
    ui->TitleStyleBox->setCurrentIndex(style.TitleStyle.FontStyle);
    ui->TitleLineSpacingBox->setCurrentText(QString::number(style.TitleStyle.LineSpacing));
    ui->TitleAlignmentBox->setCurrentIndex(style.TitleStyle.TextAlign);
    ui->TitleColorBox->setStyleSheet("QPushButton{border:none;background-color:" + style.TitleStyle.TextColor + "; "
            "color:" + QColor(255 - QColor(style.TitleStyle.TextColor).red(), 255 - QColor(style.TitleStyle.TextColor).green(),
                              255 - QColor(style.TitleStyle.TextColor).blue()).name() + ";}");
    ui->TitleColorBox->setText(style.TitleStyle.TextColor);

    ui->SubtitleNameBox->setCurrentFont(style.SubtitleStyle.FontFamily);
    ui->SubtitleSizeBox->setCurrentText(QString::number(style.SubtitleStyle.FontSize));
    ui->SubtitleStyleBox->setCurrentIndex(style.SubtitleStyle.FontStyle);
    ui->SubtitleLineSpacingBox->setCurrentText(QString::number(style.SubtitleStyle.LineSpacing));
    ui->SubtitleAlignmentBox->setCurrentIndex(style.SubtitleStyle.TextAlign);
    ui->SubtitleColorBox->setStyleSheet("QPushButton{border:none;background-color:" + style.SubtitleStyle.TextColor + "; "
            "color:" + QColor(255 - QColor(style.SubtitleStyle.TextColor).red(), 255 - QColor(style.SubtitleStyle.TextColor).green(),
                              255 - QColor(style.SubtitleStyle.TextColor).blue()).name() + ";}");
    ui->SubtitleColorBox->setText(style.SubtitleStyle.TextColor);

    ui->NoteNameBox->setCurrentFont(style.NoteStyle.FontFamily);
    ui->NoteSizeBox->setCurrentText(QString::number(style.NoteStyle.FontSize));
    ui->NoteStyleBox->setCurrentIndex(style.NoteStyle.FontStyle);
    ui->NoteLineSpacingBox->setCurrentText(QString::number(style.NoteStyle.LineSpacing));
    ui->NoteAlignmentBox->setCurrentIndex(style.NoteStyle.TextAlign);
    ui->NoteColorBox->setStyleSheet("QPushButton{border:none;background-color:" + style.NoteStyle.TextColor + "; "
            "color:" + QColor(255 - QColor(style.NoteStyle.TextColor).red(), 255 - QColor(style.NoteStyle.TextColor).green(),
                              255 - QColor(style.NoteStyle.TextColor).blue()).name() + ";}");
    ui->NoteColorBox->setText(style.NoteStyle.TextColor);

    updateTextBox();
}

ReadingStyle Settings_ReaderLayout::getStyleData()
{
    ReadingStyle style;
    style.BackgroundType = ui->BackgroundTypeBox->currentIndex();
    if (style.BackgroundType == true)
    {
        style.BackgroundImage = ui->BackgroundColorBox->text();
    }
    else
    {
        style.BackgroundImage = ui->BackgroundImageBox->currentText();
    }

    style.TextAntiAliasing = ui->TextAntiAliasingBox->currentIndex();
    style.ParLeftTopIdent = ui->ParagraphLeftIdentBox->currentText().toInt()*100 + ui->ParagraphTopIdentBox->currentText().toInt();
    style.TextLeftRightIdent = ui->TextLeftIdentBox->currentText().toInt()*100 + ui->TextRightIdentBox->currentText().toInt();

    style.RegularTextStyle.FontFamily = ui->RegularNameBox->currentText();
    style.RegularTextStyle.FontSize = ui->RegularSizeBox->currentText().toInt();
    style.RegularTextStyle.FontStyle = ui->RegularStyleBox->currentIndex();
    style.RegularTextStyle.LineSpacing = ui->RegularLineSpacingBox->currentText().toDouble();
    style.RegularTextStyle.TextAlign = ui->RegularAlignmentBox->currentIndex();
    style.RegularTextStyle.TextColor = ui->RegularColorBox->text();

    style.TitleStyle.FontFamily = ui->TitleNameBox->currentText();
    style.TitleStyle.FontSize = ui->TitleSizeBox->currentText().toInt();
    style.TitleStyle.FontStyle = ui->TitleStyleBox->currentIndex();
    style.TitleStyle.LineSpacing = ui->TitleLineSpacingBox->currentText().toDouble();
    style.TitleStyle.TextAlign = ui->TitleAlignmentBox->currentIndex();
    style.TitleStyle.TextColor = ui->TitleColorBox->text();

    style.SubtitleStyle.FontFamily = ui->SubtitleNameBox->currentText();
    style.SubtitleStyle.FontSize = ui->SubtitleSizeBox->currentText().toInt();
    style.SubtitleStyle.FontStyle = ui->SubtitleStyleBox->currentIndex();
    style.SubtitleStyle.LineSpacing = ui->SubtitleLineSpacingBox->currentText().toDouble();
    style.SubtitleStyle.TextAlign = ui->SubtitleAlignmentBox->currentIndex();
    style.SubtitleStyle.TextColor = ui->SubtitleColorBox->text();

    style.NoteStyle.FontFamily = ui->NoteNameBox->currentText();
    style.NoteStyle.FontSize = ui->NoteSizeBox->currentText().toInt();
    style.NoteStyle.FontStyle = ui->NoteStyleBox->currentIndex();
    style.NoteStyle.LineSpacing = ui->NoteLineSpacingBox->currentText().toDouble();
    style.NoteStyle.TextAlign = ui->NoteAlignmentBox->currentIndex();
    style.NoteStyle.TextColor = ui->NoteColorBox->text();

    return style;
}

void Settings_ReaderLayout::setSettingsData(settings * const Settings)
{
    ProgramSettings = Settings;
    ui->NewStyleName->hide();
    ui->YepButton->hide();
    ui->StyleBox->addItems(ProgramSettings->getTextStylesList());

    currentTextStyle = ProgramSettings->getCurrentTextStyle();
    ui->StyleBox->setCurrentText(currentTextStyle);
    setStyleData(ProgramSettings->getNamedStyle(currentTextStyle));
}

Settings_ReaderLayout::~Settings_ReaderLayout()
{
    delete ui;
}

void Settings_ReaderLayout::on_OverallSettings_clicked()
{
    if (ui->_OverallSettingsWidget->isHidden())
        ui->_OverallSettingsWidget->show();
    else
        ui->_OverallSettingsWidget->hide();
}


void Settings_ReaderLayout::on_RegularSettings_clicked()
{
    if (ui->_RegularSettingsWidget->isHidden())
        ui->_RegularSettingsWidget->show();
    else
        ui->_RegularSettingsWidget->hide();
}

void Settings_ReaderLayout::on_EmphasizedSettings_clicked()
{
    if (ui->_EmphasizedSettingsWidget->isHidden())
        ui->_EmphasizedSettingsWidget->show();
    else
        ui->_EmphasizedSettingsWidget->hide();
}

void Settings_ReaderLayout::on_TitleSettings_clicked()
{
    if (ui->_TitleSettingsWidget->isHidden())
        ui->_TitleSettingsWidget->show();
    else
        ui->_TitleSettingsWidget->hide();
}

void Settings_ReaderLayout::on_SubtitleSettings_clicked()
{
    if (ui->_SubtitleSettingsWidget->isHidden())
        ui->_SubtitleSettingsWidget->show();
    else
        ui->_SubtitleSettingsWidget->hide();
}

void Settings_ReaderLayout::on_NoteSettings_clicked()
{
    if (ui->_NoteSettingsWidget->isHidden())
        ui->_NoteSettingsWidget->show();
    else
        ui->_NoteSettingsWidget->hide();
}

void Settings_ReaderLayout::on_YepButton_clicked()
{
    if (ui->StyleBox->findText(ui->NewStyleName->text()) != -1)
        return;
    ui->NewStyleName->hide();
    ui->StyleBox->show();
    ui->YepButton->hide();
    ui->StyleBox->addItem(ui->NewStyleName->text());
    ProgramSettings->saveStyle(ui->NewStyleName->text(), getStyleData());
    ui->StyleBox->setCurrentText(ui->NewStyleName->text());
}

void Settings_ReaderLayout::on_NopeButton_clicked()
{
    if (!ui->NewStyleName->isHidden())
    {
        ui->NewStyleName->hide();
        ui->StyleBox->show();
        ui->YepButton->hide();
    }
    else if (ui->StyleBox->currentText() != "Standart")
    {
        ProgramSettings->removeNamedStyle(ui->StyleBox->currentText());
        ui->StyleBox->removeItem(ui->StyleBox->currentIndex());
        currentTextStyle = ui->StyleBox->currentText();
        if (ProgramSettings->getTextStylesList().indexOf(currentTextStyle) != -1)
            setStyleData(ProgramSettings->getNamedStyle(currentTextStyle));
    }
}

void Settings_ReaderLayout::on_SaveButton_clicked()
{
    ProgramSettings->saveStyle(ui->StyleBox->currentText(), getStyleData());
    ProgramSettings->saveSettings();
    emit settingsChanged();
}

void Settings_ReaderLayout::on_StyleBox_activated(const QString &arg1)
{
    if (arg1 == "Add new style...")
    {
        ui->NewStyleName->show();
        ui->NewStyleName->setText("New style");
        ui->StyleBox->hide();
        ui->YepButton->show();
        return;
    }

    if (arg1 == currentTextStyle)
        return;

    ProgramSettings->saveStyle(currentTextStyle, getStyleData());
    currentTextStyle = ui->StyleBox->currentText();
    if (ProgramSettings->getTextStylesList().indexOf(currentTextStyle) != -1)
        setStyleData(ProgramSettings->getNamedStyle(currentTextStyle));
}

void Settings_ReaderLayout::on_RegularColorBox_clicked()
{
    QColor RegularColor = QColorDialog::getColor();
    if (!RegularColor.isValid())
        return;
    ui->RegularColorBox->setStyleSheet("QPushButton{border:none;background-color:" + RegularColor.name() + "; "
                                     "color:" + QColor(255 - RegularColor.red(), 255 - RegularColor.green(), 255 - RegularColor.blue()).name() + ";}");
    ui->RegularColorBox->setText(RegularColor.name());
    updateTextBox();
}

void Settings_ReaderLayout::on_TitleColorBox_clicked()
{
    QColor TitleColor = QColorDialog::getColor();
    if (!TitleColor.isValid())
        return;
    ui->TitleColorBox->setStyleSheet("QPushButton{border:none;background-color:" + TitleColor.name() + "; "
                                     "color:" + QColor(255 - TitleColor.red(), 255 - TitleColor.green(), 255 - TitleColor.blue()).name() + ";}");
    ui->TitleColorBox->setText(TitleColor.name());
    updateTextBox();
}

void Settings_ReaderLayout::on_SubtitleColorBox_clicked()
{
    QColor SubtitleColor = QColorDialog::getColor();
    if (!SubtitleColor.isValid())
        return;
    ui->SubtitleColorBox->setStyleSheet("QPushButton{border:none;background-color:" + SubtitleColor.name() + "; "
                                     "color:" + QColor(255 - SubtitleColor.red(), 255 - SubtitleColor.green(), 255 - SubtitleColor.blue()).name() + ";}");
    ui->SubtitleColorBox->setText(SubtitleColor.name());
    updateTextBox();
}

void Settings_ReaderLayout::on_NoteColorBox_clicked()
{
    QColor NoteColor = QColorDialog::getColor();
    if (!NoteColor.isValid())
        return;
    ui->NoteColorBox->setStyleSheet("QPushButton{border:none;background-color:" + NoteColor.name() + "; "
                                     "color:" + QColor(255 - NoteColor.red(), 255 - NoteColor.green(), 255 - NoteColor.blue()).name() + ";}");
    ui->NoteColorBox->setText(NoteColor.name());
    updateTextBox();
}

void Settings_ReaderLayout::on_BackgroundColorBox_clicked()
{
    QColor BackgroundColor = QColorDialog::getColor();
    if (!BackgroundColor.isValid())
        return;
    ui->BackgroundColorBox->setStyleSheet("QPushButton{border:none;background-color:" + BackgroundColor.name() + "; "
                                     "color:" + QColor(255 - BackgroundColor.red(), 255 - BackgroundColor.green(), 255 - BackgroundColor.blue()).name() + ";}");
    ui->BackgroundColorBox->setText(BackgroundColor.name());
    updateTextBox();
}

void Settings_ReaderLayout::on_EmphasizedColorBox_clicked()
{
    QColor EmphasizedColor = QColorDialog::getColor();
    if (!EmphasizedColor.isValid())
        return;
    ui->EmphasizedColorBox->setStyleSheet("QPushButton{border:none;background-color:" + EmphasizedColor.name() + "; "
                                     "color:" + QColor(255 - EmphasizedColor.red(), 255 - EmphasizedColor.green(), 255 - EmphasizedColor.blue()).name() + ";}");
    ui->EmphasizedColorBox->setText(EmphasizedColor.name());
    updateTextBox();
}

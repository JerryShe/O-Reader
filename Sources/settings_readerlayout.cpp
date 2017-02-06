#include "settings_readerlayout.h"
#include "ui_settings_readerlayout.h"
#include "settings.h"
#include <QColorDialog>
#include <QFileDialog>
#include <QDebug>
#include "styles.h"
#include <QListView>

void Settings_ReaderLayout::setLayoutStyle()
{
    QString a[5];
    setReaderLayoutStyle(a, ProgramSettings->getInterfaceStyle());
    this->setStyleSheet(a[0]);
    ui->YepButton->setStyleSheet(a[2]);
    ui->NopeButton->setStyleSheet(a[3]);
    nopeButtonStyle[0] = a[3];
    nopeButtonStyle[1] = a[4];
    ui->ReaderSettingsContent->setStyleSheet(a[0]);
    setSavebuttonStyle(savebuttonStyle, ProgramSettings->getInterfaceStyle());
    ui->SaveButton->setStyleSheet(savebuttonStyle[0]);
}

Settings_ReaderLayout::Settings_ReaderLayout(QWidget *parent) : QFrame(parent), ui(new Ui::Settings_ReaderLayout)
{
    ui->setupUi(this);

    ui->_OverallSettingsWidget->hide();
    ui->_RegularSettingsWidget->hide();
    ui->_EmphasizedSettingsWidget->hide();
    ui->_TitleSettingsWidget->hide();
    ui->_SubtitleSettingsWidget->hide();
    ui->_NoteSettingsWidget->hide();

    for(double i = 1; i <= 2.5; i += 0.1)
    {
        ui->RegularLineSpacingBox->addItem(QString::number(i));
        ui->TitleLineSpacingBox->addItem(QString::number(i));
        ui->SubtitleLineSpacingBox->addItem(QString::number(i));
        ui->NoteLineSpacingBox->addItem(QString::number(i));
        ui->EmphasizedLineSpacingBox->addItem(QString::number(i));
    }

    connect(ui->BackgroundTypeBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->ColumnNumberBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->TextAntiAliasingBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->ParagraphLeftIdentBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->ParagraphTopIdentBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->TextLeftIdentBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->TextRightIdentBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->TextTopIndentBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->TextBottomIndentBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));

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

    ui->StyleBox->setView(new QListView());

    ui->BackgroundTypeBox->setView(new QListView());
    ui->ColumnNumberBox->setView(new QListView());
    ui->TextAntiAliasingBox->setView(new QListView());
    ui->ParagraphLeftIdentBox->setView(new QListView());
    ui->ParagraphTopIdentBox->setView(new QListView());
    ui->TextLeftIdentBox->setView(new QListView());
    ui->TextRightIdentBox->setView(new QListView());
    ui->TextTopIndentBox->setView(new QListView());
    ui->TextBottomIndentBox->setView(new QListView());

    ui->RegularNameBox->setView(new QListView());
    ui->RegularSizeBox->setView(new QListView());
    ui->RegularStyleBox->setView(new QListView());
    ui->RegularLineSpacingBox->setView(new QListView());
    ui->RegularAlignmentBox->setView(new QListView());

    ui->EmphasizedNameBox->setView(new QListView());
    ui->EmphasizedSizeBox->setView(new QListView());
    ui->EmphasizedStyleBox->setView(new QListView());
    ui->EmphasizedLineSpacingBox->setView(new QListView());
    ui->EmphasizedAlignmentBox->setView(new QListView());

    ui->TitleNameBox->setView(new QListView());
    ui->TitleSizeBox->setView(new QListView());
    ui->TitleStyleBox->setView(new QListView());
    ui->TitleLineSpacingBox->setView(new QListView());
    ui->TitleAlignmentBox->setView(new QListView());

    ui->SubtitleNameBox->setView(new QListView());
    ui->SubtitleSizeBox->setView(new QListView());
    ui->SubtitleStyleBox->setView(new QListView());
    ui->SubtitleLineSpacingBox->setView(new QListView());
    ui->SubtitleAlignmentBox->setView(new QListView());

    ui->NoteNameBox->setView(new QListView());
    ui->NoteSizeBox->setView(new QListView());
    ui->NoteStyleBox->setView(new QListView());
    ui->NoteLineSpacingBox->setView(new QListView());
    ui->NoteAlignmentBox->setView(new QListView());
}

void Settings_ReaderLayout::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}

void Settings_ReaderLayout::updateTextBox()
{
    QString fileName;
    if (ui->BackgroundImageBox->text() == "Standart image")
        fileName = QUrl::fromLocalFile((QCoreApplication::applicationDirPath() + "/LibraryResources/Standart.jpg")).toString();
    else
        fileName = QUrl::fromLocalFile(currentBackgroundImage).toString();

    QString htEx = "<style type='text/css'>"
       "p{"
            "margin-top:" + ui->ParagraphTopIdentBox->currentText() + "px;"
            "margin-bottom:0px;"
            "margin-left:" + ui->TextLeftIdentBox->currentText() + "px;"
            "margin-right:" + ui->TextRightIdentBox->currentText() + "px;}"

       "TitleText{"
            "font-family:'" + ui->TitleNameBox->currentText() + "';"
            "font-size:" + ui->TitleSizeBox->currentText() + "pt;"
            "font-weight:" + ((ui->TitleStyleBox->currentIndex()%2)?"900":"100") + ";"
            "line-height:" + QString::number(ui->TitleLineSpacingBox->currentText().toDouble()*100) + ";"
            "font-style:" + ((ui->TitleStyleBox->currentIndex()/2 == 1)?QString("italic"):QString("normal")) + ";"
            "text-align:" + ProgramSettings->getTextAlignName(ui->TitleAlignmentBox->currentIndex()) + ";"
            "color:" + ui->TitleColorBox->text() + ";"
            "text-indent:" + ui->ParagraphLeftIdentBox->currentText() + "px;}"

       "SubtitleText{"
            "font-family:'" + ui->SubtitleNameBox->currentText() + "';"
            "font-size:" + ui->SubtitleSizeBox->currentText() + "pt;"
            "font-weight:" + ((ui->SubtitleStyleBox->currentIndex()%2) ? "900":"100") + ";"
            "line-height:" + QString::number(ui->SubtitleLineSpacingBox->currentText().toDouble()*100) + ";"
            "font-style:" + ((ui->SubtitleStyleBox->currentIndex()/2 == 1)?QString("italic"):QString("normal")) + ";"
            "text-align:" + ProgramSettings->getTextAlignName(ui->SubtitleAlignmentBox->currentIndex()) + ";"
            "color:" + ui->SubtitleColorBox->text() + ";"
            "text-indent:" + ui->ParagraphLeftIdentBox->currentText() + "px;}"

       "Text{"
            "font-family:'" + ui->RegularNameBox->currentText() + "';"
            "font-size:" + ui->RegularSizeBox->currentText() + "pt;"
            "font-weight:" + ((ui->RegularStyleBox->currentIndex()%2)?"900":"100") + ";"
            "line-height:" + QString::number(ui->RegularLineSpacingBox->currentText().toDouble()*100) + ";"
            "font-style:" + ((ui->RegularStyleBox->currentIndex()/2 == 1)?QString("italic"):QString("normal")) + ";"
            "text-align:" + ProgramSettings->getTextAlignName(ui->RegularAlignmentBox->currentIndex()) + ";"
            "color:" + ui->RegularColorBox->text() + ";"
            "text-indent:" + ui->ParagraphLeftIdentBox->currentText() + "px;}"

       "Emphasis{"
            "font-family:'" + ui->EmphasizedNameBox->currentText() + "';"
            "font-size:" + ui->EmphasizedSizeBox->currentText() + "pt;"
            "font-weight:" + ((ui->EmphasizedStyleBox->currentIndex()%2)?"900":"normal") + ";"
            "line-height:" + QString::number(ui->EmphasizedLineSpacingBox->currentText().toDouble()*100) + ";"
            "font-style:" + ((ui->EmphasizedStyleBox->currentIndex()/2 == 1)?QString("italic"):QString("normal")) + ";"
            "text-align:" + ProgramSettings->getTextAlignName(ui->EmphasizedAlignmentBox->currentIndex()) + ";"
            "color:" + ui->EmphasizedColorBox->text() + ";"
            "text-indent:" + ui->ParagraphLeftIdentBox->currentText() + "px;}"

       "Note{"
            "font-family:'" + ui->NoteNameBox->currentText() + "';"
            "font-size:" + ui->NoteSizeBox->currentText() + "pt;"
            "font-weight:" + ((ui->NoteStyleBox->currentIndex()%2)?"900":"100") + ";"
            "line-height:" + QString::number(ui->NoteLineSpacingBox->currentText().toDouble()*100) + ";"
            "font-style:" + ((ui->NoteStyleBox->currentIndex()/2 == 1)?QString("italic"):QString("normal")) + ";"
            "text-align:" + ProgramSettings->getTextAlignName(ui->NoteAlignmentBox->currentIndex()) + ";"
            "color:" + ui->NoteColorBox->text() + ";"
            "text-indent:" + ui->ParagraphLeftIdentBox->currentText() + "px;}"

       "body{"
            "background" + ((!ui->BackgroundColorBox->isHidden()) ? ("-color:" + ui->BackgroundColorBox->text()) : ("-image:url(" + fileName + ")")) + ";}"
    "</style> <body>"

    "<table border='0' style='"
      "table-layout: fixed;"
      "empty-cells: show;"
      "margin-top: " + ui->TextTopIndentBox->currentText() + "px;"
      "margin-bottom: " + ui->TextBottomIndentBox->currentText() + "px;"
      "margin-left:" + ui->TextLeftIdentBox->currentText() + "px;"
      "margin-right:" + ui->TextRightIdentBox->currentText() + "px;' "
    "width='100%' cellspacing='-30' cellpadding='30'>"
    "<tr>"
    "<td align = 'justify'> <Text>"
    "<TitleText>"
    "<p>Гарри Гаррисон</p>"
    "<p>«Новые приключения Стальной Крысы»</p>"
    "</TitleText>"
    "<SubtitleText>"
    "<p>Мойре и Тодду, чьи любящая помощь и поддержка позволили этой книге появиться на свет.</p>"
    "</SubtitleText>"
    "<p>Стояла заветная пора дня, посягать на которую — святотатство, один из редчайших моментов в жизни, когда все идет без сучка без задоринки. Откинувшись на спинку кресла, я включил стерео размером с комнату — сабвуферы с локомотив, пищалки, от которых зубы ноют, — и воздух напоила благодать токатты и фуги И. С. Баха.</p>"
    "<p>Моя ладонь ласкала стакан только что налитого трехсотлетнего, драгоценного бурбона, охлажденного кубиками миллионолетнего льда, доставленного с одной из внешних планет. Просто идеально! Благодушно улыбнувшись, я поднес стакан к губам.</p>"
    "<p>И тут в рай вторглось нечто чуждое, будто пульсирующая зубная боль или чуть слышный комариный зуд. С могучим Бахом схлестнулось тоненькое треньканье. Чувствуя, как губы искажает оскал, я коснулся регулятора громкости, и великий орган жалобно захлебнулся молчанием. И дверной звонок прозвучал вполне отчетливо.</p>"
    "<Emphasis><p>Динь-динь…</p></Emphasis>"
    "</Text></td></tr></body>";

    ui->TextExample->setHtml(htEx);
    emit settingsChanged(changedSignal);
}

void Settings_ReaderLayout::setStyleData(const ReadingStyle style)
{
    ui->BackgroundTypeBox->setCurrentIndex(style.BackgroundType);
    if (ui->BackgroundTypeBox->currentIndex() == true)
    {
        ui->BackgroundColorBox->setStyleSheet("QPushButton{border:none;background-color:" + style.BackgroundImage + "; "
                "color:" + QColor(255 - QColor(style.BackgroundImage).red(), 255 - QColor(style.BackgroundImage).green(),
                                  255 - QColor(style.BackgroundImage).blue()).name() + ";}");
        ui->BackgroundColorBox->setText(style.BackgroundImage);
    }
    else
    {
        ui->BackgroundColor->hide();
        ui->BackgroundColorBox->hide();
        currentBackgroundImage = style.BackgroundImage;
        QFontMetrics metrics(ui->BackgroundImageBox->font());
        ui->BackgroundImageBox->setText(metrics.elidedText(currentBackgroundImage, Qt::ElideLeft, ui->BackgroundImageBox->width()));
    }

    ui->ColumnNumberBox->setCurrentText(QString::number(style.ColumnCount));
    ui->TextAntiAliasingBox->setCurrentIndex(style.TextAntiAliasing);
    ui->ParagraphLeftIdentBox->setCurrentText(QString::number(style.ParLeftTopIdent/100));
    ui->ParagraphTopIdentBox->setCurrentText(QString::number(style.ParLeftTopIdent%100));
    ui->TextLeftIdentBox->setCurrentText(QString::number(style.TextLeftRightIdent/100));
    ui->TextRightIdentBox->setCurrentText(QString::number(style.TextLeftRightIdent%100));
    ui->TextTopIndentBox->setCurrentText(QString::number(style.TextTopBottomIdent/100));
    ui->TextBottomIndentBox->setCurrentText(QString::number(style.TextTopBottomIdent%100));

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

    ui->EmphasizedNameBox->setCurrentFont(style.EmphasizedTextStyle.FontFamily);
    ui->EmphasizedSizeBox->setCurrentText(QString::number(style.EmphasizedTextStyle.FontSize));
    ui->EmphasizedStyleBox->setCurrentIndex(style.EmphasizedTextStyle.FontStyle);
    ui->EmphasizedLineSpacingBox->setCurrentText(QString::number(style.EmphasizedTextStyle.LineSpacing));
    ui->EmphasizedAlignmentBox->setCurrentIndex(style.EmphasizedTextStyle.TextAlign);
    ui->EmphasizedColorBox->setStyleSheet("QPushButton{border:none;background-color:" + style.EmphasizedTextStyle.TextColor + "; "
            "color:" + QColor(255 - QColor(style.EmphasizedTextStyle.TextColor).red(), 255 - QColor(style.EmphasizedTextStyle.TextColor).green(),
                              255 - QColor(style.EmphasizedTextStyle.TextColor).blue()).name() + ";}");
    ui->EmphasizedColorBox->setText(style.EmphasizedTextStyle.TextColor);

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
        style.BackgroundImage = currentBackgroundImage;
    }

    style.ColumnCount = ui->ColumnNumberBox->currentText().toInt();
    style.TextAntiAliasing = ui->TextAntiAliasingBox->currentIndex();
    style.ParLeftTopIdent = ui->ParagraphLeftIdentBox->currentText().toShort()*100 + ui->ParagraphTopIdentBox->currentText().toShort();
    style.TextLeftRightIdent = ui->TextLeftIdentBox->currentText().toShort()*100 + ui->TextRightIdentBox->currentText().toShort();
    style.TextTopBottomIdent = ui->TextTopIndentBox->currentText().toShort()*100 + ui->TextBottomIndentBox->currentText().toShort();

    style.RegularTextStyle.FontFamily = ui->RegularNameBox->currentText();
    style.RegularTextStyle.FontSize = ui->RegularSizeBox->currentText().toShort();
    style.RegularTextStyle.FontStyle = ui->RegularStyleBox->currentIndex();
    style.RegularTextStyle.LineSpacing = ui->RegularLineSpacingBox->currentText().toDouble();
    style.RegularTextStyle.TextAlign = ui->RegularAlignmentBox->currentIndex();
    style.RegularTextStyle.TextColor = ui->RegularColorBox->text();

    style.TitleStyle.FontFamily = ui->TitleNameBox->currentText();
    style.TitleStyle.FontSize = ui->TitleSizeBox->currentText().toShort();
    style.TitleStyle.FontStyle = ui->TitleStyleBox->currentIndex();
    style.TitleStyle.LineSpacing = ui->TitleLineSpacingBox->currentText().toDouble();
    style.TitleStyle.TextAlign = ui->TitleAlignmentBox->currentIndex();
    style.TitleStyle.TextColor = ui->TitleColorBox->text();

    style.SubtitleStyle.FontFamily = ui->SubtitleNameBox->currentText();
    style.SubtitleStyle.FontSize = ui->SubtitleSizeBox->currentText().toShort();
    style.SubtitleStyle.FontStyle = ui->SubtitleStyleBox->currentIndex();
    style.SubtitleStyle.LineSpacing = ui->SubtitleLineSpacingBox->currentText().toDouble();
    style.SubtitleStyle.TextAlign = ui->SubtitleAlignmentBox->currentIndex();
    style.SubtitleStyle.TextColor = ui->SubtitleColorBox->text();

    style.NoteStyle.FontFamily = ui->NoteNameBox->currentText();
    style.NoteStyle.FontSize = ui->NoteSizeBox->currentText().toShort();
    style.NoteStyle.FontStyle = ui->NoteStyleBox->currentIndex();
    style.NoteStyle.LineSpacing = ui->NoteLineSpacingBox->currentText().toDouble();
    style.NoteStyle.TextAlign = ui->NoteAlignmentBox->currentIndex();
    style.NoteStyle.TextColor = ui->NoteColorBox->text();

    style.EmphasizedTextStyle.FontFamily = ui->EmphasizedNameBox->currentText();
    style.EmphasizedTextStyle.FontSize = ui->EmphasizedSizeBox->currentText().toShort();
    style.EmphasizedTextStyle.FontStyle = ui->EmphasizedStyleBox->currentIndex();
    style.EmphasizedTextStyle.LineSpacing = ui->EmphasizedLineSpacingBox->currentText().toDouble();
    style.EmphasizedTextStyle.TextAlign = ui->EmphasizedAlignmentBox->currentIndex();
    style.EmphasizedTextStyle.TextColor = ui->EmphasizedColorBox->text();

    return style;
}

void Settings_ReaderLayout::setSettingsData()
{
    ProgramSettings = settings::getSettings();
    setLayoutStyle();
    ui->NewStyleName->hide();
    ui->YepButton->hide();
    ui->StyleBox->addItems(ProgramSettings->getTextStylesList());

    currentTextStyle = ProgramSettings->getCurrentTextStyle();
    ui->StyleBox->setCurrentText(currentTextStyle);
    setStyleData(ProgramSettings->getNamedStyle(currentTextStyle));
    changedSignal = 1;
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
    ui->NopeButton->setStyleSheet(nopeButtonStyle[0]);
}

void Settings_ReaderLayout::on_NopeButton_clicked()
{
    if (!ui->NewStyleName->isHidden())
    {
        ui->NopeButton->setStyleSheet(nopeButtonStyle[0]);
        ui->NewStyleName->hide();
        ui->StyleBox->show();
        ui->YepButton->hide();
    }
    else if (ui->StyleBox->currentText() != "Standart" && ui->StyleBox->currentText() != QObject::tr("Add new style..."))
    {
        AnswerDialog *answer_window = new AnswerDialog(ui->NopeButton->mapToGlobal(QPoint(ui->NopeButton->width(), ui->NopeButton->height())),
                                                       QObject::tr("Delete style?"),
                                                       ProgramSettings->getInterfaceStyle(),
                                                       this);
        answer_window->show();

        if (answer_window->exec() == QDialog::Accepted)
        {
            ProgramSettings->removeNamedStyle(ui->StyleBox->currentText());
            ui->StyleBox->removeItem(ui->StyleBox->currentIndex());
            currentTextStyle = ui->StyleBox->currentText();
            if (ProgramSettings->getTextStylesList().indexOf(currentTextStyle) != -1)
                setStyleData(ProgramSettings->getNamedStyle(currentTextStyle));
        }
        delete answer_window;
    }
}

void Settings_ReaderLayout::on_SaveButton_clicked()
{
    ProgramSettings->saveStyle(ui->StyleBox->currentText(), getStyleData());
    ProgramSettings->saveSettings();
    emit settingsChanged(0);
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

void Settings_ReaderLayout::on_BackgroundImageBox_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, QObject::tr("Set image"), "", "(*.jpeg *.jpg *.png)");
    if (file == "")
        return;
    currentBackgroundImage = file;
    QFontMetrics metrics(ui->BackgroundImageBox->font());
    ui->BackgroundImageBox->setText(metrics.elidedText(currentBackgroundImage, Qt::ElideLeft, ui->BackgroundImageBox->width()));
    updateTextBox();
}

void Settings_ReaderLayout::setSavebuttonView(int type)
{
    if (type)
        ui->SaveButton->setStyleSheet(savebuttonStyle[1]);
    else
        ui->SaveButton->setStyleSheet(savebuttonStyle[0]);
}

void Settings_ReaderLayout::on_BackgroundTypeBox_currentIndexChanged(int index)
{
    if (index == 0)
    {
        ui->BackgroundColor->hide();
        ui->BackgroundColorBox->hide();
        ui->BackgroundImage->show();
        ui->BackgroundImageBox->show();
    }
    if (index == 1)
    {
        ui->BackgroundColor->show();
        ui->BackgroundColorBox->show();
        ui->BackgroundImage->hide();
        ui->BackgroundImageBox->hide();
    }
}

void Settings_ReaderLayout::on_StyleBox_activated(int index)
{
    if (index == 0)
    {
        ui->NewStyleName->show();
        ui->NewStyleName->setText(QObject::tr("New style"));
        ui->StyleBox->hide();
        ui->YepButton->show();
        ui->NopeButton->setStyleSheet(nopeButtonStyle[1]);
        return;
    }

    if (ui->StyleBox->currentText() == currentTextStyle)
        return;

    ProgramSettings->saveStyle(currentTextStyle, getStyleData());
    currentTextStyle = ui->StyleBox->currentText();
    if (ProgramSettings->getTextStylesList().indexOf(currentTextStyle) != -1)
        setStyleData(ProgramSettings->getNamedStyle(currentTextStyle));
}

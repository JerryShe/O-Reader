#include "settings_readerlayout.h"
#include "ui_settings_readerlayout.h"
#include "settings.h"
#include "styles.h"

#include <QListView>
#include <QColorDialog>
#include <QFileDialog>

#include <QDebug>



void Settings_ReaderLayout::setStyle()
{
    QString a[5];
    setReaderLayoutStyle(a, ProgramSettings->getInterfaceStyle());
    this->setStyleSheet(a[0]);
    ui->StyleBox->setStyleSheet(a[0]);

    ui->YepButton->setStyleSheet(a[1]);
    yepButtonStyle[0] = a[1];
    yepButtonStyle[1] = a[2];

    ui->NopeButton->setStyleSheet(a[3]);
    nopeButtonStyle[0] = a[3];
    nopeButtonStyle[1] = a[4];

    ui->ReaderSettingsContent->setStyleSheet(a[0]);


    setSavebuttonStyle(savebuttonStyle, ProgramSettings->getInterfaceStyle());
    ui->SaveButton->setStyleSheet(savebuttonStyle[0]);

    setBackgroundWindowColor(a, ProgramSettings->getInterfaceStyle());
    ui->ReaderSettingArea->setStyleSheet(a[0]);
}


Settings_ReaderLayout::Settings_ReaderLayout(QWidget *parent) : QFrame(parent), ui(new Ui::Settings_ReaderLayout)
{
    ui->setupUi(this);

    ui->_OverallSettingsWidget->hide();


    connect(ui->BackgroundTypeBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->ColumnNumberBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->TextAntiAliasingBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->ParagraphLeftIdentBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->ParagraphTopIdentBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->TextLeftIdentBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->TextRightIdentBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->TextTopIndentBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->TextBottomIndentBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));

    connect(ui->RegularStyle, SIGNAL(settingsUpdate()), this, SLOT(updateTextBox()));
    connect(ui->TitleStyle, SIGNAL(settingsUpdate()), this, SLOT(updateTextBox()));
    connect(ui->EmphasizedStyle, SIGNAL(settingsUpdate()), this, SLOT(updateTextBox()));
    connect(ui->SubtitleStyle, SIGNAL(settingsUpdate()), this, SLOT(updateTextBox()));
    connect(ui->NoteStyle, SIGNAL(settingsUpdate()), this, SLOT(updateTextBox()));
    connect(ui->EpigraphStyle, SIGNAL(settingsUpdate()), this, SLOT(updateTextBox()));
    connect(ui->PoemStyle, SIGNAL(settingsUpdate()), this, SLOT(updateTextBox()));
    connect(ui->CiteStyle, SIGNAL(settingsUpdate()), this, SLOT(updateTextBox()));


    ui->RegularStyle->setStyleName(QObject::tr("Regular text"));
    ui->TitleStyle->setStyleName(QObject::tr("Title text"));
    ui->EmphasizedStyle->setStyleName(QObject::tr("Emphasized text"));
    ui->SubtitleStyle->setStyleName(QObject::tr("Subtitle text"));
    ui->NoteStyle->setStyleName(QObject::tr("Notes"));
    ui->EpigraphStyle->setStyleName(QObject::tr("Epigraph text"));
    ui->PoemStyle->setStyleName(QObject::tr("Poems"));
    ui->CiteStyle->setStyleName(QObject::tr("Citations"));

    ui->StyleBox->setView(new QListView());
    connect(ui->StyleBox, SIGNAL(activated(QString)), this, SLOT(on_StyleBox_activated(QString)));

    ui->BackgroundTypeBox->setView(new QListView());
    ui->ColumnNumberBox->setView(new QListView());
    ui->TextAntiAliasingBox->setView(new QListView());
    ui->ParagraphLeftIdentBox->setView(new QListView());
    ui->ParagraphTopIdentBox->setView(new QListView());
    ui->TextLeftIdentBox->setView(new QListView());
    ui->TextRightIdentBox->setView(new QListView());
    ui->TextTopIndentBox->setView(new QListView());
    ui->TextBottomIndentBox->setView(new QListView());

    ui->TextExample->viewport()->setAutoFillBackground(false);
    ui->TextExample->setAttribute( Qt::WA_TranslucentBackground, true );
}


void Settings_ReaderLayout::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}


void Settings_ReaderLayout::updateTextBox()
{
    QString htEx = "<style type='text/css'>"
       "p{"
            "margin-top:" + ui->ParagraphTopIdentBox->currentText() + "px;"
            "margin-bottom:0px;"
            "margin-left:" + ui->TextLeftIdentBox->currentText() + "px;"
            "margin-right:" + ui->TextRightIdentBox->currentText() + "px;"
            "text-indent:" + ui->ParagraphLeftIdentBox->currentText() + "px;}"

       "TitleText{"
            + ui->TitleStyle->getHTMLStyle() + "}"


       "subtitle{"
            + ui->SubtitleStyle->getHTMLStyle() + "}"

       "Text{"
            + ui->RegularStyle->getHTMLStyle() + "}"

       "emphasis{"
            + ui->EmphasizedStyle->getHTMLStyle() + "}"

       "Note{"
            + ui->NoteStyle->getHTMLStyle() + "}"

       "epigraph{"
            + ui->EpigraphStyle->getHTMLStyle() + "}"

       "poem{"
            + ui->PoemStyle->getHTMLStyle() + "}"

       "cite{"
            + ui->CiteStyle->getHTMLStyle() + "}"

       + ((!ui->BackgroundColorBox->isHidden()) ? ("body{background-color:" + ui->BackgroundColorBox->text()) : ("")) + ";}"

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
    "<subtitle>"
    "<p>Мойре и Тодду, чьи любящая помощь и поддержка позволили этой книге появиться на свет.</p>"
    "</subtitle>"
    "<p>Стояла заветная пора дня, посягать на которую — святотатство, один из редчайших моментов в жизни, когда все идет без сучка без задоринки. Откинувшись на спинку кресла, я включил стерео размером с комнату — сабвуферы с локомотив, пищалки, от которых зубы ноют, — и воздух напоила благодать токатты и фуги И. С. Баха.</p>"
    "<p>Моя ладонь ласкала стакан только что налитого трехсотлетнего, драгоценного бурбона, охлажденного кубиками миллионолетнего льда, доставленного с одной из внешних планет. Просто идеально! Благодушно улыбнувшись, я поднес стакан к губам.</p>"
    "<p>И тут в рай вторглось нечто чуждое, будто пульсирующая зубная боль или чуть слышный комариный зуд. С могучим Бахом схлестнулось тоненькое треньканье. Чувствуя, как губы искажает оскал, я коснулся регулятора громкости, и великий орган жалобно захлебнулся молчанием. И дверной звонок прозвучал вполне отчетливо.</p>"
    "<emphasis><p>Динь-динь…</p></emphasis>"
    "</Text></td></tr></body>";

    ui->TextExample->setHtml(htEx);
    emit settingsChanged(changedSignal);
}

void Settings_ReaderLayout::setStyleData(const ReadingProfile &profile)
{
    ui->BackgroundTypeBox->setCurrentIndex(profile.BackgroundType);
    if (ui->BackgroundTypeBox->currentIndex() == 1)
    {
        ui->BackgroundColorBox->setStyleSheet("QPushButton{border:none;background-color:" + profile.BackgroundImage + "; "
                "color:" + QColor(255 - QColor(profile.BackgroundImage).red(), 255 - QColor(profile.BackgroundImage).green(),
                                  255 - QColor(profile.BackgroundImage).blue()).name() + ";}");

        ui->BackgroundColorBox->setText(profile.BackgroundImage);
    }
    else
    {
        ui->BackgroundColor->hide();
        ui->BackgroundColorBox->hide();
        currentBackgroundImage = profile.BackgroundImage;
        QFontMetrics metrics(ui->BackgroundImageBox->font());
        ui->BackgroundImageBox->setText(metrics.elidedText(currentBackgroundImage, Qt::ElideLeft, ui->BackgroundImageBox->width()));
        ui->TextBackground->setStyleSheet("#TextBackground{background-image:url(" + currentBackgroundImage + ");}");
    }

    ui->ColumnNumberBox->setCurrentText(QString::number(profile.ColumnCount));
    ui->TextAntiAliasingBox->setCurrentIndex(profile.TextAntiAliasing);
    ui->ParagraphLeftIdentBox->setCurrentText(QString::number(profile.ParLeftTopIdent/100));
    ui->ParagraphTopIdentBox->setCurrentText(QString::number(profile.ParLeftTopIdent%100));
    ui->TextLeftIdentBox->setCurrentText(QString::number(profile.TextLeftRightIdent/100));
    ui->TextRightIdentBox->setCurrentText(QString::number(profile.TextLeftRightIdent%100));
    ui->TextTopIndentBox->setCurrentText(QString::number(profile.TextTopBottomIdent/100));
    ui->TextBottomIndentBox->setCurrentText(QString::number(profile.TextTopBottomIdent%100));


    ui->RegularStyle->setStyleData(profile.RegularStyle);
    ui->TitleStyle->setStyleData(profile.TitleStyle);
    ui->SubtitleStyle->setStyleData(profile.SubtitleStyle);
    ui->EmphasizedStyle->setStyleData(profile.EmphasizedStyle);
    ui->NoteStyle->setStyleData(profile.NoteStyle);
    ui->PoemStyle->setStyleData(profile.PoemStyle);
    ui->CiteStyle->setStyleData(profile.CiteStyle);
    ui->EpigraphStyle->setStyleData(profile.EpigraphStyle);

    updateTextBox();
}

ReadingProfile Settings_ReaderLayout::getStyleData()
{
    ReadingProfile profile;
    profile.BackgroundType = ui->BackgroundTypeBox->currentIndex();
    if (profile.BackgroundType == true)
        profile.BackgroundImage = ui->BackgroundColorBox->text();
    else
        profile.BackgroundImage = currentBackgroundImage;

    profile.ColumnCount = ui->ColumnNumberBox->currentText().toInt();
    profile.TextAntiAliasing = ui->TextAntiAliasingBox->currentIndex();
    profile.ParLeftTopIdent = ui->ParagraphLeftIdentBox->currentText().toShort()*100 + ui->ParagraphTopIdentBox->currentText().toShort();
    profile.TextLeftRightIdent = ui->TextLeftIdentBox->currentText().toShort()*100 + ui->TextRightIdentBox->currentText().toShort();
    profile.TextTopBottomIdent = ui->TextTopIndentBox->currentText().toShort()*100 + ui->TextBottomIndentBox->currentText().toShort();

    profile.RegularStyle = ui->RegularStyle->getStyleData();
    profile.TitleStyle = ui->TitleStyle->getStyleData();
    profile.SubtitleStyle = ui->SubtitleStyle->getStyleData();
    profile.EmphasizedStyle = ui->EmphasizedStyle->getStyleData();
    profile.NoteStyle = ui->NoteStyle->getStyleData();
    profile.CiteStyle = ui->CiteStyle->getStyleData();
    profile.EpigraphStyle = ui->EpigraphStyle->getStyleData();
    profile.PoemStyle = ui->PoemStyle->getStyleData();

    return profile;
}


void Settings_ReaderLayout::setSettingsData()
{
    ProgramSettings = Settings::getSettings();
    setStyle();
    ui->NewStyleName->hide();
    ui->StyleBox->addItems(ProgramSettings->getReadProfilesList());

    currentTextStyle = ProgramSettings->getCurrentReadProfileName();
    ui->StyleBox->setCurrentText(currentTextStyle);

    setStyleData(ProgramSettings->getNamedReadProfile(currentTextStyle));
    changedSignal = 1;
}


Settings_ReaderLayout::~Settings_ReaderLayout()
{
    delete ui;
}


void Settings_ReaderLayout::on_YepButton_clicked()
{
    if (ui->NewStyleName->isHidden())
    {
        ui->NewStyleName->show();
        ui->NewStyleName->setText(QObject::tr("New style"));
        ui->StyleBox->hide();

        ui->NopeButton->setStyleSheet(nopeButtonStyle[1]);
        ui->YepButton->setStyleSheet(yepButtonStyle[1]);
    }
    else
    {
        if (ui->StyleBox->findText(ui->NewStyleName->text()) != -1)
            return;

        ui->NewStyleName->hide();
        ui->StyleBox->show();

        ui->StyleBox->addItem(ui->NewStyleName->text());
        ProgramSettings->saveReadProfile(ui->NewStyleName->text(), getStyleData());
        ui->StyleBox->setCurrentText(ui->NewStyleName->text());
        currentTextStyle = ui->NewStyleName->text();
        updateTextBox();

        ui->NopeButton->setStyleSheet(nopeButtonStyle[0]);
        ui->YepButton->setStyleSheet(yepButtonStyle[0]);
    }
}


void Settings_ReaderLayout::on_NopeButton_clicked()
{
    if (!ui->NewStyleName->isHidden())
    {
        ui->NopeButton->setStyleSheet(nopeButtonStyle[0]);
        ui->NewStyleName->hide();
        ui->StyleBox->show();
    }
    else if (ui->StyleBox->currentText() != "Standart")
    {
        AnswerDialog *answer_window = new AnswerDialog(ui->NopeButton->mapToGlobal(QPoint(ui->NopeButton->width(), ui->NopeButton->height())),
                                                       QObject::tr("Delete style?"),
                                                       ProgramSettings->getInterfaceStyle(),
                                                       this);
        answer_window->show();

        if (answer_window->exec() == QDialog::Accepted)
        {
            ProgramSettings->removeNamedReadProfile(ui->StyleBox->currentText());
            ui->StyleBox->removeItem(ui->StyleBox->currentIndex());
            currentTextStyle = ui->StyleBox->currentText();
            if (ProgramSettings->getReadProfilesList().indexOf(currentTextStyle) != -1)
                setStyleData(ProgramSettings->getNamedReadProfile(currentTextStyle));
        }
        delete answer_window;
    }
}


void Settings_ReaderLayout::on_SaveButton_clicked()
{
    ProgramSettings->saveReadProfile(ui->StyleBox->currentText(), getStyleData());
    ProgramSettings->saveSettings();
    emit settingsChanged(0);
}


void Settings_ReaderLayout::on_BackgroundColorBox_clicked()
{
    QColor BackgroundColor = QColorDialog::getColor();
    if (!BackgroundColor.isValid())
        return;
    ui->BackgroundColorBox->setStyleSheet("QPushButton{border:none;background-color:" + BackgroundColor.name() + "; "
                                     "color:" + QColor(255 - BackgroundColor.red(), 255 - BackgroundColor.green(), 255 - BackgroundColor.blue()).name() + ";}");
    ui->BackgroundColorBox->setText(BackgroundColor.name());

    ui->TextBackground->setStyleSheet("");

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

    ui->TextBackground->setStyleSheet("#TextBackground{background-image:url(" + currentBackgroundImage + ");}");
}


void Settings_ReaderLayout::setSavebuttonView(const int &type)
{
    if (type)
        ui->SaveButton->setStyleSheet(savebuttonStyle[1]);
    else
        ui->SaveButton->setStyleSheet(savebuttonStyle[0]);
}


void Settings_ReaderLayout::on_BackgroundTypeBox_currentIndexChanged(int index)
{
    if (index == 0 && ui->BackgroundImageBox->isHidden())
    {
        ui->BackgroundImageBox->setText(QObject::tr("No image"));
        ui->TextBackground->setStyleSheet("");
        ui->BackgroundColor->hide();
        ui->BackgroundColorBox->hide();
        ui->BackgroundImage->show();
        ui->BackgroundImageBox->show();
    }
    else
    {
        ui->BackgroundColorBox->setStyleSheet("#BackgroundColorBox{background-color: white; color: black;}");
        ui->BackgroundColorBox->setText("#ffffff");
        ui->BackgroundColor->show();
        ui->BackgroundColorBox->show();
        ui->BackgroundImage->hide();
        ui->BackgroundImageBox->hide();
        updateTextBox();
    } 
}


void Settings_ReaderLayout::on_OverallSettings_clicked()
{
    if (ui->_OverallSettingsWidget->isHidden())
        ui->_OverallSettingsWidget->show();
    else
        ui->_OverallSettingsWidget->hide();
}


void Settings_ReaderLayout::on_StyleBox_activated(const QString &styleName)
{
    if (styleName == currentTextStyle)
        return;


    ProgramSettings->saveReadProfile(currentTextStyle, getStyleData());
    currentTextStyle = styleName;

    if (ProgramSettings->getReadProfilesList().indexOf(currentTextStyle) != -1)
    {
        setStyleData(ProgramSettings->getNamedReadProfile(currentTextStyle));
        ProgramSettings->setCurrentReadProfile(currentTextStyle);
    }
}

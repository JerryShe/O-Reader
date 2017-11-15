#include "main_window/settings/reading/settings_readerlayout.h"
#include "ui_settings_readerlayout.h"
#include "data_handlers/settings_handler.h"

#include "styles.h"

#include <QListView>
#include <QColorDialog>
#include <QFileDialog>
#include <QScroller>
#include <QTouchDevice>
#include <QScrollBar>

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

    ui->TextExample->viewport()->setAutoFillBackground(false);
    ui->TextExample->setAttribute(Qt::WA_TranslucentBackground, true);

    for (int i = 5; i <= 300; i++)
        ui->TextColumnsIndentBox->addItem(QString::number(i));


    connect(ui->BackgroundTypeBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->ColumnNumberBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
    connect(ui->TextColumnsIndentBox, SIGNAL(activated(QString)), this, SLOT(updateTextBox()));
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


    ui->StyleBox->setView(new QListView(this));
    connect(ui->StyleBox, SIGNAL(activated(QString)), this, SLOT(on_StyleBox_activated(QString)));

    ui->BackgroundTypeBox->setView(new QListView(this));
    ui->ColumnNumberBox->setView(new QListView(this));
    ui->TextColumnsIndentBox->setView(new QListView(this));
    ui->TextAntiAliasingBox->setView(new QListView(this));
    ui->ParagraphLeftIdentBox->setView(new QListView(this));
    ui->ParagraphTopIdentBox->setView(new QListView(this));
    ui->TextLeftIdentBox->setView(new QListView(this));
    ui->TextRightIdentBox->setView(new QListView(this));
    ui->TextTopIndentBox->setView(new QListView(this));
    ui->TextBottomIndentBox->setView(new QListView(this));


    ui->TextExample->viewport()->setAutoFillBackground(false);
    ui->TextExample->setAttribute( Qt::WA_TranslucentBackground, true );


    if (QTouchDevice::devices().size())
    {
        QScroller::grabGesture(ui->ReaderSettingArea->viewport(), QScroller::LeftMouseButtonGesture);
        ui->ReaderSettingArea->verticalScrollBar()->setSingleStep(1);

        QScroller::grabGesture(ui->TextExample->viewport(), QScroller::LeftMouseButtonGesture);
        ui->TextExample->verticalScrollBar()->setSingleStep(1);


        QScroller::grabGesture(ui->StyleBox->view()->viewport(), QScroller::LeftMouseButtonGesture);
        ui->StyleBox->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        QScroller::grabGesture(ui->BackgroundTypeBox->view()->viewport(), QScroller::LeftMouseButtonGesture);
        ui->BackgroundTypeBox->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        QScroller::grabGesture(ui->ColumnNumberBox->view()->viewport(), QScroller::LeftMouseButtonGesture);
        ui->ColumnNumberBox->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        QScroller::grabGesture(ui->TextColumnsIndentBox->view()->viewport(), QScroller::LeftMouseButtonGesture);
        ui->TextColumnsIndentBox->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        QScroller::grabGesture(ui->TextAntiAliasingBox->view()->viewport(), QScroller::LeftMouseButtonGesture);
        ui->TextAntiAliasingBox->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        QScroller::grabGesture(ui->ParagraphLeftIdentBox->view()->viewport(), QScroller::LeftMouseButtonGesture);
        ui->ParagraphLeftIdentBox->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        QScroller::grabGesture(ui->ParagraphTopIdentBox->view()->viewport(), QScroller::LeftMouseButtonGesture);
        ui->ParagraphLeftIdentBox->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        QScroller::grabGesture(ui->TextLeftIdentBox->view()->viewport(), QScroller::LeftMouseButtonGesture);
        ui->TextLeftIdentBox->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        QScroller::grabGesture(ui->TextRightIdentBox->view()->viewport(), QScroller::LeftMouseButtonGesture);
        ui->TextRightIdentBox->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        QScroller::grabGesture(ui->TextTopIndentBox->view()->viewport(), QScroller::LeftMouseButtonGesture);
        ui->TextTopIndentBox->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        QScroller::grabGesture(ui->TextBottomIndentBox->view()->viewport(), QScroller::LeftMouseButtonGesture);
        ui->TextBottomIndentBox->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    }
}


Settings_ReaderLayout::~Settings_ReaderLayout()
{
    delete ui;
}


void Settings_ReaderLayout::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}


void Settings_ReaderLayout::updateTextBox()
{
    QString topParMargin = "margin-top:" + ui->ParagraphTopIdentBox->currentText()  + "px;";

    QString htEx = "<style type='text/css'>"
       "p{"
            "margin-bottom:0px;"
            + topParMargin +
            "margin-left:" + ui->TextLeftIdentBox->currentText() + "px;"
            "margin-right:" + ui->TextRightIdentBox->currentText() + "px;"
            "text-indent:" + ui->ParagraphLeftIdentBox->currentText() + "px;}"

       "TitleText{"
            + topParMargin
            + ui->TitleStyle->getHTMLStyle() + "}"

       "subtitle{"
            + topParMargin
            + ui->SubtitleStyle->getHTMLStyle() + "}"

       "Text{"
            + topParMargin
            + ui->RegularStyle->getHTMLStyle() + "}"

       "emphasis{"
            + topParMargin
            + ui->EmphasizedStyle->getHTMLStyle() + "}"

       "a[type = 'note']{"
            + "vertical-align: super;"
            + topParMargin
            + ui->NoteStyle->getHTMLStyle() + "}"

       "epigraph{"
            + topParMargin
            + ui->EpigraphStyle->getHTMLStyle() + "}"

       "poem{"
            + topParMargin
            + ui->PoemStyle->getHTMLStyle() + "}"

       "cite{"
            + topParMargin
            + ui->CiteStyle->getHTMLStyle() + "}"

    "</style> <body style='margin-top: " + ui->TextTopIndentBox->currentText() + "px'>"

    "<td align = 'justify'> <Text>"
    "<TitleText>"
    "<p>Это заглавный текст</p>"
    "</TitleText>"
    "<epigraph>"
    "<p>Это эпиграф</p>"
    "</epigraph>"
    "<subtitle>"
    "<p>А это подзаголовок</p>"
    "</subtitle>"

    "<p>Похоже нам надо немного простого текста... </p>"
    "<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua."
    " Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat."
    " Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur."
    " Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.</p>"
    "<emphasis><p>Да и курсив не помешает.<a type='note' l:href='#FbAutId_1'>Заметка она такая</a></p></emphasis>"
    "<p>Стихи:</p>"
            "<poem> <p> Ламберт, Ламберт</p>"
            "<p>Хер моржовый</p>"
            "<p>Ламберт, Ламберт</p>"
            "<p>Вредный хуй</p></poem>"
            "<p><cite>Геральт из Ривии</cite></p>"
    "</Text></body>";

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
        ui->TextBackground->setStyleSheet("#TextBackground{background-color:" + profile.BackgroundImage + ";}");
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
    ui->TextColumnsIndentBox->setCurrentText(QString::number(profile.ColumnIndent));
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
    profile.ColumnIndent = ui->TextColumnsIndentBox->currentText().toInt();
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
    ProgramSettings = SettingsHandler::getSettings();
    setStyle();
    ui->NewStyleName->hide();
    ui->StyleBox->addItems(ProgramSettings->getReadProfilesList());

    currentTextStyle = ProgramSettings->getCurrentReadProfileName();
    ui->StyleBox->setCurrentText(currentTextStyle);

    setStyleData(ProgramSettings->getNamedReadProfile(currentTextStyle));
    changedSignal = 1;
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

    ui->TextBackground->setStyleSheet("#TextBackground{background-color:" + BackgroundColor.toRgb().name() + ";}");

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
    ui->TextBackground->setStyleSheet("#TextBackground{background-color:rgb(255,255,255);}");
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

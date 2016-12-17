#include "reading_window.h"
#include "ui_readingwindow.h"
#include "books.h"
#include "answer_dialog.h"
#include "settings_layout.h"
#include "synchronization_layout.h"
#include "search_window.h"
#include "settings.h"
#include "styles.h"

#include <QTimer>
#include <styles.h>
#include <QMouseEvent>
#include <QWindow>

#include <QThread>

#include <QDebug>

TextParser::TextParser(Book boo, settings* PSettings)
{
    book = boo;
    ProgramSettings = PSettings;
    ReadingStyle CurStyle = ProgramSettings->getCurrentTextStyleElem();

    QString fileName;
    if (CurStyle.BackgroundType == false)
        fileName = QUrl::fromLocalFile(CurStyle.BackgroundImage).toString();

    PageHTMLHeader = "<style type='text/css'>"
                     "p{"
                          "text-align = justify;"
                          "margin-top:" + QString::number(CurStyle.ParLeftTopIdent%100) + "px;}"

                     "TitleText{"
                          "font-family:'" + CurStyle.TitleStyle.FontFamily + "';"
                          "font-size:" + QString::number(CurStyle.TitleStyle.FontSize) + "pt;"
                          "font-weight:" + QString::number(1000*(CurStyle.TitleStyle.FontStyle%2)) + ";"
                          "line-height:" + QString::number(CurStyle.TitleStyle.LineSpacing*100) + ";"
                          "font-style:" + ((CurStyle.TitleStyle.FontStyle/2 == 1)?QString("italic"):QString("normal")) + ";"
                          "text-align:" + CurStyle.TitleStyle.TextAlign.toLower() + ";"
                          "color:" + CurStyle.TitleStyle.TextColor + ";"
                          "text-indent:" + QString::number(CurStyle.ParLeftTopIdent/100) + "px;}"

                     "SubtitleText{"
                          "font-family:'" + CurStyle.SubtitleStyle.FontFamily + "';"
                          "font-size:" + QString::number(CurStyle.SubtitleStyle.FontSize) + "pt;"
                          "font-weight:" + QString::number(1000*(CurStyle.SubtitleStyle.FontStyle%2)) + ";"
                          "line-height:" + QString::number(CurStyle.SubtitleStyle.LineSpacing*100) + ";"
                          "font-style:" + ((CurStyle.SubtitleStyle.FontStyle/2 == 1)?QString("italic"):QString("normal")) + ";"
                          "text-align:" + CurStyle.SubtitleStyle.TextAlign.toLower() + ";"
                          "color:" + CurStyle.SubtitleStyle.TextColor + ";"
                          "text-indent:" + QString::number(CurStyle.ParLeftTopIdent/100) + "px;}"

                     "Text{"
                          "font-family:'" + CurStyle.RegularTextStyle.FontFamily + "';"
                          "font-size:" + QString::number(CurStyle.RegularTextStyle.FontSize) + "pt;"
                          "font-weight:" + QString::number(1000*(CurStyle.RegularTextStyle.FontStyle%2)) + ";"
                          "line-height:" + QString::number(CurStyle.RegularTextStyle.LineSpacing*100) + ";"
                          "font-style:" + ((CurStyle.RegularTextStyle.FontStyle/2 == 1)?QString("italic"):QString("normal")) + ";"
                          "text-align:" + CurStyle.RegularTextStyle.TextAlign.toLower() + ";"
                          "color:" + CurStyle.RegularTextStyle.TextColor + ";"
                          "text-indent:" + QString::number(CurStyle.ParLeftTopIdent/100) + "px;}"

                     "Emphasis{"
                          "font-family:'" + CurStyle.EmphasizedTextStyle.FontFamily + "';"
                          "font-size:" + QString::number(CurStyle.EmphasizedTextStyle.FontSize) + "pt;"
                          "font-weight:" + QString::number(1000*(CurStyle.EmphasizedTextStyle.FontStyle%2)) + ";"
                          "line-height:" + QString::number(CurStyle.EmphasizedTextStyle.LineSpacing*100) + ";"
                          "font-style:" + ((CurStyle.EmphasizedTextStyle.FontStyle/2 == 1)?QString("italic"):QString("normal")) + ";"
                          "text-align:" + CurStyle.EmphasizedTextStyle.TextAlign.toLower() + ";"
                          "color:" + CurStyle.EmphasizedTextStyle.TextColor + ";"
                          "text-indent:" + QString::number(CurStyle.ParLeftTopIdent/100) + "px;}"

                     "Note{"
                          "font-family:'" + CurStyle.NoteStyle.FontFamily + "';"
                          "font-size:" + QString::number(CurStyle.NoteStyle.FontSize) + "pt;"
                          "font-weight:" + QString::number(1000*(CurStyle.NoteStyle.FontStyle%2)) + ";"
                          "line-height:" + QString::number(CurStyle.NoteStyle.LineSpacing*100) + ";"
                          "font-style:" + ((CurStyle.NoteStyle.FontStyle/2 == 1)?QString("italic"):QString("normal")) + ";"
                          "text-align:" + CurStyle.NoteStyle.TextAlign.toLower() + ";"
                          "color:" + CurStyle.NoteStyle.TextColor + ";"
                          "text-indent:" + QString::number(CurStyle.ParLeftTopIdent/100) + "px;}"
                     "body{"
                          "background" + ((CurStyle.BackgroundType == true) ? ("-color:" + CurStyle.BackgroundImage) : ("-image:url(" + fileName + ")")) + ";}"

                  "</style> <body>"
                  "<table border='0' style='"
                  "margin-top:0px;"
                  "margin-bottom:0px;"
                  "margin-left:" + QString::number(CurStyle.TextLeftRightIdent/100) + "px;"
                  "margin-right:" + QString::number(CurStyle.TextLeftRightIdent%100) + "px;'"

                  "width='100%' cellspacing='-30' cellpadding='40'>"
                  "<tr>"
                  "<td align = 'justify'>";

        Page1 = "<TitleText>"
               "<p>ГЛАВА 6</p>"
               "</TitleText>"
               "<Text>"
               "<p>Я вертелся, как уж на сковородке.</p>"
               "<p>— Подготовить корабль будет нелегко. Найти здесь, на Уймабашлии, квалифицированного капитана попросту невозможно…</p>"
               "<p>В ответ Массуд широко улыбнулся, продемонстрировав белоснежные зубы.</p>"
               "<p>— Да возраздуется мой будущий босс Джим, ибо я квалифицированный и опытный космический пилот. Мне уже не терпится встать у кормила сего судна, каковое вскорости будет весьма усовершенствовано.</p>"
               "<p>— Но радист уволился. Заменить некем…</p>"
               "<p>— Уже! В моем резюме перечислены мои лицензии, опыт работы и так далее в качестве компетентного офицера связи.</p>"
               "<p>Мне оставалось лишь хвататься за соломинку.</p>"
               "<p>— Вам понадобится экипаж…</p>"
               "<p>— Лишь по закону, как продемонстрировал предыдущий капитан со своими спившимися лежебоками. Корабль полностью автоматизирован. Дабы удовлетворить бюрократов, мы можем завербовать кое-кого из ваших фермеров. Зачислить их в команду для отчетности.</p>"
               "<p>Очаровательно! Космоплаваюший свинарник под управлением полоумных мужланов.</p>"
               "<p>— Уже приглашены квалифицированные инопланетные космические инспекторы, сейчас направляющиеся сюда, — добавил Массуд, прежде чем я успел измыслить очередную отговорку. — Необходимый ремонт будет проведен незамедлительно.</p>"
               "<p>— Мы с Массудом все уладим, — вставил Боливар. — А вы собирайте вещи и ни о чем не беспокойтесь. И приготовьтесь к путешествию всей своей жизни.</p>"
               "<p>Именно этого я и боялся. Тут зазвонил мой синафон, прошив вибрацией всю голову. В момент помутнения рассудка я выбросил свой карманный телефон и согласился на вживление в синус этого нового прибамбаса. Используя энергию тепла тела, он может работать десятилетиями. Но громкость звонка надо убавить. Все еще не оправившись от шока, я пробормотал «включить», и в голове у меня зазудел голос Анжелины: <Emphasis>«Я разнесла добрую весть, и теперь все празднуют. — </Emphasis>Голос тонул в радостных воплях, звоне стаканов и свином визге. — <Emphasis>Хотят тебя поблагодарить…»</Emphasis></p>"
               "<p><Emphasis>— Я </Emphasis>потрясен, но стесняюсь предстать перед ними. Да и дело не ждет: компьютер сообщил, что нашел для наших паломников подходящую планету. Надо ковать, пока горячо…</p>"
               "</Text></td>";
       Page2 = "<td align = 'justify'><Text><p>Отмахнувшись от возражений, я пробормотал «отключить» и позволил плаксивой жалости к себе захлестнуть меня на пару секунд с головой.</p>"
               "<p>— Довольно, Джим, — пробормотал я, по-садистски упиваясь собственными невзгодами. И тряхнул себя за метафорический шиворот. — Найди планету, доставь туда эту родню неотесанную вкупе с их свинством, пожелай им всего доброго и возвращайся к собственной жизни. Подумай, с каким удовольствием ты вернешься на эту планету удовольствий.</p>"
               "<p>Я пробирался по коридорам украдкой, чтобы избежать всяческих встреч и нескончаемых отговорок. Выходя, я не мог не улыбнуться при виде того, как сержант охраны молодцевато козырнул мне благодаря моей изрядной финансовой щедрости.</p>"
               "<p>Вернувшись домой, я решительно миновал бар, вошел в кабинет и велел компьютеру включиться. Потом умерил свой абстинентский пыл холодным пивом; пока не найду приемлемую планету, ограничимся этим.</p>"
               "<p>Я сидел, прихлебывая, глядя на экран и шипя ругательства при виде прокручивавшегося на экране нескончаемого списка подходящих планет.</p>"
               "<p>Чтобы укоротить список, я быстренько написал программный фильтр. Климат, туземное население, форма правления, средний коэффициент интеллекта полицейских, смертная казнь, процент заключенных на душу населения, капитализация банковской системы — подумать о деловых возможностях никогда не повредит, — словом, традиционный набор.</p>"
               "<p>Часы спустя я выпрямился и вздохнул. Пиво выдохлось, тысячи планет обратились в электроны; уцелели лишь три. Зевнув, я потянулся и отправился за свежим пивом. На баре лежала записка.</p>"
               "<p><Emphasis>Не хотела мешать. Увидимся утром. Удачи.</Emphasis></p>"
               "<p>Я бросил взгляд на часы: порядком за полночь. Я даже не слыхал, как пришла Анжелина. Добавил к пиву стопочку виски, получив древнюю смесь, прозванную «ершом» по причинам, затерявшимся в дебрях времен. И снова зевнул.</p>"
               "<p>Как только синапсы заскворчали от стимулятора, я вернулся к работе. Отпало еще две планеты. Я ударил по клавише, и экран заполнило одно-единственное уцелевшее название:</p>"
               "</Text>";
    PageHTMLBottom = "</td></tr></table></body>";

    qDebug()<<CurStyle.BackgroundImage;
}

TextParser::~TextParser()
{
    delete ProgramSettings;
}


void TextParser::setPageGeometry(int width, int height)
{
    pageWidth = width;
    pageHeight = height;
}

QString TextParser::getCurrentPage()
{
    //qDebug()<<PageHTMLHeader + Page1 + Page2 + PageHTMLBottom;
    return PageHTMLHeader + Page1 + Page2 + PageHTMLBottom;
}

void TextParser::startParse()
{

}

int TextParser::getPageCount()
{

}

QString TextParser::getNextPage()
{

}

QString TextParser::getPrevPage()
{

}

QString TextParser::reparse()
{

}

void ReadingWindow::setStyle(QString currentStyle)
{
    QString styleSheets[8];
    setWindowTopButtonsStyle(styleSheets, currentStyle);
    ui->min_button->setStyleSheet(styleSheets[0]);
    ui->full_size_button->setStyleSheet(styleSheets[1]);
    ui->exit_button->setStyleSheet(styleSheets[2]);

    setBackgroundWindowColor(styleSheets, currentStyle);
    ui->MainWidget->setStyleSheet(styleSheets[0]);

    setReaderWindowStyle(styleSheets, currentStyle);
    ui->Clock->setStyleSheet(styleSheets[1]);
    ui->Progress->setStyleSheet(styleSheets[1]);
    ui->MenuButton->setStyleSheet(styleSheets[0]);

    setReaderWindowMenuButtons(styleSheets, currentStyle);
    _BackToMainWindowButton->setStyleSheet(styleSheets[0]);
    _ContentsButton->setStyleSheet(styleSheets[0]);
    _SynchronizationButton->setStyleSheet(styleSheets[0]);
    _FindButton->setStyleSheet(styleSheets[0]);
    _SettingsButton->setStyleSheet(styleSheets[0]);
}

ReadingWindow::ReadingWindow(settings * PSettings, Book book) : ui(new Ui::ReadingWindow)
{
    ui->setupUi(this);
    ui->TextPage->setAlignment(Qt::AlignJustify);

    BookParse = new TextParser(book, PSettings);
    parserThread = new QThread(this);
    BookParse->moveToThread(parserThread);
    connect(this, SIGNAL(destroyed(QObject*)), parserThread, SLOT(quit()));
    parserThread->start();
    ui->TextPage->setHtml(BookParse->getCurrentPage());

    ui->TextPage->setMouseTracking(true);
    ui->MainWidget->setMouseTracking(true);

    setMouseTracking(true);
    prev_geometry = geometry();
    TopBarNeedHide = true;
    HidenTimer = 0;

    MenuWidget = new QWidget(this);

    MenuWidget->hide();
    MenuWidget->setGeometry(0, 0, ui->MenuButton->width(),ui->MenuButton->width()*5);

    MenuLayout = new QVBoxLayout();
    MenuWidget->setLayout(MenuLayout);
    MenuLayout->setContentsMargins(0,0,0,0);
    MenuLayout->setSpacing(0);

    _ContentsButton = new QPushButton("cont");
    _ContentsButton->setFixedSize(QSize(ui->MenuButton->width(),ui->MenuButton->width()));
    MenuLayout->addWidget(_ContentsButton, 0);
    connect(_ContentsButton, SIGNAL(clicked(bool)), this, SLOT(ContentsButton_clicked()));

    _FindButton = new QPushButton("find");
    _FindButton->setFixedSize(QSize(ui->MenuButton->width(),ui->MenuButton->width()));
    MenuLayout->addWidget(_FindButton, 1);
    connect(_FindButton, SIGNAL(clicked(bool)), this, SLOT(FindButton_Clicked()));

    _SettingsButton = new QPushButton("sett");
    _SettingsButton->setFixedSize(QSize(ui->MenuButton->width(),ui->MenuButton->width()));
    MenuLayout->addWidget(_SettingsButton, 2);
    connect(_SettingsButton, SIGNAL(clicked(bool)), this, SLOT(SettingsButton_Clicked()));

    _SynchronizationButton = new QPushButton("synch");
    _SynchronizationButton->setFixedSize(QSize(ui->MenuButton->width(),ui->MenuButton->width()));
    MenuLayout->addWidget(_SynchronizationButton, 3);
    connect(_SynchronizationButton, SIGNAL(clicked(bool)), this, SLOT(SynchronizationButton_Clicked()));

    _BackToMainWindowButton = new QPushButton("back");
    _BackToMainWindowButton->setFixedSize(QSize(ui->MenuButton->width(),ui->MenuButton->width()));
    MenuLayout->addWidget(_BackToMainWindowButton, 4);
    connect(_BackToMainWindowButton, SIGNAL(clicked(bool)), this, SLOT(BackToMainWindowButton_Clicked()));

    ProgramSettings = PSettings;
    setStyle(ProgramSettings->getInterfaceStyle());
    ui->Clock->setText(QTime::currentTime().toString("hh:mm"));

    QTimer *clockTimer = new QTimer(this);
    connect(clockTimer, SIGNAL(timeout()), this, SLOT(clockStep()));
    clockTimer->start(1000);

    show();
}

ReadingWindow::~ReadingWindow()
{
    delete ui;
    delete ProgramSettings;
    delete MenuWidget;
    delete MenuLayout;
    delete _BackToMainWindowButton;
    delete _ContentsButton;
    delete _SynchronizationButton;
    delete _FindButton;
    delete SettingsPage;
    delete WindowLayout;
    delete SettingsTabsLayout;
    delete MiniWindow;
    delete ProfileButton;
    delete ProgramButton;
    delete ReaderButton;
    delete parserThread;
}


void ReadingWindow::clockStep()
{
    ui->Clock->setText(QDateTime::currentDateTime().toString("hh:mm:ss"));
    if (ProgramSettings->getHideTopBar() == true && this->isMaximized())
        if (!ui->TopBarWidget->isHidden() && MenuWidget->isHidden() && TopBarNeedHide)
        {
            if (HidenTimer == 2)
            {
                ui->TopBarWidget->hide();
                HidenTimer = 0;
            }
            else
            {
                HidenTimer++;
            }
        }
}

void ReadingWindow::on_min_button_clicked()
{
    if(isMinimized())
    {
        normalGeometry() = prev_geometry;
        showNormal();
    }
    else
    {
        prev_geometry = geometry();
        showMinimized();
    }
}

void ReadingWindow::on_full_size_button_clicked()
{
    if(isMaximized())
    {
        normalGeometry() = prev_geometry;
        showNormal();
    }
    else
    {
        prev_geometry = geometry();
        showMaximized();
    }
}

void ReadingWindow::on_exit_button_clicked()
{
    AnswerDialog *answer_window = new AnswerDialog(ui->exit_button->mapToGlobal(QPoint(0,0)).x() - 300 + ui->exit_button->width(),
                                                   ui->exit_button->mapToGlobal(QPoint(0,0)).y() + ui->exit_button->height(),"Exit?",
                                                   ProgramSettings->getInterfaceStyle());
    answer_window->show();

    if (answer_window->exec() == QDialog::Accepted)
    {
        exit(0);
    }
    else
        delete answer_window;
}

void ReadingWindow::on_MenuButton_clicked()
{
    if (MenuWidget->isHidden())
    {
        MenuWidget->move(ui->MenuButton->x(), ui->MenuButton->y() + ui->MenuButton->height());
        MenuWidget->show();
    }
    else
        MenuWidget->hide();

}

void ReadingWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (e->pos().y() <= 50 && ui->TopBarWidget->isHidden() && ProgramSettings->getHideTopBar())
    {
        ui->TopBarWidget->show();
        TopBarNeedHide = false;
    }
    if (e->pos().y() > 50 && !ui->TopBarWidget->isHidden())
        TopBarNeedHide = true;


    if (moving)
    {
        if (!isMaximized())
        {
            move(e->globalX() - lastPoint.x() - 7, e->globalY() - lastPoint.y() - 7);
            if (!MenuWidget->isHidden())
                MenuWidget->move(ui->MenuButton->x(), ui->MenuButton->y() + ui->MenuButton->height());
        }
        else
        {
            prev_geometry.setY(e->globalY());
            normalGeometry() = prev_geometry;
            showNormal();
        }
    }
}

void ReadingWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        if (e->pos().y() <= 20)
        {
            moving = true;
            lastPoint = e->pos();
        }
    }
}

void ReadingWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        if (moving)
            moving = false;
    }
}

void ReadingWindow::ContentsButton_clicked()
{
    MenuWidget->hide();
}

void ReadingWindow::FindButton_Clicked()
{
    MenuWidget->hide();
    Search = new SearchWindow(0, this->height() - 80, ProgramSettings->getInterfaceStyle(), true, this);
    connect(Search, SIGNAL(startSearch(QString,QString)), this, SLOT(StartSearch(QString,QString)));
    connect(Search, SIGNAL(nextResult()), this, SLOT(NextSearchStep()));
    connect(Search, SIGNAL(previousResult()), this, SLOT(PrevSearchStep()));
}

void ReadingWindow::StartSearch(QString key, QString type)
{

}

void ReadingWindow::NextSearchStep()
{

}

void ReadingWindow::PrevSearchStep()
{

}

void ReadingWindow::SettingsButton_Clicked()
{
    MenuWidget->hide();

    MiniWindow = new QDialog(this);
    MiniWindow->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);

    int frame, w, h;
    if (this->width() - 100 < 1066)
        w = 1066;
    else
        w = this->width() - 100;
    if (this->height() - 100 < 536)
        h = 536;
    else
        h = this->height() - 100;
    frame = (this->height() - h)/2;

    MiniWindow->setGeometry(this->x() + frame, this->y() + frame, w, h);

    WindowLayout = new QVBoxLayout(MiniWindow);
    WindowLayout->setContentsMargins(0,0,0,0);
    WindowLayout->setSpacing(0);

    SettingsPage = new settingslayout();
    SettingsPage->setSettingsData(ProgramSettings);

    SettingsTabsLayout = new QHBoxLayout();

    WindowLayout->addLayout(SettingsTabsLayout, 0);
    WindowLayout->addWidget(SettingsPage, 1);

    ProfileButton = new QPushButton("Profile", MiniWindow);
    ProgramButton = new QPushButton("Program", MiniWindow);
    ReaderButton = new QPushButton("Reader", MiniWindow);

    ProfileButton->setFixedSize(w/3, 30);
    ProgramButton->setFixedSize(w/3, 30);
    ReaderButton->setFixedSize(w/3, 30);

    SettingsTabsLayout->addWidget(ProfileButton, 0);
    SettingsTabsLayout->addWidget(ProgramButton, 1);
    SettingsTabsLayout->addWidget(ReaderButton, 2);

    setBackgroundWindowColor(styles, ProgramSettings->getInterfaceStyle());
    MiniWindow->setStyleSheet(styles[1]);
    setTabButtonsStyle(styles, ProgramSettings->getInterfaceStyle());
    ProfileButton->setStyleSheet(styles[0]);
    ProgramButton->setStyleSheet(styles[1]);
    ReaderButton->setStyleSheet(styles[0]);

    connect(ProfileButton, SIGNAL(clicked(bool)), SettingsPage, SLOT(showProfile()));
    connect(ProfileButton, SIGNAL(clicked(bool)), this, SLOT(settings_profile_clicked()));

    connect(ProgramButton, SIGNAL(clicked(bool)), SettingsPage, SLOT(showProgram()));
    connect(ProgramButton, SIGNAL(clicked(bool)), this, SLOT(settings_program_clicked()));

    connect(ReaderButton, SIGNAL(clicked(bool)), SettingsPage, SLOT(showReader()));
    connect(ReaderButton, SIGNAL(clicked(bool)), this, SLOT(settings_reader_clicked()));

    SettingsPage->show();
    MiniWindow->show();
}

void ReadingWindow::settings_profile_clicked()
{
    ProfileButton->setStyleSheet(styles[1]);
    changeSettingsTab(0);
}
void ReadingWindow::settings_program_clicked()
{
    ProgramButton->setStyleSheet(styles[1]);
    changeSettingsTab(1);
}
void ReadingWindow::settings_reader_clicked()
{
    ReaderButton->setStyleSheet(styles[1]);
    changeSettingsTab(2);
}

void ReadingWindow::changeSettingsTab(int i)
{
    switch (SettingsTab) {
    case 0:
        ProfileButton->setStyleSheet(styles[0]);
        break;
    case 1:
        ProgramButton->setStyleSheet(styles[0]);
        break;
    case 2:
        ReaderButton->setStyleSheet(styles[0]);
        break;
    default:
        break;
    }
    SettingsTab = i;
}

void ReadingWindow::SynchronizationButton_Clicked()
{
    MenuWidget->hide();

    MiniWindow = new QDialog(this);
    MiniWindow->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);

    int frame, w, h;
    if (this->width() - 100 < 1066)
        w = 1066;
    else
        w = this->width() - 100;
    if (this->height() - 100 < 536)
        h = 536;
    else
        h = this->height() - 100;
    frame = (this->height() - h)/2;

    MiniWindow->setGeometry(this->x() + frame, this->y() + frame, w, h);

    WindowLayout = new QVBoxLayout(MiniWindow);
    WindowLayout->setContentsMargins(0,0,0,0);
    WindowLayout->setSpacing(0);

    SynchronizationPage = new synchronizationlayout(MiniWindow);
    SynchronizationPage->setSettingsData(ProgramSettings);

    WindowLayout->addWidget(SynchronizationPage, 0);
    setBackgroundWindowColor(styles, ProgramSettings->getInterfaceStyle());
    MiniWindow->setStyleSheet(styles[1]);

    SynchronizationPage->show();
    MiniWindow->show();
}

void ReadingWindow::BackToMainWindowButton_Clicked()
{
    emit showMainWindow();
    this->close();
}

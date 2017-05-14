#include "reading_window.h"
#include "ui_reading_window.h"
#include "books.h"
#include "answer_dialog.h"
#include "settings_layout.h"
#include "synchronization_layout.h"
#include "search_window.h"
#include "settings.h"
#include "styles.h"
#include "booktableofcontents.h"
#include "styles.h"

#include <QTimer>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QThread>
#include <QDialog>
#include <QListWidget>
#include <QMessageBox>

#include <QDebug>


void ReadingWindow::setStyle(const QString &currentStyle)
{
    QString styleSheets[6];

    setTopBarBackgroundColor(styleSheets, currentStyle);
    ui->TopBarWidget->setStyleSheet(styleSheets[0]);

    setWindowTopButtonsStyle(styleSheets, currentStyle);
    ui->min_button->setStyleSheet(styleSheets[0]);
    ui->full_size_button->setStyleSheet(styleSheets[1]);

    setExitButtonStyle(styleSheets, currentStyle);
    ui->exit_button->setStyleSheet(styleSheets[0]);

    setBackgroundWindowColor(styleSheets, currentStyle);
    this->setStyleSheet(styleSheets[0]);

    setReaderWindowStyle(styleSheets, currentStyle);
    ui->Clock->setStyleSheet(styleSheets[1]);
    ui->Progress->setStyleSheet(styleSheets[1]);
    ui->BookName->setStyleSheet(styleSheets[1]);
    ui->MenuButton->setStyleSheet(styleSheets[0]);

    ui->ReadProfilesButton->setStyleSheet(styleSheets[2]);
    ProfilesView->setStyleSheet(styleSheets[3]);

}


ReadingWindow::ReadingWindow(QWidget* parent, Book *book) : QWidget(parent), ui(new Ui::ReadingWindow)
{
    qDebug()<<"create readingWindow";
    CurBook = book;

    ActiveWindow = false;

    TopBarNeedHide = true;
    HidenTimer = 0;

    ui->setupUi(this);
    ui->BookName->setText(CurBook->getAuthorName() + ": " + CurBook->getTitle());

    ui->TextPage->viewport()->setAutoFillBackground(false);
    ui->TextPage->setAttribute( Qt::WA_TranslucentBackground, true );

    ui->TextPage->setFocus();
    ui->MenuButton->setFocusPolicy(Qt::NoFocus);
    ui->min_button->setFocusPolicy(Qt::NoFocus);
    ui->exit_button->setFocusPolicy(Qt::NoFocus);
    ui->full_size_button->setFocusPolicy(Qt::NoFocus);

    ui->TextPage->setFocusPolicy(Qt::StrongFocus);


    BookPaginator = new XMLTextPaginator(this);

    ui->TextPage->setMouseTracking(true);
    setMouseTracking(true);


    MenuWidget = new ReadingMenu(this);
    connect(ui->MenuButton, SIGNAL(clicked(bool)), MenuWidget, SIGNAL(MenuButtonClicked()));

    connect(MenuWidget, SIGNAL(showMainWindow()), this, SIGNAL(showMainWindow()));
    connect(MenuWidget, SIGNAL(showContentsTable()), this, SLOT(showContentsTable()));
    connect(MenuWidget, SIGNAL(showSettingsWindow()), this, SLOT(showSettingsWindow()));

    connect(MenuWidget, &ReadingMenu::hideMenuWidget, [this](){ui->TextPage->setFocus();});


    ProfilesWidget = new QWidget(this);
    QVBoxLayout* ProfilesLayout = new QVBoxLayout(ProfilesWidget);
    ProfilesWidget->setLayout(ProfilesLayout);
    ProfilesWidget->setContentsMargins(0,0,0,0);
    ProfilesLayout->setContentsMargins(0,0,0,0);

    ProfilesView = new QListWidget(ProfilesWidget);
    ProfilesWidget->setFixedWidth(200);
    ProfilesLayout->addWidget(ProfilesView);
    ProfilesWidget->hide();

    connect(ui->MenuButton, &QPushButton::clicked, [this](){ProfilesWidget->hide();});
    connect(ui->ReadProfilesButton, &QPushButton::clicked, [this](){MenuWidget->hideMenu();});


    ProgramSettings = Settings::getSettings();
    setStyle(ProgramSettings->getInterfaceStyle());
    setBackgroundImage();

    ui->Clock->setText(QTime::currentTime().toString("hh:mm"));

    QTimer *clockTimer = new QTimer(this);
    connect(clockTimer, SIGNAL(timeout()), this, SLOT(clockStep()));
    clockTimer->start(1000);

    ui->TextPage->installEventFilter(this);
    ui->TopBarWidget->installEventFilter(this);

    connect(ui->min_button, SIGNAL(clicked(bool)), this, SIGNAL(showWindowMinimazed()));
    connect(ui->full_size_button, SIGNAL(clicked(bool)), this, SIGNAL(showWindowMaximazed()));

    qDebug()<<"readingWindow created";
}


void ReadingWindow::setBackgroundImage()
{
    if (ProgramSettings->getCurrentReadProfileElem().BackgroundType == false)
    {
        ui->TextBackground->setStyleSheet("#TextBackground{background-image:url(" +
                                          ProgramSettings->getCurrentReadProfileElem().BackgroundImage +
                                          + ");}");
    }
    else
    {
        ui->TextBackground->setStyleSheet("");
    }
}


void ReadingWindow::startReading()
{
    connect(this, SIGNAL(windowWasResized()), this, SLOT(reprintResizedText()));

    ui->TextPage->setHtml(BookPaginator->startParser(CurBook,ui->TextPage->width(), ui->TextPage->height()));
    updateProgress();
}


void ReadingWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}


ReadingWindow::~ReadingWindow()
{
    delete BookPaginator;
    delete ui;
    qDebug()<<"delete reading window";
}


void ReadingWindow::on_ReadProfilesButton_clicked()
{
    if (ProfilesWidget->isHidden())
    {
        QStringList ProfilesList;
        ProfilesList = ProgramSettings->getReadProfilesList();

        ProfilesView->clear();
        ProfilesView->addItems(ProfilesList);
        ProfilesView->setCurrentRow(ProfilesList.indexOf(ProgramSettings->getCurrentReadProfileName()));

        ProfilesWidget->show();
        ProfilesWidget->move(ui->ReadProfilesButton->x(), ui->ReadProfilesButton->height());
        ProfilesWidget->setFixedHeight(ProfilesList.size() * 30);

        connect(ProfilesView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(changeReadProfile(QModelIndex)));
    }
    else
    {
        ProfilesWidget->hide();
    }
}

void ReadingWindow::changeReadProfile(const QModelIndex &index)
{
    ProgramSettings->setCurrentReadProfile(ProgramSettings->getReadProfilesList().at(index.row()));
    reprintNewSettText();
    setBackgroundImage();
}


void ReadingWindow::clockStep()
{
    ui->Clock->setText(QDateTime::currentDateTime().toString("hh:mm"));

    if (ProgramSettings->getHideTopBar() == true && this->parentWidget()->isMaximized())
        if (!ui->TopBarWidget->isHidden() && MenuWidget->menuIsHidden() && TopBarNeedHide)
        {
            if (HidenTimer == 4)
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


void ReadingWindow::on_exit_button_clicked()
{
    if (ActiveWindow)
        return;

    AnswerDialog *answer_window = new AnswerDialog(ui->exit_button->mapToGlobal(QPoint(ui->exit_button->width() - 300, ui->exit_button->height())),
                                                   QObject::tr("Exit?"),
                                                   ProgramSettings->getInterfaceStyle(),
                                                   this);
    answer_window->show();

    if (answer_window->exec() == QDialog::Accepted)
    {
        delete answer_window;
        emit closeWindow();
    }
    else
        delete answer_window;
}


bool ReadingWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (ActiveWindow || obj == 0)
        return true;

    switch (event->type())
    {
        case QEvent::MouseMove:
        {
            QMouseEvent* MouseMoveEvent = static_cast<QMouseEvent*>(event);
            if (ProgramSettings->getHideTopBar())
            {
                if (MouseMoveEvent->pos().y() <= 50 && ui->TopBarWidget->isHidden())
                {
                    ui->TopBarWidget->show();
                    TopBarNeedHide = false;
                }
                if (MouseMoveEvent->pos().y() > 50 && !ui->TopBarWidget->isHidden())
                    TopBarNeedHide = true;
            }
            break;
        }

        case QEvent::KeyPress:
        {
            QKeyEvent *KeyEvent = static_cast<QKeyEvent*>(event);
            if (KeyEvent->key() == ProgramSettings->getFForwardKey() || KeyEvent->key() == ProgramSettings->getSForwardKey())
            {
                ui->TextPage->setHtml(BookPaginator->getPageForward());
                updateProgress();
            }
            else
            if (KeyEvent->key() == ProgramSettings->getFBackwardKey() || KeyEvent->key() == ProgramSettings->getSBackwardKey())
            {
                ui->TextPage->setHtml(BookPaginator->getPageBackward());
                updateProgress();
            }
            else
            if (KeyEvent->key() == Qt::Key_Escape && this->parentWidget()->isMaximized())
            {
                emit showWindowMaximazed();
                ui->TopBarWidget->show();
            }
            break;
        }

        case QEvent::Wheel:
        {
            if (ProgramSettings->getTurnByWheel() == true)
            {
                QWheelEvent* Wheel = static_cast<QWheelEvent*>(event);
                if (Wheel->delta() < 0)
                {
                    ui->TextPage->setHtml(BookPaginator->getPageForward());
                    updateProgress();
                }
                else if (Wheel->delta() > 0)
                {
                    ui->TextPage->setHtml(BookPaginator->getPageBackward());
                    updateProgress();
                }
            }
            break;
        }

        case QEvent::MouseButtonPress:
        {
            QMouseEvent* MousePressEvent = static_cast<QMouseEvent*>(event);
            if(MousePressEvent->button() == Qt::LeftButton)
            {
                if (MousePressEvent->pos().y() > 20)
                {
                    if (ProgramSettings->getTurnByTap())
                    {
                        if (MousePressEvent->pos().x() > this->size().width() - 100)
                        {
                            ui->TextPage->setHtml(BookPaginator->getPageForward());
                            updateProgress();
                        }
                        else
                        if (MousePressEvent->pos().x() < 100)
                        {
                            ui->TextPage->setHtml(BookPaginator->getPageBackward());
                            updateProgress();
                        }
                    }
                }
            }
            break;
        }

        case QEvent::MouseButtonDblClick:
        {
            qDebug()<<"yepe";
            QMouseEvent* MousePressEvent = static_cast<QMouseEvent*>(event);
            if(MousePressEvent->button() == Qt::LeftButton)
            {
                if (MousePressEvent->pos().y() > 20)
                {
                    if (ProgramSettings->getTurnByTap())
                    {
                        if (MousePressEvent->pos().x() > this->size().width() - 100)
                        {
                            ui->TextPage->setHtml(BookPaginator->getPageForward());
                            updateProgress();
                        }
                        else
                        if (MousePressEvent->pos().x() < 100)
                        {
                            ui->TextPage->setHtml(BookPaginator->getPageBackward());
                            updateProgress();
                        }
                    }

                    if (MousePressEvent->pos().x() > this->size().width()/2 - 100 && MousePressEvent->pos().x() < this->size().width()/2 + 100)
                    {
                        emit showWindowMaximazed();
                        ui->TopBarWidget->show();
                    }
                }
            }
            break;
        }
        case QEvent::Resize:
        {
            emit windowWasResized();
            break;
        }

        default:
            break;
    }

    return true;
}


void ReadingWindow::reprintResizedText()
{
    ui->TextPage->setHtml(BookPaginator->resizePage(ui->TextPage->width(), ui->TextPage->height()));
}


void ReadingWindow::updateProgress()
{
    ui->Progress->setText(QString::number(floor(BookPaginator->getProgress()*10)/10) + "%");
}


void ReadingWindow::showContentsTable()
{
    ActiveWindow = true;
    BookTableOfContents* tableWindow = new BookTableOfContents(ProgramSettings->getInterfaceStyle(), BookPaginator->getBookContentTable(), this);
    tableWindow->move(0, ui->MenuButton->height());
    connect(tableWindow, SIGNAL(goToSection(long long)), this, SLOT(goToSection(long long)));
    if (tableWindow->exec() == QDialog::Rejected)
    {
        delete tableWindow;
        ActiveWindow = false;
    }
}


void ReadingWindow::goToSection(const long long sectionIndex)
{
    ui->TextPage->setHtml(BookPaginator->goToSection(sectionIndex));
    updateProgress();
}


void ReadingWindow::showSearchWindow()
{
    Search = new SearchWindow(QPoint(0, this->height() - 80), ProgramSettings->getInterfaceStyle(), true, this);

    connect(Search, SIGNAL(startSearch(QString,QString)), this, SLOT(StartSearch(QString,QString)));
    connect(Search, SIGNAL(nextResult()), this, SLOT(NextSearchStep()));
    connect(Search, SIGNAL(previousResult()), this, SLOT(PrevSearchStep()));
    connect(Search, &QDialog::finished, [this](){ui->TextPage->setFocus();});
}


void ReadingWindow::StartSearch(const QString &key, const QString &type)
{

}


void ReadingWindow::NextSearchStep()
{

}


void ReadingWindow::PrevSearchStep()
{

}


void ReadingWindow::reprintNewSettText()
{
    setBackgroundImage();
    ui->TextPage->setHtml(BookPaginator->updateSettings(ui->TextPage->width(), ui->TextPage->height()));
}


void ReadingWindow::showSettingsWindow()
{
    ActiveWindow = true;

    MiniWindow = new QDialog(this);
    QString style[2];
    setBackgroundWindowColor(style, ProgramSettings->getInterfaceStyle());
    setStyleSheet(style[1]);

    MiniWindow->setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);

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

    MiniWindow->setGeometry(frame, frame, w, h);
    MiniWindow->setContentsMargins(0,0,0,0);


    MiniWindowLayout = new QVBoxLayout(MiniWindow);
    MiniWindow->setLayout(MiniWindowLayout);
    MiniWindowLayout->setContentsMargins(0,0,0,0);

    SettingsPage = new SettingsLayout(MiniWindow);

    SettingsPage->setSettingsData();

    MiniWindowLayout->addWidget(SettingsPage);

    SettingsPage->addExitButton();
    connect(SettingsPage, SIGNAL(settingsClosed()), MiniWindow, SLOT(reject()));

    MiniWindow->show();

    if (MiniWindow->exec() == QDialog::Rejected)
    {
        reprintNewSettText();
        ui->TextPage->setFocus();
        delete MiniWindow;
        ActiveWindow = false;
    }
}


void ReadingWindow::showSynchronizationWindow()
{
    MiniWindow = new QDialog(this);

    MiniWindow->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);

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

    MiniWindow->show();

    if (MiniWindow->exec() == QDialog::Rejected)
    {
        delete MiniWindow;
        ui->TextPage->setFocus();
    }
}

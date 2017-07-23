#include "reading_window.h"
#include "ui_reading_window.h"
#include "books.h"
#include "answer_dialog.h"
#include "settings_layout.h"
#include "synchronization_layout.h"
#include "search_window.h"
#include "settings.h"
#include "styles.h"
#include "book_table_of_contents.h"
#include "styles.h"
#include "battery_widget.h"
#include "settings_layout.h"

#include <QTimer>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QThread>
#include <QDialog>
#include <QListWidget>
#include <QMessageBox>
#include <QScroller>
#include <QScrollBar>

#include <QDesktopServices>

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
    MiniWindow = 0;
    ContentsTableWindow = 0;
    Search = 0;

    TopBarNeedHide = true;
    HidenTimer = 0;

    ui->setupUi(this);
    ui->BookName->setText(CurBook->getAuthorName() + ": " + CurBook->getTitle());

    ui->TextPage->viewport()->setAutoFillBackground(false);
    ui->TextPage->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->TextPage->verticalScrollBar()->setSingleStep(0);

    BookPaginator = new XMLTextPaginator(this);

    ui->TextPage->setMouseTracking(true);
    setMouseTracking(true);

    createReadingMenuWidget();
    createReadProfilesWidget();


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


    ui->TextPage->setFocus();
    ui->TextPage->setFocusProxy(ui->TopBarWidget);


    connect(ui->TextPage, SIGNAL(anchorClicked(QUrl)), this, SLOT(showNoteText(QUrl)));
    //connect(ui->TextPage, SIGNAL(highlighted(QUrl)), this, SLOT(showNoteText(QUrl)));
}


void ReadingWindow::createReadingMenuWidget()
{
    MenuWidget = new ReadingMenu(this);
    MenuWidget->installEventFilter(this);
    connect(ui->MenuButton, SIGNAL(clicked(bool)), MenuWidget, SIGNAL(MenuButtonClicked()));

    connect(MenuWidget, SIGNAL(showMainWindow()), this, SIGNAL(showMainWindow()));
    connect(MenuWidget, SIGNAL(showContentsTable()), this, SLOT(showContentsTable()));
    connect(MenuWidget, SIGNAL(showSettingsWindow()), this, SLOT(showSettingsWindow()));
    connect(MenuWidget, SIGNAL(showSearchWindow()), this, SLOT(showSearchWindow()));
}


void ReadingWindow::createReadProfilesWidget()
{
    ProfilesWidget = new QWidget(this);
    QVBoxLayout* ProfilesLayout = new QVBoxLayout(ProfilesWidget);
    ProfilesWidget->setLayout(ProfilesLayout);
    ProfilesWidget->setContentsMargins(0,0,0,0);
    ProfilesLayout->setContentsMargins(0,0,0,0);

    ProfilesView = new QListWidget(ProfilesWidget);
    ProfilesWidget->setFixedWidth(200);
    ProfilesLayout->addWidget(ProfilesView);
    ProfilesWidget->hide();

    if (QTouchDevice::devices().size())
        QScroller::grabGesture(ProfilesView->viewport(), QScroller::LeftMouseButtonGesture);

    connect(ui->MenuButton, &QPushButton::clicked, [this](){ProfilesWidget->hide();});
    connect(ui->ReadProfilesButton, &QPushButton::clicked, [this](){MenuWidget->hideMenu();});
}


void ReadingWindow::setBackgroundImage()
{
    if (ProgramSettings->getCurrentReadProfile().BackgroundType == false)
        ui->TextBackground->setStyleSheet("#TextBackground{background-image:url(" +
                                          ProgramSettings->getCurrentReadProfile().BackgroundImage +
                                          + ");}");
    else
        ui->TextBackground->setStyleSheet("");
}


void ReadingWindow::startReading()
{
    connect(this, SIGNAL(windowWasResized()), this, SLOT(resizeWindow()));

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


void ReadingWindow::showNextPage()
{
    if (ActiveWindow)
        return;

    ui->TextPage->setHtml(BookPaginator->getPageForward());
    updateProgress();
}


void ReadingWindow::showPrevPage()
{
    if (ActiveWindow)
        return;

    ui->TextPage->setHtml(BookPaginator->getPageBackward());
    updateProgress();
}


void ReadingWindow::showNoteText(const QUrl &link)
{
    if (!link.isEmpty())
    {
        if (link.toString()[0] == '#')
        {
            QString noteID = link.toString();
            noteID.remove(0,1);

            QString note = BookPaginator->getPageNote(noteID, 666);

            if (note.isEmpty())
                return;

            QDialog* NoteWidget = new QDialog(this, Qt::Popup);
            connect(NoteWidget, &QDialog::finished, [this](){ui->TextPage->setFocus();});

            NoteWidget->setFixedWidth(this->width()/4);
            NoteWidget->setContentsMargins(0,0,0,0);

            QVBoxLayout* layout = new QVBoxLayout(NoteWidget);
            layout->setContentsMargins(0,0,0,0);

            QTextBrowser* NoteText = new QTextBrowser(NoteWidget);
            layout->addWidget(NoteText);

            NoteText->setFrameStyle(2);
            NoteText->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
            NoteText->setTextInteractionFlags(Qt::NoTextInteraction);

            NoteText->setHtml(note);
            NoteWidget->show();

            if (NoteText->document()->size().toSize().height() + 15 <= this->height()/4)
                NoteWidget->setFixedHeight(NoteText->document()->size().toSize().height() + 15);

            QPoint pos = QCursor::pos() + QPoint(0,15);

            if (pos.x() + NoteWidget->width() > this->mapToGlobal(QPoint()).x() + this->width())
                pos.setX(this->mapToGlobal(QPoint()).x() + this->width() - NoteWidget->width());
            else
                if (pos.x() < this->mapToGlobal(QPoint()).x())
                    pos.setX(this->mapToGlobal(QPoint()).x());

            if (pos.y() + NoteWidget->height() > this->mapToGlobal(QPoint()).y() + this->height())
                pos.setY(pos.y() - NoteWidget->height());
            else
                if (pos.y() < this->mapToGlobal(QPoint()).y())
                    pos.setY(pos.y() + NoteWidget->height());


            if (QTouchDevice::devices().size())
            {
                QScroller::grabGesture(NoteText->viewport(), QScroller::LeftMouseButtonGesture);
                NoteText->verticalScrollBar()->setSingleStep(1);
            }

            NoteWidget->move(pos);
        }
        else
            if (link.isValid())
                QDesktopServices::openUrl(link);

    }
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

        connect(ProfilesView, &QListWidget::doubleClicked, [this](const QModelIndex &index){
            ProgramSettings->setCurrentReadProfile(ProgramSettings->getReadProfilesList().at(index.row()));
            reprintNewSettText();
            ui->TextPage->setFocus();
        });
    }
    else        
        ProfilesWidget->hide();
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
                ui->TextPage->setFocus();
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
                                                   this);
    answer_window->show();

    if (answer_window->exec() == QDialog::Accepted)
        emit closeWindow();

    delete answer_window;

    ui->TextPage->setFocus();
}


bool ReadingWindow::eventFilter(QObject *obj, QEvent *event)
{
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
            showNextPage();
        }
        else if (KeyEvent->key() == ProgramSettings->getFBackwardKey() || KeyEvent->key() == ProgramSettings->getSBackwardKey())
        {
            showPrevPage();
        }
        else if (KeyEvent->key() == Qt::Key_Escape)
        {
            if (!MenuWidget->menuIsHidden())
            {
                MenuWidget->hideMenu();
                ui->TextPage->setFocus();
            }
            else if (MiniWindow != 0)
            {
                MiniWindow->closeWindow();
            }
            else if (!ProfilesWidget->isHidden())
            {
                ProfilesWidget->hide();
            }
            else if (ContentsTableWindow != 0)
            {
                ContentsTableWindow->close();
            }
            else if (this->parentWidget()->isFullScreen())
            {
                emit showWindowMaximazed();
                ui->TopBarWidget->show();
            }
            return true;
        }
        else if (KeyEvent->modifiers() & Qt::CTRL)
        {
            if (KeyEvent->key() == Qt::Key_F)
                showSearchWindow();
            else if (KeyEvent->key() == Qt::Key_S)
                showSettingsWindow();
            else if (KeyEvent->key() == Qt::Key_T)
                showContentsTable();
        }

        break;
    }

    case QEvent::Wheel:
    {
        if (ProgramSettings->getTurnByWheel() == true)
        {
            QWheelEvent* Wheel = static_cast<QWheelEvent*>(event);
            QPoint wheelSteps = Wheel->pixelDelta();

            if (wheelSteps.isNull())
                wheelSteps = Wheel->angleDelta() / 120;

            if (wheelSteps.y() < 0)
            {
                showNextPage();
            }
            else if (wheelSteps.y() > 0)
            {
                showPrevPage();
            }

            Wheel->accept();
        }
        return true;
    }

    case QEvent::MouseButtonPress:
    {
        QMouseEvent* MousePressEvent = static_cast<QMouseEvent*>(event);

        if (!MenuWidget->menuIsHidden())
        {
            MenuWidget->hideMenu();
            ui->TextPage->setFocus();
            break;
        }

        if(MousePressEvent->button() == Qt::LeftButton)
        {
            if (MousePressEvent->pos().y() > 20)
            {
                if (ProgramSettings->getTurnByTap())
                {
                    if (MousePressEvent->pos().x() > this->size().width() - 100)
                    {
                        showNextPage();
                    }
                    else if (MousePressEvent->pos().x() < 100)
                    {
                        showPrevPage();
                    }
                }
            }
        }
        break;
    }

    case QEvent::MouseButtonDblClick:
    {
        QMouseEvent* MousePressEvent = static_cast<QMouseEvent*>(event);

        if (!MenuWidget->menuIsHidden())
        {
            MenuWidget->hideMenu();
            break;
        }

        if(MousePressEvent->button() == Qt::LeftButton)
        {
            if (MousePressEvent->pos().y() > 20)
            {
                if (ProgramSettings->getTurnByTap())
                {
                    if (MousePressEvent->pos().x() > this->size().width() - 100)
                    {
                        showNextPage();
                    }
                    else if (MousePressEvent->pos().x() < 100)
                    {
                        showPrevPage();
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
    default:
        break;
    }


    if (obj == ui->TextPage && event->type() == QEvent::Resize)
        emit windowWasResized();

    else if (event->type() == QEvent::LanguageChange)
        ui->retranslateUi(this);

    return false;
}


void ReadingWindow::resizeWindow()
{
    ui->TextPage->setHtml(BookPaginator->resizePage(ui->TextPage->width(), ui->TextPage->height()));
}


void ReadingWindow::updateProgress()
{
    ui->Progress->setText(QString::number(floor(BookPaginator->getProgress()*10)/10) + "%");
}


void ReadingWindow::showContentsTable()
{
    if (ContentsTableWindow != 0 || ActiveWindow)
        return;

    ActiveWindow = true;
    ContentsTableWindow = new BookTableOfContents(ProgramSettings->getInterfaceStyle(), BookPaginator->getBookContentTable(), this);
    ContentsTableWindow->move(0, ui->MenuButton->height());
    ContentsTableWindow->installEventFilter(this);


    connect(ContentsTableWindow, &BookTableOfContents::goToSection, [this](const long long sectionPos){
        ui->TextPage->setHtml(BookPaginator->goToSection(sectionPos));
        updateProgress();
    });


    connect(ContentsTableWindow, &BookTableOfContents::finished, [this](){
        ContentsTableWindow = 0;
        ActiveWindow = false;
        ui->TextPage->setFocus();
    });

    ContentsTableWindow->show();
}


void ReadingWindow::reprintNewSettText()
{
    setBackgroundImage();
    ui->TextPage->setHtml(BookPaginator->updateSettings(ui->TextPage->width(), ui->TextPage->height()));
}


bool ReadingWindow::createMiniWindow()
{
    if (MiniWindow != 0 || ActiveWindow)
        return false;

    ActiveWindow = true;

    MiniWindow = new ReadingMiniWindow(this);
    MiniWindow->installEventFilter(this);

    connect(MiniWindow, &ReadingMiniWindow::finished, [this](){
        MiniWindow = 0;
        ActiveWindow = false;
        ui->TextPage->setFocus();
    });

    return true;
}


void ReadingWindow::showSearchWindow()
{
    if (!createMiniWindow())
        return;

    SearchWidget = new ReadingSearchWidget(BookPaginator->getBookContentTable(),
                                           CurBook->getProgressPosition(),
                                           BookPaginator->getTextStyles(),
                                           MiniWindow);

    MiniWindow->layout()->addWidget(SearchWidget);

    connect(SearchWidget, &ReadingSearchWidget::startSearch, [this](const QString &token, const bool &caseSensitivity, const bool &punctuation, const int &previewSize){
        SearchWidget->setSearchResults(BookPaginator->searchStart(token, caseSensitivity, punctuation, previewSize));
    });

    connect(SearchWidget, &ReadingSearchWidget::goTo, [this](const BookPosition &pos){
        ui->TextPage->setHtml(BookPaginator->goToPosition(pos));
        updateProgress();
    });

    connect(SearchWidget, SIGNAL(searchClosed()), MiniWindow, SLOT(closeWindow()));

    MiniWindow->openWindow();
}


void ReadingWindow::showSettingsWindow()
{
    if (!createMiniWindow())
        return;

    SettingsLayout *SettingsPage = new SettingsLayout(MiniWindow);

    SettingsPage->setSettingsData();

    MiniWindow->layout()->addWidget(SettingsPage);

    SettingsPage->addExitButton();
    connect(SettingsPage, SIGNAL(settingsClosed()), MiniWindow, SLOT(closeWindow()));

    //TODO: убрать лаг анимации при закрытии
    connect(SettingsPage, SIGNAL(destroyed(QObject*)), this, SLOT(reprintNewSettText()));

    MiniWindow->openWindow();
}


void ReadingWindow::showSynchronizationWindow()
{
    if (!createMiniWindow())
        return;

    MiniWindow->openWindow();
}

#include "main_window.h"
#include "ui_main_window.h"
#include "answer_dialog.h"
#include "styles.h"
#include "genresmap.h"
#include "synchronization.h"
#include "settings.h"

#include <QSizePolicy>
#include <QKeyEvent>
#include <QThread>
#include <QDir>
#include <QProcess>

#include <QDebug>

void MainWindow::setStyle()
{
    QString currentStyle = ProgramSettings->getInterfaceStyle();

    QString styleSheets [10];

    setTopBarBackgroundColor(styleSheets, currentStyle);
    ui->TopBarWidget->setStyleSheet(styleSheets[0]);

    setWindowTopButtonsStyle(styleSheets, currentStyle);
    ui->min_button->setStyleSheet(styleSheets[0]);
    ui->full_size_button->setStyleSheet(styleSheets[1]);

    setExitButtonStyle(styleSheets, currentStyle);
    ui->exit_button->setStyleSheet(styleSheets[0]);

    setBackgroundWindowColor(styleSheets, currentStyle);
    ui->MainWidget->setStyleSheet(styleSheets[0]);

    setMenusButtonsStyle(styleSheets, currentStyle);

    tabSwitcher->setButtonStyleSheet(0, styleSheets[4], styleSheets[0]);
    tabSwitcher->setButtonStyleSheet(1, styleSheets[5], styleSheets[1]);
    tabSwitcher->setButtonStyleSheet(2, styleSheets[6], styleSheets[2]);

    ui->Logout->setStyleSheet(styleSheets[3]);

    ui->LeftExpandingWidget->setStyleSheet(styleSheets[8]);
}




MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainWindow)
{

    UserActions = Synchronization::getSynchronization();
    ProgramSettings = Settings::getSettings();

    ui->setupUi(this);

    connect(ui->min_button, SIGNAL(clicked(bool)), this, SIGNAL(showWindowMinimazed()));
    connect(ui->full_size_button, SIGNAL(clicked(bool)), this, SIGNAL(showWindowMaximazed()));

    connect(ui->LibraryWidget, SIGNAL(showBookPage(unsigned int)), this, SLOT(showBookPage(unsigned int)));

    ui->SettingsWidget->setSettingsData();

    tabSwitcher = new QTabSwitcher(this);

    tabSwitcher->addTab(ui->LibraryWidget, ui->Library);
    tabSwitcher->addTab(ui->SettingsWidget, ui->Settings);
    tabSwitcher->addTab(ui->SynchronizationWidget, ui->Synchronization);

    setStyle();

    tabSwitcher->start(0);
    this->show();
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

library* MainWindow::getLibraryWidget()
{
    return ui->LibraryWidget->getLibraryWidget();
}


void MainWindow::showBookPage(const unsigned int index)
{
    page = new BookPage(ui->LibraryWidget->getBookByIndex(index), ProgramSettings->getInterfaceStyle(), this);
    connect(page, SIGNAL(startReading(unsigned int)), this, SLOT(startReading(unsigned int)));
    connect(page, SIGNAL(deleteBook(unsigned int)), ui->LibraryWidget, SLOT(deleteBook(unsigned int)));
}


void MainWindow::startReading(const unsigned int index)
{
    UserActions->setLastOpenedBookIndex(index);
    emit showReadingWindow();
}

void MainWindow::on_exit_button_clicked()
{
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



void MainWindow::on_Logout_clicked()
{

    AnswerDialog *answer_window = new AnswerDialog(ui->Logout->mapToGlobal(QPoint(ui->Logout->width(),0)),
                                                   QObject::tr("Logout?"),
                                                   ProgramSettings->getInterfaceStyle(),
                                                   this);
    answer_window->show();

    if (answer_window->exec() == QDialog::Accepted)
    {
        delete answer_window;
        emit showLoginWindow();
        return;
    }
    else
        delete answer_window;
}

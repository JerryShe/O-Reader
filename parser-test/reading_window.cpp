#include "reading_window.h"
#include "ui_readingwindow.h"
#include "books.h"
#include "answer_dialog.h"
#include "settings_layout.h"
#include <settings.h>
#include <QTimer>
#include <styles.h>
#include <QMouseEvent>

void ReadingWindow::setStyle(QString currentStyle)
{
    QString styleSheets[8];
    setWindowTopButtonsStyle(styleSheets, currentStyle);
    ui->min_button->setStyleSheet(styleSheets[0]);
    ui->full_size_button->setStyleSheet(styleSheets[1]);
    ui->exit_button->setStyleSheet(styleSheets[2]);

    setBackgroundWindowColor(styleSheets, currentStyle);
    ui->MainWidget->setStyleSheet(styleSheets[0]);
}

ReadingWindow::ReadingWindow(settings * PSettings, Book book) : ui(new Ui::ReadingWindow)
{
    ui->setupUi(this);
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

    ContentsButton = new QPushButton("cont");
    ContentsButton->setMinimumSize(QSize(ui->MenuButton->width(),ui->MenuButton->width()));
    ContentsButton->setMaximumSize(QSize(ui->MenuButton->width(),ui->MenuButton->width()));
    MenuLayout->addWidget(ContentsButton, 0);
    connect(ContentsButton, SIGNAL(clicked(bool)), this, SLOT(ContentsButton_clicked()));

    FindButton = new QPushButton("find");
    FindButton->setMinimumSize(QSize(ui->MenuButton->width(),ui->MenuButton->width()));
    FindButton->setMaximumSize(QSize(ui->MenuButton->width(),ui->MenuButton->width()));
    MenuLayout->addWidget(FindButton, 1);
    connect(FindButton, SIGNAL(clicked(bool)), this, SLOT(FindButton_Clicked()));

    SettingsButton = new QPushButton("sett");
    SettingsButton->setMinimumSize(QSize(ui->MenuButton->width(),ui->MenuButton->width()));
    SettingsButton->setMaximumSize(QSize(ui->MenuButton->width(),ui->MenuButton->width()));
    MenuLayout->addWidget(SettingsButton, 2);
    connect(SettingsButton, SIGNAL(clicked(bool)), this, SLOT(SettingsButton_Clicked()));

    SynchronizationButton = new QPushButton("synch");
    SynchronizationButton->setMinimumSize(QSize(ui->MenuButton->width(),ui->MenuButton->width()));
    SynchronizationButton->setMaximumSize(QSize(ui->MenuButton->width(),ui->MenuButton->width()));
    MenuLayout->addWidget(SynchronizationButton, 3);
    connect(SynchronizationButton, SIGNAL(clicked(bool)), this, SLOT(SynchronizationButton_Clicked()));

    BackToMainWindowButton = new QPushButton("back");
    BackToMainWindowButton->setMinimumSize(QSize(ui->MenuButton->width(),ui->MenuButton->width()));
    BackToMainWindowButton->setMaximumSize(QSize(ui->MenuButton->width(),ui->MenuButton->width()));
    MenuLayout->addWidget(BackToMainWindowButton, 4);
    connect(BackToMainWindowButton, SIGNAL(clicked(bool)), this, SLOT(BackToMainWindowButton_Clicked()));

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
    delete BackToMainWindowButton;
    delete ContentsButton;
    delete SynchronizationButton;
    delete FindButton;
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
            move(e->globalX() - lastPoint.x(),  e->globalY() - lastPoint.y());
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
        if (e->pos().y() <= 50)
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

}

void ReadingWindow::FindButton_Clicked()
{

}

void ReadingWindow::SettingsButton_Clicked()
{

}

void ReadingWindow::SynchronizationButton_Clicked()
{

}

void ReadingWindow::BackToMainWindowButton_Clicked()
{
    emit showMainWindow();
    this->close();
}

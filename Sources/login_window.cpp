
#include "styles.h"
#include "login_window.h"
#include "ui_login_window.h"
#include "answer_dialog.h"
#include "settings.h"

#include <QMouseEvent>
#include <QString>
#include <QDebug>

void LoginWindow::setStyle()
{
    QString styleSheets [8];
    QString currentStyle = Settings::getSettings()->getInterfaceStyle();

    setWindowTopButtonsStyle(styleSheets, currentStyle);

    ui->min_button->setStyleSheet(styleSheets[0]);
    ui->full_size_button->setStyleSheet(styleSheets[1]);

    setExitButtonStyle(styleSheets, currentStyle);
    ui->exit_button->setStyleSheet(styleSheets[0]);

    setBackgroundWindowColor(styleSheets, currentStyle);
    ui->MainWidget->setStyleSheet(styleSheets[0]);

    setLoginWindowStyle(styleSheets, currentStyle);
    ui->login->setStyleSheet(styleSheets[0]);
    ui->Pass->setStyleSheet(styleSheets[1]);
    ui->Name->setStyleSheet(styleSheets[1]);
    ui->repeatPassword->setStyleSheet(styleSheets[1]);
    ui->Recovery->setStyleSheet(styleSheets[2]);
    ui->Registration->setStyleSheet(styleSheets[3]);
    ui->Remember->setStyleSheet(styleSheets[4]);
}

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent), ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setStyle();
    ui->repeatPassword->hide();
    ui->Error->hide();

    connect(ui->min_button, SIGNAL(clicked(bool)), this, SIGNAL(showWindowMinimazed()));
    connect(ui->full_size_button, SIGNAL(clicked(bool)), this, SIGNAL(showWindowMaximazed()));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::backToMainPage()
{
    LoginWindow::activePage = 0;
    ui->Name->setPlaceholderText(QObject::tr("email"));
    ui->Name->clear();
    ui->Error->hide();
    ui->Pass->setPlaceholderText(QObject::tr("password"));
    ui->Pass->clear();
    ui->Pass->show();
    ui->repeatPassword->hide();
    ui->repeatPassword->clear();
    ui->Remember->show();
    ui->Registration->setText(QObject::tr("Create account"));
    ui->Recovery->show();
    ui->login->setText(QObject::tr("Log in"));
}

void LoginWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}

void LoginWindow::on_exit_button_clicked()
{
    AnswerDialog *answer_window = new AnswerDialog(ui->exit_button->mapToGlobal(QPoint(ui->exit_button->width() - 300, ui->exit_button->height())),
                                                   QObject::tr("Exit?"),
                                                   Settings::getSettings()->getInterfaceStyle(),
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

void LoginWindow::on_Registration_clicked()
{
    if (activePage != 0)
    {
        backToMainPage();
    }
    else
    {
        activePage = 1;
        ui->login->setText(QObject::tr("Sign up"));
        ui->repeatPassword->show();
        ui->Remember->hide();
        ui->Recovery->hide();
        ui->Registration->setText(QObject::tr("Back"));
    }
}


void LoginWindow::on_login_clicked()
{

    switch (activePage)
    {
    case 0:
        // здесь надо вставить проверку пароля на серве
        // если соединения с сервером нет, то сказать, что программа будет работать в автономном режиме и проверить пароль локально

        emit showMainWindow();
        return;

    case 1:
        //здесь надо пингануть серву, чтобы зарегал пользователя и выслал код подтверждения
        LoginWindow::activePage = 2;
        ui->Name->setPlaceholderText(QObject::tr("enter code from email"));
        ui->Name->clear();
        ui->Pass->hide();
        ui->repeatPassword->hide();
        ui->login->setText(QObject::tr("Verify account"));
        return;

    case 2:
        if (ui->Pass->text() != ui->repeatPassword->text())
        {
            ui->Error->show();
        }
        else
        {
            //здесь надо вывести окно Done! если все норм
            //и заменить пароль на серве и в хеше
            backToMainPage();
        }
        return;

    case 3:
        if (ui->Pass->text() == ui->repeatPassword->text())
        {
            //здесь надо вставить проверку легитимности введенного email
            //и выслать код смены пароля с серва пользователю
            LoginWindow::activePage = 4;
            ui->Name->setPlaceholderText(QObject::tr("enter code from email"));
            ui->Name->clear();
            ui->Pass->setPlaceholderText(QObject::tr("new password"));
            ui->Pass->clear();
            ui->Pass->show();
            ui->repeatPassword->clear();
            ui->repeatPassword->show();
            return;
        }
        else
        {
            ui->Error->show();
            return;
        }

    case 4:
        //здесь надо отослать код серву для проверки
        backToMainPage();
        return;

    default:
        return;
    }
}

void LoginWindow::on_Recovery_clicked()
{
    LoginWindow::activePage = 3;
    ui->Pass->hide();
    ui->repeatPassword->hide();
    ui->Remember->hide();
    ui->Registration->setText(QObject::tr("Back"));
    ui->Recovery->hide();
    ui->login->setText(QObject::tr("Change password"));
}

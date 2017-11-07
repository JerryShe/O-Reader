#include "styles.h"
#include "login_window/login_window.h"
#include "ui_login_window.h"
#include "custom_widgets/answer_dialog.h"
#include "data_handlers/settings_handler.h"

#include <QMouseEvent>
#include <QString>
#include <QDebug>

void LoginWindow::setStyle()
{
    QString styleSheets [8];
    QString currentStyle = SettingsHandler::getSettings()->getInterfaceStyle();

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

    ui->Error->setStyleSheet("color: red;");
}


LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent), ui(new Ui::LoginWindow)
{
    clientHandler = ClientHandler::getClientHandler();

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


void LoginWindow::toMainPage()
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


void LoginWindow::toSignupPage()
{
    activePage = 1;
    ui->Error->hide();
    ui->login->setText(QObject::tr("Sign up"));
    ui->repeatPassword->show();
    ui->Remember->hide();
    ui->Recovery->hide();
    ui->Registration->setText(QObject::tr("Back"));
}


void LoginWindow::toSignupConfPage()
{
    activePage = 2;
    ui->Error->hide();
    ui->Name->setPlaceholderText(QObject::tr("enter code from email"));
    ui->Name->clear();
    ui->Pass->hide();
    ui->repeatPassword->hide();
    ui->login->setText(QObject::tr("Verify account"));
}


void LoginWindow::toRecoveryPage()
{
    activePage = 3;
    ui->Error->hide();
    ui->Pass->hide();
    ui->repeatPassword->hide();
    ui->Remember->hide();
    ui->Registration->setText(QObject::tr("Back"));
    ui->Recovery->hide();
    ui->login->setText(QObject::tr("Change password"));
}


void LoginWindow::toRecoveryConfirmPage()
{
    activePage = 4;
    ui->Error->hide();
    ui->Name->setPlaceholderText(QObject::tr("enter code from email"));
    ui->Name->clear();
    ui->Pass->setPlaceholderText(QObject::tr("new password"));
    ui->Pass->clear();
    ui->Pass->show();
    ui->repeatPassword->clear();
    ui->repeatPassword->show();
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
                                                   this);
    answer_window->show();

    if (answer_window->exec() == QDialog::Accepted)
        emit closeWindow();

    delete answer_window;
}


void LoginWindow::on_login_clicked()
{

    switch (activePage)
    {
    case 0:
        if (clientHandler->loginOnServer(ui->Name->text(), ui->Pass->text()))
        {
            ui->Error->hide();
            emit showMainWindow();
        }
        else
        {
            ui->Error->show();
            ui->Error->setText(QObject::tr("Invalid login or password!"));
        }
        return;

    case 1:
        if (!checkEmail(ui->Name->text()))
        {
            ui->Error->show();
            ui->Error->setText(QObject::tr("Incorrect Email!"));
        }
        else
        if (ui->Pass->text() != ui->repeatPassword->text())
        {
            ui->Error->show();
            ui->Error->setText(QObject::tr("Passwords do not match!"));
        }
        else
        {
            ui->Error->hide();

            if (clientHandler->signup(ui->Name->text(), ui->Pass->text()))
                toSignupConfPage();
            else
                ui->Error->setText(QObject::tr("This email is already registered!"));
        }
        return;

    case 2:
        if (clientHandler->signupConfirm(ui->Name->text()))
            toMainPage();
        else
        {
            ui->Error->show();
            ui->Error->setText(QObject::tr("Incorrect code!"));
        }
        return;

    case 3:
        if (clientHandler->changePass(ui->Name->text()) && checkEmail(ui->Name->text()))
            toRecoveryConfirmPage();
        else
        {
            ui->Error->show();
            ui->Error->setText(QObject::tr("Incorrect Email!"));
        }
        return;

    case 4:
        if (ui->Pass->text() != ui->repeatPassword->text())
        {
            ui->Error->show();
            ui->Error->setText(QObject::tr("Passwords do not match!"));
        }
        else
        if (clientHandler->changeConfirm(ui->Name->text(), ui->Pass->text()))
        {
            ///well done
            toMainPage();
        }
        else
        {
            ui->Error->show();
            ui->Error->setText(QObject::tr("Incorrect code!"));
        }
        return;

    default:
        return;
    }
}


void LoginWindow::on_Registration_clicked()
{
    if (activePage != 0)
        toMainPage();
    else
        toSignupPage();
}


void LoginWindow::on_Recovery_clicked()
{
    toRecoveryPage();
}


bool LoginWindow::checkEmail(const QString &email)
{
    if (email.isEmpty())
        return false;

    QRegularExpression regex("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");
    if (regex.match(email).hasMatch())
        return true;
    else
        return false;
}

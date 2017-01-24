#include <styles.h>
#include "login_window.h"
#include "ui_loginwindow.h"
#include "answer_dialog.h"
#include "settings.h"

#include <QMouseEvent>
#include <QString>
#include <QDebug>


void LoginWindow::setStyle()
{
    setWindowTopButtonsStyle(LoginWindow::styleSheets, LoginWindow::currentStyle);

    ui->min_button->setStyleSheet(LoginWindow::styleSheets[0]);
    ui->full_size_button->setStyleSheet(LoginWindow::styleSheets[1]);

    setExitButtonStyle(LoginWindow::styleSheets, LoginWindow::currentStyle);
    ui->exit_button->setStyleSheet(LoginWindow::styleSheets[0]);

    setBackgroundWindowColor(LoginWindow::styleSheets, LoginWindow::currentStyle);
    ui->MainWidget->setStyleSheet(LoginWindow::styleSheets[0]);

    setLoginWindowStyle(LoginWindow::styleSheets, LoginWindow::currentStyle);
    ui->login->setStyleSheet(LoginWindow::styleSheets[0]);
    ui->Pass->setStyleSheet(LoginWindow::styleSheets[1]);
    ui->Name->setStyleSheet(LoginWindow::styleSheets[1]);
    ui->repeatPassword->setStyleSheet(LoginWindow::styleSheets[1]);
    ui->Recovery->setStyleSheet(LoginWindow::styleSheets[2]);
    ui->Registration->setStyleSheet(LoginWindow::styleSheets[3]);
    ui->Remember->setStyleSheet(LoginWindow::styleSheets[4]);
}

LoginWindow::LoginWindow(QTranslator *translator, QWidget *parent) : QMainWindow(parent), ui(new Ui::LoginWindow), LanguageTranslator(translator)
{
    QFile SettingsFile("LibraryResources/Settings.conf");

    if(SettingsFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QDataStream in(&SettingsFile);
        in>>currentStyle; //for token
        in>>currentStyle;
    }
    else
    {
        currentStyle = "Red";
    }
    SettingsFile.close();
    LanguageTranslator = translator;

    ui->setupUi(this);
    LoginWindow::setStyle();
    LoginWindow::prev_geometry = LoginWindow::geometry();
    ui->repeatPassword->hide();
    ui->Error->hide();

    ui->MainWidget->setAttribute(Qt::WA_MouseTracking);
    LoginWindow::setMouseTracking(true);
}

LoginWindow::~LoginWindow()
{
    delete ui;
    delete main_window;
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

void LoginWindow::on_exit_button_clicked()
{
    AnswerDialog *answer_window = new AnswerDialog(ui->exit_button->mapToGlobal(QPoint(0,0)).x() - 300 + ui->exit_button->width(),ui->exit_button->mapToGlobal(QPoint(0,0)).y() + ui->exit_button->height(),"Exit?", currentStyle);
    answer_window->show();

    if (answer_window->exec() == QDialog::Accepted)
    {
        exit(0);
    }
    else
        delete answer_window;
}


void LoginWindow::on_full_size_button_clicked()
{
    if( LoginWindow::isMaximized())
    {
        LoginWindow::normalGeometry() = LoginWindow::prev_geometry;
        LoginWindow::showNormal();
    }
    else
    {
        LoginWindow::prev_geometry = LoginWindow::geometry();
        LoginWindow::showMaximized();
    }
}

void LoginWindow::on_min_button_clicked()
{
    if( LoginWindow::isMinimized())
    {
        LoginWindow::normalGeometry() = LoginWindow::prev_geometry;
        LoginWindow::showNormal();
    }
    else
    {
        LoginWindow::prev_geometry = LoginWindow::geometry();
        LoginWindow::showMinimized();
    }
}

void LoginWindow::on_Registration_clicked()
{
    if (LoginWindow::activePage != 0)
    {
        backToMainPage();
    }
    else
    {
        LoginWindow::activePage = 1;
        ui->login->setText(QObject::tr("Sign up"));
        ui->repeatPassword->show();
        ui->Remember->hide();
        ui->Recovery->hide();
        ui->Registration->setText(QObject::tr("Back"));
    }
}


void LoginWindow::on_login_clicked()
{

    switch (LoginWindow::activePage)
    {
    case 0:
        // здесь надо вставить проверку пароля на серве
        // если соединения с сервером нет, то сказать, что программа будет работать в автономном режиме и проверить пароль локально
        main_window = new MainWindow(LanguageTranslator);
        main_window->setWindowFlags(Qt::CustomizeWindowHint);
        main_window->show();
        LoginWindow::close();

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




void LoginWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (LoginWindow::moving)
    {
        if (!LoginWindow::isMaximized())
        {
            move(e->globalX() - lastPoint.x() - 7, e->globalY() - lastPoint.y() - 7);
        }
        else
        {
            LoginWindow::prev_geometry.setY(e->globalY());
            LoginWindow::normalGeometry() = LoginWindow::prev_geometry;
            LoginWindow::showNormal();
        }
    }
}

void LoginWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        if (e->pos().y() <= 50 && e->pos().y() > LoginWindow::resizingFrame)
        {
            LoginWindow::moving = true;
            LoginWindow::lastPoint = e->pos();
        }
    }
}

void LoginWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        if (LoginWindow::moving)
            LoginWindow::moving = false;
    }
}

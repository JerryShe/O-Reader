#include <styles.h>
#include "login_window.h"
#include "ui_loginwindow.h"
#include "answer_dialog.h"
#include <QMouseEvent>
#include <QString>


#include <iostream>


LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::LoginWindow)
{

    ui->setupUi(this);
    LoginWindow::prev_geometry = LoginWindow::geometry();
    ui->repeatPassword->hide();
    ui->Error->hide();

    ui->MainWidget->setAttribute(Qt::WA_MouseTracking);
    LoginWindow::setMouseTracking(true);


    /////////////////////////////////////////////////////////////////////////////////////
    setWindowTopButtonsStyle(LoginWindow::styleSheets, "red");

    ui->min_button->setStyleSheet(LoginWindow::styleSheets[0]);
    ui->full_size_button->setStyleSheet(LoginWindow::styleSheets[1]);
    ui->exit_button->setStyleSheet(LoginWindow::styleSheets[2]);

    setBackgroundWindowColor(LoginWindow::styleSheets, "red");

    ui->MainWidget->setStyleSheet(LoginWindow::styleSheets[0]);

    setLoginWindowStyle(LoginWindow::styleSheets, "red");

    ui->login->setStyleSheet(LoginWindow::styleSheets[0]);
    ui->Pass->setStyleSheet(LoginWindow::styleSheets[1]);
    ui->Name->setStyleSheet(LoginWindow::styleSheets[1]);
    ui->repeatPassword->setStyleSheet(LoginWindow::styleSheets[1]);
    ui->Forgot->setStyleSheet(LoginWindow::styleSheets[2]);
    ui->Registration->setStyleSheet(LoginWindow::styleSheets[3]);
    ui->Remember->setStyleSheet(LoginWindow::styleSheets[4]);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::backToMainPage()
{
    ui->Name->setPlaceholderText("email");
    ui->Name->clear();
    ui->Error->hide();
    ui->Pass->setPlaceholderText("password");
    ui->Pass->clear();
    ui->Pass->show();
    ui->repeatPassword->hide();
    ui->repeatPassword->clear();
    ui->Remember->show();
    ui->Registration->setText("Create account");
    ui->Forgot->show();
    ui->login->setText("Log in");
}




void LoginWindow::on_exit_button_clicked()
{
    AnswerDialog *answer_window = new AnswerDialog(ui->exit_button->mapToGlobal(QPoint(0,0)).x()-280,ui->exit_button->mapToGlobal(QPoint(0,0)).y()+20,"Fuck?");
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
    if (ui->Registration->text() == "Back")
    {
        backToMainPage();
    }
    else
    {
        ui->login->setText("Sign up");
        ui->repeatPassword->show();
        ui->Remember->hide();
        ui->Forgot->hide();
        ui->Registration->setText("Back");
    }
}


void LoginWindow::on_login_clicked()
{
    if (ui->Name->placeholderText() == "enter code from email")
    {
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
    }

    if (ui->login->text() == "Change password")
    {
        //здесь надо вставить проверку легитимности введенного email
        //и выслать код смены пароля с серва пользователю
        ui->Name->setPlaceholderText("enter code from email");
        ui->Name->clear();
        ui->Pass->setPlaceholderText("new password");
        ui->Pass->clear();
        ui->Pass->show();
        ui->repeatPassword->clear();
        ui->repeatPassword->show();
        return;
    }
    if (ui->login->text() == "Sign up")
    {
        if (ui->Pass->text() == ui->repeatPassword->text())
        {
            //здесь надо пингануть серву, чтобы зарегал пользователя и выслал код подтверждения
            ui->Name->setPlaceholderText("enter code from email");
            ui->Name->clear();
            ui->Pass->hide();
            ui->repeatPassword->hide();
            ui->login->setText("Verify account");
            return;
        }
        else
        {
            ui->Error->show();
            return;
        }
    }
    if (ui->login->text() == "Verify account")
    {
        //здесь надо отослать код серву для проверки
        backToMainPage();
        return;
    }



     // здесь надо вставить проверку пароля на серве
     // если создинения с сервером нет, то сказать, что программа будет работать в автономном режиме и проверить из хеша


    main_fucking_window = new MainWindow();
    main_fucking_window->setWindowFlags(Qt::CustomizeWindowHint);
    main_fucking_window->show();
    LoginWindow::close();

}

void LoginWindow::on_Forgot_clicked()
{
    ui->Pass->hide();
    ui->repeatPassword->hide();
    ui->Remember->hide();
    ui->Registration->setText("Back");
    ui->Forgot->hide();
    ui->login->setText("Change password");
}




void LoginWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (LoginWindow::moving)
    {
        if (!LoginWindow::isMaximized())
        {
            move(e->globalX() - LoginWindow::lastPoint.x(),  e->globalY() - LoginWindow::lastPoint.y());
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




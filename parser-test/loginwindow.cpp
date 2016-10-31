#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include "answerdialog.h"

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::LoginWindow)
{

    ui->setupUi(this);
    LoginWindow::prev_geometry = LoginWindow::geometry();
    ui->MainWidget->setAttribute(Qt::WA_MouseTracking);
    LoginWindow::setMouseTracking(true);

}

LoginWindow::~LoginWindow()
{
    delete ui;
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

void LoginWindow::on_login_clicked()
{
    main_fucking_window = new MainWindow();
    main_fucking_window->setWindowFlags(Qt::FramelessWindowHint);
    main_fucking_window->show();
    LoginWindow::close();

}

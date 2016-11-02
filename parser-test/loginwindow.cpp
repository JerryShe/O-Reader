#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "LoginWindow.h"
#include "answerdialog.h"

#include <QMouseEvent>

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

void LoginWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (LoginWindow::resizing && !LoginWindow::moving)
    {
        switch (LoginWindow::resizingMethod)
        {
        case 1:
            LoginWindow::resize(LoginWindow::width(), LoginWindow::lastWindowHeight + (LoginWindow::lastMouseGlobalPos.y() - e->globalY()));
            if (LoginWindow::height() > 643)
            LoginWindow::move(LoginWindow::x(), e->globalY());
            break;
        case 3:
            LoginWindow::resize(LoginWindow::lastWindowWidth + (LoginWindow::lastMouseGlobalPos.x() - e->globalX()), LoginWindow::height());
            if (LoginWindow::width() > 566)
                LoginWindow::move(e->globalX(), LoginWindow::y());
            break;
        case 2:
            LoginWindow::resize(LoginWindow::width(), LoginWindow::lastWindowHeight - (LoginWindow::lastMouseGlobalPos.y() - e->globalY()));
            break;
        case 6:
            LoginWindow::resize(LoginWindow::lastWindowWidth - (LoginWindow::lastMouseGlobalPos.x() - e->globalX()), LoginWindow::height());
            break;
        case 4:
            LoginWindow::resize(LoginWindow::lastWindowWidth + (LoginWindow::lastMouseGlobalPos.x() - e->globalX()), LoginWindow::lastWindowHeight + (LoginWindow::lastMouseGlobalPos.y() - e->globalY()));
            if (LoginWindow::width() > 566 && LoginWindow::height() > 543)
                LoginWindow::move(e->globalX(), e->globalY());
            break;
        case 7:
            LoginWindow::resize(LoginWindow::lastWindowWidth - (LoginWindow::lastMouseGlobalPos.x() - e->globalX()), LoginWindow::lastWindowHeight + (LoginWindow::lastMouseGlobalPos.y() - e->globalY()));
            if (LoginWindow::height() > 543)
                LoginWindow::move(LoginWindow::x(), e->globalY());
            break;
        case 5:
            LoginWindow::resize(LoginWindow::lastWindowWidth + (LoginWindow::lastMouseGlobalPos.x() - e->globalX()), LoginWindow::lastWindowHeight - (LoginWindow::lastMouseGlobalPos.y() - e->globalY()));
            if (LoginWindow::width() > 566)
                LoginWindow::move(e->globalX(), LoginWindow::y());
            break;
        case 8:
            LoginWindow::resize(LoginWindow::lastWindowWidth - (LoginWindow::lastMouseGlobalPos.x() - e->globalX()), LoginWindow::lastWindowHeight - (LoginWindow::lastMouseGlobalPos.y() - e->globalY()));
            break;

        }
    }
    else
    if (!LoginWindow::moving && !LoginWindow::resizing)
    {
        LoginWindow::resizingMethod = 0;
        if (e->pos().y() < LoginWindow::resizingFrame)
            LoginWindow::resizingMethod += 1;
        if (e->pos().y() > LoginWindow::size().height() - LoginWindow::resizingFrame)
            LoginWindow::resizingMethod += 2;
        if (e->pos().x() < LoginWindow::resizingFrame)
            LoginWindow::resizingMethod += 3;
        if(e->pos().x() > LoginWindow::size().width() - LoginWindow::resizingFrame)
            LoginWindow::resizingMethod += 6;

        switch (LoginWindow::resizingMethod)
        {
        case 0:
            LoginWindow::setCursor(Qt::ArrowCursor);
            break;
        case 1:
            LoginWindow::setCursor(Qt::SizeVerCursor);
            break;
        case 2:
            LoginWindow::setCursor(Qt::SizeVerCursor);
            break;
        case 3:
            LoginWindow::setCursor(Qt::SizeHorCursor);
            break;
        case 4:
            LoginWindow::setCursor(Qt::SizeFDiagCursor);
            break;
        case 5:
            LoginWindow::setCursor(Qt::SizeBDiagCursor);
            break;
        case 6:
            LoginWindow::setCursor(Qt::SizeHorCursor);
            break;
        case 7:
            LoginWindow::setCursor(Qt::SizeBDiagCursor);
            break;
        case 8:
            LoginWindow::setCursor(Qt::SizeFDiagCursor);
            break;
        }

    }
    else
    if (LoginWindow::moving && !LoginWindow::resizing)
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

        if(LoginWindow::resizingMethod)
        {
            resizing = true;
            LoginWindow::lastMouseGlobalPos = e->globalPos();
            LoginWindow::lastWindowHeight = LoginWindow::height();
            LoginWindow::lastWindowWidth = LoginWindow::width();
        }
    }
}

void LoginWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        if (LoginWindow::moving)
            LoginWindow::moving = false;

        if (LoginWindow::resizing)
        {
            LoginWindow::resizing = false;
            LoginWindow::setCursor(Qt::ArrowCursor);
        }
    }
}




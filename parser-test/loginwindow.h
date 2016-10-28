#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <mainwindow.h>

namespace Ui
{
    class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private slots:
    void on_exit_button_clicked();

    void on_full_size_button_clicked();

    void on_min_button_clicked();


    void on_login_clicked();

private:

    QRect prev_geometry;

    int activeMenuButton;
    bool moving;
    bool resizing;
    QPoint lastPoint;
    QPoint lastGlobalPos;
    int resizingFrame = 5;

    Ui::LoginWindow *ui;

    MainWindow main_fucking_window;
};

#endif // LOGINWINDOW_H

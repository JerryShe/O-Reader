#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <main_window.h>

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
    void on_Recovery_clicked();
    void on_Registration_clicked();
    void backToMainPage();

    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    QString styleSheets [8];

    QRect prev_geometry;

    // 0 - Main
    // 1 - Registration - email
    // 2 - Registration - confirm
    // 3 - Recovery - email
    // 4 - Recovery - confirm
    int activePage = 0;


    bool moving = false;
    int resizingMethod;
    bool resizing = false;
    QPoint lastPoint;
    QPoint lastMouseGlobalPos;
    int lastWindowHeight;
    int lastWindowWidth;
    int resizingFrame = 5;

    Ui::LoginWindow *ui;

    MainWindow *main_window;
};

#endif // LOGINWINDOW_H

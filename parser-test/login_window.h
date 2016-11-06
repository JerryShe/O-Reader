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
    void on_Forgot_clicked();
    void on_Registration_clicked();
    void backToMainPage();

    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    QString styleSheets [8];

    QRect prev_geometry;

    int activeMenuButton;
    bool moving = false;
    int resizingMethod;
    bool resizing = false;
    QPoint lastPoint;
    QPoint lastMouseGlobalPos;
    int lastWindowHeight;
    int lastWindowWidth;
    int resizingFrame = 5;

    Ui::LoginWindow *ui;

    MainWindow *main_fucking_window;
};

#endif // LOGINWINDOW_H

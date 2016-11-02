#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QRect>
#include <QEvent>
#include <QPalette>


namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_exit_button_clicked();

    void on_full_size_button_clicked();

    void on_min_button_clicked();

    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    void on_Library_clicked();
    void on_Settings_clicked();
    void on_Synchronization_clicked();
    void on_Logout_clicked();
    void on_AddBook_clicked();
    void on_AddFolder_clicked();
    void on_TableView_clicked();

private:
    QString MenuButtonsSheets [8];
    QRect prev_geometry;

    int activeWindow = 1;
    bool moving = false;
    int resizingMethod;
    bool resizing = false;
    QPoint lastPoint;
    QPoint lastMouseGlobalPos;
    int lastWindowHeight;
    int lastWindowWidth;
    int resizingFrame = 5;

    Ui::MainWindow *ui;

    bool eventFilter(QObject *target, QEvent *event);

};


#endif // MAINWINDOW_H

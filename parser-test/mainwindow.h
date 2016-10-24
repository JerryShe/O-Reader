#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSize>
#include <QRect>
#include <QEvent>


namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    QRect prev_geometry;

    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_exit_button_clicked();

    void on_full_size_button_clicked();

    void on_min_button_clicked();

    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    bool moving;
    bool resizing;
    QPoint lastPoint;
    QPoint lastGlobalPos;
    int resizingFrame = 5;
    Ui::MainWindow *ui;

};


#endif // MAINWINDOW_H

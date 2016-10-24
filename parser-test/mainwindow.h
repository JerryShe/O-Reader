#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSize>
#include <QRect>

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

private:
    Ui::MainWindow *ui;

};


#endif // MAINWINDOW_H

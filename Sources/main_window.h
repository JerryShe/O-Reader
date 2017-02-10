#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QFile>
#include <QTranslator>

#include "synchronization.h"
#include "settings.h"
#include "reading_window.h"
#include "book_page.h"
#include "QTabSwitcher.h"


namespace Ui
{
    class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QTranslator *translator, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void showWindow(bool closeType);

    void setStyle();

    void on_exit_button_clicked();
    void on_full_size_button_clicked();
    void on_min_button_clicked();

    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    void on_Logout_clicked();

    void startReading(const int index);
    void showBookPage(const int index);

protected:
    void changeEvent(QEvent *event);

private:
    QString styleSheets [9];
    QString tabsStyleSheets [5];

    QRect prev_geometry;
    QPoint lastPoint;
    QPoint lastMouseGlobalPos;

    bool moving = false;
    int resizingMethod;
    bool resizing = false;

    int lastWindowHeight;
    int lastWindowWidth;
    int resizingFrame = 5;

    Ui::MainWindow* ui;

    ReadingWindow* readingWindow;
    BookPage* page;

    QTabSwitcher* tabSwitcher;

    QString resoursesFolderPath;

    QThread * HandlerThread;

    Synchronization* UserActions;
    settings* ProgramSettings;
};

#endif // MAINWINDOW_H

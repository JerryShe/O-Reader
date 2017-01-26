#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRect>
#include <QEvent>
#include <QGridLayout>
#include <QFile>
#include <QTranslator>

#include "library_layout.h"
#include "books.h"
#include "book_or_folder.h"
#include "book_page.h"
#include "library_layout.h"
#include "synchronization.h"
#include "settings.h"
#include "reading_window.h"
#include "search_window.h"
#include "libraryhandler.h"


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

    void on_exit_button_clicked();
    void on_full_size_button_clicked();
    void on_min_button_clicked();

    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    void libraryButtonsHide();
    void libraryButtonsShow();

    void returnButton();

    void on_Library_clicked();
    void on_Settings_clicked();
    void on_Synchronization_clicked();
    void on_Logout_clicked();
    void on__AddBooks_clicked();

    void on__SortBox_activated(const QString &arg1);

    void setWindowStyle(QString currentStyle);

    void on__Delete_clicked();
    void on__ChangeViewMode_toggled(bool checked);
    void on__Upscale_clicked();
    void on__Downscale_clicked();
    void on__Find_toggled(bool checked);

    void startReading(const int index);
    void showBookPage(const int index);

    void addBooksFolder();
    void addBooksFiles();

protected:
    void changeEvent(QEvent *event);

private:
    int activeWindow = 1;
    QString styleSheets [9];
    QString tabsStyleSheets [5];
    QString currentStyle;

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
    SearchWindow* searchWindow;
    BookPage* page;

    QString resoursesFolderPath;

    QThread * HandlerThread;
    LibraryHandler * LibHandler;
    librarylayout* LibraryLayout;
    Synchronization* UserActions;
    settings* ProgramSettings;
};

#endif // MAINWINDOW_H

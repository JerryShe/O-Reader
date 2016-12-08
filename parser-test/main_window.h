#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QRect>
#include <QEvent>
#include <QPalette>
#include <QGridLayout>
#include <QFrame>
#include <QFile>

#include "library_layout.h"
#include "books.h"
#include "book_or_folder.h"
#include "book_page.h"
#include "library_layout.h"
#include "synchronization.h"
#include "settings.h"
#include "reading_window.h"
#include "search_window.h"


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
    void loadBookList();
    void saveBookList();

    void AddBook();
    void AddFolder();
    void deleteBook(int index);

    void startReading(int index);
    void showBookPage(int index);
    void showWindow();

    void settingsTabChanged(int tab);

    void on_exit_button_clicked();
    void on_full_size_button_clicked();
    void on_min_button_clicked();

    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    void libraryButtonsHide();
    void settingsButtonsHide();
    void libraryButtonsShow();
    void settingsButtonsShow();

    void returnButton();

    void openNewBooks(QString fileList, GenresMap *Gmap);
    QString getFileTipe(QString fileName);
    void findBooks(QString,QString);

    void on_Library_clicked();
    void on_Settings_clicked();
    void on_Synchronization_clicked();
    void on_Logout_clicked();
    void on__AddBooks_clicked();
    void on__SettingsProfile_clicked();
    void on__SettingsProgram_clicked();
    void on__SettingsReader_clicked();

    void setStyle();

    void on__Delete_clicked();
    void on__ChangeViewMode_clicked();
    void on__Upscale_clicked();
    void on__Downscale_clicked();
    void on__Find_toggled(bool checked);

private:
    int activeWindow = 1;
    QString styleSheets [9];
    QString tabsStyleSheets [5];
    QString currentStyle;

    int currentBookIndex;

    QRect prev_geometry;
    QPoint lastPoint;
    QPoint lastMouseGlobalPos;

    bool moving = false;
    int resizingMethod;
    bool resizing = false;

    int lastWindowHeight;
    int lastWindowWidth;
    int resizingFrame = 5;

    Ui::MainWindow * ui;
    BookPage * page;
    ReadingWindow * readingWindow;
    SearchWindow * searchWindow;

    librarylayout * LibraryLayout;
    Synchronization *UserActions;
    settings *ProgramSettings;

    QStringList filesMask;
    QVector <Book> bookList;
    QString resoursesFolderPath;

    QThread * HandlerThread;

};


#endif // MAINWINDOW_H

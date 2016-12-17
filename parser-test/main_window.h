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

class LibraryHandler;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
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

    void on_Library_clicked();
    void on_Settings_clicked();
    void on_Synchronization_clicked();
    void on_Logout_clicked();
    void on__AddBooks_clicked();
    void on__SettingsProfile_clicked();
    void on__SettingsProgram_clicked();
    void on__SettingsReader_clicked();    

    void on__SortBox_activated(const QString &arg1);

    void setStyle();

    void on__Delete_clicked();
    void on__ChangeViewMode_clicked();
    void on__Upscale_clicked();
    void on__Downscale_clicked();
    void on__Find_toggled(bool checked);

    void startReading(int index);
    void showBookPage(int index);

    void addBooksFolder();
    void addBooksFiles();

    //QVector <Book> BookSort( bool(*compare)(Book&, Book&) );

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

    Ui::MainWindow * ui;

    librarylayout * LibraryLayout;
    Synchronization *UserActions;
    settings *ProgramSettings;

    ReadingWindow * readingWindow;
    SearchWindow * searchWindow;
    BookPage * page;

    QString resoursesFolderPath;

    QThread * HandlerThread;

    LibraryHandler * LibHandler;
    friend class LibraryHandler;

};

class LibraryHandler: public QObject
{
    Q_OBJECT

public:
    LibraryHandler(MainWindow *par)
    {
        window = par;
        currentBookIndex = 0;
        filesMask<<"*.fb2"<<"*.zip";
    }

public slots:
    void AddBooks(QStringList fileList);
    void AddFolder(QString path);
    void deleteBook(int index);
    void deleteBooks(QVector <int> deletedItemsIndexes);

    void openNewBooks(QString fileList, GenresMap *Gmap);
    QString getFileTipe(QString fileName);

    void findBooks(QString,QString);

    void loadBookList();
    void saveBookList();

public:
    QStringList filesMask;
    QVector <Book> bookList;
    int currentBookIndex;

private:
    MainWindow * window;
};




#endif // MAINWINDOW_H

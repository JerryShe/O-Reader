#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QRect>
#include <QEvent>
#include <QPalette>
#include <QGridLayout>
#include <QFrame>
#include <QFile>
#include <library_layout.h>
#include <books.h>


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

    void openNewBooks(QStringList fileList);
    QString FileTipe(QString fileName);

    void on_Library_clicked();
    void on_Settings_clicked();
    void on_Synchronization_clicked();
    void on_Logout_clicked();
    void on__AddBook_clicked();
    void on__AddFolder_clicked();

    void on__SettingsProfile_clicked();

    void on__SettingsProgram_clicked();

    void on__SettingsReader_clicked();

    void on__SettingsSynchronization_clicked();

private:
    int activeWindow = 1;
    QString styleSheets [9];
    QString tabsStyleSheets [2];


    QRect prev_geometry;
    QPoint lastPoint;
    QPoint lastMouseGlobalPos;

    bool moving = false;
    int resizingMethod;
    bool resizing = false;

    int lastWindowHeight;
    int lastWindowWidth;
    int resizingFrame = 5;

    Ui::MainWindow *ui;

    QStringList filesMask;

    QVector <Book> bookList;

    QString resoursesFolderPath;
};


#endif // MAINWINDOW_H

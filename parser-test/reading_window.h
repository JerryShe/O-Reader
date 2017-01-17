#ifndef READINGWINDOW_H
#define READINGWINDOW_H

#include <QMainWindow>
#include <books.h>
#include <answer_dialog.h>
#include <QThread>
#include <settings.h>
#include <QVBoxLayout>
#include "settings_layout.h"
#include "search_window.h"
#include "synchronization_layout.h"
#include "fb2textparser.h"

#include <QThread>
#include <QDomDocument>
#include <QKeyEvent>

namespace Ui {
class ReadingWindow;
}

class ReadingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReadingWindow(settings * PSettings, Book book);
    ~ReadingWindow();

private slots:
    void on_min_button_clicked();
    void on_full_size_button_clicked();
    void on_exit_button_clicked();
    void on_MenuButton_clicked();
    void ContentsButton_clicked();
    void FindButton_Clicked();
    void SettingsButton_Clicked();
    void SynchronizationButton_Clicked();
    void BackToMainWindowButton_Clicked();

    void setStyle(QString currentStyle);

    void mouseMoveEvent(QMouseEvent * e);
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);

    void StartSearch(QString key, QString type);
    void NextSearchStep();
    void PrevSearchStep();

    void settings_profile_clicked();
    void settings_program_clicked();
    void settings_reader_clicked();
    void changeSettingsTab(int i);

    void clockStep();
    void updateProgress();

    void resizeEvent(QResizeEvent * e);
    void reprintText();

signals:
    void showMainWindow();
    void windowWasResized();

protected:
   virtual void keyPressEvent(QKeyEvent *event);

private:
    QRect prev_geometry;
    bool moving = false;
    bool TopBarNeedHide;
    short HidenTimer;
    QPoint lastPoint;
    int resizingFrame = 5;

    int SettingsTab;

    Ui::ReadingWindow *ui;
    QThread * HandlerThread;
    settings * ProgramSettings;

    QWidget * MenuWidget;
    QVBoxLayout * MenuLayout;
    QPushButton * _BackToMainWindowButton;
    QPushButton * _ContentsButton;
    QPushButton * _SynchronizationButton;
    QPushButton * _FindButton;
    QPushButton * _SettingsButton;

    settingslayout *SettingsPage;
    synchronizationlayout *SynchronizationPage;

    QThread * parserThread;

    QVBoxLayout * WindowLayout;
    QHBoxLayout * SettingsTabsLayout;
    QDialog *MiniWindow;
    QPushButton * ProfileButton;
    QPushButton * ProgramButton;
    QPushButton * ReaderButton;
    QPushButton * SettingsExitButton;

    SearchWindow * Search;

    QString styles[5];

    FB2TextParser * BookParse;
};

#endif // READINGWINDOW_H


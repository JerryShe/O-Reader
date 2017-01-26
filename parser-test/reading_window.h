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
#include "fb2textpaginator.h"

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
    explicit ReadingWindow(Book *book);
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

    void StartSearch(QString key, QString type);
    void NextSearchStep();
    void PrevSearchStep();

    void clockStep();
    void updateProgress();

    void reprintResizedText();
    void reprintNewSettText();

    void goToSection(int sectionIndex);

signals:
    void showMainWindow(bool closeType);
    void windowWasResized();

protected:
   bool eventFilter(QObject *obj, QEvent *event);
   void changeEvent(QEvent *event);

private:
    QRect prev_geometry;
    bool moving = false;
    bool TopBarNeedHide;
    short HidenTimer;
    QPoint lastPoint;
    int resizingFrame = 5;

    bool ActiveWindow;   // 0 - главное, 1 - не главное

    Ui::ReadingWindow* ui;
    QThread* HandlerThread;
    settings* ProgramSettings;

    QWidget* MenuWidget;
    QVBoxLayout* MenuLayout;
    QPushButton* MenuBackToMainWindowButton;
    QPushButton* MenuContentsButton;
    QPushButton* MenuSynchronizationButton;
    QPushButton* MenuFindButton;
    QPushButton* MenuSettingsButton;

    QThread* parserThread;

    QDialog* MiniWindow;
    QVBoxLayout* MiniWindowLayout;
    settingslayout* SettingsPage;
    synchronizationlayout* SynchronizationPage;

    SearchWindow* Search;

    QString styles[5];

    FB2TextPaginator* BookPaginator;
};

#endif // READINGWINDOW_H


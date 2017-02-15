#ifndef READING_WINDOW_H
#define READING_WINDOW_H

#include <QWidget>

#include <QMainWindow>
#include "books.h"
#include "answer_dialog.h"
#include <QThread>
#include "settings.h"
#include <QVBoxLayout>
#include "settings_layout.h"
#include "search_window.h"
#include "fb2textpaginator.h"

#include <QThread>
#include <QDomDocument>
#include <QKeyEvent>

namespace Ui {
class ReadingWindow;
}

class ReadingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ReadingWindow(QWidget* parent, Book *book);
    ~ReadingWindow();

    void startReading();

private slots:
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
    void showMainWindow();
    void windowWasResized();

    void showWindowMinimazed();
    void showWindowMaximazed();
    void closeWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void changeEvent(QEvent *event);

private:
    Book* CurBook;

    bool TopBarNeedHide;
    short HidenTimer;

    bool ActiveWindow;   // 0 - главное, 1 - не главное

    QThread* HandlerThread;
    Settings* ProgramSettings;

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
    SettingsLayout* SettingsPage;

    SearchWindow* Search;

    QString styles[5];

    FB2TextPaginator* BookPaginator;

    Ui::ReadingWindow* ui;
};

#endif // READING_WINDOW_H

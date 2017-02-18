#ifndef READING_WINDOW_H
#define READING_WINDOW_H

#include <QWidget>

#include "books.h"
#include "answer_dialog.h"
#include "settings.h"
#include "settings_layout.h"
#include "search_window.h"
#include "fb2textpaginator.h"
#include "reading_menu.h"

#include <QVBoxLayout>
#include <QThread>


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

    void setFullSize(bool fullSize);

private slots:
    void on_exit_button_clicked();

    void showContentsTable();
    void FindButton_Clicked();
    void showSettingsWindow();
    void SynchronizationButton_Clicked();
    void BackToMainWindowButton_Clicked();

    void setStyle(const QString &currentStyle);

    void StartSearch(const QString &key, const QString &type);
    void NextSearchStep();
    void PrevSearchStep();

    void clockStep();
    void updateProgress();

    void reprintResizedText();
    void reprintNewSettText();

    void goToSection(const int &sectionIndex);

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

    ReadingMenu* MenuWidget;

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

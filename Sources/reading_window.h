#ifndef READING_WINDOW_H
#define READING_WINDOW_H

#include <QWidget>

#include "books.h"
#include "answer_dialog.h"
#include "settings.h"
#include "search_window.h"
#include "xml_text_paginator.h"
#include "reading_menu.h"
#include "reading_table_of_contents.h"
#include "reading_mini_window.h"
#include "reading_search_widget.h"

#include <QThread>
#include <QKeyEvent>
#include <QListWidget>

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

    void createReadProfilesWidget();
    void createReadingMenuWidget();

    void showContentsTable();
    void showSearchWindow();
    void showSettingsWindow();
    void showSynchronizationWindow();
    void showNoteText(const QUrl &link);

    bool createMiniWindow();

    void setStyle(const QString &currentStyle);

    void clockStep();
    void updateProgress();

    void resizeWindow();
    void reprintNewSettText();

    void on_ReadProfilesButton_clicked();

    void setBackgroundImage();

    void showNextPage();
    void showPrevPage();

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

    QWidget* ProfilesWidget;
    QListWidget* ProfilesView;

    ReadingMiniWindow* MiniWindow;
    ReadingSearchWidget* SearchWidget;
    ReadingTableOfContents* ContentsTableWindow;
    SearchWindow* Search;

    QString styles[5];

    XMLTextPaginator* BookPaginator;

    Ui::ReadingWindow* ui;
};

#endif // READING_WINDOW_H

#ifndef READING_WINDOW_H
#define READING_WINDOW_H

#include <QWidget>

#include "data_handlers/book.h"
#include "custom_widgets/answer_dialog.h"
#include "data_handlers/settings_handler.h"
#include "search_window.h"
#include "xml_text_paginator.h"
#include "left_menu.h"
#include "table_of_contents_widget.h"
#include "mini_window.h"
#include "search_widget.h"

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
    void showSearchWindow(QString searchKey = QString());
    void showSettingsWindow();
    void showSynchronizationWindow();
    void showNoteText(const QUrl &link);

    bool createMiniWindow();
    void createRightClickMenu(QPoint mousePoint);

    void setStyle(const QString &currentStyle);

    void clockStep();
    void updateProgress();

    void resizeWindow();
    void reprintNewSettText();
    void rescaleBookText(const bool &inc);

    void enableTextSelection();
    void disableTextSelection();

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
    SettingsHandler* ProgramSettings;

    LeftMenu* MenuWidget;

    QWidget* ProfilesWidget;
    QListWidget* ProfilesView;

    MiniWindow* miniWindow;
    ReadingSearchWidget* SearchWidget;
    TableOfContentsWidget* ContentsTableWindow;
    SearchWindow* Search;

    QString styles[5];

    XMLTextPaginator* BookPaginator;

    Ui::ReadingWindow* ui;
};

#endif // READING_WINDOW_H

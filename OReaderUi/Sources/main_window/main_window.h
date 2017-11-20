#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QEvent>
#include <QFile>
#include <QTranslator>

#include "data_handlers/synchronization.h"
#include "data_handlers/settings_handler.h"
#include "reading_window/reading_window.h"
#include "main_window/library/book_page/book_page.h"
#include "main_window/library/library_view/library_view.h"
#include "QTabSwitcher.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    LibraryView* getLibraryWidget() const;

private slots:
    void setStyle();

    void on_exit_button_clicked();

    void on_Logout_clicked();

    void startReading(const QString &index);

protected:
    void changeEvent(QEvent *event);

signals:
    void showLoginWindow();
    void showReadingWindow();

    void showWindowMinimazed();
    void showWindowMaximazed();
    void closeWindow();

private:
    Ui::MainWindow* ui;

    ReadingWindow* readingWindow;

    QTabSwitcher* tabSwitcher;

    Synchronization* UserActions;
    SettingsHandler* ProgramSettings;

};

#endif // MAIN_WINDOW_H

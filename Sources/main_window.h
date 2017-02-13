#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QEvent>
#include <QFile>
#include <QTranslator>

#include "synchronization.h"
#include "settings.h"

#include "reading_window.h"
#include "book_page.h"
#include "QTabSwitcher.h"
#include "library.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    library* getLibraryWidget();

private slots:
    void setStyle();

    void on_exit_button_clicked();

    void on_Logout_clicked();

    void startReading(const unsigned int index);
    void showBookPage(const unsigned int index);

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
    BookPage* page;

    QTabSwitcher* tabSwitcher;

    Synchronization* UserActions;
    Settings* ProgramSettings;
};

#endif // MAIN_WINDOW_H

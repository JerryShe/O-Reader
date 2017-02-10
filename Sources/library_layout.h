#ifndef LIBRARY_LAYOUT_H
#define LIBRARY_LAYOUT_H

#include <QWidget>

#include "search_window.h"
#include "library_handler.h"



namespace Ui {
class LibraryLayout;
}

class LibraryLayout : public QWidget
{
    Q_OBJECT

public:
    explicit LibraryLayout(QWidget *parent = 0);
    ~LibraryLayout();

private slots:
    void on__AddBooks_clicked();
    void on__Delete_clicked();
    void on__ChangeViewMode_toggled(bool checked);
    void on__Upscale_clicked();
    void on__Downscale_clicked();
    void on__SortBox_activated(const QString &arg1);
    void on__Find_toggled(bool checked);

    void addBooksFromFiles();
    void addBooksFromFolder();

public slots:
    void setStyle();

    void saveBookList();
    Book* getBookByIndex(int index);
    void deleteBook(int index);

private slots:
    void deactiveFindButton();

protected:
    void changeEvent(QEvent *event);

signals:
    void showBookPage(int index);

private:
    Ui::LibraryLayout *ui;

    QThread * HandlerThread;

    settings* ProgramSettings;
    LibraryHandler * LibHandler;
    library* Library;

    SearchWindow* searchWindow;
};

#endif // LIBRARY_LAYOUT_H

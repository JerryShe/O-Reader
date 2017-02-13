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
    library* getLibraryWidget();


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

    void deactiveFindButton();

public slots:
    void setStyle();

    Book* getBookByIndex(unsigned int index);
    void deleteBook(unsigned int index);

protected:
    void changeEvent(QEvent *event);
    void dropEvent(QDropEvent *e);
    void dragEnterEvent(QDragEnterEvent *e);

signals:
    void showBookPage(unsigned int index);

private:
    Ui::LibraryLayout *ui;

    QThread * HandlerThread;

    Settings* ProgramSettings;
    LibraryHandler * LibHandler;
    library* Library;

    SearchWindow* searchWindow;
};

#endif // LIBRARY_LAYOUT_H

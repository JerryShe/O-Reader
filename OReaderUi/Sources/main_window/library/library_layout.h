#ifndef LIBRARY_LAYOUT_H
#define LIBRARY_LAYOUT_H

#include "main_window/library/widgets/search_window.h"
#include "data_handlers/library_handler.h"
#include "main_window/library/book_widget/book_widget.h"

#include <QWidget>


namespace Ui {
class LibraryLayout;
}

class LibraryLayout : public QWidget
{
    Q_OBJECT

public:
    explicit LibraryLayout(QWidget *parent = 0);
    ~LibraryLayout();

    LibraryView* getLibraryWidget() const;


private slots:
    void on__AddBooks_clicked();
    void on__Delete_clicked();
    void on__ChangeViewMode_toggled(bool checked);
    void on__Downscale_clicked();
    void on__Find_toggled(bool checked);

    void addBooksFromFiles();
    void addBooksFromFolder();

    void hideFind();
    void hideBookWidget();

    void lostBooks(QVector <Book*> losted);

    void updateViewSort();

    void showBookPage(QString index);
    void hideBookPage();

public slots:
    void setStyle();

    Book* getBookByIndex(const QString &index) const;
    void deleteBook(QString index);

protected:
    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void startReading(QString index);

private:
    Ui::LibraryLayout *ui;

    BookWidget *bookWidget;

    QThread * HandlerThread;

    SettingsHandler* ProgramSettings;
    LibraryHandler * LibHandler;

    SearchWindow* searchWindow;
};

#endif // LIBRARY_LAYOUT_H

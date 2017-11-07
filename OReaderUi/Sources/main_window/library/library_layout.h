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
    void on__SortBox_activated(const QString &arg1);
    void on__Find_toggled(bool checked);

    void addBooksFromFiles();
    void addBooksFromFolder();

    void hideFind();
    void hideBookWidget();

    void lostBooks(QVector <Book*> losted);

    void on__SortDirection_toggled(bool checked);

public slots:
    void setStyle();

    Book* getBookByIndex(const unsigned int &index) const;
    void deleteBook(const unsigned int &index);

protected:
    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void showBookPage(unsigned int index);
    void startReading(unsigned int index);

private:
    Ui::LibraryLayout *ui;

    BookWidget *bookWidget;

    QThread * HandlerThread;

    SettingsHandler* ProgramSettings;
    LibraryHandler * LibHandler;

    SearchWindow* searchWindow;
};

#endif // LIBRARY_LAYOUT_H

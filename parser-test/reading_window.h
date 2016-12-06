#ifndef READINGWINDOW_H
#define READINGWINDOW_H

#include <QMainWindow>
#include <books.h>
#include <answer_dialog.h>
#include <QThread>
#include <settings.h>
#include <QVBoxLayout>

namespace Ui {
class ReadingWindow;
}

class ReadingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReadingWindow(settings * PSettings, QString file);
    ~ReadingWindow();

private slots:
    void on_min_button_clicked();
    void on_full_size_button_clicked();
    void on_exit_button_clicked();
    void on_MenuButton_clicked();
    void setStyle(QString currentStyle);

    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    void clockStep();

private:
    QRect prev_geometry;
    bool moving = false;
    bool TopBarNeedHide;
    short HidenTimer;
    QPoint lastPoint;
    int resizingFrame = 5;

    Ui::ReadingWindow *ui;
    QThread * HandlerThread;
    settings * ProgramSettings;


    QWidget * MenuWidget;
    QVBoxLayout * MenuLayout;
    QPushButton * BackToMainWindowButton;
    QPushButton * ContentsButton;
    QPushButton * SynchronizationButton;
    QPushButton * FindButton;
    QPushButton * SettingsButton;

    class TextParser
    {
    public:
        TextParser(Book *book);
        ~TextParser();

        void setPageSize(int width, int height);
        int getCurrentPage();
        int getCurrentProgress();

        QString getTextPage();

    private:

        int pageWidth;
        int pageHeight;

        int currentWidth;
        int currentHeight;
        int currentColumn;

        int currentPage;

        settings *ProgramSettings;

        QString PageHTMLHeader;
        QStringList PagesList;
        QVector <QPair<QString,QString>> ParagrafList;

    };
};

#endif // READINGWINDOW_H

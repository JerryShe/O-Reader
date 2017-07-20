#ifndef READING_MINI_WINDOW_H
#define READING_MINI_WINDOW_H

#include <QDialog>


class ReadingMiniWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ReadingMiniWindow(QWidget* parent);
    ~ReadingMiniWindow();

public slots:
    void openWindow();
    void closeWindow();

    void setStyle();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    void resizeWindow();
};

#endif // READING_MINI_WINDOW_H

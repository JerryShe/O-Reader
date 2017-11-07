#ifndef MINI_WINDOW_H
#define MINI_WINDOW_H

#include <QDialog>


class MiniWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MiniWindow(QWidget* parent);
    ~MiniWindow();

public slots:
    void openWindow();
    void closeWindow();

    void setStyle();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    void resizeWindow();
};

#endif // MINI_WINDOW_H

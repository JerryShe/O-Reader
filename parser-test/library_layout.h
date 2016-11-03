#ifndef LIBRARYLAYOUT_H
#define LIBRARYLAYOUT_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QMainWindow>

class librarylayout : public QWidget
{
    Q_OBJECT
public:
    explicit librarylayout(QWidget *widget);

    void addWidget(QWidget* widget);
    void checkTheMouse(QMouseEvent *event, int height, int width, int resizingFrame);
    void setStyle(QString libraryStyle[]);



private:
    void setColumnsAndMargins();

    QGridLayout* gridLayout;
    int row;
    int column;
    int max_columns = 0;
    int windowSize;
    bool needReflow = false;

    QScrollArea* scrollArea;
    QWidget *content;
    void mouseMoveEvent(QMouseEvent *event);

};

#endif // LIBRARYLAYOUT_H

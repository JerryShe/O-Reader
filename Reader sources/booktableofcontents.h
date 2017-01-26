#ifndef BOOKTABLEOFCONTENTS_H
#define BOOKTABLEOFCONTENTS_H

#include <QDialog>

namespace Ui {
class BookTableOfContents;
}

class BookTableOfContents : public QDialog
{
    Q_OBJECT

public:
    explicit BookTableOfContents(QString style, QStringList contentList, int currentPos, QWidget *parent = 0);
    ~BookTableOfContents();

signals:
    void goToSection(int pos);

private slots:
    void on_GoTo_clicked();
    void setWindowStyle(QString style);

private:
    Ui::BookTableOfContents *ui;
};

#endif // BOOKTABLEOFCONTENTS_H

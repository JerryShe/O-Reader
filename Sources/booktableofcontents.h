#ifndef BOOKTABLEOFCONTENTS_H
#define BOOKTABLEOFCONTENTS_H

#include <QDialog>

#include <QTreeWidgetItem>

namespace Ui {
class BookTableOfContents;
}

class BookTableOfContents : public QDialog
{
    Q_OBJECT

public:
    explicit BookTableOfContents(const QString &style, QTreeWidgetItem *contentList, QWidget *parent = 0);
    ~BookTableOfContents();

signals:
    void goToSection(long long pos);

private slots:
    void setStyle(const QString &style);

private:
    Ui::BookTableOfContents *ui;
};

#endif // BOOKTABLEOFCONTENTS_H

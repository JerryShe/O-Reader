#ifndef READINGTABLEOFCONTENTS_H
#define READINGTABLEOFCONTENTS_H

#include <QDialog>

#include <QTreeWidgetItem>

namespace Ui {
class ReadingTableOfContents;
}

class ReadingTableOfContents : public QDialog
{
    Q_OBJECT

public:
    explicit ReadingTableOfContents(QTreeWidgetItem *contentList, const long long &pos, QWidget *parent = 0);
    ~ReadingTableOfContents();

signals:
    void goToSection(long long pos);

private slots:
    void setStyle();

private:
    void getCurrentSection(QTreeWidgetItem* item);
    QTreeWidgetItem* curSection;
    long long curPos;

    Ui::ReadingTableOfContents *ui;
};

#endif // READINGTABLEOFCONTENTS_H

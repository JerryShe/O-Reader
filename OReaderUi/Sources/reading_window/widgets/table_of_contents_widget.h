#ifndef TABLEOFCONTENTSWIDGET_H
#define TABLEOFCONTENTSWIDGET_H

#include <QTreeWidgetItem>

#include <QDialog>


namespace Ui {
class TableOfContentsWidget;
}

class TableOfContentsWidget : public QDialog
{
    Q_OBJECT

public:
    explicit TableOfContentsWidget(QTreeWidgetItem *contentList, const long long &pos, QWidget *parent = 0);
    ~TableOfContentsWidget();

signals:
    void goToSection(long long pos);

private slots:
    void setStyle();

private:
    void getCurrentSection(QTreeWidgetItem* item);
    QTreeWidgetItem* curSection;
    long long curPos;

    Ui::TableOfContentsWidget *ui;
};

#endif // TABLEOFCONTENTSWIDGET_H

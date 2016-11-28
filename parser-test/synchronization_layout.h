#ifndef SYNCHRONIZATIONLAYOUT_H
#define SYNCHRONIZATIONLAYOUT_H

#include <QWidget>
#include <QGridLayout>

class synchronizationlayout : public QWidget
{
    Q_OBJECT
public:
    explicit synchronizationlayout(QWidget *Parent=0);
    ~synchronizationlayout();

signals:

public slots:

private:
    QGridLayout *synchronizationGridLayout;
};

#endif // SYNCHRONIZATIONLAYOUT_H

#ifndef SYNCHRONIZATIONLAYOUT_H
#define SYNCHRONIZATIONLAYOUT_H

#include <QWidget>
#include <QGridLayout>

class synchronizationlayout : public QWidget
{
    Q_OBJECT
public:
    explicit synchronizationlayout(QWidget *parent = 0);

signals:

public slots:

private:
    QGridLayout *synchronizationGridLayout;
};

#endif // SYNCHRONIZATIONLAYOUT_H

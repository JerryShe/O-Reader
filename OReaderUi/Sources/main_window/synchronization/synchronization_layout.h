#ifndef SYNCHRONIZATION_LAYOUT_H
#define SYNCHRONIZATION_LAYOUT_H

#include <QWidget>

namespace Ui {
class SynchronizationLayout;
}

class SynchronizationLayout : public QWidget
{
    Q_OBJECT

public:
    explicit SynchronizationLayout(QWidget *parent = 0);
    ~SynchronizationLayout();

private:
    Ui::SynchronizationLayout *ui;
};

#endif // SYNCHRONIZATION_LAYOUT_H

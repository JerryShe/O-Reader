#include "synchronization_layout.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

synchronizationlayout::synchronizationlayout(QWidget *AreaLayout)
{
    synchronizationGridLayout = new QGridLayout();

    QPushButton *synch = new QPushButton("synchronization");
    synchronizationGridLayout->addWidget(synch, 0, 0);

    synchronizationlayout::setLayout(synchronizationGridLayout);
    synchronizationlayout::hide();
}

#include "synchronization_layout.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

synchronizationlayout::synchronizationlayout(QWidget *Parent)
{
    this->setParent(Parent);
    synchronizationGridLayout = new QGridLayout();

    QPushButton *synch = new QPushButton("synchronization");
    synchronizationGridLayout->addWidget(synch, 0, 0);

    setLayout(synchronizationGridLayout);
    hide();

}

synchronizationlayout::~synchronizationlayout()
{
    delete synchronizationGridLayout;
}

void synchronizationlayout::setSettingsData(settings *PSettings)
{
    ProgramSettings = PSettings;
}

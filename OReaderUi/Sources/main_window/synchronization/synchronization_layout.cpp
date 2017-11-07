#include "main_window/synchronization/synchronization_layout.h"
#include "ui_synchronization_layout.h"

SynchronizationLayout::SynchronizationLayout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SynchronizationLayout)
{
    ui->setupUi(this);
}


SynchronizationLayout::~SynchronizationLayout()
{
    delete ui;
}

#include "settings_layout.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>


settingslayout::settingslayout(QWidget *AreaLayout)
{
    settingsGridLayout = new QGridLayout();

    QPushButton *sett = new QPushButton("settings");
    settingsGridLayout->addWidget(sett, 0, 0);

    settingslayout::setLayout(settingsGridLayout);
    settingslayout::hide();
}

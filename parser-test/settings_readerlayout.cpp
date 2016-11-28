#include "settings_readerlayout.h"
#include "ui_settings_readerlayout.h"

Settings_ReaderLayout::Settings_ReaderLayout(QWidget *parent, QString style) : QFrame(parent), ui(new Ui::Settings_ReaderLayout)
{
    Style = style;
    ui->setupUi(this);
}

Settings_ReaderLayout::~Settings_ReaderLayout()
{
    delete ui;
}

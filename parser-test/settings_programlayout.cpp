#include "settings_programlayout.h"
#include "ui_settings_programlayout.h"

Settings_ProgramLayout::Settings_ProgramLayout(QWidget *parent, QString style) : QFrame(parent), ui(new Ui::Settings_ProgramLayout)
{
    Style = style;
    ui->setupUi(this);
}

Settings_ProgramLayout::~Settings_ProgramLayout()
{
    delete ui;
}

#ifndef SYNCHRONIZATIONLAYOUT_H
#define SYNCHRONIZATIONLAYOUT_H

#include <QWidget>
#include <QGridLayout>
#include "settings.h"

class synchronizationlayout : public QWidget
{
    Q_OBJECT
public:
    explicit synchronizationlayout(QWidget *Parent=0);
    ~synchronizationlayout();

    void setSettingsData(Settings *PSettings);

private:
    QGridLayout *synchronizationGridLayout;

    Settings *ProgramSettings;
};

#endif // SYNCHRONIZATIONLAYOUT_H

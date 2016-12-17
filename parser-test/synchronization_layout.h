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

    void setSettingsData(settings *PSettings);

private:
    QGridLayout *synchronizationGridLayout;

    settings *ProgramSettings;
};

#endif // SYNCHRONIZATIONLAYOUT_H

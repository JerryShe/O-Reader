#ifndef SETTINGSLAYOUT_H
#define SETTINGSLAYOUT_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>

class settingslayout : public QWidget
{
    Q_OBJECT
public:
    explicit settingslayout(QWidget *parent = 0);
    void showProfile();
    void showProgram();
    void showReader();
    void showSynchronization();

signals:
    void tabChanged(int prevTab);

public slots:

private:

    QHBoxLayout *settingsMainLayout;

    QWidget *ProfileWidget;                 //0
    QWidget *ReaderWidget;                  //1
    QWidget *SynchronizationWidget;         //2
    QWidget *ProgramWidget;                 //3

    QGridLayout *ProfileLayout;
    QGridLayout *ReaderLayout;
    QGridLayout *SynchronizationLayout;
    QGridLayout *ProgramLayout;

    short currentTab = 1;

};

#endif // SETTINGSLAYOUT_H

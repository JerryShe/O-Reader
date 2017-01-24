#include "synchronization.h"
#include <QFile>
#include <QQueue>
#include <QDir>
#include <QDataStream>
#include <QDebug>
#include <QString>


Synchronization::Synchronization()
{
    loadLog();
}

Synchronization::action::action(int index, QString itemSpec, QString data)
{
    actionTime = QDateTime::currentDateTime();
    actionIndex = index;
    spec = itemSpec;
    dataChanges = data;
}

Synchronization::action::action(int index, QDateTime time, QString itemSpec, QString data)
{
    actionTime = time;
    actionIndex = index;
    spec = itemSpec;
    dataChanges = data;
}

void Synchronization::loadLog()
{
    QString resoursesFolderPath = "LibraryResources";
    if ( ! QDir(resoursesFolderPath).exists()==true)
    {
        QDir().mkdir(resoursesFolderPath);
    }
    QFile LogList(resoursesFolderPath + "/ChangesLogs.log");

    if(LogList.open(QIODevice::ReadOnly | QIODevice::Text ))
        qDebug() << "Log File Has Been Created" << endl;
    else
    {
        qDebug() << "Log Failed to Create File" << endl;
        qDebug() << "error = " << LogList.error ();

        ///оповещение - невозможно открыть или создать файл логов
        return;
    }

    QDataStream in(&LogList);
    unsigned short actionIndex;
    UActions actionI;
    QDateTime actionTime;
    QString spec;
    QString dataChanges;

    while (!in.atEnd())
    {
        in>>actionIndex;
        if (actionIndex < 6)
            actionI = static_cast<UActions>(actionIndex);
        else
            continue;
        in>>actionTime;
        in>>spec;
        in>>dataChanges;

        SynchroQueue.enqueue(action(actionI, actionTime, spec, dataChanges));
    }
    LogList.close();
}

void Synchronization::saveLog()
{
    if (SynchroQueue.isEmpty())
        return;
    QString resoursesFolderPath = "LibraryResources";
    if ( ! QDir(resoursesFolderPath).exists()==true)
    {
        QDir().mkdir(resoursesFolderPath);
    }
    QFile LogList(resoursesFolderPath + "/ChangesLogs.log");

    if(LogList.open(QIODevice::WriteOnly | QIODevice::Text ))
        qDebug() << "Log File Has Been Created" << endl;
    else
    {
        qDebug() << "Log Failed to Create File" << endl;
        qDebug() << "error = " << LogList.error ();

        ///оповещение - невозможно открыть или создать файл логов
        return;
    }

    QDataStream out(&LogList);
    action temp;
    for (int i = 0; i < SynchroQueue.size(); i++)
    {
        temp = SynchroQueue.at(i);
        out<<temp.actionTime;
        out<<temp.actionIndex;
        out<<temp.spec;
        out<<temp.dataChanges;
    }
    LogList.close();
}

int Synchronization::synchronizeToServer()
{
    //пингуем
    //сохраняем лог
    //грузим файл лога на сервер
    //чистим очередь и локальный лог
    saveLog();
    return 0;
}

int Synchronization::synchronizeFromServer()
{
    //пингуем
    //грузим файл лога с сервера
    //применяем изменения
    loadLog();
    return 0;
}


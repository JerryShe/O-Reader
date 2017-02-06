#include "synchronization.h"
#include <QFile>
#include <QQueue>
#include <QDir>
#include <QDataStream>
#include <QDebug>
#include <QString>


Synchronization::Synchronization()
{
    SettingsChanged = false;
    loadLog();
}

Synchronization::~Synchronization()
{
    saveLog();
}

Synchronization* Synchronization::getSynchronization()
{
    static Synchronization UserActions;
    return &UserActions;
}

action::action(int index, QString itemSpec, QString data)
{
    actionTime = QDateTime::currentMSecsSinceEpoch();
    actionIndex = index;
    spec = itemSpec;
    dataChanges = data;
}

action::action(int index, quint64 time, QString itemSpec, QString data)
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
        qDebug() << "Log File Has Been Opened" << endl;
    else
    {
        qDebug() << "Log Failed to Create File" << endl;
        qDebug() << "error = " << LogList.error ();

        ///оповещение - невозможно открыть или создать файл логов
        return;
    }

    QDataStream in(&LogList);

    in>>SettingsChanged;
    if (SettingsChanged)
        in>>SettingsChangedTime;

    in>>BookQueue;
    in>>FileQueue;

    LogList.close();
}

void Synchronization::saveLog()
{
    if (BookQueue.isEmpty())
        return;
    QString resoursesFolderPath = "LibraryResources";
    if ( ! QDir(resoursesFolderPath).exists()==true)
    {
        QDir().mkdir(resoursesFolderPath);
    }
    QFile LogList(resoursesFolderPath + "/ChangesLogs.log");

    if(LogList.open(QIODevice::WriteOnly | QIODevice::Text ))
        qDebug() << "Log File Has Been Opened" << endl;
    else
    {
        qDebug() << "Log Failed to Create File" << endl;
        qDebug() << "error = " << LogList.error ();

        ///оповещение - невозможно открыть или создать файл логов
        return;
    }

    QDataStream out(&LogList);
    out<<SettingsChanged;
    if (SettingsChanged)
        out<<SettingsChangedTime;

    out<<BookQueue;
    out<<FileQueue;

    qDebug()<<"log saved";
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

QString Synchronization::getNumber(QString item)
{
    return item;
}

QString Synchronization::getNumber(int item)
{
    return QString::number(item);
}

QDataStream &operator>>(QDataStream &in, action &actionElem)
{
    in>>actionElem.actionIndex;
    in>>actionElem.actionTime;
    in>>actionElem.spec;
    in>>actionElem.dataChanges;
    return in;
}

QDataStream &operator<<(QDataStream &out, const action &actionElem)
{
    out<<actionElem.actionIndex;
    out<<actionElem.actionTime;
    out<<actionElem.spec;
    out<<actionElem.dataChanges;
    return out;
}


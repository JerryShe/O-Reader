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
    LastOpenedWindow = 0;
    LastOpenedBookIndex = -1;
}

Synchronization::~Synchronization()
{
    //saveLog();
}

Synchronization* Synchronization::getSynchronization()
{
    static Synchronization UserActions;
    return &UserActions;
}

action::action(unsigned int index, QString itemSpec, QString data)
{
    actionTime = QDateTime::currentMSecsSinceEpoch();
    actionIndex = index;
    spec = itemSpec;
    dataChanges = data;
}

action::action(unsigned int index, quint64 time, QString itemSpec, QString data)
{
    actionTime = time;
    actionIndex = index;
    spec = itemSpec;
    dataChanges = data;
}

bool Synchronization::loadLog()
{
    QString resoursesFolderPath = "LibraryResources";
    if ( ! QDir(resoursesFolderPath).exists()==true)
    {
        QDir().mkdir(resoursesFolderPath);
    }
    QFile LogList(resoursesFolderPath + "/ChangesLogs.log");

    if(!LogList.open(QIODevice::ReadOnly | QIODevice::Text ))
    {
        qDebug() << "Log Failed to Create File";
        qDebug() << "error = " << LogList.error()<< endl;

        ///оповещение - невозможно открыть или создать файл логов
        return 1;
    }

    QDataStream in(&LogList);

    in>>SettingsChanged;
    if (SettingsChanged)
        in>>SettingsChangedTime;
    in>>LastOpenedWindow;
    in>>LastOpenedBookIndex;

    in>>BookQueue;
    in>>FileQueue;

    qDebug()<<"logs loaded";
    LogList.close();
    return 1;
}

bool Synchronization::saveLog()
{
    QString resoursesFolderPath = "LibraryResources";
    if ( ! QDir(resoursesFolderPath).exists()==true)
    {
        QDir().mkdir(resoursesFolderPath);
    }

    QFile LogList(resoursesFolderPath + "/ChangesLogs.log");

    LogList.open(QIODevice::WriteOnly);

    QDataStream out(&LogList);
    out<<SettingsChanged;
    if (SettingsChanged)
        out<<SettingsChangedTime;
    out<<LastOpenedWindow;
    out<<LastOpenedBookIndex;

    out<<BookQueue;
    out<<FileQueue;

    qDebug()<<"log saved";
    LogList.close();
    return 1;
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

int Synchronization::getLastOpenedWindow()
{
    return LastOpenedWindow;
}

void Synchronization::setLastOpenedWindow(unsigned int index)
{
    LastOpenedWindow = index;
}

unsigned int Synchronization::getLastOpenedBookIndex()
{
    return LastOpenedBookIndex;
}

void Synchronization::setLastOpenedBookIndex(unsigned int index)
{
    LastOpenedBookIndex = index;
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


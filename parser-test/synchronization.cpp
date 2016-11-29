#include "synchronization.h"
#include <QFile>
#include <QQueue>
#include <QDir>
#include <QDataStream>
#include <QDebug>


Synchronization::Synchronization()
{
    loadLog();
}

Synchronization::action::action(QDateTime time, int index, QString fileName, int Bindex, QString data)
{
        actionTime = time;
        actionIndex = index;
        file = fileName;
        bookIndex = Bindex;
        dataChanges = data;
}

Synchronization::action::action(int index, QString fileName, int Bindex, QString data)
{
        actionTime = QDateTime::currentDateTime();
        actionIndex = index;
        file = fileName;
        bookIndex = Bindex;
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
    QDateTime actionTime;
    int actionIndex;
    QString file;
    int bookIndex;
    QString dataChanges;

    while (!in.atEnd())
    {
        in>>actionTime;
        in>>actionIndex;
        in>>file;
        in>>bookIndex;
        in>>dataChanges;

        SynchroQueue.enqueue(action(actionTime, actionIndex, file, bookIndex, dataChanges));
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
        out<<temp.file;
        out<<temp.bookIndex;
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
}

int Synchronization::synchronizeFromServer()
{
    //пингуем
    //грузим файл лога с сервера
    //применяем изменения
    loadLog();

}

/* Добавление книги - 1: файл
 * Удаление книги - 2: файл
 * Изменение прогресса - 3: индекс, значение
 * Редактирование описания - 4: индекс, значение
 * Изменение настроек - 5
 * Добавление фона - 6
 */
void Synchronization::addAction(int actionIndex, QString file, int bookIndex, QString dataChanges)
{
    switch (actionIndex)
    {
    case 1:
        break;

    case 2:
        for (int i = 0; i < SynchroQueue.size(); i++)
            if (SynchroQueue.at(i).actionIndex == 1 && file == SynchroQueue.at(i).file)
            {
                SynchroQueue.removeAt(i);
                return;
            }
        break;

    case 3:
        for (int i = 0; i < SynchroQueue.size(); i++)
            if (SynchroQueue.at(i).actionIndex == 3 && bookIndex == SynchroQueue.at(i).bookIndex)
            {
                SynchroQueue.removeAt(i);
                break;
            }
        break;

    case 4:
        break;

    case 5:
        for (int i = 0; i < SynchroQueue.size(); i++)
            if (SynchroQueue.at(i).actionIndex == 5)
            {
                SynchroQueue.removeAt(i);
                break;
            }
        break;

    case 6:
        for (int i = 0; i < SynchroQueue.size(); i++)
            if (SynchroQueue.at(i).actionIndex == 6)
            {
                SynchroQueue.removeAt(i);
                break;
            }
        break;

    }

    SynchroQueue.enqueue(action(actionIndex, file, bookIndex, dataChanges));
}

















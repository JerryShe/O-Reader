#ifndef SYNCHRONIZATION_H
#define SYNCHRONIZATION_H
#include <QQueue>
#include <QDateTime>
#include <QDataStream>
#include <QObject>


class Synchronization : public QObject
{

private:

    /* Добавление книги - 1: файл
     * Удаление книги - 2: файл
     * Изменение прогресса - 3: индекс, значение
     * Редактирование описания - 4: индекс, значение
     * Изменение настроек - 5:
     * Добавление фона - 6: файл
     */

    struct action
    {
        short actionIndex;
        QDateTime actionTime;
        QString spec;
        QString dataChanges;

        action(){}
        action(short index, QString itemSpec, QString data);
        action(short index, QDateTime time, QString itemSpec, QString data);
    };

    QQueue <action> SynchroQueue;

public:
    friend QDataStream &operator>>(QDataStream &in, action &actionElem);
    friend QDataStream &operator<<(QDataStream &out, const action &actionElem);

    Synchronization();

    int synchronizeToServer();
    int synchronizeFromServer();
    void saveLog();
    void loadLog();

    template <typename T1, typename T2> void addAction(int actionIndex, T1 fArg, T2 sArg)
    {
        QString newFArg, newSArg;

        switch (actionIndex)
        {
        case 1:
            newFArg = fArg;
            break;

        case 2:
            for (int i = 0; i < SynchroQueue.size(); i++)
                if (SynchroQueue.at(i).actionIndex == 1 && fArg == SynchroQueue.at(i).spec)
                {
                    SynchroQueue.removeAt(i);
                    return;
                }
            newFArg = fArg;
            break;

        case 3:
            for (int i = 0; i < SynchroQueue.size(); i++)
                if (SynchroQueue.at(i).actionIndex == 3 && fArg == SynchroQueue.at(i).spec)
                {
                    SynchroQueue.removeAt(i);
                    break;
                }
            //newFArg = QString::number(fArg);
            newSArg = QString::number(sArg);
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

            //newFArg = QString::number(fArg);
            newSArg = sArg;
            break;

        case 6:
            for (int i = 0; i < SynchroQueue.size(); i++)
                if (SynchroQueue.at(i).actionIndex == 6)
                {
                    SynchroQueue.removeAt(i);
                    break;
                }
            newFArg = fArg;
            break;
        }

        SynchroQueue.enqueue(action(actionIndex, newFArg, newSArg));
    }

};

#endif // SYNCHRONIZATION_H

#ifndef SYNCHRONIZATION_H
#define SYNCHRONIZATION_H
#include <QQueue>
#include <QDateTime>
#include <QDataStream>
#include <QObject>

enum UActions
{
    AddBook,
    DeleteBook,
    UpdateProgress,
    UpdateBookInf,
    UpdateSettings,
    AddBackground
};



class Synchronization : public QObject
{

private:

    struct action
    {
        int actionIndex;
        QDateTime actionTime;
        QString spec;
        QString dataChanges;

        action(){}
        action(int index, QString itemSpec, QString data);
        action(int index, QDateTime time, QString itemSpec, QString data);
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

    template <typename T1, typename T2> void addAction(UActions actionIndex, T1 fArg, T2 sArg)
    {
        QString newFArg, newSArg;

        switch (actionIndex)
        {
        case UActions::AddBook:
            newFArg = fArg;
            break;

        case UActions::DeleteBook:
            for (int i = 0; i < SynchroQueue.size(); i++)
                if (UActions::AddBook == SynchroQueue.at(i).actionIndex && fArg == SynchroQueue.at(i).spec)
                {
                    SynchroQueue.removeAt(i);
                    return;
                }
            newFArg = fArg;
            break;

        case UActions::UpdateProgress:
            for (int i = 0; i < SynchroQueue.size(); i++)
                if (SynchroQueue.at(i).actionIndex == UActions::UpdateProgress && fArg == SynchroQueue.at(i).spec)
                {
                    SynchroQueue.removeAt(i);
                    break;
                }
            //newFArg = QString::number(fArg);
            newSArg = QString::number(sArg);
            break;

        case UActions::UpdateBookInf:
            break;

        case UActions::UpdateSettings:
            for (int i = 0; i < SynchroQueue.size(); i++)
                if (SynchroQueue.at(i).actionIndex == UActions::UpdateSettings)
                {
                    SynchroQueue.removeAt(i);
                    break;
                }

            //newFArg = QString::number(fArg);
            newSArg = sArg;
            break;

        case UActions::AddBackground:
            for (int i = 0; i < SynchroQueue.size(); i++)
                if (SynchroQueue.at(i).actionIndex == UActions::AddBackground)
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

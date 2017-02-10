#ifndef SYNCHRONIZATION_H
#define SYNCHRONIZATION_H
#include <QQueue>
#include <QDateTime>
#include <QDataStream>
#include <QObject>

#include <QDebug>

enum UActions
{
    AddBook,
    DeleteBook,
    UpdateProgress,
    UpdateBookInf,
    UpdateSettings,
    AddBackground
};

struct action
{
    int actionIndex;
    quint64 actionTime;
    QString spec;
    QString dataChanges;

    action(){}
    action(int index, QString itemSpec, QString data);
    action(int index, quint64 time, QString itemSpec, QString data);

    friend QDataStream &operator>>(QDataStream &in, action &actionElem);
    friend QDataStream &operator<<(QDataStream &out, const action &actionElem);
};

class Synchronization : public QObject
{

private:
    Synchronization();
    ~Synchronization();

    QQueue <action> BookQueue;
    QQueue <action> FileQueue;

    bool SettingsChanged;
    quint64 SettingsChangedTime;

    QString getNumber(QString item);
    QString getNumber(int item);

public:
    static Synchronization* getSynchronization();

    int synchronizeToServer();
    int synchronizeFromServer();
    void saveLog();
    void loadLog();



    /// Добавление книги - 1: файл, индекс
    /// Удаление книги - 2: файл, индекс
    /// Изменение прогресса - 3: индекс, значение
    /// Редактирование описания - 4: значение, индекс
    /// Изменение настроек - 5
    /// Добавление фона - 6: файл

    template <typename T1> void addAction(UActions actionIndex, T1 qualifier, long long data = 0)
    {
        //qDebug()<<static_cast<int>(actionIndex)<<qualifier<<data;

        QString Squalifier, Sdata;

        switch (actionIndex)
        {
        case UActions::AddBook:
            Sdata = QString::number(data);
            FileQueue.enqueue(action(actionIndex, qualifier, Sdata));
            return;

        case UActions::DeleteBook:
            for (int i = 0; i < FileQueue.size(); i++)
                if (UActions::AddBook == FileQueue.at(i).actionIndex && qualifier == FileQueue.at(i).spec)
                {
                    FileQueue.removeAt(i);
                    return;
                }
            FileQueue.enqueue(action(actionIndex, qualifier, Sdata));
            return;

        case UActions::UpdateProgress:
            for (int i = 0; i < BookQueue.size(); i++)
                if (BookQueue.at(i).actionIndex == UActions::UpdateProgress && qualifier == BookQueue.at(i).spec)
                {
                    BookQueue[i].actionTime = QDateTime::currentMSecsSinceEpoch();
                    BookQueue[i].dataChanges = getNumber(data);
                    return;
                }
            Squalifier = getNumber(qualifier);
            Sdata = QString::number(data);
            BookQueue.enqueue(action(actionIndex, Squalifier, Sdata));
            return;

        case UActions::UpdateBookInf:
            for (int i = 0; i < BookQueue.size(); i++)
                if (BookQueue.at(i).actionIndex == UActions::UpdateProgress && qualifier == BookQueue.at(i).spec)
                {
                    BookQueue[i].actionTime = QDateTime::currentMSecsSinceEpoch();
                    BookQueue[i].dataChanges = getNumber(data);
                    return;
                }
            Squalifier = getNumber(qualifier);
            Sdata = QString::number(data);
            BookQueue.enqueue(action(actionIndex, Squalifier, Sdata));
            return;

        case UActions::UpdateSettings:
            SettingsChanged = true;
            SettingsChangedTime = QDateTime::currentMSecsSinceEpoch();
            return;

        case UActions::AddBackground:
            FileQueue.enqueue(action(actionIndex, qualifier, Sdata));
            break;
        }
    }
};

#endif // SYNCHRONIZATION_H

#ifndef SYNCHRONIZATION_H
#define SYNCHRONIZATION_H
#include <QQueue>
#include <QDateTime>
#include <QDataStream>
#include <QObject>
#include <QJsonObject>

#include <QDebug>

#include <books.h>
#include <settings.h>

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
    unsigned int Index;
    quint64 Time;
    QString Spec;
    QString Changes;

    action(){}
    action(QJsonObject &json);
    action(unsigned int index, QString itemSpec, QString data);
    action(unsigned int index, quint64 time, QString itemSpec, QString data);

    QJsonObject toJson();
    void fromJson(QJsonObject &json);


};




class Synchronization : public QObject
{

private:
    Synchronization();
    ~Synchronization();

    QString getNumber(QString item);
    QString getNumber(int item);



    QQueue <action> BookQueue;
    QQueue <action> FileQueue;

    bool SettingsChanged;
    quint64 SettingsChangedTime;

    int LastOpenedWindow;

    unsigned int LastOpenedBookIndex;

public:
    static Synchronization* getSynchronization();

    int getLastOpenedWindow();
    void setLastOpenedWindow(unsigned int index);

    unsigned int getLastOpenedBookIndex();
    void setLastOpenedBookIndex(unsigned int index);

    int synchronizeToServer();
    int synchronizeFromServer();

    bool saveLog();
    bool loadLog();



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
                if (UActions::AddBook == FileQueue.at(i).Index && qualifier == FileQueue.at(i).Spec)
                {
                    FileQueue.removeAt(i);
                    return;
                }
            FileQueue.enqueue(action(actionIndex, qualifier, Sdata));
            return;

        case UActions::UpdateProgress:
            for (int i = 0; i < BookQueue.size(); i++)
                if (BookQueue.at(i).Index == UActions::UpdateProgress && qualifier == BookQueue.at(i).Spec)
                {
                    BookQueue[i].Time = QDateTime::currentMSecsSinceEpoch();
                    BookQueue[i].Changes = getNumber(data);
                    return;
                }
            Squalifier = getNumber(qualifier);
            Sdata = QString::number(data);
            BookQueue.enqueue(action(actionIndex, Squalifier, Sdata));
            return;

        case UActions::UpdateBookInf:
            for (int i = 0; i < BookQueue.size(); i++)
                if (BookQueue.at(i).Index == UActions::UpdateProgress && qualifier == BookQueue.at(i).Spec)
                {
                    BookQueue[i].Time = QDateTime::currentMSecsSinceEpoch();
                    BookQueue[i].Changes = getNumber(data);
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

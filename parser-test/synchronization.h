#ifndef SYNCHRONIZATION_H
#define SYNCHRONIZATION_H
#include <QQueue>
#include <QDateTime>
#include <QDataStream>
#include <QObject>


class Synchronization : public QObject
{
public:
    Synchronization();
    void addAction(int actionIndex, QString file, int bookIndex, QString dataChanges);
    int synchronizeToServer();
    int synchronizeFromServer();
    void saveLog();
    void loadLog();


private:

    /* Добавление книги - 1: файл, время
     * Удаление книги - 2: файл
     * Изменение прогресса - 3: индекс, значение
     * Редактирование описания - 4: индекс, значение
     * Изменение настроек - 5
     * Добавление фона - 6
     */

    struct action
    {
        QDateTime actionTime;
        short actionIndex;
        QString file;
        int bookIndex;
        QString dataChanges;

        action(){}
        action(int index, QString fileName, int Bindex, QString data);
        action(QDateTime time, int index, QString fileName, int Bindex, QString data);
    };

    QQueue <action> SynchroQueue;

public:
    friend QDataStream &operator>>(QDataStream &in, action &actionElem);
    friend QDataStream &operator<<(QDataStream &out, const action &actionElem);

};

#endif // SYNCHRONIZATION_H

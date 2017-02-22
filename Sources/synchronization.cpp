#include "synchronization.h"
#include <QFile>
#include <QQueue>
#include <QDir>
#include <QDataStream>
#include <QDebug>
#include <QString>

#include <QJsonArray>
#include <QJsonDocument>


action::action(const unsigned int &index, const QString &itemSpec, const QString &data)
{
    Time = QDateTime::currentMSecsSinceEpoch();
    Index = index;
    Spec = itemSpec;
    Changes = data;
}


action::action(const unsigned int &index, const quint64 &time, const QString &itemSpec, const QString &data)
{
    Time = time;
    Index = index;
    Spec = itemSpec;
    Changes = data;
}


action::action(QJsonObject &json)
{
    this->fromJson(json);
}


QJsonObject action::toJson()
{
    QJsonObject json;

    json["Time"] = QString::number(Time);
    json["Index"] = (int)Index;
    json["Spec"] = Spec;
    json["Changes"] = Changes;

    return json;
}


void action::fromJson(const QJsonObject &json)
{
    Time = json["Time"].toString().toULongLong();
    Index = (unsigned int)json["Index"].toInt();
    Spec = json["Spec"].toString();
    Changes = json["Changes"].toString();
}





Synchronization::Synchronization()
{
    SettingsChanged = false;
    LastOpenedWindow = 0;
    LastOpenedBookIndex = 0;
}


Synchronization::~Synchronization()
{}


Synchronization* Synchronization::getSynchronization()
{
    static Synchronization UserActions;
    return &UserActions;
}


bool Synchronization::loadLog()
{
    QString resoursesFolderPath = "LibraryResources";
    if ( ! QDir(resoursesFolderPath).exists()==true)
    {
        QDir().mkdir(resoursesFolderPath);
    }
    QFile LogList(resoursesFolderPath + "/ChangesLogs.json");

    if(!LogList.open(QIODevice::ReadOnly))
    {
        qDebug() << "Log Failed to Create File";
        qDebug() << "error = " << LogList.error()<< endl;

        ///оповещение - невозможно открыть или создать файл логов
        return 1;
    }

    QByteArray in = LogList.readAll();

    QJsonDocument SynJson(QJsonDocument::fromJson(in));

    QJsonObject SynObj = SynJson.object();

    SettingsChanged = SynObj["SettingsChanged"].toBool();
    SettingsChangedTime = SynObj["SettingsChangedTime"].toString().toULongLong();
    LastOpenedWindow = SynObj["LastOpenedWindow"].toInt();
    LastOpenedBookIndex = (unsigned int)SynObj["LastOpenedBookIndex"].toInt();

    BookQueue.clear();
    QJsonArray BookArray = SynObj["Books"].toArray();
    QJsonObject temp;
    for (int i = 0; i < BookArray.size(); i++)
    {
        temp = BookArray[i].toObject();
        BookQueue.append(action(temp));
    }

    FileQueue.clear();
    QJsonArray FileArray = SynObj["Files"].toArray();
    for (int i = 0; i < FileArray.size(); i++)
    {
        temp = FileArray[i].toObject();
        FileQueue.append(action(temp));
    }

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

    QFile LogList(resoursesFolderPath + "/ChangesLogs.json");

    LogList.open(QIODevice::WriteOnly);
    ///проверка

    QJsonObject SynObj;
    SynObj["SettingsChanged"] = SettingsChanged;
    SynObj["SettingsChangedTime"] = QString::number(SettingsChangedTime);
    SynObj["LastOpenedWindow"] = LastOpenedWindow;
    SynObj["LastOpenedBookIndex"] = (int)LastOpenedBookIndex;

    QJsonArray BookArray;
    for (int i = 0; i < BookQueue.size(); i++)
        BookArray.append(BookQueue[i].toJson());

    QJsonArray FileArray;
    for (int i = 0; i < FileQueue.size(); i++)
        FileArray.append(FileQueue[i].toJson());

    SynObj["Books"] = BookArray;
    SynObj["Files"] = FileArray;

    QJsonDocument SynJson(SynObj);
    LogList.write(SynJson.toJson());

    qDebug()<<"log saved";
    LogList.close();
    return 1;
}


QString Synchronization::getNumber(const QString &item)
{
    return item;
}


QString Synchronization::getNumber(const int &item)
{
    return QString::number(item);
}


int Synchronization::getLastOpenedWindow()
{
    return LastOpenedWindow;
}


void Synchronization::setLastOpenedWindow(const unsigned int &index)
{
    LastOpenedWindow = index;
}


unsigned int Synchronization::getLastOpenedBookIndex()
{
    return LastOpenedBookIndex;
}

void Synchronization::setLastOpenedBookIndex(const unsigned int &index)
{
    LastOpenedBookIndex = index;
}


QDataStream &operator>>(QDataStream &in, action &actionElem)
{
    in>>actionElem.Index;
    in>>actionElem.Time;
    in>>actionElem.Spec;
    in>>actionElem.Changes;
    return in;
}


QDataStream &operator<<(QDataStream &out, const action &actionElem)
{
    out<<actionElem.Index;
    out<<actionElem.Time;
    out<<actionElem.Spec;
    out<<actionElem.Changes;
    return out;
}

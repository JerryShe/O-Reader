#ifndef GENRESMAP_H
#define GENRESMAP_H
#include <QString>
#include <QMap>

class GenresMap
{
public:
    GenresMap();
    QString getGenreFromMap(const QString &key);

private:
    QMap <QString, QString> FB2GMap;
};

#endif // GENRESMAP_H

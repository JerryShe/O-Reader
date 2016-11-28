#ifndef GENRESMAP_H
#define GENRESMAP_H
#include <QString>
#include <QMap>

class GenresMap
{
public:
    GenresMap();
    QString getGenreFromMap(QString key);

private:
    QMap <QString, QString> GMap;
};

#endif // GENRESMAP_H

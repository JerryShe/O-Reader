#ifndef GENRESMAP_H
#define GENRESMAP_H

#include <QString>
#include <QMap>

class GenresMap
{
public:
    GenresMap();
    QString getFB2Genre(const QString &key) const;

private:
    void createFB2Map();
    void createEPubMap();

    QMap <QString, QString> FB2Map;
};

#endif // GENRESMAP_H

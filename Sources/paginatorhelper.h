#ifndef PAGINATORHELPER_H
#define PAGINATORHELPER_H

#include <QObject>
#include <QHash>
#include <QFontMetrics>

#include <settings.h>

class PaginatorHelper : public QObject
{
public:
    PaginatorHelper(QObject* parent);
    ~PaginatorHelper();

    void setHTMLPageElems(QString &PageHTMLStyles, QString &PageHTMLHeader, QString &PageHTMLSep, QString &PageHTMLBottom);
    void setFontMetrics(QHash <QString, QFontMetrics *> *fontsMetrics, QHash <QString, double> *fontsLinespaces);
    void setPageSizes(unsigned short &columnCount, unsigned short &TextLeftRightIdent, unsigned short &TextTopBottomIdent, unsigned short &ParLeftTopIdent);

    void refreshSettings();
private:
    ReadingProfile CurProfile;
};

#endif // PAGINATORHELPER_H

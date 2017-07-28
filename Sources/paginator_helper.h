#ifndef PAGINATOR_HELPER_H
#define PAGINATOR_HELPER_H

#include <QObject>
#include <QHash>
#include <QFontMetrics>

#include <settings.h>

class PaginatorHelper : public QObject
{
public:
    PaginatorHelper(QObject* parent);
    ~PaginatorHelper();

    //0 - decrement, 1 - increment
    void rescaleText(const bool &inc);

    void setHTMLPageStyles(QString &PageHTMLStyles);
    void setHTMLPageElems(QString &PageHTMLHeader, QString &PageHTMLSep, QString &PageHTMLBottom, const int &windowWidth);
    void setFontMetrics(QHash <QString, QFontMetrics *> *fontsMetrics, QHash <QString, double> *fontsLinespaces);
    void setPageSizes(unsigned short &columnCount, unsigned short &TextLeftRightIdent, unsigned short &TextTopBottomIdent, unsigned short &ParLeftTopIdent, unsigned short &columnIndent);

    void refreshSettings();
private:
    ReadingProfile CurProfile;
    int textScale;
};

#endif // PAGINATOR_HELPER_H

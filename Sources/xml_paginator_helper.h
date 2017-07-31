#ifndef XML_PAGINATOR_HELPER_H
#define XML_PAGINATOR_HELPER_H

#include <QObject>
#include <QHash>
#include <QFontMetrics>

#include <settings.h>

class XMLPaginatorHelper : public QObject
{
public:
    XMLPaginatorHelper(QObject* parent);
    ~XMLPaginatorHelper();

    //0 - decrement, 1 - increment
    void rescaleText(const bool &inc);

    QSize getPageSize(const int widgetWidth, const int widgetHeight);

    void setHTMLPageStyles(QString &PageHTMLStyles);
    void setHTMLPageElems(QString &PageHTMLHeader, QString &PageHTMLSep, QString &PageHTMLBottom, const int &windowWidth);
    void setFontMetrics(QHash <QString, QFontMetrics *> *fontsMetrics, QHash <QString, double> *fontsLinespaces);
    void setPageData(unsigned short &columnCount, unsigned short &ParLeftTopIdent);


    void refreshSettings();
private:
    ReadingProfile CurProfile;
    int textScale;
};

#endif // XML_PAGINATOR_HELPER_H

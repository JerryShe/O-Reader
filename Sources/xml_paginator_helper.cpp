#include "xml_paginator_helper.h"

#include <QDebug>

XMLPaginatorHelper::XMLPaginatorHelper(QObject *parent)
{
    qDebug()<<"create PaginatorHelper";
    setParent(parent);
    refreshSettings();

    textScale = 0;
}

XMLPaginatorHelper::~XMLPaginatorHelper()
{
    qDebug()<<"delete PaginatorHelper";
}


void XMLPaginatorHelper::rescaleText(const bool &inc)
{
    if (inc)
    {
        if (CurProfile.TitleStyle.Size + textScale< 75 &&
                CurProfile.EpigraphStyle.Size + textScale < 75 &&
                CurProfile.SubtitleStyle.Size + textScale < 75 &&
                CurProfile.RegularStyle.Size + textScale < 75 &&
                CurProfile.EmphasizedStyle.Size + textScale < 75 &&
                CurProfile.PoemStyle.Size + textScale < 75 &&
                CurProfile.CiteStyle.Size + textScale < 75 &&
                CurProfile.NoteStyle.Size + textScale < 75)
            textScale++;
    }
    else
    {
        if (CurProfile.TitleStyle.Size + textScale > 6 &&
                CurProfile.EpigraphStyle.Size + textScale > 6 &&
                CurProfile.SubtitleStyle.Size + textScale > 6 &&
                CurProfile.RegularStyle.Size + textScale > 6 &&
                CurProfile.EmphasizedStyle.Size + textScale > 6 &&
                CurProfile.PoemStyle.Size + textScale > 6 &&
                CurProfile.CiteStyle.Size + textScale > 6 &&
                CurProfile.NoteStyle.Size + textScale > 6)
            textScale--;
    }
}

//TODO: curprofile to pointer
void XMLPaginatorHelper::setHTMLPageStyles(QString &PageHTMLStyles)
{
    QString topMargin = "margin-top:" + QString::number(CurProfile.ParLeftTopIdent%100) + "px;";

    PageHTMLStyles = "<style type='text/css'>"
                     "p{"
                          + topMargin +
                          "margin-bottom:0px;"
                          "text-indent:" + QString::number(CurProfile.ParLeftTopIdent/100) + "px;"
                          "text-align-last: justify;}"

                     "p.begin{text-indent: 0px;}"
                     "P.image {text-align: center; text-indent:0px}"

                     "TitleText{"
                           + topMargin + CurProfile.TitleStyle.getHTMLStyle(textScale) + "}"

                     "epigraph{"
                           + topMargin + CurProfile.EpigraphStyle.getHTMLStyle(textScale) + "}"

                     "subtitle{"
                           + topMargin + CurProfile.SubtitleStyle.getHTMLStyle(textScale) + "}"

                     "Text{"
                           + topMargin + CurProfile.RegularStyle.getHTMLStyle(textScale) + "}"

                     "emphasis{"
                           + topMargin + CurProfile.EmphasizedStyle.getHTMLStyle(textScale) + "}"

                     "poem{"
                           + topMargin + CurProfile.PoemStyle.getHTMLStyle(textScale) + "}"

                     "cite{"
                           + topMargin + CurProfile.CiteStyle.getHTMLStyle(textScale) + "}"

                     "a[type = 'note']{"
                           + "vertical-align: super;"
                           + topMargin + CurProfile.NoteStyle.getHTMLStyle(textScale) + "}"

                     "strong{"
                          + topMargin + "font-weight:" + QString::number(99) + "}"

                      + ((CurProfile.BackgroundType == true) ? ("body{background-color:" + CurProfile.BackgroundImage + ";}") : ("")) +
                  "</style>";
}


void XMLPaginatorHelper::setHTMLPageElems(QString &PageHTMLHeader, QString &PageHTMLSep, QString &PageHTMLBottom, const int &columnWidth)
{
    int width = columnWidth/CurProfile.ColumnCount;

    PageHTMLHeader = "<body>"
                     "<table style='"
                       "table-layout: fixed;"
                       "border:0;"
                       "empty-cells: show;"
                       "margin-top: " + QString::number(CurProfile.TextTopBottomIdent/100) + "px;"
                       "margin-bottom: " + QString::number(CurProfile.TextTopBottomIdent%100) + "px;"
                       "margin-left:" + QString::number(CurProfile.TextLeftRightIdent/100) + "px;"
                       "margin-right:" + QString::number(CurProfile.TextLeftRightIdent%100) + "px;'"
                       "width='100%'"
                       "cellspacing='-" + QString::number(CurProfile.ColumnIndent) + "' cellpadding='" + QString::number(CurProfile.ColumnIndent) + "'>"
                     "<tr>"
                     "<td align = 'justify' width=\"" + QString::number(width + CurProfile.ColumnIndent) + "\"><Text>";

    PageHTMLSep = "</Text></td><td align = 'justify' width=\"" + QString::number(width + CurProfile.ColumnIndent) + "\"><Text>";
    PageHTMLBottom = "</Text></td></tr></table></body>";
}


void XMLPaginatorHelper::setFontMetrics(QHash <QString, QFontMetrics*> *fontsMetrics, QHash <QString, double> *fontsLinespaces)
{
    fontsMetrics->clear();
    fontsLinespaces->clear();

    QFont textFont(CurProfile.RegularStyle.Family, CurProfile.RegularStyle.Size + textScale, 49*(CurProfile.RegularStyle.Style%2) + 50, CurProfile.RegularStyle.Style/10);
    fontsMetrics->insert("Text", new QFontMetrics(textFont));

    textFont.setWeight(75);
    fontsMetrics->insert("strong", new QFontMetrics(textFont));

    QFont titleFont(CurProfile.TitleStyle.Family, CurProfile.TitleStyle.Size + textScale, 49*(CurProfile.TitleStyle.Style%2) + 50, CurProfile.TitleStyle.Style/10);
    fontsMetrics->insert("TitleText", new QFontMetrics(titleFont));

    QFont epigraphFont(CurProfile.EpigraphStyle.Family, CurProfile.EpigraphStyle.Size + textScale, 49*(CurProfile.EpigraphStyle.Style%2) + 50, CurProfile.EpigraphStyle.Style/10);
    fontsMetrics->insert("epigraph", new QFontMetrics(epigraphFont));

    QFont empFont(CurProfile.EmphasizedStyle.Family, CurProfile.EmphasizedStyle.Size + textScale, 49*(CurProfile.EmphasizedStyle.Style%2) + 50, CurProfile.EmphasizedStyle.Style/10);
    fontsMetrics->insert("emphasis", new QFontMetrics(empFont));

    QFont noteFont(CurProfile.NoteStyle.Family, CurProfile.NoteStyle.Size + textScale, 49*(CurProfile.NoteStyle.Style%2) + 50, CurProfile.NoteStyle.Style/10);
    fontsMetrics->insert("note", new QFontMetrics(noteFont));

    QFont subtitleFont(CurProfile.SubtitleStyle.Family, CurProfile.SubtitleStyle.Size + textScale, 49*(CurProfile.SubtitleStyle.Style%2) + 50, CurProfile.SubtitleStyle.Style/10);
    fontsMetrics->insert("subtitle", new QFontMetrics(subtitleFont));

    QFont poemFont(CurProfile.PoemStyle.Family, CurProfile.PoemStyle.Size + textScale, 49*(CurProfile.PoemStyle.Style%2) + 50, CurProfile.PoemStyle.Style/10);
    fontsMetrics->insert("poem", new QFontMetrics(poemFont));

    QFont citeFont(CurProfile.CiteStyle.Family, CurProfile.CiteStyle.Size + textScale, 49*(CurProfile.CiteStyle.Style%2) + 50, CurProfile.CiteStyle.Style/10);
    fontsMetrics->insert("cite", new QFontMetrics(citeFont));


    fontsLinespaces->insert("Text", CurProfile.RegularStyle.LineSpacing * fontsMetrics->value("Text")->lineSpacing());
    fontsLinespaces->insert("strong", CurProfile.RegularStyle.LineSpacing * fontsMetrics->value("strong")->lineSpacing());
    fontsLinespaces->insert("TitleText", CurProfile.TitleStyle.LineSpacing * fontsMetrics->value("TitleText")->lineSpacing());
    fontsLinespaces->insert("epigraph", CurProfile.EpigraphStyle.LineSpacing * fontsMetrics->value("epigraph")->lineSpacing());
    fontsLinespaces->insert("emphasis", CurProfile.EmphasizedStyle.LineSpacing * fontsMetrics->value("emphasis")->lineSpacing());
    fontsLinespaces->insert("note", CurProfile.NoteStyle.LineSpacing * fontsMetrics->value("note")->lineSpacing());
    fontsLinespaces->insert("cite", CurProfile.CiteStyle.LineSpacing * fontsMetrics->value("cite")->lineSpacing());
    fontsLinespaces->insert("poem", CurProfile.PoemStyle.LineSpacing * fontsMetrics->value("poem")->lineSpacing());
    fontsLinespaces->insert("subtitle", CurProfile.SubtitleStyle.LineSpacing * fontsMetrics->value("subtitle")->lineSpacing());
}


void XMLPaginatorHelper::refreshSettings()
{
    CurProfile = Settings::getSettings()->getCurrentReadProfile();
}


QSize XMLPaginatorHelper::getPageSize(const int widgetWidth, const int widgetHeight)
{
    return QSize ((widgetWidth - 10 - CurProfile.ColumnIndent*(CurProfile.ColumnCount-1) - CurProfile.TextLeftRightIdent/100 - CurProfile.TextLeftRightIdent%100)/CurProfile.ColumnCount,
                widgetHeight - 20 - CurProfile.TextTopBottomIdent/100 - CurProfile.TextTopBottomIdent%100);
}


void XMLPaginatorHelper::setPageData(unsigned short &columnCount, unsigned short &ParLeftTopIdent)
{
    columnCount = CurProfile.ColumnCount;
    ParLeftTopIdent = CurProfile.ParLeftTopIdent;
}

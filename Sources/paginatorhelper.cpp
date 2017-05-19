#include "paginatorhelper.h"

#include <QDebug>

PaginatorHelper::PaginatorHelper(QObject *parent)
{
    qDebug()<<"create PaginatorHelper";
    setParent(parent);
    refreshSettings();
}

PaginatorHelper::~PaginatorHelper()
{
    qDebug()<<"delete PaginatorHelper";
}


void PaginatorHelper::setHTMLPageElems(QString &PageHTMLStyles, QString &PageHTMLHeader, QString &PageHTMLSep, QString &PageHTMLBottom)
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
                           + topMargin + CurProfile.TitleStyle.getHTMLStyle() + ";}"

                     "epigraph{"
                           + topMargin + CurProfile.EpigraphStyle.getHTMLStyle() + ";}"

                     "subtitle{"
                           + topMargin + CurProfile.SubtitleStyle.getHTMLStyle() + ";}"

                     "Text{"
                           + topMargin + CurProfile.RegularStyle.getHTMLStyle() + ";}"

                     "emphasis{"
                           + topMargin + CurProfile.EmphasizedStyle.getHTMLStyle() + ";}"

                     "poem{"
                           + topMargin + CurProfile.PoemStyle.getHTMLStyle() + ";}"

                     "cite{"
                           + topMargin + CurProfile.CiteStyle.getHTMLStyle() + ";}"

                     "note{"
                           + "vertical-align: super;"
                           + topMargin + CurProfile.NoteStyle.getHTMLStyle() + ";}"

                     "strong{"
                          + topMargin + "font-weight:" + QString::number(99) + ";}"

                      + ((CurProfile.BackgroundType == true) ? ("body{background-color:" + CurProfile.BackgroundImage + ";}") : ("")) +
                  "</style>";

    PageHTMLHeader = "<body>"
                     "<table border='0' style='"
                       "table-layout: fixed;"
                       "empty-cells: show;"
                       "margin-top: " + QString::number(CurProfile.TextTopBottomIdent/100) + "px;"
                       "margin-bottom: " + QString::number(CurProfile.TextTopBottomIdent%100) + "px;"
                       "margin-left:" + QString::number(CurProfile.TextLeftRightIdent/100) + "px;"
                       "margin-right:" + QString::number(CurProfile.TextLeftRightIdent%100) + "px;'"
                       "width='100%'"
                       "cellspacing='-30' cellpadding='30'>"
                     "<tr>"
                     "<td align = 'justify' width = '" + QString::number(100/CurProfile.ColumnCount) + "%'>"
                     "<Text>";

    PageHTMLSep = "</Text></td><td align = 'justify' width = '" + QString::number(100/CurProfile.ColumnCount) + "%'><Text>";
    PageHTMLBottom = "</Text></td></tr></table></body>";
}


void PaginatorHelper::setFontMetrics(QHash <QString, QFontMetrics*> *fontsMetrics, QHash <QString, double> *fontsLinespaces)
{
    fontsMetrics->clear();
    fontsLinespaces->clear();

    QFont textFont(CurProfile.RegularStyle.Family, CurProfile.RegularStyle.Size, 49*(CurProfile.RegularStyle.Style%2) + 50, CurProfile.RegularStyle.Style/10);
    fontsMetrics->insert("Text", new QFontMetrics(textFont));

    textFont.setWeight(75);
    fontsMetrics->insert("strong", new QFontMetrics(textFont));

    QFont titleFont(CurProfile.TitleStyle.Family, CurProfile.TitleStyle.Size, 49*(CurProfile.TitleStyle.Style%2) + 50, CurProfile.TitleStyle.Style/10);
    fontsMetrics->insert("TitleText", new QFontMetrics(titleFont));

    QFont epigraphFont(CurProfile.EpigraphStyle.Family, CurProfile.EpigraphStyle.Size, 49*(CurProfile.EpigraphStyle.Style%2) + 50, CurProfile.EpigraphStyle.Style/10);
    fontsMetrics->insert("epigraph", new QFontMetrics(epigraphFont));

    QFont empFont(CurProfile.EmphasizedStyle.Family, CurProfile.EmphasizedStyle.Size, 49*(CurProfile.EmphasizedStyle.Style%2) + 50, CurProfile.EmphasizedStyle.Style/10);
    fontsMetrics->insert("emphasis", new QFontMetrics(empFont));

    QFont noteFont(CurProfile.NoteStyle.Family, CurProfile.NoteStyle.Size, 49*(CurProfile.NoteStyle.Style%2) + 50, CurProfile.NoteStyle.Style/10);
    fontsMetrics->insert("note", new QFontMetrics(noteFont));

    QFont subtitleFont(CurProfile.SubtitleStyle.Family, CurProfile.SubtitleStyle.Size, 49*(CurProfile.SubtitleStyle.Style%2) + 50, CurProfile.SubtitleStyle.Style/10);
    fontsMetrics->insert("subtitle", new QFontMetrics(subtitleFont));

    QFont poemFont(CurProfile.PoemStyle.Family, CurProfile.PoemStyle.Size, 49*(CurProfile.PoemStyle.Style%2) + 50, CurProfile.PoemStyle.Style/10);
    fontsMetrics->insert("poem", new QFontMetrics(poemFont));

    QFont citeFont(CurProfile.CiteStyle.Family, CurProfile.CiteStyle.Size, 49*(CurProfile.CiteStyle.Style%2) + 50, CurProfile.CiteStyle.Style/10);
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


void PaginatorHelper::refreshSettings()
{
    CurProfile = Settings::getSettings()->getCurrentReadProfileElem();
}


void PaginatorHelper::setPageSizes(unsigned short &columnCount, unsigned short &TextLeftRightIdent, unsigned short &TextTopBottomIdent, unsigned short &ParLeftTopIdent)
{
    columnCount = CurProfile.ColumnCount;
    TextLeftRightIdent = CurProfile.TextLeftRightIdent;
    TextTopBottomIdent = CurProfile.TextTopBottomIdent;
    ParLeftTopIdent = CurProfile.ParLeftTopIdent;
}

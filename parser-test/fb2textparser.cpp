#include "fb2textparser.h"
#include <QFont>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QUrl>
#include <QString>
#include <QFontMetrics>


FB2TextParser::FB2TextParser(Book boo, settings* PSettings, int width, int height)
{
    setPageGeometry(width, height);

    book = boo;
    ProgramSettings = PSettings;
    currentEStrNum = currentBStrNum = book.getBookProgress();
    tagStack.push("Text");

    parseBookText();
    setHTMLinf();
    setFontMap();
    setLinespaceMap();
    setSpacesWidth();
}

FB2TextParser::~FB2TextParser()
{
    delete ProgramSettings;
    //очистить мапу шрифтов
}

void FB2TextParser::setFontMap()
{

    QFont textFont(CurStyle.RegularTextStyle.FontFamily, CurStyle.RegularTextStyle.FontSize, 100*(CurStyle.RegularTextStyle.FontStyle%2) -1, CurStyle.RegularTextStyle.FontStyle/10);
    QFontMetrics * a = new QFontMetrics(textFont);
    fontMap.insert("Text", a);

    textFont.setWeight(99);
    QFontMetrics *b = new QFontMetrics(textFont);
    fontMap.insert("strong", b);

    QFont titleFont(CurStyle.TitleStyle.FontFamily, CurStyle.TitleStyle.FontSize, 100*(CurStyle.TitleStyle.FontStyle%2) -1, CurStyle.TitleStyle.FontStyle/10);
    QFontMetrics * c = new QFontMetrics(titleFont);
    fontMap.insert("TitleText", c);

    QFont subtitleFont(CurStyle.SubtitleStyle.FontFamily, CurStyle.SubtitleStyle.FontSize, 100*(CurStyle.SubtitleStyle.FontStyle%2) -1, CurStyle.SubtitleStyle.FontStyle/10);
    QFontMetrics * d = new QFontMetrics(subtitleFont);
    fontMap.insert("epigraph", d);

    QFont empFont(CurStyle.EmphasizedTextStyle.FontFamily, CurStyle.EmphasizedTextStyle.FontSize, 100*(CurStyle.EmphasizedTextStyle.FontStyle%2) -1, CurStyle.EmphasizedTextStyle.FontStyle/10);
    QFontMetrics * e = new QFontMetrics(empFont);
    fontMap.insert("emphasis", e);

    QFont noteFont(CurStyle.NoteStyle.FontFamily, CurStyle.NoteStyle.FontSize, 100*(CurStyle.NoteStyle.FontStyle%2) -1, CurStyle.NoteStyle.FontStyle/10);
    QFontMetrics * f = new QFontMetrics(noteFont);
    fontMap.insert("Note", f);

}

void FB2TextParser::setSpacesWidth()
{
    spacesMap.insert("Text", fontMap["Text"]->charWidth(" ", 0));
    spacesMap.insert("strong", fontMap["strong"]->charWidth(" ", 0));
    spacesMap.insert("TitleText", fontMap["TitleText"]->charWidth(" ", 0));
    spacesMap.insert("epigraph", fontMap["epigraph"]->charWidth(" ", 0));
    spacesMap.insert("emphasis", fontMap["emphasis"]->charWidth(" ", 0));
    spacesMap.insert("Note", fontMap["Note"]->charWidth(" ", 0));
}

void FB2TextParser::setLinespaceMap()
{
    linespaceMap.insert("Text", CurStyle.RegularTextStyle.LineSpacing * fontMap["Text"]->lineSpacing());
    linespaceMap.insert("strong", CurStyle.RegularTextStyle.LineSpacing * fontMap["strong"]->lineSpacing());
    linespaceMap.insert("TitleText", CurStyle.TitleStyle.LineSpacing * fontMap["TitleText"]->lineSpacing());
    linespaceMap.insert("epigraph", CurStyle.SubtitleStyle.LineSpacing * fontMap["epigraph"]->lineSpacing());
    linespaceMap.insert("emphasis", CurStyle.EmphasizedTextStyle.LineSpacing * fontMap["emphasis"]->lineSpacing());
    linespaceMap.insert("Note", CurStyle.NoteStyle.LineSpacing * fontMap["Note"]->lineSpacing());
}

void FB2TextParser::setPageGeometry(int width, int height)
{
    pageWidth = (width - 10 - (CurStyle.TextLeftRightIdent/100) * CurStyle.ColumnCount - (CurStyle.TextLeftRightIdent%100)*CurStyle.ColumnCount - 30)/CurStyle.ColumnCount;
    pageHeight = height - CurStyle.TextTopBottomIdent/100;// - CurStyle.TextTopBottomIdent%100;
    qDebug()<<pageWidth<<pageHeight;
}

void FB2TextParser::setHTMLinf()
{
    CurStyle = ProgramSettings->getCurrentTextStyleElem();

    QString fileName;
    if (CurStyle.BackgroundType == false)
        fileName = QUrl::fromLocalFile(CurStyle.BackgroundImage).toString();

    PageHTMLHeader = "<style type='text/css'>"
                     "p{"

                          "margin-top:" + QString::number(CurStyle.ParLeftTopIdent%100) + "px;"
                          //"text-align = justify;"
                          "margin-bottom:0px;"
                          "margin-left:" + QString::number(CurStyle.TextLeftRightIdent/100) + "px;"
                          "margin-right:" + QString::number(CurStyle.TextLeftRightIdent%100) + "px;}"

                     "TitleText{"
                          "font-family:'" + CurStyle.TitleStyle.FontFamily + "';"
                          "font-size:" + QString::number(CurStyle.TitleStyle.FontSize) + "pt;"
                          "font-weight:" + ((CurStyle.TitleStyle.FontStyle%2)? QString("bold"):QString("normal")) + ";"
                          "line-height:" + QString::number(CurStyle.TitleStyle.LineSpacing*100) + ";"
                          "font-style:" + ((CurStyle.TitleStyle.FontStyle/2 == 1)?QString("italic"):QString("normal")) + ";"
                          "text-align:" + CurStyle.TitleStyle.TextAlign.toLower() + ";"
                          "color:" + CurStyle.TitleStyle.TextColor + ";"
                          "text-indent:" + QString::number(CurStyle.ParLeftTopIdent/100) + "px;}"

                     "epigraph{"
                          "font-family:'" + CurStyle.SubtitleStyle.FontFamily + "';"
                          "font-size:" + QString::number(CurStyle.SubtitleStyle.FontSize) + "pt;"
                          "font-weight:" + ((CurStyle.SubtitleStyle.FontStyle%2)? QString("bold"):QString("normal")) + ";"
                          "line-height:" + QString::number(CurStyle.SubtitleStyle.LineSpacing*100) + ";"
                          "font-style:" + ((CurStyle.SubtitleStyle.FontStyle/2 == 1)?QString("italic"):QString("normal")) + ";"
                          "text-align:" + CurStyle.SubtitleStyle.TextAlign.toLower() + ";"
                          "color:" + CurStyle.SubtitleStyle.TextColor + ";"
                          "text-indent:" + QString::number(CurStyle.ParLeftTopIdent/100) + "px;}"

                     "Text{"
                          "font-family:'" + CurStyle.RegularTextStyle.FontFamily + "';"
                          "font-size:" + QString::number(CurStyle.RegularTextStyle.FontSize) + "pt;"
                          "font-weight:" + ((CurStyle.RegularTextStyle.FontStyle%2)? QString("bold"):QString("normal")) + ";"
                          "line-height:" + QString::number(CurStyle.RegularTextStyle.LineSpacing*100) + ";"
                          "font-style:" + ((CurStyle.RegularTextStyle.FontStyle/2 == 1)?QString("italic"):QString("normal")) + ";"
                          "text-align:" + CurStyle.RegularTextStyle.TextAlign.toLower() + ";"
                          "color:" + CurStyle.RegularTextStyle.TextColor + ";"
                          "text-indent:" + QString::number(CurStyle.ParLeftTopIdent/100) + "px;}"

                     "emphasis{"
                          "font-family:'" + CurStyle.EmphasizedTextStyle.FontFamily + "';"
                          "font-size:" + QString::number(CurStyle.EmphasizedTextStyle.FontSize) + "pt;"
                          "font-weight:" + ((CurStyle.EmphasizedTextStyle.FontStyle%2)? QString("bold"):QString("normal")) + ";"
                          "line-height:" + QString::number(CurStyle.EmphasizedTextStyle.LineSpacing*100) + ";"
                          "font-style:" + ((CurStyle.EmphasizedTextStyle.FontStyle/2 == 1)?QString("italic"):QString("normal")) + ";"
                          "text-align:" + CurStyle.EmphasizedTextStyle.TextAlign.toLower() + ";"
                          "color:" + CurStyle.EmphasizedTextStyle.TextColor + ";"
                          "text-indent:" + QString::number(CurStyle.ParLeftTopIdent/100) + "px;}"

                     "Note{"
                          "font-family:'" + CurStyle.NoteStyle.FontFamily + "';"
                          "font-size:" + QString::number(CurStyle.NoteStyle.FontSize) + "pt;"
                          "font-weight:" + ((CurStyle.NoteStyle.FontStyle%2)? QString("bold"):QString("normal")) + ";"
                          "line-height:" + QString::number(CurStyle.NoteStyle.LineSpacing*100) + ";"
                          "font-style:" + ((CurStyle.NoteStyle.FontStyle/2 == 1)?QString("italic"):QString("normal")) + ";"
                          "text-align:" + CurStyle.NoteStyle.TextAlign.toLower() + ";"
                          "color:" + CurStyle.NoteStyle.TextColor + ";"
                          "text-indent:" + QString::number(CurStyle.ParLeftTopIdent/100) + "px;}"

                     "strong{"
                          "font-weight:" + QString::number(99) + ";}"

                     "body{"
                          "background" + ((CurStyle.BackgroundType == true) ? ("-color:" + CurStyle.BackgroundImage) : ("-image:url(" + fileName + ")")) + ";}"
                  "</style>"
                  "<body>"
                  "<table border='0' style='"
                    "table-layout: fixed;"
                    "empty-cells: show;'"
                    "width='100%' cellspacing='-30' cellpadding='30'>"
                  "<tr>"
                  "<td align = 'justify' width = '" + QString::number(100/CurStyle.ColumnCount) + "%'>"
                  "<Text>";

    PageHTMLSep = "</Text></td><td align = 'justify' width = '" + QString::number(100/CurStyle.ColumnCount) + "%'><Text>";
    PageHTMLBottom = "</Text></td></tr></table></body>";

}

void FB2TextParser::parseBookText()
{
    QFile bookFile(book.File);
    if (bookFile.open(QIODevice::ReadOnly))
    {
        QTextStream doc (&bookFile);
        doc.setCodec(book.getBookCodec().toStdString().c_str());

        QString temp;

        do
            doc>>temp;
        while(temp.indexOf("<body>") == -1);

        temp = temp.remove(0, temp.indexOf("<body>") + 6);
        temp.replace("<title>", "<TitleText>");
        temp.replace("</title>", "</TitleText>");
        bookText.append(temp);

        while(!doc.atEnd() )
        {
            doc>>temp;
            if (temp.indexOf("<binary") != -1)
                strCount = bookText.size();
            temp.replace("<title>", "<TitleText>");
            temp.replace("</title>", "</TitleText>");
            bookText.append(temp);
        }
        bookText.back() = bookText.back().remove(bookText.back().indexOf("</FictionBook>"), bookText.back().size());

        bookFile.close();
    }
    else
    {
        qDebug()<<"невозможно открыть файл книги";
    }
}

int FB2TextParser::getWordHeight(QString word)
{
    /*
    for (int i = tagStack.size() - 1; i > 0; i--)
        if (fontMap.contains(tagStack[i]))
            return fontMap[tagStack[i]]->size(Qt::TextSingleLine,word).height();
    return fontMap[tagStack[0]]->size(Qt::TextSingleLine,word).height();
    */
    for (int i = tagStack.size() - 1; i > 0; i--)
        if (linespaceMap.contains(tagStack[i]))
            return linespaceMap[tagStack[i]];
    return linespaceMap[tagStack[0]];
}

int FB2TextParser::getWordWidth(QString word)
{
    for (int i = tagStack.size() - 1; i > 0; i--)
        if (fontMap.contains(tagStack[i]))
            return fontMap[tagStack[i]]->boundingRect(word).width() + 1;
    return fontMap[tagStack[0]]->boundingRect(word).width() + 1;
}

int FB2TextParser::getSpaceWidth()
{
    for (int i = tagStack.size() - 1; i > 0; i--)
        if (spacesMap.contains(tagStack[i]))
            return spacesMap[tagStack[i]];
    return spacesMap[tagStack[0]];
}

QString FB2TextParser::getPageFrom()
{
    Columns.clear();
    int pageBegin = currentEStrNum;

    qDebug()<<"width: "<<pageWidth;

    int i;
    int wordWidth = 0, wordHeight = 0;

    for (int col = 0; col < CurStyle.ColumnCount; col++)
    {
        qDebug()<<col << i;
        Columns.append(columnTale);
        currentHeight = currentWidth = 0;
        int stringHeight = 0;
        QString word;
        QString tag;
        int stringWordCount = 0;
        int stringStep = 0;
        for (i = pageBegin; i < strCount && currentHeight + wordHeight <= pageHeight; i++)
        {
            word = tag = "";
            bool flag = 0;
            for (int j = 0; j < bookText[i].size(); j++)
            {
                if (bookText[i][j] == '<')
                {
                    //посчитать размер для уже считанного
                    if (word != "")
                    {
                        wordHeight = getWordHeight(word);
                        if (wordHeight > stringHeight)
                        {
                            stringHeight = wordHeight;
                            if (currentHeight + stringHeight > pageHeight)
                            {
                                //перенос на сл колонку
                                //отрезать stringWordCount слов от колонки
                                flag = 1;
                                break;
                            }
                        }

                        wordWidth = getWordWidth(word);
                        qDebug()<<word<<": "<< wordHeight << wordWidth << currentHeight << currentWidth;

                        if (currentWidth + wordWidth + getSpaceWidth() > pageWidth)
                        {
                            if (currentWidth + wordWidth > pageWidth)
                            {
                                if (currentHeight + wordHeight  > pageHeight)
                                {
                                    //переносим колонку
                                    for (int p = tagStack.size() - 1; p > 0; p--)
                                        Columns[col] += "</" + tagStack[p] + ">";

                                    for (int p = 1; p < tagStack.size(); p++)
                                        columnTale += "<" + tagStack[p] + ">";

                                    break;
                                }
                                else
                                {
                                    //переносим строку
                                    qDebug()<<"Yepe, it's line ->>>>>"<< currentHeight<<stringHeight;

                                    currentHeight += stringHeight;
                                    if (stringStep != 0)
                                    {
                                        currentWidth = stringStep;
                                        stringStep = 0;
                                    }
                                    else
                                        currentWidth = 0;
                                }
                            }
                            else
                                currentWidth += wordWidth;
                        }
                        else
                            currentWidth += wordWidth + getSpaceWidth();
                    }

                    if (flag)
                        break;

                    tag = "";
                    for (j = j + 1; j < bookText[i].size() && bookText[i][j] != '>'; j++)
                        tag += bookText[i][j];
                    if (bookText[i][j] != '>')
                        tag = "";

                    if (tag == "image")
                    {
                        i++;
                        i++;
                        //сделать загрузку картинки


                        //qDebug()<<bookText[i];
                        //for (j = 0; j < bookText[i].size() && bookText[i][0] != '>'; j++)

                        continue;
                    }

                    if (tag != "empty-line/")
                    {
                        if (tag == "p")
                        {
                            currentHeight += stringHeight + CurStyle.ParLeftTopIdent%100;
                            stringHeight = 0;
                            currentWidth = CurStyle.ParLeftTopIdent/100 + 1;
                        }

                        if (tag.indexOf("/") != -1)
                            tag  = tag.remove(0, 1);

                        if (tag != "body" && tag != "section")
                        {
                            if (tagStack.back() == tag)
                            {
                                word = "";
                                tagStack.pop();
                            }
                            else
                            {
                                tagStack.push(tag);
                            }
                        }
                    }
                    else
                    {
                        currentHeight += stringHeight;
                        stringHeight = 0;
                        currentWidth = 0;
                    }
                }
                else
                    word += bookText[i][j];
            }
            //посчитать размер для считанного
            if (word != "")
            {
                wordHeight = getWordHeight(word);
                if (wordHeight > stringHeight)
                {
                    stringHeight = wordHeight;
                    if (currentHeight + stringHeight > pageHeight)
                    {
                        //перенос на сл колонку
                        //отрезать stringWordCount слов от колонки

                        stringWordCount = 0;
                        break;
                    }
                }

                wordWidth = getWordWidth(word);
                qDebug()<<word<<": "<< wordHeight << wordWidth << currentHeight << currentWidth;

                flag = 0;
                if (currentWidth + wordWidth + getSpaceWidth() > pageWidth)
                {
                    if (currentWidth + wordWidth > pageWidth)
                    {
                        if (currentHeight + wordHeight > pageHeight)
                        {
                            //переносим колонку
                            flag = 1;
                            break;
                        }
                        else
                        {
                            //переносим строку
                            qDebug()<<"Yepe, it's line ->>>>>"<< currentHeight<<stringHeight;

                            currentHeight += stringHeight;
                            if (stringStep != 0)
                            {
                                currentWidth = stringStep;
                                stringStep = 0;
                            }
                            else
                                currentWidth = 0;
                        }
                    }
                    else
                        currentWidth += wordWidth;
                }
                else
                    currentWidth += wordWidth + getSpaceWidth();
            }

            if (!flag)
                Columns[col] += bookText[i] + " ";
            else
                i--;
        }

        for (int p = tagStack.size() - 1; p > 0; p--)
            Columns[col] += "</" + tagStack[p] + ">";

        for (int p = 1; p < tagStack.size(); p++)
            columnTale += "<" + tagStack[p] + ">";

        qDebug()<<col << i;
        pageBegin += i;
    }

    currentBStrNum = pageBegin;
    currentEStrNum = currentBStrNum + i;

    QString HTMLPage = Columns[0];
    for (int i = 1; i < CurStyle.ColumnCount; ++i)
        HTMLPage += PageHTMLSep + Columns[i];

    return PageHTMLHeader + HTMLPage + PageHTMLBottom;
}



QString FB2TextParser::getPageTo()
{
    //QString HTMLPage;
    return PageHTMLHeader + PageHTMLBottom;
}

QString FB2TextParser::updatePage()
{
    //QString HTMLPage;
    return PageHTMLHeader + PageHTMLBottom;
}

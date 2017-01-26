#include "fb2textpaginator.h"
#include <QFont>
#include <QFile>
#include <QDebug>
#include <QUrl>
#include <QString>
#include <QFontMetrics>

QStringList FB2TextPaginator::splitTextToWords(QString temp)
{
    QStringList tempList;
    tempList.append(temp);
    for (int i = 0; i < tempList.size(); i++)
    {
        int pos = tempList[i].indexOf("<");
        if (pos > 0)
        {
            tempList.append(tempList[i].right(tempList[i].size() - pos));
            tempList[i] = tempList[i].left(pos);
            i++;
        }

        if (tempList[i][0] == '<')
        {
            pos = tempList[i].indexOf(">");
            if (pos == -1)
            {
                do
                {
                    doc->operator >>(temp);
                    tempList[i].append(" " + temp);
                }
                while (temp.indexOf(">") == -1);
            }

            if (pos != tempList[i].size() - 1)
            {
                tempList.append(tempList[i].right(tempList[i].size() - pos - 1));
                tempList[i] = tempList[i].left(pos + 1);
            }
        }
    }

    for (int i = 0; i < tempList.size(); i++)
    {
        if (tempList[i][0] != '<')
        {
            int pos = tempList[i].indexOf("-");
            if (pos > 0 && pos != tempList[i].size() - 1)
            {
                QStringList newTemp = tempList[i].split("-");
                if (newTemp.size() > 1)
                {
                    for (int j = 0; j < newTemp.size() - 1; j++)
                        newTemp[j] += "-";

                    tempList.removeAt(i);

                    for (int j = 0; j < newTemp.size(); j++)
                        tempList.insert(i++, newTemp[j]);
                }
            }
        }
        else
        {
            if (tempList[i] == "<title>")
                tempList[i] = "<TitleText>";
            if (tempList[i] == "</title>")
                tempList[i] = "</TitleText>";
            if (tempList[i] == "<empty-line/>")
                tempList[i] = "<br/>";
            if (tempList[i] == "<subtitle>")
            {
                tempList[i] = "<p>";
                tempList.insert(++i, "<epigraph>");
            }
            if (tempList[i] == "</subtitle>")
            {
                tempList[i] = "</epigraph>";
                tempList.insert(++i, "</p>");
            }
        }
    }
    return tempList;
}

void FB2TextPaginator::parseBookText()
{
    QFile bookFile(book->File);
    if (bookFile.open(QIODevice::ReadOnly))
    {
        doc = new QTextStream(&bookFile);
        doc->setCodec(book->getBookCodec().toStdString().c_str());

        QString temp;

        do
            doc->operator >>(temp);
        while(temp.indexOf("<body>") == -1);
        temp = temp.remove(0, temp.indexOf("<body>") + 6);
        bookText.append(splitTextToWords(temp));

        bool flag = true;
        while(!doc->atEnd())
        {
            doc->operator >>(temp);
            if (temp.indexOf("<binary") != -1)
                flag = false;

            if (flag)
            {
                bookText.append(splitTextToWords(temp));
                strCount = bookText.size();
            }
            else
                bookText.append(temp);
        }

        bookText.back() = bookText.back().remove(bookText.back().indexOf("</FictionBook>"), bookText.back().size());

        bookFile.close();
    }
    else
    {
        qDebug()<<"невозможно открыть файл книги";
    }

    delete doc;
}


FB2TextPaginator::FB2TextPaginator()
{
    columnWidth = 0;
    columnHeight = 0;
    tableWidth = 0;

    pageBegin = 0;

    currentBStrNum = 0;
    currentTextPos = 0;
    currentEStrNum = 0;
    strCount = 0;

    currentColumn = 0;
    currentWordPos = 0;

    wordWidth = 0;
    wordHeight = 0;

    currentWidth = 0;
    currentHeight = 0;
    stringStep = 0;
    stringHeight = 0;

    tagType = false;
    parseDirection = false;
}



QString FB2TextPaginator::startParser(Book *OpeningBook, int Pwidth, int Pheight)
{
    book = OpeningBook;
    ProgramSettings = settings::getSettings();
    currentEStrNum = currentBStrNum = book->getBookProgress();
    currentTextPos = 0;


    tagStack.fromList(book->getBookProgressTagStack());
    if (tagStack.size() == 0)
        tagStack.push("Text");

    parseBookText();
    createTableOfContents();
    setHTMLinf();
    setFontMap();
    setLinespaceMap();
    setPageGeometry(Pwidth, Pheight);

    return getPageForward();
}

FB2TextPaginator::~FB2TextPaginator()
{
    foreach (auto FontMetricsPointer, fontMap) {
        delete FontMetricsPointer;
    }
}

void FB2TextPaginator::setFontMap()
{

    QFont textFont(CurStyle.RegularTextStyle.FontFamily, CurStyle.RegularTextStyle.FontSize, 49*(CurStyle.RegularTextStyle.FontStyle%2) + 50, CurStyle.RegularTextStyle.FontStyle/10);
    fontMap.insert("Text", new QFontMetrics(textFont));

    textFont.setWeight(75);
    fontMap.insert("strong", new QFontMetrics(textFont));

    QFont titleFont(CurStyle.TitleStyle.FontFamily, CurStyle.TitleStyle.FontSize, 49*(CurStyle.TitleStyle.FontStyle%2) + 50, CurStyle.TitleStyle.FontStyle/10);
    fontMap.insert("TitleText", new QFontMetrics(titleFont));

    QFont subtitleFont(CurStyle.SubtitleStyle.FontFamily, CurStyle.SubtitleStyle.FontSize, 49*(CurStyle.SubtitleStyle.FontStyle%2) + 50, CurStyle.SubtitleStyle.FontStyle/10);
    fontMap.insert("epigraph", new QFontMetrics(subtitleFont));

    QFont empFont(CurStyle.EmphasizedTextStyle.FontFamily, CurStyle.EmphasizedTextStyle.FontSize, 49*(CurStyle.EmphasizedTextStyle.FontStyle%2) + 50, CurStyle.EmphasizedTextStyle.FontStyle/10);
    fontMap.insert("emphasis", new QFontMetrics(empFont));

    QFont noteFont(CurStyle.NoteStyle.FontFamily, CurStyle.NoteStyle.FontSize, 49*(CurStyle.NoteStyle.FontStyle%2) + 50, CurStyle.NoteStyle.FontStyle/10);
    fontMap.insert("Note", new QFontMetrics(noteFont));
}

void FB2TextPaginator::setLinespaceMap()
{
    linespaceMap.insert("Text", CurStyle.RegularTextStyle.LineSpacing * fontMap["Text"]->lineSpacing());
    linespaceMap.insert("strong", CurStyle.RegularTextStyle.LineSpacing * fontMap["strong"]->lineSpacing());
    linespaceMap.insert("TitleText", CurStyle.TitleStyle.LineSpacing * fontMap["TitleText"]->lineSpacing());
    linespaceMap.insert("epigraph", CurStyle.SubtitleStyle.LineSpacing * fontMap["epigraph"]->lineSpacing());
    linespaceMap.insert("emphasis", CurStyle.EmphasizedTextStyle.LineSpacing * fontMap["emphasis"]->lineSpacing());
    linespaceMap.insert("Note", CurStyle.NoteStyle.LineSpacing * fontMap["Note"]->lineSpacing());
}

void FB2TextPaginator::setPageGeometry(int width, int height)
{
    columnWidth = (width - 10 - 30*(CurStyle.ColumnCount-1) - CurStyle.TextLeftRightIdent/100 - CurStyle.TextLeftRightIdent%100)/CurStyle.ColumnCount;
    tableWidth = columnWidth*CurStyle.ColumnCount + 10 + 30*(CurStyle.ColumnCount-1) + CurStyle.TextLeftRightIdent/100 + CurStyle.TextLeftRightIdent%100;
    columnHeight = height - 20 - CurStyle.TextTopBottomIdent/100 - CurStyle.TextTopBottomIdent%100;
}

void FB2TextPaginator::setHTMLinf()
{
    CurStyle = ProgramSettings->getCurrentTextStyleElem();

    QString fileName;
    if (CurStyle.BackgroundType == false)
        fileName = QUrl::fromLocalFile(CurStyle.BackgroundImage).toString();

    PageHTMLHeader = "<style type='text/css'>"
                     "p{"
                          "margin-top:" + QString::number(CurStyle.ParLeftTopIdent%100) + "px;"
                          "margin-bottom:0px;}"

                     "TitleText{"
                          "font-family:'" + CurStyle.TitleStyle.FontFamily + "';"
                          "font-size:" + QString::number(CurStyle.TitleStyle.FontSize) + "pt;"
                          "font-weight:" + ((CurStyle.TitleStyle.FontStyle%2)? QString("bold"):QString("normal")) + ";"
                          "line-height:" + QString::number(CurStyle.TitleStyle.LineSpacing*100) + "%;"
                          "font-style:" + ((CurStyle.TitleStyle.FontStyle/2 == 1)?QString("italic"):QString("normal")) + ";"
                          "text-align:" + ProgramSettings->getTextAlignName(CurStyle.TitleStyle.TextAlign) + ";"
                          "color:" + CurStyle.TitleStyle.TextColor + ";"
                          "text-indent:" + QString::number(CurStyle.ParLeftTopIdent/100) + "px;}"

                     "epigraph{"
                          "font-family:'" + CurStyle.SubtitleStyle.FontFamily + "';"
                          "font-size:" + QString::number(CurStyle.SubtitleStyle.FontSize) + "pt;"
                          "font-weight:" + ((CurStyle.SubtitleStyle.FontStyle%2)? QString("bold"):QString("normal")) + ";"
                          "line-height:" + QString::number(CurStyle.SubtitleStyle.LineSpacing*100) + "%;"
                          "font-style:" + ((CurStyle.SubtitleStyle.FontStyle/2 == 1)?QString("italic"):QString("normal")) + ";"
                          "text-align:" + ProgramSettings->getTextAlignName(CurStyle.SubtitleStyle.TextAlign) + ";"
                          "color:" + CurStyle.SubtitleStyle.TextColor + ";"
                          "text-indent:" + QString::number(CurStyle.ParLeftTopIdent/100) + "px;}"

                     "Text{"
                          "font-family:'" + CurStyle.RegularTextStyle.FontFamily + "';"
                          "font-size:" + QString::number(CurStyle.RegularTextStyle.FontSize) + "pt;"
                          "font-weight:" + ((CurStyle.RegularTextStyle.FontStyle%2)? QString("bold"):QString("normal")) + ";"
                          "line-height:" + QString::number(CurStyle.RegularTextStyle.LineSpacing*100) + "%;"
                          "font-style:" + ((CurStyle.RegularTextStyle.FontStyle/2 == 1)?QString("italic"):QString("normal")) + ";"
                          "text-align:" + ProgramSettings->getTextAlignName(CurStyle.RegularTextStyle.TextAlign) + ";"
                          "color:" + CurStyle.RegularTextStyle.TextColor + ";"
                          "text-indent:" + QString::number(CurStyle.ParLeftTopIdent/100) + "px;}"

                     "emphasis{"
                          "font-family:'" + CurStyle.EmphasizedTextStyle.FontFamily + "';"
                          "font-size:" + QString::number(CurStyle.EmphasizedTextStyle.FontSize) + "pt;"
                          "font-weight:" + ((CurStyle.EmphasizedTextStyle.FontStyle%2)? QString("bold"):QString("normal")) + ";"
                          "line-height:" + QString::number(CurStyle.EmphasizedTextStyle.LineSpacing*100) + "%;"
                          "font-style:" + ((CurStyle.EmphasizedTextStyle.FontStyle/2 == 1)?QString("italic"):QString("normal")) + ";"
                          "text-align:" + ProgramSettings->getTextAlignName(CurStyle.EmphasizedTextStyle.TextAlign) + ";"
                          "color:" + CurStyle.EmphasizedTextStyle.TextColor + ";"
                          "text-indent:" + QString::number(CurStyle.ParLeftTopIdent/100) + "px;}"

                     "Note{"
                          "font-family:'" + CurStyle.NoteStyle.FontFamily + "';"
                          "font-size:" + QString::number(CurStyle.NoteStyle.FontSize) + "pt;"
                          "font-weight:" + ((CurStyle.NoteStyle.FontStyle%2)? QString("bold"):QString("normal")) + ";"
                          "line-height:" + QString::number(CurStyle.NoteStyle.LineSpacing*100) + "%;"
                          "font-style:" + ((CurStyle.NoteStyle.FontStyle/2 == 1)?QString("italic"):QString("normal")) + ";"
                          "text-align:" + ProgramSettings->getTextAlignName(CurStyle.NoteStyle.TextAlign) + ";"
                          "color:" + CurStyle.NoteStyle.TextColor + ";"
                          "text-indent:" + QString::number(CurStyle.ParLeftTopIdent/100) + "px;}"

                     "strong > p{"
                          "font-weight:" + QString::number(99) + ";}"

                     "body{"
                          "background" + ((CurStyle.BackgroundType == true) ? ("-color:" + CurStyle.BackgroundImage) : ("-image:url(" + fileName + ")")) + ";}"
                  "</style>"
                  "<body>"
                  "<table border='0' style='"
                    "table-layout: fixed;"
                    "empty-cells: show;"
                    "margin-top: " + QString::number(CurStyle.TextTopBottomIdent/100) + "px;"
                    "margin-bottom: " + QString::number(CurStyle.TextTopBottomIdent%100) + "px;"
                    "margin-left:" + QString::number(CurStyle.TextLeftRightIdent/100) + "px;"
                    "margin-right:" + QString::number(CurStyle.TextLeftRightIdent%100) + "px;' "
                    "width='100%'"
                    " cellspacing='-30' cellpadding='30'>"
                  "<tr>"
                  "<td align = 'justify' width = '" + QString::number(100/CurStyle.ColumnCount) + "%'>"
                  "<Text>";

    PageHTMLSep = "</Text></td><td align = 'justify' width = '" + QString::number(100/CurStyle.ColumnCount) + "%'><Text>";
    PageHTMLBottom = "</Text></td></tr></table></body>";
}

void FB2TextPaginator::createTableOfContents()
{
    for (long long i = 0; i < strCount; i++)
        if (bookText[i] == "<section>")
        {
            if (bookText[++i] == "<TitleText>")
            {
                long long pos;
                QString text;
                for (pos = i + 1; pos < strCount && bookText[pos][0] == '<'; pos++);
                for (; pos < strCount && bookText[pos] != "</TitleText>"; pos++)
                    if (bookText[pos][0] != '<')
                        text += bookText[pos] + " ";
                TableOfContentsText.append(text);
                TableOfContentsIndexes.append(i);
                i = pos;
            }
        }
}

QStringList FB2TextPaginator::getBookContentTable()
{
    return TableOfContentsText;
}

long long FB2TextPaginator::getCurrentSectionIndex()
{
    int pos;
    for (pos = 1; pos < TableOfContentsIndexes.size() && currentBStrNum > TableOfContentsIndexes[pos]; ++pos);
    if (currentBStrNum > TableOfContentsIndexes.back())
        return TableOfContentsIndexes.size() - 1;
    return pos;
}

QString FB2TextPaginator::goToSection(int sectionIndex)
{
    currentTextPos = currentEStrNum = TableOfContentsIndexes[sectionIndex];
    tagStack.clear();
    tagStack.append("Text");
    parseDirection = false;
    return getPageForward();
}


int FB2TextPaginator::getWordHeight()
{
    for (int i = tagStack.size() - 1; i > 0; i--)
        if (linespaceMap.contains(tagStack[i]))
            return linespaceMap[tagStack[i]];
    return linespaceMap[tagStack[0]];
}

int FB2TextPaginator::getWordWidth(QString word)
{
    for (int i = tagStack.size() - 1; i > 0; i--)
        if (fontMap.contains(tagStack[i]))
            return fontMap[tagStack[i]]->width(word);
    return fontMap[tagStack[0]]->width(word);
}

int FB2TextPaginator::getSpaceWidth()
{
    for (int i = tagStack.size() - 1; i > 0; i--)
        if (fontMap.contains(tagStack[i]))
            return fontMap[tagStack[i]]->charWidth(" ", 0);
    return fontMap[tagStack[0]]->charWidth(" ", 0);
}


void FB2TextPaginator::findTagsTale()
{
    bool realParseDirection = parseDirection;
    int parseResalt = 1;
    parseDirection = true;

    do
    {
        if (parseResalt == 1)
            applyTag();

        if (realParseDirection)
            Columns[currentColumn].prepend(bookText[currentTextPos]);
        else
            Columns[currentColumn].remove(Columns[currentColumn].lastIndexOf(bookText[currentTextPos]), bookText[currentTextPos].size());

        if (bookText[currentTextPos-1][0] == '<')
        {
            tag = bookText[--currentTextPos];
            parseResalt = parseTag();
            if (tagType == true && parseResalt != 2)
                break;
        }
        else
            break;
    }
    while(currentTextPos > 0);
    currentTextPos++;
    parseDirection = realParseDirection;
}


// 1 - нужный тег, 0 - бесполезный тег, 2 - лишний тег, 3 - тег перевода колонки
int FB2TextPaginator::parseTag()
{
    tag = tag.mid(1, tag.size()-2);
    if (tag[0] == '/')
    {
        tag  = tag.remove(0, 1);
        tagType = true;
    }
    else
        tagType = false;
    if (tag == "p /")
        return 0;
    if (tag == "p")
    {
        if (tagType == parseDirection)
        {
            if (currentHeight + stringHeight + (CurStyle.ParLeftTopIdent%100)*((int)!parseDirection) > columnHeight)
            {
                findTagsTale();
                return 3;
            }
        }
        else
        {
            if (!parseDirection)
                currentWidth = CurStyle.ParLeftTopIdent/100;
            else
                currentWidth = 0;

            currentHeight += stringHeight + CurStyle.ParLeftTopIdent%100;
            stringHeight = 0;
        }
        return 1;
    }

    if (tag == "section" && tagType == parseDirection)
    {
        currentTextPos += (parseDirection)?-1:1;
        return 3;
    }

    if (tag.mid(0,2) == "a " || (tag == "a" && tagType == parseDirection))
    {
        return 2;
    }

    if (tag.mid(0,5) == "image")
    {
        return 2;
    }

    if (tag == "br/")
    {
        tagType = true;
        if (currentHeight == 0)
            return 2;

        if (currentHeight + getWordHeight() + CurStyle.ParLeftTopIdent%100 > columnHeight)
            return 2;

        currentHeight += getWordHeight() + CurStyle.ParLeftTopIdent%100;

        if (parseDirection)
            Columns[currentColumn].prepend("<p>&nbsp;</p>");
        else
            Columns[currentColumn] += "<p>&nbsp;</p>";

        stringHeight = 0;
        return 2;
    }

    if (tag == "epigraph" || tag == "TitleText" || tag == "subtitle" || tag == "emphasis" || tag == "Note" || tag == "strong")
        return 1;

    return 2;
}

void FB2TextPaginator::applyTag()
{
    if (tag != "")
    {
        if (tagStack.back() == tag)
        {
            if (tagType == !parseDirection)
            {
                word = "";
                tagStack.pop();
            }
        }
        else if (tagType == parseDirection)
        {
            tagStack.push(tag);
        }
    }
}

bool FB2TextPaginator::applyWord()
{
    if (word != "")
    {
        wordHeight = getWordHeight();
        if (wordHeight > stringHeight)
        {
            stringHeight = wordHeight;
            if (currentHeight + stringHeight > columnHeight)
            {
                //перенос на сл колонку
                //отрезать stringWordCount слов от колонки
                if (parseDirection)
                    currentTextPos++;
                else
                    currentTextPos--;
                return false;
            }
        }

        wordWidth = getWordWidth(word);

        if (currentWidth + wordWidth + getSpaceWidth() > columnWidth)
        {
            if (currentWidth + wordWidth > columnWidth)
            {
                if (currentHeight + stringHeight + wordHeight  > columnHeight)
                {
                    //переносим колонку
                    return false;
                }
                else
                {
                    //переносим строку
                    currentHeight += stringHeight;
                    currentWidth = wordWidth;

                    if (word.right(1) != "-")
                        currentWidth += getSpaceWidth();
                }
            }
            else
                currentWidth += wordWidth;
        }
        else
            currentWidth += wordWidth + getSpaceWidth();
    }
    return true;
}


QString FB2TextPaginator::getPageForward()
{
    if (currentTextPos < strCount)
    {
        if (!parseDirection)
            beginTagStack = tagStack;
        else
            tagStack = beginTagStack;

        parseDirection = false;

        Columns.clear();
        currentTextPos = currentBStrNum = currentEStrNum;
        book->setBookProgress(currentBStrNum, getProgress(), tagStack.toList());
        wordWidth = wordHeight = 0;
        tagType = 0;

        for (currentColumn = 0; currentColumn < CurStyle.ColumnCount; currentColumn++)
        {
            columnTale = "";
            for (int p = 1; p < tagStack.size(); p++)
                columnTale += "<" + tagStack[p] + ">";
            Columns.append(columnTale);

            currentHeight = currentWidth = 0;
            stringHeight = 0;
            for (; currentTextPos < strCount && currentTextPos < bookText.size(); currentTextPos++)
            {
                if (bookText[currentTextPos].size())
                {
                    if (bookText[currentTextPos][0] == '<')
                    {
                        tag = bookText[currentTextPos];
                        int parseResalt = parseTag();
                        if (parseResalt == 1)
                            applyTag();
                        else
                            if (parseResalt == 2)
                                continue;

                        /// отработать переход секции

                        else
                            if (parseResalt == 3)
                                break;
                    }
                    else
                    {
                        word = bookText[currentTextPos];
                        if (!applyWord())
                            break;
                    }
                }
                Columns[currentColumn] += bookText[currentTextPos];
                if (bookText[currentTextPos].right(1) != "-")
                    Columns[currentColumn] += " ";
            }

            for (int p = tagStack.size() - 1; p > 0; p--)
                Columns[currentColumn] += "</" + tagStack[p] + ">";
            currentEStrNum = currentTextPos;
        }
        HTMLPage = Columns[0];
        for (int i = 1; i < CurStyle.ColumnCount; i++)
            HTMLPage += PageHTMLSep + Columns[i];
        //debugSave(PageHTMLHeader + HTMLPage + PageHTMLBottom);
    }
    return PageHTMLHeader + HTMLPage + PageHTMLBottom;
}


QString FB2TextPaginator::getPageBackward()
{
    if (currentBStrNum > 0)
    {
        if (parseDirection)
            beginTagStack = tagStack;
        else
            tagStack = beginTagStack;

        parseDirection = true;
        Columns.clear();

        currentEStrNum = currentBStrNum;
        currentTextPos = currentBStrNum - 1;

        wordWidth = wordHeight = 0;
        tagType = 0;

        for (currentColumn = 0; currentColumn < CurStyle.ColumnCount; currentColumn++)
        {
            columnTale = "";
            for (int p = tagStack.size() - 1; p > 0 ; p--)
                columnTale += "</" + tagStack[p] + ">";
            Columns.append(columnTale);

            currentHeight = 0;
            currentWidth = 0;
            stringHeight = 0;

            for (; currentTextPos >= 0; currentTextPos--)
            {
                if (bookText[currentTextPos][0] == '<')
                {
                    tag = bookText[currentTextPos];
                    int parseResalt = parseTag();
                    if (parseResalt == 1)
                        applyTag();
                    else
                        if (parseResalt == 2)
                            continue;

                    /// отработать переход секции
                    else
                        if (parseResalt == 3)
                            break;
                }
                else
                {
                    word = bookText[currentTextPos];
                    if (!applyWord())
                        break;
                }

                if (bookText[currentTextPos].right(1) != "-")
                    Columns[currentColumn].prepend(" ");
                Columns[currentColumn].prepend(bookText[currentTextPos]);
            }

            for (int p = tagStack.size() - 1; p > 0; p--)
                Columns[currentColumn].prepend( "<" + tagStack[p] + ">");
        }
        currentBStrNum = currentTextPos + 1;

        book->setBookProgress(currentBStrNum,getProgress(), tagStack.toList());

        HTMLPage = Columns[CurStyle.ColumnCount - 1];
        for (int i = CurStyle.ColumnCount - 2; i >= 0; i--)
            HTMLPage += PageHTMLSep + Columns[i];

    }

    return PageHTMLHeader + HTMLPage + PageHTMLBottom;
}


QString FB2TextPaginator::updatePage(const int width, const int height)
{
    setPageGeometry(width, height);
    currentEStrNum = currentBStrNum;
    tagStack = beginTagStack;
    return getPageForward();
}

QString FB2TextPaginator::updateSettings(const int width, const int height)
{
    setPageGeometry(width, height);
    setHTMLinf();
    setFontMap();
    setLinespaceMap();
    currentEStrNum = currentBStrNum;
    tagStack = beginTagStack;
    return getPageForward();
}

float FB2TextPaginator::getProgress()
{
    if (currentBStrNum > 0 && strCount)
        return (((float)currentEStrNum/(float)strCount) * 100);
    else
        return 0;
}

void FB2TextPaginator::debugSave(QString HTMLPage)
{
    QFile asd("F:/asd.html");
    asd.open(QIODevice::WriteOnly);
    QTextStream out(&asd);
    out<<PageHTMLHeader + HTMLPage + PageHTMLBottom;
    asd.close();
}

#include "fb2textparser.h"
#include <QFont>
#include <QFile>
#include <QDebug>
#include <QUrl>
#include <QString>
#include <QFontMetrics>


FB2TextParser::FB2TextParser(Book boo, settings* PSettings, int width, int height)
{
    book = boo;
    ProgramSettings = PSettings;
    currentEStrNum = currentBStrNum = book.getBookProgress();
    currentTextPos = 0;
    tagStack.push("Text");

    parseBookText();
    setHTMLinf();
    setFontMap();
    setLinespaceMap();
    setPageGeometry(width, height);
}

FB2TextParser::~FB2TextParser()
{
    delete ProgramSettings;
    //очистить мапу шрифтов
}

void FB2TextParser::setFontMap()
{

    QFont textFont(CurStyle.RegularTextStyle.FontFamily, CurStyle.RegularTextStyle.FontSize, 49*(CurStyle.RegularTextStyle.FontStyle%2) + 50, 0);// CurStyle.RegularTextStyle.FontStyle/10);
    fontMap.insert("Text", new QFontMetrics(textFont));

    textFont.setWeight(75);
    fontMap.insert("strong", new QFontMetrics(textFont));

    QFont titleFont(CurStyle.TitleStyle.FontFamily, CurStyle.TitleStyle.FontSize, 49*(CurStyle.TitleStyle.FontStyle%2) + 50, 0);//CurStyle.TitleStyle.FontStyle/10);
    fontMap.insert("TitleText", new QFontMetrics(titleFont));

    QFont subtitleFont(CurStyle.SubtitleStyle.FontFamily, CurStyle.SubtitleStyle.FontSize, 49*(CurStyle.SubtitleStyle.FontStyle%2) + 50, 0);//CurStyle.SubtitleStyle.FontStyle/10);
    fontMap.insert("epigraph", new QFontMetrics(subtitleFont));

    QFont empFont(CurStyle.EmphasizedTextStyle.FontFamily, CurStyle.EmphasizedTextStyle.FontSize, 49*(CurStyle.EmphasizedTextStyle.FontStyle%2) + 50, 0);//CurStyle.EmphasizedTextStyle.FontStyle/10);
    fontMap.insert("emphasis", new QFontMetrics(empFont));

    QFont noteFont(CurStyle.NoteStyle.FontFamily, CurStyle.NoteStyle.FontSize, 49*(CurStyle.NoteStyle.FontStyle%2) + 50, 0);//CurStyle.NoteStyle.FontStyle/10);
    fontMap.insert("Note", new QFontMetrics(noteFont));
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
    qDebug()<<width;
    pageWidth = (width - 10 - 30*(CurStyle.ColumnCount-1) - CurStyle.TextLeftRightIdent/100 - CurStyle.TextLeftRightIdent%100)/CurStyle.ColumnCount;
    qDebug()<<"LR"<<CurStyle.TextLeftRightIdent;

    pageHeight = height - CurStyle.TextTopBottomIdent/100 - CurStyle.TextTopBottomIdent%100;
    qDebug()<<pageWidth<<pageHeight;
}

void FB2TextParser::setHTMLinf()
{
    CurStyle = ProgramSettings->getCurrentTextStyleElem();
    qDebug()<<CurStyle.TextLeftRightIdent;

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
                          "line-height:" + QString::number(CurStyle.TitleStyle.LineSpacing*100) + ";"
                          "font-style:" + ((CurStyle.TitleStyle.FontStyle/2 == 1)?QString("italic"):QString("normal")) + ";"
                          "text-align:" + CurStyle.TitleStyle.TextAlign.toLower() + ";"
                          "color:" + CurStyle.TitleStyle.TextColor + ";"
                          "text-indent:" + QString::number(CurStyle.ParLeftTopIdent/100) + "px;}"

                     "epigraph, subtitle{"
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
                    "width='100%' cellspacing='-30' cellpadding='30'>"
                  "<tr>"
                  "<td align = 'justify' width = '" + QString::number(100/CurStyle.ColumnCount) + "%'>"
                  "<Text>";

    PageHTMLSep = "</Text></td><td align = 'justify' width = '" + QString::number(100/CurStyle.ColumnCount) + "%'><Text>";
    PageHTMLBottom = "</Text></td></tr></table></body>";

}

QStringList FB2TextParser::splitTextToWords(QString temp)
{
    QStringList tempList;
    tempList.append(temp);
    if (temp == "978-5-17-095334-9</p>")
    {
        temp == "978-5-17-095334-9</p>";
    }
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
                QStringList newTemp = temp.split("-");
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
                tempList[i] = " ";
        }
    }
    return tempList;
}

void FB2TextParser::parseBookText()
{
    QFile bookFile(book.File);
    if (bookFile.open(QIODevice::ReadOnly))
    {

        doc = new QTextStream(&bookFile);
        doc->setCodec(book.getBookCodec().toStdString().c_str());
        qDebug()<<"start parse";

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
    for (int i = 0; i < strCount / 4; i++)
        qDebug()<<bookText[i];

    qDebug()<<"strCount: "<<strCount;
}

int FB2TextParser::getWordHeight()
{
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
        if (fontMap.contains(tagStack[i]))
            return fontMap[tagStack[i]]->charWidth(" ", 0);
    return fontMap[tagStack[0]]->charWidth(" ", 0);
}

void FB2TextParser::extractTag(QString tagBeg, QString tagEnd)
{
    qDebug()<<"_________________________________delete tag________________________________";
    qDebug()<<bookText[currentTextPos];
    bookText[currentTextPos].remove(bookText[currentTextPos].size() - tagBeg.size(), bookText[currentTextPos].size());
    qDebug()<<bookText[currentTextPos];

    int strEndTag = currentTextPos+1;
    int posEndTag = bookText[strEndTag].indexOf(">");
    int wasDelete = 0;
    while (posEndTag == -1 && strEndTag < bookText.size())
    {
        bookText.removeAt(strEndTag);
        wasDelete++;
        posEndTag = bookText[strEndTag].indexOf(">");
    }

    for (int j = currentTextPos; j <= strEndTag; j++)
        qDebug()<<bookText[j];

    if (bookText[strEndTag][posEndTag - 1] == '/')
        bookText[strEndTag].remove(0, posEndTag + 1);
    else
    {
        bookText[strEndTag].remove(0, posEndTag + 1);
        for (; bookText[strEndTag].indexOf(tagEnd) == -1; strEndTag++);
        posEndTag = bookText[strEndTag].indexOf(tagEnd);
        bookText[strEndTag].remove(posEndTag - 1, tagEnd.size()+1);
    }

    if (parseDirection)
    {
        currentTextPos -= wasDelete;
        currentWordPos = posEndTag;
    }

    qDebug()<<"_________________________________delete tag end________________________________";
}

void FB2TextParser::takeTag()
{
    tag = "";
    if (!parseDirection)
    {
        for (currentWordPos = currentWordPos + 1; currentWordPos < bookText[currentTextPos].size() && bookText[currentTextPos][currentWordPos] != '>'; currentWordPos++)
            tag += bookText[currentTextPos][currentWordPos];

        if (bookText[currentTextPos][currentWordPos] != '>' && tag == "p" && bookText[currentTextPos+1][0] == '/')
            tag = "";
    }
    else
    {
        for (currentWordPos = currentWordPos - 1; currentWordPos >= 0 && bookText[currentTextPos][currentWordPos] != '<'; currentWordPos--)
            tag += bookText[currentTextPos][currentWordPos];

        if (tag == "/a")
        {
            for (--currentTextPos; currentTextPos >= 0; currentTextPos--)
                for (currentWordPos = bookText[currentTextPos].size() - 1; currentWordPos >= 0; currentWordPos--)
                    if (bookText[currentTextPos][currentWordPos] == '<')
                        break;
            tag = "a";
            tagType = 0;
            return;
        }


        if (tag == "/")
        {
            for (--currentTextPos; currentTextPos >= 0; currentTextPos--)
                for (currentWordPos = bookText[currentTextPos].size() - 1; currentWordPos >= 0; currentWordPos--)
                    if (bookText[currentTextPos][currentWordPos] == '<')
                        break;
            tag = "";
            for (int i = currentWordPos; i < bookText[currentTextPos].size(); i++)
                tag+=bookText[currentTextPos][i];
            if (tag == "image")
                tagType = 0;
            else
                tag = "";
            return;
        }

    }

    int pos = tag.indexOf("/");
    if (pos != -1)
    {
        tag  = tag.remove(pos, pos+1);
        tagType = !parseDirection;
    }
    else
        tagType = parseDirection;
}


bool FB2TextParser::parseTag()
{
    takeTag();

    if (tag == "p")
    {
        if (tagType == parseDirection)
        {
            currentHeight += stringHeight + CurStyle.ParLeftTopIdent%100;
            stringHeight = 0;
            currentWidth = CurStyle.ParLeftTopIdent/100 + 1;
        }
        else if (currentHeight + stringHeight + getWordHeight() + CurStyle.ParLeftTopIdent%100 > pageHeight)
        {
            bookText.insert(currentTextPos+1, bookText[currentTextPos].right(bookText[currentTextPos].size() - currentWordPos - 1));
            bookText[currentTextPos]=bookText[currentTextPos].left(currentWordPos+1);
        }
        return false;
    }

    if (tag == "section")
    {
        if (tagType == !parseDirection)
        {
            //надо закрыть главу
        }
        return true;
    }

    if (tag == "a")
    {
        extractTag("<a", "/a>");
        if (!parseDirection)
        {
            Columns[currentColumn] += bookText[currentTextPos++] + " ";
            currentWordPos = -1;
        }
        return true;

    }

    if (tag == "image")
    {
        extractTag("<image", "/>");
        if (!parseDirection)
        {
            Columns[currentColumn] += bookText[currentTextPos++] + " ";
            currentWordPos = -1;
        }
        return true;
    }

    if (tag == "br")
    {
        qDebug()<<"<br>"<<currentHeight<<getWordHeight()<<CurStyle.ParLeftTopIdent%100;
        currentHeight += getWordHeight() + stringHeight + CurStyle.ParLeftTopIdent%100;
        stringHeight = 0;
        return true;
    }

    if (tag == "subtitle")
        tag = "epigraph";

    return false;
}

void FB2TextParser::applyTag()
{
    if (tag != "body" && tag != "")
    {
        if (tagStack.back() == tag && tagType == !parseDirection)
        {
            word = "";
            tagStack.pop();
            qDebug()<<tagStack;
        }
        else if (tagType == parseDirection)
        {
            tagStack.push(tag);
            qDebug()<<tagStack;
        }
    }
}

bool FB2TextParser::applyWord()
{
    if (word != "")
    {
        wordHeight = getWordHeight();
        if (wordHeight > stringHeight)
        {
            stringHeight = wordHeight;
            if (currentHeight + stringHeight > pageHeight)
            {
                //перенос на сл колонку
                //отрезать stringWordCount слов от колонки
                qDebug()<<"<------- Yepe, it's column ------->";

                /*
                if (tagType == 1)
                    while ((currentTextPos < strCount) && tagType == false)
                    {
                        for (currentWordPos; currentWordPos < bookText[currentTextPos].size(); currentWordPos++)
                            if (bookText[currentTextPos][currentWordPos] == '<')
                            {
                                forwardParseTag();
                                if (tagType == true)
                                    applyTag();
                                else
                                {
                                    currentWordPos -= tag.size() + 2;
                                    bookText.insert(currentTextPos+1, bookText[currentTextPos].right(bookText[currentTextPos].size() - currentWordPos - 1));
                                    bookText[currentTextPos] = bookText[currentTextPos].left(currentWordPos+1);
                                    qDebug()<<bookText[currentTextPos]<<bookText[currentTextPos+1];
                                    currentTextPos++;
                                    break;
                                }
                            }
                        Columns[currentColumn] += bookText[currentTextPos] + " ";
                        currentTextPos++;
                    }
                    */

                return false;
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
                    qDebug()<<"<------- Yepe, it's column №1 ------->";
                    qDebug()<<tagStack;
                    return false;
                }
                else
                {
                    //переносим строку
                    qDebug()<<"Yepe, it's line №1 ->>>>>"<< currentHeight<<stringHeight;
                    currentHeight += stringHeight;
                    currentWidth = wordWidth;
                    if (stringStep != 0)
                    {
                        currentWidth += stringStep;
                        stringStep = 0;
                    }

                    if (word[word.size()-1] != '-')
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


QString FB2TextParser::getPageForward()
{
    if (currentTextPos < strCount)
    {
        parseDirection = false;
        beginTagStack = tagStack;
        Columns.clear();
        currentTextPos = currentBStrNum = currentEStrNum;
        book.setBookProgress(currentBStrNum);
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
            stringStep = 0;

            bool flag = 1;
            for (; currentTextPos < strCount; currentTextPos++)
            {
                word = "";
                for (currentWordPos = 0; currentWordPos < bookText[currentTextPos].size(); currentWordPos++)
                {
                    if (bookText[currentTextPos][currentWordPos] == '<')
                    {
                        //посчитать размер для уже считанного
                        flag = applyWord();
                        if (flag == false)
                            break;

                        if (!parseTag())
                            applyTag();
                    }
                    else
                    {
                        word += bookText[currentTextPos][currentWordPos];
                    }
                }
                if (flag == false)
                    break;

                //посчитать размер для считанного
                if (applyWord() == false)
                    break;

                if (bookText[currentTextPos].size() != 0)
                {
                    Columns[currentColumn] += bookText[currentTextPos];
                    if (bookText[currentTextPos][bookText[currentTextPos].size() - 1] != '-')
                        Columns[currentColumn] += " ";
                }
            }

            for (int p = tagStack.size() - 1; p > 0; p--)
                Columns[currentColumn] += "</" + tagStack[p] + ">";
        }
        currentEStrNum = currentTextPos;
    }

    QString HTMLPage = Columns[0];
    for (int i = 1; i < CurStyle.ColumnCount; ++i)
        HTMLPage += PageHTMLSep + Columns[i];

    //debugSave();
    qDebug()<<currentBStrNum<<currentEStrNum;

    return PageHTMLHeader + HTMLPage + PageHTMLBottom;
}

QString FB2TextParser::getPageBackward()
{
    int wtf = 0;
    if (currentTextPos > 0)
    {
        parseDirection = true;
        tagStack = beginTagStack;
        Columns.clear();
        currentTextPos = currentEStrNum = currentBStrNum - 1;
        book.setBookProgress(currentBStrNum);
        wordWidth = wordHeight = 0;
        tagType = 0;

        for (int i = 0; i < CurStyle.ColumnCount; i++)
            Columns.append(" ");
        qDebug()<<Columns.size();
        qDebug()<<"wtf"<<wtf++;

        for (currentColumn = CurStyle.ColumnCount - 1; currentColumn >= 0; currentColumn--)
        {
            qDebug()<<"wtf"<<wtf++;
            columnTale = "";
            for (int p = tagStack.size() - 1; p >= 1; p--)
                columnTale += "</" + tagStack[p] + ">";
            Columns[currentColumn] = columnTale;
            qDebug()<<"wtf"<<wtf++;

            currentHeight = currentWidth = 0;
            stringHeight = 0;
            stringStep = 0;

            bool flag = 1;
            qDebug()<<"wtf"<<wtf++;

            for (currentTextPos; currentTextPos >= 0; currentTextPos--)
            {
                qDebug()<<"wtf"<<"a"<<wtf++;
                word = "";
                for (currentWordPos = bookText[currentTextPos].size() - 1; currentWordPos >= 0; currentWordPos--)
                {
                    if (bookText[currentTextPos][currentWordPos] == '>')
                    {
                        //посчитать размер для уже считанного
                        flag = applyWord();
                        if (flag == false)
                            break;

                        if (!parseTag())
                            applyTag();
                    }
                    else
                    {
                        word = word.prepend(bookText[currentTextPos][currentWordPos]);
                    }
                }
                if (flag == false)
                    break;

                //посчитать размер для считанного
                if (applyWord() == false)
                    break;
                qDebug()<<"wtf"<<"aa"<<wtf++;
                qDebug()<<

                Columns[currentColumn].prepend(bookText[currentTextPos]);
                if (currentTextPos)
                    if (bookText[currentTextPos-1].size())
                        if (bookText[currentTextPos-1][bookText[currentTextPos].size() - 1] != '-')
                            Columns[currentColumn] = Columns[currentColumn].prepend(" ");

            }

            qDebug()<<"wtf"<<"b"<<wtf++;
            for (int p = 1; p < tagStack.size(); p++)
                Columns[currentColumn] += "<" + tagStack[p] + ">";
        }
        qDebug()<<"wtf"<<"c"<<wtf++;
        currentEStrNum = currentTextPos;
    }

    QString HTMLPage = Columns[0];
    for (int i = 1; i < CurStyle.ColumnCount; ++i)
        HTMLPage += PageHTMLSep + Columns[i];

    debugSave(HTMLPage);

    return PageHTMLHeader + HTMLPage + PageHTMLBottom;
}


QString FB2TextParser::updatePage(const int width, const int height)
{
    setPageGeometry(width, height);
    currentEStrNum = currentBStrNum;
    tagStack = beginTagStack;
    return getPageForward();
}

QString FB2TextParser::updateSettings()
{
    setHTMLinf();
    setFontMap();
    setLinespaceMap();
    currentEStrNum = currentBStrNum;
    tagStack = beginTagStack;
    return getPageForward();
}

float FB2TextParser::getProgress()
{
    if (currentBStrNum && strCount)
        return (((float)currentBStrNum/(float)strCount) * 100);
    else
        return 0;
}

void FB2TextParser::debugSave(QString HTMLPage)
{
    QFile asd("F:/asd.html");
    asd.open(QIODevice::WriteOnly);
    QTextStream out(&asd);
    out<<PageHTMLHeader + HTMLPage + PageHTMLBottom;
    asd.close();
}
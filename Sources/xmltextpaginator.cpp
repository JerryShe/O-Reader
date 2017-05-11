#include "xmltextpaginator.h"

#include <QFont>
#include <QFile>
#include <QDebug>
#include <QUrl>
#include <QString>
#include <QFontMetrics>
#include <QThread>

#include "xmltextparser.h"


XMLTextPaginator::XMLTextPaginator()
{
    ProgramSettings = Settings::getSettings();

    columnWidth = columnHeight = 0;

    currentBStrNum = currentTextPos = currentEStrNum = 0;
    strCount = 0;

    currentColumn = 0;
    lastLineSize = 0;

    tagsLineCount = 0;

    wordWidth = wordHeight = 0;

    currentWidth = currentHeight = 0;

    stringHeight = 0;

    tagType = false;
    parseDirection = false;

    beginParagrafTail = ParagrafTail = false;
}



QString XMLTextPaginator::startParser(Book *OpeningBook, const int &Pwidth, const int &Pheight)
{
    book = OpeningBook;

    currentEStrNum = currentBStrNum = book->getBookProgress();
    currentTextPos = 0;
    HTMLImageSize = 0;

    Columns.clear();
    for (int i = 0; i < CurProfile.ColumnCount; i++)
        Columns.append(QStringList());


    tagStack.fromList(book->getBookProgressTagStack());
    if (tagStack.size() == 0)
        tagStack.push("Text");

    setHTMLinf();
    setFontMap();
    setLinespaceMap();

    setPageGeometry(Pwidth, Pheight);

    Resolver = new TagsResolver(this, book->getFormat());

    XMLTextParser parser(book);

    bookText = parser.getText();
    TableOfContentsIndexes = parser.getTableOfContentsIndexes();
    TableOfContentsText = parser.getTableOfContentsText();
    ImageTable = parser.getImageTable();

    strCount = bookText.size();

    QFile asd("F:/all.txt");
    asd.open(QIODevice::WriteOnly);
    QTextStream out(&asd);
    for (int i = 0; i < strCount; i++)
        out<<i<<"   "<<bookText[i]<<'\n';
    asd.close();

    return getPageForward();
}


XMLTextPaginator::~XMLTextPaginator()
{
    foreach (auto FontMetricsPointer, fontMap) {
        delete FontMetricsPointer;
    }

    delete ImageTable;
}


void XMLTextPaginator::setFontMap()
{

    QFont textFont(CurProfile.RegularStyle.Family, CurProfile.RegularStyle.Size, 49*(CurProfile.RegularStyle.Style%2) + 50, CurProfile.RegularStyle.Style/10);
    fontMap.insert("Text", new QFontMetrics(textFont));

    textFont.setWeight(75);
    fontMap.insert("strong", new QFontMetrics(textFont));

    QFont titleFont(CurProfile.TitleStyle.Family, CurProfile.TitleStyle.Size, 49*(CurProfile.TitleStyle.Style%2) + 50, CurProfile.TitleStyle.Style/10);
    fontMap.insert("TitleText", new QFontMetrics(titleFont));

    QFont epigraphFont(CurProfile.EpigraphStyle.Family, CurProfile.EpigraphStyle.Size, 49*(CurProfile.EpigraphStyle.Style%2) + 50, CurProfile.EpigraphStyle.Style/10);
    fontMap.insert("epigraph", new QFontMetrics(epigraphFont));

    QFont empFont(CurProfile.EmphasizedStyle.Family, CurProfile.EmphasizedStyle.Size, 49*(CurProfile.EmphasizedStyle.Style%2) + 50, CurProfile.EmphasizedStyle.Style/10);
    fontMap.insert("emphasis", new QFontMetrics(empFont));

    QFont noteFont(CurProfile.NoteStyle.Family, CurProfile.NoteStyle.Size, 49*(CurProfile.NoteStyle.Style%2) + 50, CurProfile.NoteStyle.Style/10);
    fontMap.insert("Note", new QFontMetrics(noteFont));

    QFont subtitleFont(CurProfile.SubtitleStyle.Family, CurProfile.SubtitleStyle.Size, 49*(CurProfile.SubtitleStyle.Style%2) + 50, CurProfile.SubtitleStyle.Style/10);
    fontMap.insert("subtitle", new QFontMetrics(subtitleFont));

    QFont poemFont(CurProfile.PoemStyle.Family, CurProfile.PoemStyle.Size, 49*(CurProfile.PoemStyle.Style%2) + 50, CurProfile.PoemStyle.Style/10);
    fontMap.insert("poem", new QFontMetrics(poemFont));

    QFont citeFont(CurProfile.CiteStyle.Family, CurProfile.CiteStyle.Size, 49*(CurProfile.CiteStyle.Style%2) + 50, CurProfile.CiteStyle.Style/10);
    fontMap.insert("cite", new QFontMetrics(citeFont));
}


void XMLTextPaginator::setLinespaceMap()
{
    linespaceMap.insert("Text", CurProfile.RegularStyle.LineSpacing * fontMap["Text"]->lineSpacing());
    linespaceMap.insert("strong", CurProfile.RegularStyle.LineSpacing * fontMap["strong"]->lineSpacing());
    linespaceMap.insert("TitleText", CurProfile.TitleStyle.LineSpacing * fontMap["TitleText"]->lineSpacing());
    linespaceMap.insert("epigraph", CurProfile.EpigraphStyle.LineSpacing * fontMap["epigraph"]->lineSpacing());
    linespaceMap.insert("emphasis", CurProfile.EmphasizedStyle.LineSpacing * fontMap["emphasis"]->lineSpacing());
    linespaceMap.insert("Note", CurProfile.NoteStyle.LineSpacing * fontMap["Note"]->lineSpacing());
    linespaceMap.insert("cite", CurProfile.CiteStyle.LineSpacing * fontMap["cite"]->lineSpacing());
    linespaceMap.insert("poem", CurProfile.PoemStyle.LineSpacing * fontMap["poem"]->lineSpacing());
    linespaceMap.insert("subtitle", CurProfile.SubtitleStyle.LineSpacing * fontMap["subtitle"]->lineSpacing());
}


void XMLTextPaginator::setPageGeometry(const int &width, const int &height)
{
    columnWidth = (width - 10 - 30*(CurProfile.ColumnCount-1) - CurProfile.TextLeftRightIdent/100 - CurProfile.TextLeftRightIdent%100)/CurProfile.ColumnCount;
    columnHeight = height - 20 - CurProfile.TextTopBottomIdent/100 - CurProfile.TextTopBottomIdent%100;
}


void XMLTextPaginator::setHTMLinf()
{
    CurProfile = ProgramSettings->getCurrentReadProfileElem();
    QString topMargin = "margin-top:" + QString::number(CurProfile.ParLeftTopIdent%100) + "px;";

    PageHTMLHeader = "<style type='text/css'>"
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

                     "Note{"
                           + topMargin + CurProfile.NoteStyle.getHTMLStyle() + ";}"

                     "strong{"
                          + topMargin + "font-weight:" + QString::number(99) + ";}"

                      + ((CurProfile.BackgroundType == true) ? ("body{background-color:" + CurProfile.BackgroundImage + ";}") : ("")) +
                  "</style>"
                  "<body>"
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


QStringList XMLTextPaginator::getBookContentTable()
{
    return TableOfContentsText;
}


long long XMLTextPaginator::getCurrentSectionIndex()
{
    int pos;
    for (pos = 1; pos < TableOfContentsIndexes.size() && currentBStrNum > TableOfContentsIndexes[pos]; ++pos);
    if (currentBStrNum > TableOfContentsIndexes.back())
        return TableOfContentsIndexes.size() - 1;
    return pos;
}


QString XMLTextPaginator::goToSection(const int &sectionIndex)
{
    currentTextPos = currentEStrNum = TableOfContentsIndexes[sectionIndex];
    tagStack.clear();
    tagStack.append("Text");
    parseDirection = false;
    return getPageForward();
}


int XMLTextPaginator::getWordHeight()
{
    for (int i = tagStack.size() - 1; i > 0; i--)
        if (linespaceMap.contains(tagStack[i]))
            return linespaceMap[tagStack[i]];

    return linespaceMap[tagStack[0]];
}


int XMLTextPaginator::getWordHeightFor(QString name)
{
    if (linespaceMap.contains(name))
        return linespaceMap[name];
    if (name == "p")
        return linespaceMap["Text"];

    return -1;
}


int XMLTextPaginator::getWordWidth(const QString &word)
{
    for (int i = tagStack.size() - 1; i > 0; i--)
        if (fontMap.contains(tagStack[i]))
            return fontMap[tagStack[i]]->width(word);

    return fontMap[tagStack[0]]->width(word);
}


int XMLTextPaginator::getSpaceWidth()
{
    for (int i = tagStack.size() - 1; i > 0; i--)
        if (fontMap.contains(tagStack[i]))
            return fontMap[tagStack[i]]->charWidth(" ", 0);

    return fontMap[tagStack[0]]->charWidth(" ", 0);
}


void XMLTextPaginator::findTagsTail()
{
    bool realParseDirection = parseDirection;
    parseDirection = true;

    for (int i = 0; i < tagsLineCount; i++)
    {
        tag = Columns[currentColumn].last();
        int parseResalt = parseTag();
        if (parseResalt == 1 || parseResalt == 0)
        {
            tagType = !tagType;
            applyTag();
            Columns[currentColumn].removeLast();
        }
    }
    currentTextPos -= tagsLineCount;
    parseDirection = realParseDirection;
}


void XMLTextPaginator::placeImage()
{
    Columns[currentColumn].append(HTMLImage);
    tagsLineCount = 0;

    HTMLImage.clear();
    currentHeight += HTMLImageSize + 15;
    HTMLImageSize = 0;
    currentWidth = 0;

    qDebug()<<"image inserted";
}


void XMLTextPaginator::doStep(int direction = 1)
{
    if (!parseDirection)
        currentTextPos += direction;
    else
        currentTextPos -= direction;
}


///1 - нужный тег, 2 - лишний тег, 3 - тег перевода колонки
int XMLTextPaginator::parseTag()
{
    tagInfo TagInf = Resolver->getTag(tag);
    if (TagInf.index == -1)
        return 2;

    tagType = TagInf.type;
    tag = TagInf.html;


    if (TagInf.index < 31)
    {
        if (tagType == parseDirection)
        {
            int height = getWordHeightFor(tag);
            if (height != -1)
            {
                int addSize = 0;
                if (stringHeight == 0)
                    addSize = (CurProfile.ParLeftTopIdent%100)*(parseDirection && tagType?0:1);

                if (currentHeight + height + addSize > columnHeight)
                {
                    findTagsTail();
                    return 3;
                }
            }
        }
    }


    if (TagInf.index == 30)        ///<p>
    {
        if (!parseDirection && !tagType)
            currentWidth = CurProfile.ParLeftTopIdent/100;
        else
            currentWidth = 0;

        if (tagType != parseDirection)
            currentHeight += stringHeight + CurProfile.ParLeftTopIdent%100;

        stringHeight = 0;

        if (ParagrafTail && parseDirection)
        {
            tag = "p class='end'";
            tagType = false;

            ParagrafTail = false;
            commitTag();

            return 2;
        }

        return 1;
    }


    if (TagInf.index == 33)                ///<br/>
    {
        if (currentHeight == 0)
            return 2;

        if (currentHeight + getWordHeight() + CurProfile.ParLeftTopIdent%100 > columnHeight)
            return 2;

        currentHeight += getWordHeight() + CurProfile.ParLeftTopIdent%100;

        stringHeight = 0;

        tag = "br/";
        tagType = false;
        commitTag();

        return 2;
    }


    if (TagInf.index < 10)              ///<title, subtitle, epigraph, annotation>
    {
        currentHeight += stringHeight;
        currentWidth = 0;
    }


    if ((TagInf.index == 1 || TagInf.index == 31) && tagType == false)                              ///<title><section>
    {
        if (currentHeight != 0)
            return 3;
        else
            return 1;
    }


    if (TagInf.index == 31 && tagType == false)       ///
    {
    }


    if (TagInf.index == 41)                ///<a>
    {
        return 2;
    }


    if (TagInf.index == 40)                ///<img>
    {
        QString imageName = parseTagAttribute(tag, "href");
        imageName.remove(0,1);

        if (!ImageTable->contains(imageName))
            return 2;

        QPair <QString, int> imgData = ImageTable->getImage(imageName, columnHeight - currentHeight, columnWidth, columnHeight);

        HTMLImage = imgData.first;
        if (HTMLImage.isEmpty())
        {
            HTMLImageSize = 0;
            return 2;
        }

        HTMLImageSize = imgData.second;

        if (HTMLImageSize > columnHeight - currentHeight)
        {
            doStep();
            return 3;
        }

        placeImage();
        return 2;
    }

    if (TagInf.index < 20)
        return 1;

    return 2;
}


void XMLTextPaginator::applyTag()
{
    if (tagStack.back() == tag)
    {
        if (tagType != parseDirection)
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


void XMLTextPaginator::commitTag()
{
    if (tagType == tagsLineDirection)
        tagsLineCount++;
    else
        tagsLineCount = 0;

    if (tagType)
        Columns[currentColumn].append("</" + tag + ">");
    else
        Columns[currentColumn].append("<" + tag + ">");
}


bool XMLTextPaginator::applyWord()
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
                doStep(-1);
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


void XMLTextPaginator::commitWord()
{
    if (bookText[currentTextPos].right(1) != "-" || bookText[currentTextPos].size() == 1)
        Columns[currentColumn].append(bookText[currentTextPos] + " ");
    else
        Columns[currentColumn].append(bookText[currentTextPos]);

    tagsLineCount = 0;
}


void XMLTextPaginator::preparePage(bool direction)
{
    if (direction == parseDirection)
    {
            beginTagStack = tagStack;
            beginParagrafTail = ParagrafTail;
    }
    else
    {
        //меняем направление верстки
        tagStack = beginTagStack;
        ParagrafTail = beginParagrafTail;

        HTMLImage.clear();
        HTMLImageSize = 0;
    }

    parseDirection = direction;

    for (int i = 0; i < Columns.size(); i++)
        Columns[i].clear();

    wordWidth = wordHeight = tagType = 0;
}


void XMLTextPaginator::createHTMLPage()
{
    HTMLPage.clear();

    if (!parseDirection)
    {
        for (int i = 0; i < Columns[0].size(); i++)
            HTMLPage += Columns[0][i];

        for (int i = 1; i < CurProfile.ColumnCount; i++)
        {
            HTMLPage += PageHTMLSep;
            for (int j = 0; j < Columns[i].size(); j++)
                HTMLPage += Columns[i][j];
        }
    }
    else
    {
        for (int i = Columns[CurProfile.ColumnCount - 1].size() - 1; i >= 0; i--)
            HTMLPage += Columns[CurProfile.ColumnCount - 1][i];

        for (int i = Columns.size() - 2; i >= 0; i--)
        {
            HTMLPage += PageHTMLSep;
            for (int j = Columns[i].size() - 1; j >= 0; j--)
                HTMLPage += Columns[i][j];
        }
    }
}



QString XMLTextPaginator::getPageForward()
{
    if (currentTextPos < strCount)
    {
        preparePage(false);

        currentTextPos = currentBStrNum = currentEStrNum + 1;

        for (currentColumn = 0; currentColumn < CurProfile.ColumnCount; currentColumn++)
        {
            currentHeight = currentWidth = stringHeight = 0;

            //вставка картинки с прошлой колонки
            if (HTMLImageSize != 0)
            {
                placeImage();
                if (currentHeight >= columnHeight)
                    continue;
            }

            columnTail.clear();
            for (int p = 1; p < tagStack.size(); p++)
                columnTail += "<" + tagStack[p] + ">";

            if (ParagrafTail)
            {
                //учитываем разделение параграфа
                int pos = columnTail.lastIndexOf("<p>");
                if (pos != -1)
                    columnTail.insert(pos + 2, " class = 'begin'");

                ParagrafTail = false;
            }

            Columns[currentColumn].append(columnTail);

            for (; currentTextPos < strCount && currentTextPos < bookText.size(); currentTextPos++)
            {
                if (bookText[currentTextPos].size())
                {
                    if (bookText[currentTextPos][0] == '<')
                    {
                        tag = bookText[currentTextPos];
                        int parseResalt = parseTag();

                        if (parseResalt == 1)
                        {
                            applyTag();
                            commitTag();
                            continue;
                        }
                        else if (parseResalt == 2)
                                continue;
                        else if (parseResalt == 3)
                                break;
                    }
                    else
                    {
                        word = bookText[currentTextPos];
                        if (!applyWord())
                        {
                            // переносим колонку с разделением параграфа
                            int pos = Columns[currentColumn].lastIndexOf("<p>");
                            if (pos != -1)
                                Columns[currentColumn][pos].insert(2, " class = 'end'");
                            ParagrafTail = true;
                            break;
                        }
                        commitWord();
                    }
                }
            }
            for (int p = tagStack.size() - 1; p > 0; p--)
                Columns[currentColumn].append("</" + tagStack[p] + ">");
        }

        currentEStrNum = currentTextPos - 1;

        book->setBookProgress(currentBStrNum,getProgress(), tagStack.toList());

        createHTMLPage();
        debugSave(HTMLPage);
    }

    return PageHTMLHeader + HTMLPage + PageHTMLBottom;
}


QString XMLTextPaginator::getPageBackward()
{
    if (currentBStrNum > 0)
    {
        preparePage(true);

        currentTextPos = currentEStrNum = currentBStrNum - 1;

        for (currentColumn = 0; currentColumn < CurProfile.ColumnCount; currentColumn++)
        {
            currentHeight = currentWidth = stringHeight = 0;
            ///дописать разрыв параграфа

            //вставка картинки с прошлой колонки
            if (HTMLImageSize != 0)
            {
                placeImage();
                if (currentHeight >= columnHeight)
                    continue;
            }

            columnTail.clear();
            for (int p = tagStack.size() - 1; p > 0 ; p--)
                columnTail += "</" + tagStack[p] + ">";
            Columns[currentColumn].append(columnTail);

            for (; currentTextPos >= 0; currentTextPos--)
            {
                if (bookText[currentTextPos][0] == '<')
                {
                    tag = bookText[currentTextPos];
                    int parseResalt = parseTag();
                    if (parseResalt == 1)
                    {
                        applyTag();
                        commitTag();
                        continue;
                    }
                    else if (parseResalt == 2)
                            continue;
                    else if (parseResalt == 3)
                            break;
                }
                else
                {
                    word = bookText[currentTextPos];
                    if (!applyWord())
                    {
                        ParagrafTail = true;
                        break;
                    }
                    commitWord();
                }
            }

            columnTail.clear();
            for (int p = tagStack.size() - 1; p > 0; p--)
                columnTail.prepend( "<" + tagStack[p] + ">");

            if (ParagrafTail)
            {
                int pos = columnTail.indexOf("<p>");
                if (pos != -1)
                    columnTail.insert(pos+2, " class = 'begin'");
            }

            Columns[currentColumn].append(columnTail);
        }

        currentBStrNum = currentTextPos + 1;

        book->setBookProgress(currentBStrNum,getProgress(), tagStack.toList());

        createHTMLPage();
        debugSave(HTMLPage);
    }

    return PageHTMLHeader + HTMLPage + PageHTMLBottom;
}


QString XMLTextPaginator::updatePage(const int &width, const int &height)
{
    setPageGeometry(width, height);
    currentEStrNum = currentBStrNum;
    tagStack = beginTagStack;
    return getPageForward();
}


QString XMLTextPaginator::updateSettings(const int &width, const int &height)
{
    setPageGeometry(width, height);
    setHTMLinf();
    setFontMap();
    setLinespaceMap();
    currentEStrNum = currentBStrNum;
    tagStack = beginTagStack;
    return getPageForward();
}


float XMLTextPaginator::getProgress()
{
    if (currentBStrNum > 0 && strCount)
        return (((float)currentEStrNum/(float)strCount) * 100);
    else
        return 0;
}


void XMLTextPaginator::debugSave(const QString &HTMLPage)
{
    QFile asd("F:/asd.html");
    asd.open(QIODevice::WriteOnly);
    QTextStream out(&asd);
    out<<PageHTMLHeader + HTMLPage + PageHTMLBottom;
    asd.close();
}

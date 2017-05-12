#include "xmltextpaginator.h"

#include <QFont>
#include <QFile>
#include <QDebug>
#include <QUrl>
#include <QString>
#include <QFontMetrics>
#include <QThread>

#include "xmltextparser.h"


XMLTextPaginator::XMLTextPaginator(QObject *parent)
{
    setParent(parent);

    currentTextPos = 0;
    HTMLImageSize = 0;

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
    if (currentEStrNum < 5)
        currentEStrNum = currentBStrNum = -1;

    tagStack.fromList(book->getBookProgressTagStack());

    if (tagStack.size() == 0)
        tagStack.push("Text");

    Resolver = new TagsResolver(this, book->getFormat());
    Helper = new PaginatorHelper(this);

    Helper->setHTMLPageElems(PageHTMLHeader, PageHTMLSep, PageHTMLBottom);
    Helper->setFontMetrics(&fontsMetrics, &fontsLinespaces);
    Helper->setPageSizes(ColumnCount, TextLeftRightIdent, TextTopBottomIdent, ParLeftTopIdent);

    setPageGeometry(Pwidth, Pheight);

    XMLTextParser parser(book);

    bookText = parser.getText();
    TableOfContentsIndexes = parser.getTableOfContentsIndexes();
    TableOfContentsText = parser.getTableOfContentsText();
    ImageTable = parser.getImageTable();

    strCount = bookText.size();


    Columns.clear();
    for (int i = 0; i < ColumnCount; i++)
        Columns.append(QStringList());



    QFile asd("F:/all.txt");
    asd.open(QIODevice::WriteOnly);
    QTextStream out(&asd);
    for (int i = 0; i < strCount; i++)
    {
        out<<i<<"   "<<bookText[i];
        out<<endl;
    }
    asd.close();


    qDebug()<<"parser started";
    return getPageForward();
}


XMLTextPaginator::~XMLTextPaginator()
{
    foreach (auto FontMetricsPointer, fontsMetrics) {
        delete FontMetricsPointer;
    }

    delete ImageTable;

    qDebug()<<"delete paginator";
}


void XMLTextPaginator::setPageGeometry(const int &width, const int &height)
{
    columnWidth = (width - 10 - 30*(ColumnCount-1) - TextLeftRightIdent/100 - TextLeftRightIdent%100)/ColumnCount;
    columnHeight = height - 20 - TextTopBottomIdent/100 - TextTopBottomIdent%100;
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
        if (fontsLinespaces.contains(tagStack[i]))
            return fontsLinespaces[tagStack[i]];

    return fontsLinespaces[tagStack[0]];
}


int XMLTextPaginator::getWordHeightFor(QString name)
{
    if (fontsLinespaces.contains(name))
        return fontsLinespaces[name];
    if (name == "p")
        return fontsLinespaces["Text"];

    return -1;
}


int XMLTextPaginator::getWordWidth()
{
    for (int i = tagStack.size() - 1; i > 0; i--)
        if (fontsMetrics.contains(tagStack[i]))
            return fontsMetrics[tagStack[i]]->width(word);

    return fontsMetrics[tagStack[0]]->width(word);
}


int XMLTextPaginator::getSpaceWidth()
{
    for (int i = tagStack.size() - 1; i > 0; i--)
        if (fontsMetrics.contains(tagStack[i]))
            return fontsMetrics[tagStack[i]]->charWidth(" ", 0);

    return fontsMetrics[tagStack[0]]->charWidth(" ", 0);
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
                    addSize = (ParLeftTopIdent%100)*(parseDirection && tagType?0:1);

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
            currentWidth = ParLeftTopIdent/100;
        else
            currentWidth = 0;

        if (tagType != parseDirection)
            currentHeight += stringHeight + ParLeftTopIdent%100;

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

        if (currentHeight + getWordHeight() + ParLeftTopIdent%100 > columnHeight)
            return 2;

        currentHeight += getWordHeight() + ParLeftTopIdent%100;

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
        if (!parseDirection)
        {
            if (currentHeight != 0)
                return 3;
            else
                return 1;
        }
        else
        {
            applyTag();
            commitTag();
            doStep();
            return 3;
        }

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

        wordWidth = getWordWidth();

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

    for (int i = 0; i < ColumnCount; i++)
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

        for (int i = 1; i < ColumnCount; i++)
        {
            HTMLPage += PageHTMLSep;
            for (int j = 0; j < Columns[i].size(); j++)
                HTMLPage += Columns[i][j];
        }
    }
    else
    {
        for (int i = Columns[ColumnCount - 1].size() - 1; i >= 0; i--)
            HTMLPage += Columns[ColumnCount - 1][i];

        for (int i = ColumnCount - 2; i >= 0; i--)
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

        qDebug()<<currentBStrNum<< "    "<<currentEStrNum;
        qDebug()<<bookText[currentBStrNum];
        qDebug()<<tagStack;

        for (currentColumn = 0; currentColumn < ColumnCount; currentColumn++)
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

        book->setBookProgress(currentBStrNum - 1, getProgress(), beginTagStack.toList());

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

        for (currentColumn = 0; currentColumn < ColumnCount; currentColumn++)
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

        book->setBookProgress(currentBStrNum - 1, getProgress(), tagStack.toList());

        qDebug()<<currentBStrNum<< "    "<<currentEStrNum;
        qDebug()<<bookText[currentBStrNum - 1];
        qDebug()<<tagStack;

        createHTMLPage();
        debugSave(HTMLPage);
    }

    return PageHTMLHeader + HTMLPage + PageHTMLBottom;
}


QString XMLTextPaginator::resizePage(const int &width, const int &height)
{
    setPageGeometry(width, height);
    currentEStrNum = currentBStrNum;
    tagStack = beginTagStack;
    return getPageForward();
}


QString XMLTextPaginator::updateSettings(const int &width, const int &height)
{
    Helper->setHTMLPageElems(PageHTMLHeader, PageHTMLSep, PageHTMLBottom);
    Helper->setFontMetrics(&fontsMetrics, &fontsLinespaces);
    Helper->setPageSizes(ColumnCount, TextLeftRightIdent, TextTopBottomIdent, ParLeftTopIdent);

    return resizePage(width, height);
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

#include "xml_text_paginator.h"

#include <QFont>
#include <QFile>
#include <QDebug>
#include <QUrl>
#include <QString>
#include <QFontMetrics>
#include <QThread>

#include "xml_text_parser.h"


XMLTextPaginator::XMLTextPaginator(QObject *parent)
{
    setParent(parent);

    currentTextPos = 0;
    HTMLImageSize = 0;

    columnWidth = columnHeight = 0;

    pageBeginTextPos = currentTextPos = pageEndTextPos = 0;

    currentColumn = 0;
    lastLineSize = 0;

    tagsLineCount = 0;

    wordWidth = wordHeight = 0;
    currentWidth = currentHeight = 0;

    stringHeight = 0;

    tagType = false;
    parseDirection = false;

    beginParagrafTail = ParagrafTail = false;

    Searcher = 0;


    TagParseFunctions.insert(30, &tag_p);
    TagParseFunctions.insert(33, &tag_br);
    TagParseFunctions.insert(32, &tag_section);
    TagParseFunctions.insert(41, &tag_a);
    TagParseFunctions.insert(40, &tag_img);
}



QString XMLTextPaginator::startParser(Book *OpeningBook, const int &Pwidth, const int &Pheight)
{
    book = OpeningBook;

    BookPosition lastPos = book->getProgress();
    pageEndTextPos = pageBeginTextPos = lastPos.TextPos;
    if (pageEndTextPos < 5)
        pageEndTextPos = pageBeginTextPos = -1;

    tagStack = lastPos.PrevTags;
    ParagrafTail = lastPos.ParagrafTail;

    if (tagStack.size() == 0)
        tagStack.push("Text");

    Resolver = new TagsResolver(this, book->getFormat());
    Helper = new PaginatorHelper(this);

    Helper->setHTMLPageElems(PageHTMLStyles, PageHTMLHeader, PageHTMLSep, PageHTMLBottom);
    Helper->setFontMetrics(&fontsMetrics, &fontsLinespaces);
    Helper->setPageSizes(ColumnCount, TextLeftRightIdent, TextTopBottomIdent, ParLeftTopIdent);

    setPageGeometry(Pwidth, Pheight);

    XMLTextParser parser(book);

    bookText = parser.getText();
    TableOfContents = parser.getTableOfContents();
    ImageTable = parser.getImageTable();
    notesTable = parser.getNotesTable();

    Columns.clear();
    for (int i = 0; i < ColumnCount; i++)
        Columns.append(QStringList());

    qDebug()<<"parser started";
    return getPageForward();
}


XMLTextPaginator::~XMLTextPaginator()
{
    foreach (auto FontMetricsPointer, fontsMetrics) {
        delete FontMetricsPointer;
    }

    delete TableOfContents;
    delete ImageTable;

    if (Searcher != 0)
        delete Searcher;

    qDebug()<<"delete paginator";
}


void XMLTextPaginator::setPageGeometry(const int &width, const int &height)
{
    columnWidth = (width - 10 - 30*(ColumnCount-1) - TextLeftRightIdent/100 - TextLeftRightIdent%100)/ColumnCount;
    columnHeight = height - 20 - TextTopBottomIdent/100 - TextTopBottomIdent%100;
}


QTreeWidgetItem *XMLTextPaginator::getBookContentTable() const
{
    return TableOfContents->clone();
}


long long XMLTextPaginator::getCurrentSectionIndex() const
{
    /*
    int pos;
    for (pos = 1; pos < TableOfContentsIndexes.size() && currentBStrNum > TableOfContentsIndexes[pos]; ++pos);
    if (currentBStrNum > TableOfContentsIndexes.back())
        return TableOfContentsIndexes.size() - 1;
    return pos;
    */
    return 0;
}


QString XMLTextPaginator::goToSection(const long long sectionIndex)
{
    currentTextPos = pageEndTextPos = sectionIndex;
    tagStack.clear();
    tagStack.append("Text");
    parseDirection = false;
    return getPageForward();
}


int XMLTextPaginator::getWordHeight() const
{
    for (int i = tagStack.size() - 1; i > 0; i--)
        if (fontsLinespaces.contains(tagStack[i]))
            return fontsLinespaces[tagStack[i]];

    return fontsLinespaces[tagStack[0]];
}


int XMLTextPaginator::getWordHeightFor(QString name) const
{
    if (fontsLinespaces.contains(name))
        return fontsLinespaces[name];
    if (name == "p")
        return fontsLinespaces["Text"];

    return -1;
}


int XMLTextPaginator::getWordWidth() const
{
    for (int i = tagStack.size() - 1; i > 0; i--)
        if (fontsMetrics.contains(tagStack[i]))
            return fontsMetrics[tagStack[i]]->width(word);

    return fontsMetrics[tagStack[0]]->width(word);
}


int XMLTextPaginator::getSpaceWidth() const
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


int XMLTextPaginator::tag_p()
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


int XMLTextPaginator::tag_br()
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


int XMLTextPaginator::tag_section()
{
    if (!parseDirection)
    {
        if (currentHeight != 0)
            return 3;
    }
    return 2;
}


int XMLTextPaginator::tag_a()
{
    if (tag.contains("l:href"))
        tag.replace("l:href", "href");
    else if (tag.contains("xlink:href"))
        tag.replace("xlink:href", "href");

    commitTag();

    return 2;
}


int XMLTextPaginator::tag_img()
{
    QString imageName = parseTagAttribute(tag, "href");
    imageName.remove(0,1);

    if (!ImageTable->contains(imageName))
        return 2;

    QPair <QString, int> imgData = ImageTable->getHTMLImage(imageName, columnHeight - currentHeight, columnWidth, columnHeight);

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

    if (columnHeight <= currentHeight)
    {
        doStep();
        return 3;
    }
    return 2;
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
        /*
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
        }*/
    }


    if (TagParseFunctions.contains(TagInf.index))
        return (this->*(TagParseFunctions[TagInf.index]))();


    if (TagInf.index < 10)              ///<title, subtitle, epigraph, annotation>
    {
        currentHeight += stringHeight;
        currentWidth = 0;
    }

    if (TagInf.index < 30)
        return 1;

    return 2;
}


void XMLTextPaginator::applyTag()
{
    if (tagStack.contains(tag))
    {
        if (tagType != parseDirection)
        {
            word = "";
            tagStack.removeAt(tagStack.lastIndexOf(tag));
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
                //перенос колонки
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
                    //перенос колонки
                    return false;
                }
                else
                {
                    //перенос строки
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
    tagsLineDirection = false;
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
    if (pageEndTextPos + 1 < bookText.size())
    {
        preparePage(false);

        currentTextPos = pageBeginTextPos = pageEndTextPos + 1;

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

            for (; currentTextPos < bookText.size() && currentTextPos < bookText.size(); currentTextPos++)
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
                            // костыть костылей
                            // сам иисус воскрес, чтобы сделать его
                            for (unsigned int i = currentWidth; i <= columnWidth + 10; i += 1)
                                Columns[currentColumn].append("&nbsp;");

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

        pageEndTextPos = currentTextPos - 1;

        book->setProgress(pageBeginTextPos - 1, ParagrafTail, beginTagStack, getProgress());

        createHTMLPage();
        debugSave(HTMLPage);
    }

    return PageHTMLStyles + PageHTMLHeader + HTMLPage + PageHTMLBottom;
}


QString XMLTextPaginator::getPageBackward()
{
    if (pageBeginTextPos > 0)
    {
        preparePage(true);

        currentTextPos = pageEndTextPos = pageBeginTextPos - 1;

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

        pageBeginTextPos = currentTextPos + 1;

        book->setProgress(pageBeginTextPos - 1, ParagrafTail, tagStack, getProgress());

        createHTMLPage();
        debugSave(HTMLPage);
    }

    return PageHTMLStyles + PageHTMLHeader + HTMLPage + PageHTMLBottom;
}


QString XMLTextPaginator::getPageNote(const QString &ID, const int &viewWidth) const
{
    if (!notesTable.contains(ID))
        return QString();


    QStringList temp = notesTable[ID];
    QString note;

    for (int i = 0; i < temp.size(); i++)
    {
        if (temp[i][0] == '<')
        {
            tagInfo noteTag = Resolver->getTag(temp[i]);
            if (noteTag.index == 40)
            {
                QString imageName = parseTagAttribute(temp[i], "href");
                imageName.remove(0,1);

                if (ImageTable->contains(imageName))
                    note.append(ImageTable->getHTMLImage(imageName, 6666, viewWidth, 6666).first);
            }
            else
            {
                if (!noteTag.type)
                    note.append("<" + noteTag.html + ">");
                else
                    note.append("</" + noteTag.html + ">");
            }
        }
        else
        {
            if (temp[i].right(1) != "-" || temp[i].size() == 1)
                note.append(temp[i] + " ");
            else
                note.append(temp[i]);
        }
    }

    return PageHTMLStyles + "<body align = 'justify'>" + note + "</body>";
}


QString XMLTextPaginator::searchStart(QString key, QString type)
{
    if (Searcher != 0)
        return refreshPage();

    Searcher = new XMLTextSearcher(book->getFormat());
    Searcher->setStartData(tagStack, pageBeginTextPos, ParagrafTail);
    Searcher->start(bookText, key);

    if (Searcher->getResultCount() == 0)
    {
        emit currentSearchStep(tr("No matches"));
        return searchStop();
    }

    preparePage(false);

    HTMLImage.clear();
    HTMLImageSize = 0;


    if (type == QObject::tr("From the beginning"))
    {
        searchStep = -1;
    }
    else if (type == QObject::tr("From the end"))
    {
        searchStep = Searcher->getResultCount() - 2;
    }
    else if (type == QObject::tr("From the current position"))
    {
        searchStep = Searcher->getResultFrom(pageBeginTextPos);
    }
    else
        return refreshPage();

    return searchNextStep();
}


QString XMLTextPaginator::searchNextStep()
{
    qDebug()<<"search next step";
    if (Searcher == 0)
        return refreshPage();

    searchStep++;
    if (searchStep >= Searcher->getResultCount())
        searchStep = 0;

    return doSearchStep();
}


QString XMLTextPaginator::searchPrevStep()
{
    qDebug()<<"search prev step";

    if (Searcher == 0)
        return refreshPage();

    searchStep--;
    if (searchStep < 0)
        searchStep = Searcher->getResultCount() - 1;

    return doSearchStep();
}


QString XMLTextPaginator::doSearchStep()
{
    BookPosition* res = Searcher->getResultAt(searchStep);
    if (res == 0)
        return refreshPage();

    tagStack = res->PrevTags;
    ParagrafTail = res->ParagrafTail;
    pageEndTextPos = res->TextPos - 1;

    emit currentSearchStep(QString::number(searchStep+1) + "/" + QString::number(Searcher->getResultCount()));

    return getPageForward();
}


QString XMLTextPaginator::searchStop()
{
    qDebug()<<"stop search";
    emit currentSearchStep("");

    if (Searcher != 0)
        delete Searcher;

    Searcher = 0;
    return refreshPage();
}


QString XMLTextPaginator::searchBack()
{
    qDebug()<<"back to search start";
    if (Searcher == 0)
        return refreshPage();

    BookPosition res = Searcher->getStartData();
    beginTagStack = res.PrevTags;
    beginParagrafTail = res.ParagrafTail;
    pageBeginTextPos = res.TextPos;

    return searchStop();
}


QString XMLTextPaginator::refreshPage()
{
    qDebug()<<"refresh page";

    pageEndTextPos = pageBeginTextPos = pageBeginTextPos - 1;
    tagStack = beginTagStack;
    ParagrafTail = beginParagrafTail;
    return getPageForward();
}


QString XMLTextPaginator::resizePage(const int &width, const int &height)
{
    setPageGeometry(width, height);
    return refreshPage();
}


QString XMLTextPaginator::updateSettings(const int &width, const int &height)
{
    Helper->refreshSettings();
    Helper->setHTMLPageElems(PageHTMLStyles, PageHTMLHeader, PageHTMLSep, PageHTMLBottom);
    Helper->setFontMetrics(&fontsMetrics, &fontsLinespaces);
    Helper->setPageSizes(ColumnCount, TextLeftRightIdent, TextTopBottomIdent, ParLeftTopIdent);

    setPageGeometry(width, height);

    return refreshPage();
}


float XMLTextPaginator::getProgress() const
{
    if (pageBeginTextPos > 0 && bookText.size())
        return (((float)(pageEndTextPos+1)/(float)bookText.size()) * 100);
    else
        return 0;
}


void XMLTextPaginator::debugSave(const QString &HTMLPage) const
{
    QFile asd("F:/asd.html");
    asd.open(QIODevice::WriteOnly);
    QTextStream out(&asd);
    out<<PageHTMLStyles + PageHTMLHeader + HTMLPage + PageHTMLBottom;
    asd.close();
}

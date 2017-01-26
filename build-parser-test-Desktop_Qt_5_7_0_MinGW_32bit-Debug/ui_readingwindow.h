/********************************************************************************
** Form generated from reading UI file 'readingwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_READINGWINDOW_H
#define UI_READINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReadingWindow
{
public:
    QWidget *MainWidget;
    QGridLayout *gridLayout;
    QTextBrowser *TextPage;
    QWidget *TopBarWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *MenuButton;
    QSpacerItem *horizontalSpacer_3;
    QLabel *BookName;
    QSpacerItem *horizontalSpacer;
    QLabel *Progress;
    QSpacerItem *horizontalSpacer_2;
    QLabel *Clock;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *min_button;
    QPushButton *full_size_button;
    QPushButton *exit_button;

    void setupUi(QMainWindow *ReadingWindow)
    {
        if (ReadingWindow->objectName().isEmpty())
            ReadingWindow->setObjectName(QStringLiteral("ReadingWindow"));
        ReadingWindow->resize(1200, 710);
        MainWidget = new QWidget(ReadingWindow);
        MainWidget->setObjectName(QStringLiteral("MainWidget"));
        gridLayout = new QGridLayout(MainWidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        TextPage = new QTextBrowser(MainWidget);
        TextPage->setObjectName(QStringLiteral("TextPage"));
        TextPage->setInputMethodHints(Qt::ImhMultiLine);
        TextPage->setFrameShape(QFrame::NoFrame);
        TextPage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        TextPage->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        TextPage->setAutoFormatting(QTextEdit::AutoNone);
        TextPage->setDocumentTitle(QStringLiteral(""));
        TextPage->setLineWrapMode(QTextEdit::FixedColumnWidth);
        TextPage->setLineWrapColumnOrWidth(2000);
        TextPage->setHtml(QString::fromUtf8("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\" bgcolor=\"#ffffff\">\n"
"<table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" width=\"100%\" cellspacing=\"2\" cellpadding=\"0\">\n"
"<tr>\n"
"<td>\n"
"<p align=\"center\" style=\" margin-top:10px; margin-bottom:10px; margin-left:15px; margin-right:15px; -qt-block-indent:0; text-indent:15px; line-height:100%;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:12pt; font-weight:792; color:#ff0000;\">\320\223\320\260\321\200\321\200\320\270 \320\223\320\260\321\200\321\200\320\270\321\201\320\276\320\275</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:10px; margin-left:15px; margin-right:15px; -qt-block-inde"
                        "nt:0; text-indent:15px; line-height:100%;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:12pt; font-weight:792; color:#ff0000;\">\302\253\320\235\320\276\320\262\321\213\320\265 \320\277\321\200\320\270\320\272\320\273\321\216\321\207\320\265\320\275\320\270\321\217 \320\241\321\202\320\260\320\273\321\214\320\275\320\276\320\271 \320\232\321\200\321\213\321\201\321\213\302\273</span></p>\n"
"<p align=\"right\" style=\" margin-top:10px; margin-bottom:10px; margin-left:15px; margin-right:15px; -qt-block-indent:0; text-indent:15px; line-height:100%;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; font-weight:792; font-style:italic; color:#005500;\">\320\234\320\276\320\271\321\200\320\265 \320\270 \320\242\320\276\320\264\320\264\321\203, \321\207\321\214\320\270 \320\273\321\216\320\261\321\217\321\211\320\260\321\217 \320\277\320\276\320\274\320\276\321\211\321\214 \320\270 \320\277\320\276\320\264\320\264\320\265\321\200\320\266\320\272\320\260 \320\277\320\276\320\267\320\262\320\276"
                        "\320\273\320\270\320\273\320\270 \321\215\321\202\320\276\320\271 \320\272\320\275\320\270\320\263\320\265 \320\277\320\276\321\217\320\262\320\270\321\202\321\214\321\201\321\217 \320\275\320\260 \321\201\320\262\320\265\321\202.</span></p>\n"
"<p align=\"justify\" style=\" margin-top:10px; margin-bottom:10px; margin-left:15px; margin-right:15px; -qt-block-indent:0; text-indent:15px; line-height:100%;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; color:#000000;\">\320\241\321\202\320\276\321\217\320\273\320\260 \320\267\320\260\320\262\320\265\321\202\320\275\320\260\321\217 \320\277\320\276\321\200\320\260 \320\264\320\275\321\217, \320\277\320\276\321\201\321\217\320\263\320\260\321\202\321\214 \320\275\320\260 \320\272\320\276\321\202\320\276\321\200\321\203\321\216 \342\200\224 \321\201\320\262\321\217\321\202\320\276\321\202\320\260\321\202\321\201\321\202\320\262\320\276, \320\276\320\264\320\270\320\275 \320\270\320\267 \321\200\320\265\320\264\321\207\320\260\320\271\321\210\320\270\321"
                        "\205 \320\274\320\276\320\274\320\265\320\275\321\202\320\276\320\262 \320\262 \320\266\320\270\320\267\320\275\320\270, \320\272\320\276\320\263\320\264\320\260 \320\262\321\201\320\265 \320\270\320\264\320\265\321\202 \320\261\320\265\320\267 \321\201\321\203\321\207\320\272\320\260 \320\261\320\265\320\267 \320\267\320\260\320\264\320\276\321\200\320\270\320\275\320\272\320\270. \320\236\321\202\320\272\320\270\320\275\321\203\320\262\321\210\320\270\321\201\321\214 \320\275\320\260 \321\201\320\277\320\270\320\275\320\272\321\203 \320\272\321\200\320\265\321\201\320\273\320\260, \321\217 \320\262\320\272\320\273\321\216\321\207\320\270\320\273 \321\201\321\202\320\265\321\200\320\265\320\276 \321\200\320\260\320\267\320\274\320\265\321\200\320\276\320\274 \321\201 \320\272\320\276\320\274\320\275\320\260\321\202\321\203 \342\200\224 \321\201\320\260\320\261\320\262\321\203\321\204\320\265\321\200\321\213 \321\201 \320\273\320\276\320\272\320\276\320\274\320\276\321\202\320\270\320\262, \320\277\320\270\321"
                        "\211\320\260\320\273\320\272\320\270, \320\276\321\202 \320\272\320\276\321\202\320\276\321\200\321\213\321\205 \320\267\321\203\320\261\321\213 \320\275\320\276\321\216\321\202, \342\200\224 \320\270 \320\262\320\276\320\267\320\264\321\203\321\205 \320\275\320\260\320\277\320\276\320\270\320\273\320\260 \320\261\320\273\320\260\320\263\320\276\320\264\320\260\321\202\321\214 \321\202\320\276\320\272\320\260\321\202\321\202\321\213 \320\270 \321\204\321\203\320\263\320\270 \320\230. \320\241. \320\221\320\260\321\205\320\260.</span></p></td>\n"
"<td>\n"
"<p align=\"justify\" style=\" margin-top:10px; margin-bottom:10px; margin-left:15px; margin-right:15px; -qt-block-indent:0; text-indent:15px; line-height:100%;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; color:#000000;\">\320\234\320\276\321\217 \320\273\320\260\320\264\320\276\320\275\321\214 \320\273\320\260\321\201\320\272\320\260\320\273\320\260 \321\201\321\202\320\260\320\272\320\260\320\275 \321\202\320\276\320\273\321\214\320\272\320"
                        "\276 \321\207\321\202\320\276 \320\275\320\260\320\273\320\270\321\202\320\276\320\263\320\276 \321\202\321\200\320\265\321\205\321\201\320\276\321\202\320\273\320\265\321\202\320\275\320\265\320\263\320\276, \320\264\321\200\320\260\320\263\320\276\321\206\320\265\320\275\320\275\320\276\320\263\320\276 \320\261\321\203\321\200\320\261\320\276\320\275\320\260, \320\276\321\205\320\273\320\260\320\266\320\264\320\265\320\275\320\275\320\276\320\263\320\276 \320\272\321\203\320\261\320\270\320\272\320\260\320\274\320\270 \320\274\320\270\320\273\320\273\320\270\320\276\320\275\320\276\320\273\320\265\321\202\320\275\320\265\320\263\320\276 \320\273\321\214\320\264\320\260, \320\264\320\276\321\201\321\202\320\260\320\262\320\273\320\265\320\275\320\275\320\276\320\263\320\276 \321\201 \320\276\320\264\320\275\320\276\320\271 \320\270\320\267 \320\262\320\275\320\265\321\210\320\275\320\270\321\205 \320\277\320\273\320\260\320\275\320\265\321\202. \320\237\321\200\320\276\321\201\321\202\320\276 \320\270\320\264"
                        "\320\265\320\260\320\273\321\214\320\275\320\276! \320\221\320\273\320\260\320\263\320\276\320\264\321\203\321\210\320\275\320\276 \321\203\320\273\321\213\320\261\320\275\321\203\320\262\321\210\320\270\321\201\321\214, \321\217 \320\277\320\276\320\264\320\275\320\265\321\201 \321\201\321\202\320\260\320\272\320\260\320\275 \320\272 \320\263\321\203\320\261\320\260\320\274.</span></p>\n"
"<p align=\"justify\" style=\" margin-top:10px; margin-bottom:10px; margin-left:15px; margin-right:15px; -qt-block-indent:0; text-indent:15px; line-height:100%;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; color:#000000;\">\320\230 \321\202\321\203\321\202 \320\262 \321\200\320\260\320\271 \320\262\321\202\320\276\321\200\320\263\320\273\320\276\321\201\321\214 \320\275\320\265\321\207\321\202\320\276 \321\207\321\203\320\266\320\264\320\276\320\265, \320\261\321\203\320\264\321\202\320\276 \320\277\321\203\320\273\321\214\321\201\320\270\321\200\321\203\321\216\321\211\320\260\321\217 \320\267\321\203\320\261"
                        "\320\275\320\260\321\217 \320\261\320\276\320\273\321\214 \320\270\320\273\320\270 \321\207\321\203\321\202\321\214 \321\201\320\273\321\213\321\210\320\275\321\213\320\271 \320\272\320\276\320\274\320\260\321\200\320\270\320\275\321\213\320\271 \320\267\321\203\320\264. \320\241 \320\274\320\276\320\263\321\203\321\207\320\270\320\274 \320\221\320\260\321\205\320\276\320\274 \321\201\321\205\320\273\320\265\321\201\321\202\320\275\321\203\320\273\320\276\321\201\321\214 \321\202\320\276\320\275\320\265\320\275\321\214\320\272\320\276\320\265 \321\202\321\200\320\265\320\275\321\214\320\272\320\260\320\275\321\214\320\265. \320\247\321\203\320\262\321\201\321\202\320\262\321\203\321\217, \320\272\320\260\320\272 \320\263\321\203\320\261\321\213 \320\270\321\201\320\272\320\260\320\266\320\260\320\265\321\202 \320\276\321\201\320\272\320\260\320\273, \321\217 \320\272\320\276\321\201\320\275\321\203\320\273\321\201\321\217 \321\200\320\265\320\263\321\203\320\273\321\217\321\202\320\276\321\200\320\260 \320\263"
                        "\321\200\320\276\320\274\320\272\320\276\321\201\321\202\320\270, \320\270 \320\262\320\265\320\273\320\270\320\272\320\270\320\271 \320\276\321\200\320\263\320\260\320\275 \320\266\320\260\320\273\320\276\320\261\320\275\320\276 \320\267\320\260\321\205\320\273\320\265\320\261\320\275\321\203\320\273\321\201\321\217 \320\274\320\276\320\273\321\207\320\260\320\275\320\270\320\265\320\274. \320\230 \320\264\320\262\320\265\321\200\320\275\320\276\320\271 \320\267\320\262\320\276\320\275\320\276\320\272 \320\277\321\200\320\276\320\267\320\262\321\203\321\207\320\260\320\273 \320\262\320\277\320\276\320\273\320\275\320\265 \320\276\321\202\321\207\320\265\321\202\320\273\320\270\320\262\320\276.</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p align=\"justify\" style=\" margin-top:10px; margin-bottom:10px; margin-left:15px; margin-right:15px; -qt-block-indent:0; text-indent:15px; line-height:100%;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; font-style:it"
                        "alic; color:#000000;\">\320\224\320\270\320\275\321\214-\320\264\320\270\320\275\321\214\342\200\246</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p></td></tr></table></body></html>"));
        TextPage->setTabStopWidth(80);
        TextPage->setTextInteractionFlags(Qt::NoTextInteraction);
        TextPage->setPlaceholderText(QStringLiteral(""));
        TextPage->setSearchPaths(QStringList());
        TextPage->setOpenLinks(false);

        gridLayout->addWidget(TextPage, 1, 0, 1, 1);

        TopBarWidget = new QWidget(MainWidget);
        TopBarWidget->setObjectName(QStringLiteral("TopBarWidget"));
        TopBarWidget->setMinimumSize(QSize(0, 25));
        TopBarWidget->setMaximumSize(QSize(16777215, 25));
        horizontalLayout_2 = new QHBoxLayout(TopBarWidget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        MenuButton = new QPushButton(TopBarWidget);
        MenuButton->setObjectName(QStringLiteral("MenuButton"));
        MenuButton->setMinimumSize(QSize(70, 25));
        MenuButton->setMaximumSize(QSize(60, 25));
        QFont font;
        font.setFamily(QStringLiteral("Browallia New"));
        font.setPointSize(16);
        font.setBold(false);
        font.setWeight(50);
        MenuButton->setFont(font);

        horizontalLayout_2->addWidget(MenuButton);

        horizontalSpacer_3 = new QSpacerItem(100, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        BookName = new QLabel(TopBarWidget);
        BookName->setObjectName(QStringLiteral("BookName"));
        QFont font1;
        font1.setFamily(QStringLiteral("Calibri"));
        font1.setPointSize(14);
        BookName->setFont(font1);
        BookName->setMidLineWidth(0);
        BookName->setText(QString::fromUtf8("\320\223\320\260\321\200\321\200\320\270\321\201\320\276\320\275 \320\223\320\260\321\200\321\200\320\270"));

        horizontalLayout_2->addWidget(BookName);

        horizontalSpacer = new QSpacerItem(686, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        Progress = new QLabel(TopBarWidget);
        Progress->setObjectName(QStringLiteral("Progress"));
        QFont font2;
        font2.setFamily(QStringLiteral("Batang"));
        font2.setPointSize(14);
        font2.setBold(false);
        font2.setWeight(50);
        font2.setStyleStrategy(QFont::NoAntialias);
        Progress->setFont(font2);
        Progress->setText(QStringLiteral("30%"));

        horizontalLayout_2->addWidget(Progress);

        horizontalSpacer_2 = new QSpacerItem(50, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        Clock = new QLabel(TopBarWidget);
        Clock->setObjectName(QStringLiteral("Clock"));
        Clock->setMinimumSize(QSize(75, 25));
        Clock->setMaximumSize(QSize(50, 25));
        Clock->setFont(font2);
        Clock->setText(QStringLiteral("20:59:59"));

        horizontalLayout_2->addWidget(Clock);

        horizontalSpacer_4 = new QSpacerItem(50, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        min_button = new QPushButton(TopBarWidget);
        min_button->setObjectName(QStringLiteral("min_button"));
        min_button->setMinimumSize(QSize(25, 25));
        min_button->setMaximumSize(QSize(25, 25));
        QPalette palette;
        QBrush brush(QColor(255, 255, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush1);
        palette.setBrush(QPalette::Active, QPalette::Link, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Link, brush1);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Highlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Link, brush1);
        min_button->setPalette(palette);
        QFont font3;
        font3.setPointSize(40);
        min_button->setFont(font3);
        min_button->setStyleSheet(QStringLiteral(""));
        min_button->setText(QStringLiteral(""));
        min_button->setShortcut(QStringLiteral(""));
        min_button->setAutoDefault(false);
        min_button->setFlat(true);

        horizontalLayout_2->addWidget(min_button);

        full_size_button = new QPushButton(TopBarWidget);
        full_size_button->setObjectName(QStringLiteral("full_size_button"));
        full_size_button->setMinimumSize(QSize(25, 25));
        full_size_button->setMaximumSize(QSize(25, 25));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Highlight, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Link, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Highlight, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Link, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Highlight, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Link, brush1);
        full_size_button->setPalette(palette1);
        full_size_button->setFont(font3);
        full_size_button->setStyleSheet(QStringLiteral(""));
        full_size_button->setText(QStringLiteral(""));
        full_size_button->setShortcut(QStringLiteral(""));
        full_size_button->setAutoDefault(false);
        full_size_button->setFlat(true);

        horizontalLayout_2->addWidget(full_size_button);

        exit_button = new QPushButton(TopBarWidget);
        exit_button->setObjectName(QStringLiteral("exit_button"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(exit_button->sizePolicy().hasHeightForWidth());
        exit_button->setSizePolicy(sizePolicy);
        exit_button->setMinimumSize(QSize(25, 25));
        exit_button->setMaximumSize(QSize(25, 25));
        exit_button->setSizeIncrement(QSize(1, 1));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Highlight, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Link, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Highlight, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Link, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Highlight, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Link, brush1);
        exit_button->setPalette(palette2);
        QFont font4;
        font4.setPointSize(12);
        exit_button->setFont(font4);
        exit_button->setStyleSheet(QStringLiteral(""));
        exit_button->setText(QStringLiteral(""));
        exit_button->setShortcut(QStringLiteral(""));
        exit_button->setAutoDefault(false);
        exit_button->setFlat(true);

        horizontalLayout_2->addWidget(exit_button);


        gridLayout->addWidget(TopBarWidget, 0, 0, 1, 1);

        ReadingWindow->setCentralWidget(MainWidget);

        retranslateUi(ReadingWindow);

        min_button->setDefault(false);
        full_size_button->setDefault(false);
        exit_button->setDefault(false);


        QMetaObject::connectSlotsByName(ReadingWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ReadingWindow)
    {
        ReadingWindow->setWindowTitle(QApplication::translate("ReadingWindow", "Reader", Q_NULLPTR));
        MenuButton->setText(QApplication::translate("ReadingWindow", "Menu", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ReadingWindow: public Ui_ReadingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_READINGWINDOW_H

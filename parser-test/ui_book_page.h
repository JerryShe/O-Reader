/********************************************************************************
** Form generated from reading UI file 'book_page.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOK_PAGE_H
#define UI_BOOK_PAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BookPage
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QFrame *leftLine;
    QVBoxLayout *ButtonBlock;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *exit_button;
    QVBoxLayout *VerticalButtonBlock;
    QPushButton *startReading;
    QSpacerItem *verticalSpacer_2;
    QPushButton *deleteBook;
    QVBoxLayout *ImageBlock;
    QLabel *Image;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *BookProgress;
    QSpacerItem *verticalSpacer_4;
    QVBoxLayout *BookData;
    QSpacerItem *verticalSpacer_6;
    QLabel *author;
    QLabel *title;
    QLabel *series;
    QLabel *genres;
    QFrame *leftLine_2;
    QTextEdit *annotation;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QMainWindow *BookPage)
    {
        if (BookPage->objectName().isEmpty())
            BookPage->setObjectName(QStringLiteral("BookPage"));
        BookPage->resize(812, 493);
        centralwidget = new QWidget(BookPage);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(0);
        gridLayout->setContentsMargins(0, 1, 0, 1);
        leftLine = new QFrame(centralwidget);
        leftLine->setObjectName(QStringLiteral("leftLine"));
        leftLine->setFrameShadow(QFrame::Plain);
        leftLine->setMidLineWidth(0);
        leftLine->setFrameShape(QFrame::VLine);

        gridLayout->addWidget(leftLine, 0, 2, 1, 1);

        ButtonBlock = new QVBoxLayout();
        ButtonBlock->setSpacing(15);
        ButtonBlock->setObjectName(QStringLiteral("ButtonBlock"));
        ButtonBlock->setContentsMargins(0, 0, 0, -1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, -1, 0);
        horizontalSpacer = new QSpacerItem(0, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        exit_button = new QPushButton(centralwidget);
        exit_button->setObjectName(QStringLiteral("exit_button"));
        exit_button->setMinimumSize(QSize(30, 30));
        exit_button->setMaximumSize(QSize(30, 30));

        horizontalLayout_2->addWidget(exit_button);


        ButtonBlock->addLayout(horizontalLayout_2);

        VerticalButtonBlock = new QVBoxLayout();
        VerticalButtonBlock->setSpacing(0);
        VerticalButtonBlock->setObjectName(QStringLiteral("VerticalButtonBlock"));
        VerticalButtonBlock->setContentsMargins(-1, 10, 10, 9);
        startReading = new QPushButton(centralwidget);
        startReading->setObjectName(QStringLiteral("startReading"));
        startReading->setMinimumSize(QSize(90, 30));
        startReading->setMaximumSize(QSize(70, 30));

        VerticalButtonBlock->addWidget(startReading);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        VerticalButtonBlock->addItem(verticalSpacer_2);

        deleteBook = new QPushButton(centralwidget);
        deleteBook->setObjectName(QStringLiteral("deleteBook"));
        deleteBook->setMinimumSize(QSize(90, 30));
        deleteBook->setMaximumSize(QSize(70, 30));

        VerticalButtonBlock->addWidget(deleteBook);


        ButtonBlock->addLayout(VerticalButtonBlock);


        gridLayout->addLayout(ButtonBlock, 0, 4, 1, 1);

        ImageBlock = new QVBoxLayout();
        ImageBlock->setSpacing(0);
        ImageBlock->setObjectName(QStringLiteral("ImageBlock"));
        ImageBlock->setContentsMargins(10, 9, 10, 9);
        Image = new QLabel(centralwidget);
        Image->setObjectName(QStringLiteral("Image"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(2);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Image->sizePolicy().hasHeightForWidth());
        Image->setSizePolicy(sizePolicy);
        Image->setMinimumSize(QSize(0, 0));
        Image->setMaximumSize(QSize(200, 300));
        Image->setFrameShape(QFrame::Box);
        Image->setText(QStringLiteral("TextLabel"));

        ImageBlock->addWidget(Image);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        ImageBlock->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 0);
        BookProgress = new QLabel(centralwidget);
        BookProgress->setObjectName(QStringLiteral("BookProgress"));
        QFont font;
        font.setPointSize(20);
        BookProgress->setFont(font);
        BookProgress->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(BookProgress);


        ImageBlock->addLayout(horizontalLayout);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        ImageBlock->addItem(verticalSpacer_4);


        gridLayout->addLayout(ImageBlock, 0, 0, 1, 1);

        BookData = new QVBoxLayout();
        BookData->setSpacing(0);
        BookData->setObjectName(QStringLiteral("BookData"));
        BookData->setContentsMargins(10, 0, 10, 0);
        verticalSpacer_6 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        BookData->addItem(verticalSpacer_6);

        author = new QLabel(centralwidget);
        author->setObjectName(QStringLiteral("author"));
        author->setMinimumSize(QSize(0, 25));
        author->setMaximumSize(QSize(16777215, 25));
        QFont font1;
        font1.setPointSize(14);
        author->setFont(font1);
        author->setText(QStringLiteral("author"));
        author->setAlignment(Qt::AlignCenter);

        BookData->addWidget(author);

        title = new QLabel(centralwidget);
        title->setObjectName(QStringLiteral("title"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(title->sizePolicy().hasHeightForWidth());
        title->setSizePolicy(sizePolicy1);
        title->setMinimumSize(QSize(0, 25));
        title->setMaximumSize(QSize(16777215, 25));
        title->setFont(font1);
        title->setText(QStringLiteral("title"));
        title->setAlignment(Qt::AlignCenter);

        BookData->addWidget(title);

        series = new QLabel(centralwidget);
        series->setObjectName(QStringLiteral("series"));
        series->setMinimumSize(QSize(0, 30));
        series->setText(QStringLiteral("series"));

        BookData->addWidget(series);

        genres = new QLabel(centralwidget);
        genres->setObjectName(QStringLiteral("genres"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(genres->sizePolicy().hasHeightForWidth());
        genres->setSizePolicy(sizePolicy2);
        genres->setMinimumSize(QSize(0, 25));
        genres->setMaximumSize(QSize(16777215, 25));
        genres->setText(QStringLiteral("genres"));

        BookData->addWidget(genres);

        leftLine_2 = new QFrame(centralwidget);
        leftLine_2->setObjectName(QStringLiteral("leftLine_2"));
        leftLine_2->setMinimumSize(QSize(0, 0));
        leftLine_2->setFrameShadow(QFrame::Plain);
        leftLine_2->setMidLineWidth(0);
        leftLine_2->setFrameShape(QFrame::HLine);

        BookData->addWidget(leftLine_2);

        annotation = new QTextEdit(centralwidget);
        annotation->setObjectName(QStringLiteral("annotation"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(annotation->sizePolicy().hasHeightForWidth());
        annotation->setSizePolicy(sizePolicy3);
        QFont font2;
        font2.setPointSize(10);
        font2.setKerning(false);
        font2.setStyleStrategy(QFont::PreferAntialias);
        annotation->setFont(font2);
        annotation->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        annotation->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        annotation->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        annotation->setDocumentTitle(QStringLiteral(""));
        annotation->setUndoRedoEnabled(true);
        annotation->setLineWrapMode(QTextEdit::WidgetWidth);
        annotation->setReadOnly(true);
        annotation->setHtml(QLatin1String("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>"));
        annotation->setTextInteractionFlags(Qt::NoTextInteraction);
        annotation->setPlaceholderText(QStringLiteral(""));

        BookData->addWidget(annotation);

        verticalSpacer_3 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        BookData->addItem(verticalSpacer_3);

        BookData->setStretch(6, 10);

        gridLayout->addLayout(BookData, 0, 3, 1, 1);

        gridLayout->setColumnStretch(2, 1);
        gridLayout->setColumnStretch(3, 1);
        gridLayout->setColumnMinimumWidth(2, 1);
        BookPage->setCentralWidget(centralwidget);

        retranslateUi(BookPage);

        QMetaObject::connectSlotsByName(BookPage);
    } // setupUi

    void retranslateUi(QMainWindow *BookPage)
    {
        BookPage->setWindowTitle(QApplication::translate("BookPage", "MainWindow", 0));
        exit_button->setText(QString());
        startReading->setText(QApplication::translate("BookPage", "Read", 0));
        deleteBook->setText(QApplication::translate("BookPage", "Delete Book", 0));
        BookProgress->setText(QApplication::translate("BookPage", "59,2%", 0));
    } // retranslateUi

};

namespace Ui {
    class BookPage: public Ui_BookPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOK_PAGE_H

/********************************************************************************
** Form generated from reading UI file 'booktableofcontents.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOKTABLEOFCONTENTS_H
#define UI_BOOKTABLEOFCONTENTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BookTableOfContents
{
public:
    QVBoxLayout *verticalLayout_2;
    QListWidget *TableOfContents;
    QHBoxLayout *horizontalLayout;
    QPushButton *Close;
    QPushButton *GoTo;

    void setupUi(QDialog *BookTableOfContents)
    {
        if (BookTableOfContents->objectName().isEmpty())
            BookTableOfContents->setObjectName(QStringLiteral("BookTableOfContents"));
        BookTableOfContents->resize(400, 500);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BookTableOfContents->sizePolicy().hasHeightForWidth());
        BookTableOfContents->setSizePolicy(sizePolicy);
        BookTableOfContents->setMinimumSize(QSize(400, 500));
        BookTableOfContents->setMaximumSize(QSize(400, 600));
        verticalLayout_2 = new QVBoxLayout(BookTableOfContents);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        TableOfContents = new QListWidget(BookTableOfContents);
        TableOfContents->setObjectName(QStringLiteral("TableOfContents"));
        TableOfContents->setFrameShape(QFrame::NoFrame);
        TableOfContents->setFrameShadow(QFrame::Plain);
        TableOfContents->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        TableOfContents->setEditTriggers(QAbstractItemView::NoEditTriggers);
        TableOfContents->setProperty("showDropIndicator", QVariant(false));
        TableOfContents->setSpacing(5);

        verticalLayout_2->addWidget(TableOfContents);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        Close = new QPushButton(BookTableOfContents);
        Close->setObjectName(QStringLiteral("Close"));
        Close->setMinimumSize(QSize(0, 30));
        Close->setMaximumSize(QSize(16777215, 30));
        Close->setStyleSheet(QStringLiteral(""));
        Close->setFlat(true);

        horizontalLayout->addWidget(Close);

        GoTo = new QPushButton(BookTableOfContents);
        GoTo->setObjectName(QStringLiteral("GoTo"));
        GoTo->setMinimumSize(QSize(0, 30));
        GoTo->setMaximumSize(QSize(16777215, 30));
        GoTo->setFlat(true);

        horizontalLayout->addWidget(GoTo);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(BookTableOfContents);

        QMetaObject::connectSlotsByName(BookTableOfContents);
    } // setupUi

    void retranslateUi(QDialog *BookTableOfContents)
    {
        BookTableOfContents->setWindowTitle(QApplication::translate("BookTableOfContents", "Dialog", 0));
        Close->setText(QApplication::translate("BookTableOfContents", "Close", 0));
        GoTo->setText(QApplication::translate("BookTableOfContents", "Go to the selected", 0));
    } // retranslateUi

};

namespace Ui {
    class BookTableOfContents: public Ui_BookTableOfContents {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOKTABLEOFCONTENTS_H

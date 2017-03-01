/********************************************************************************
** Form generated from reading UI file 'book_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOK_WIDGET_H
#define UI_BOOK_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BookWidget
{
public:
    QVBoxLayout *verticalLayout_4;
    QWidget *LastBookLayout;
    QVBoxLayout *verticalLayout;
    QLabel *ImageLabel;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QLabel *Author;
    QSpacerItem *verticalSpacer_2;
    QLabel *Title;
    QSpacerItem *verticalSpacer_3;
    QLabel *BookProgress;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *PageButton;
    QPushButton *ReadButton;

    void setupUi(QWidget *BookWidget)
    {
        if (BookWidget->objectName().isEmpty())
            BookWidget->setObjectName(QStringLiteral("BookWidget"));
        BookWidget->resize(220, 580);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BookWidget->sizePolicy().hasHeightForWidth());
        BookWidget->setSizePolicy(sizePolicy);
        BookWidget->setMinimumSize(QSize(220, 0));
        BookWidget->setMaximumSize(QSize(220, 16777215));
        verticalLayout_4 = new QVBoxLayout(BookWidget);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        LastBookLayout = new QWidget(BookWidget);
        LastBookLayout->setObjectName(QStringLiteral("LastBookLayout"));
        verticalLayout = new QVBoxLayout(LastBookLayout);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        ImageLabel = new QLabel(LastBookLayout);
        ImageLabel->setObjectName(QStringLiteral("ImageLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ImageLabel->sizePolicy().hasHeightForWidth());
        ImageLabel->setSizePolicy(sizePolicy1);
        ImageLabel->setMaximumSize(QSize(220, 16777215));
        ImageLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout->addWidget(ImageLabel);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(5);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout_3->setContentsMargins(-1, -1, -1, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        Author = new QLabel(LastBookLayout);
        Author->setObjectName(QStringLiteral("Author"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(Author->sizePolicy().hasHeightForWidth());
        Author->setSizePolicy(sizePolicy2);
        QFont font;
        font.setPointSize(15);
        Author->setFont(font);
        Author->setAlignment(Qt::AlignCenter);
        Author->setWordWrap(true);

        verticalLayout_3->addWidget(Author);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        Title = new QLabel(LastBookLayout);
        Title->setObjectName(QStringLiteral("Title"));
        sizePolicy2.setHeightForWidth(Title->sizePolicy().hasHeightForWidth());
        Title->setSizePolicy(sizePolicy2);
        Title->setFont(font);
        Title->setAlignment(Qt::AlignCenter);
        Title->setWordWrap(true);

        verticalLayout_3->addWidget(Title);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        BookProgress = new QLabel(LastBookLayout);
        BookProgress->setObjectName(QStringLiteral("BookProgress"));
        sizePolicy2.setHeightForWidth(BookProgress->sizePolicy().hasHeightForWidth());
        BookProgress->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setPointSize(20);
        BookProgress->setFont(font1);
        BookProgress->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(BookProgress);

        verticalSpacer_4 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, 0, -1);
        PageButton = new QPushButton(LastBookLayout);
        PageButton->setObjectName(QStringLiteral("PageButton"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(PageButton->sizePolicy().hasHeightForWidth());
        PageButton->setSizePolicy(sizePolicy3);
        PageButton->setMinimumSize(QSize(0, 50));
        PageButton->setMaximumSize(QSize(16777215, 50));

        horizontalLayout_2->addWidget(PageButton);

        ReadButton = new QPushButton(LastBookLayout);
        ReadButton->setObjectName(QStringLiteral("ReadButton"));
        sizePolicy3.setHeightForWidth(ReadButton->sizePolicy().hasHeightForWidth());
        ReadButton->setSizePolicy(sizePolicy3);
        ReadButton->setMinimumSize(QSize(100, 50));
        ReadButton->setMaximumSize(QSize(16777215, 50));

        horizontalLayout_2->addWidget(ReadButton);


        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(4, 1);

        verticalLayout->addLayout(verticalLayout_3);

        verticalLayout->setStretch(0, 1);
        ImageLabel->raise();
        ImageLabel->raise();

        verticalLayout_4->addWidget(LastBookLayout);


        retranslateUi(BookWidget);

        QMetaObject::connectSlotsByName(BookWidget);
    } // setupUi

    void retranslateUi(QWidget *BookWidget)
    {
        BookWidget->setWindowTitle(QApplication::translate("BookWidget", "Form", Q_NULLPTR));
        ImageLabel->setText(QString());
        Author->setText(QApplication::translate("BookWidget", "Author", Q_NULLPTR));
        Title->setText(QApplication::translate("BookWidget", "Title", Q_NULLPTR));
        BookProgress->setText(QApplication::translate("BookWidget", "59,2%", Q_NULLPTR));
        PageButton->setText(QApplication::translate("BookWidget", "Open book page", Q_NULLPTR));
        ReadButton->setText(QApplication::translate("BookWidget", "Continue reading", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BookWidget: public Ui_BookWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOK_WIDGET_H

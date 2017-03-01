/********************************************************************************
** Form generated from reading UI file 'reading_menu.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_READING_MENU_H
#define UI_READING_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReadingMenu
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *MainWidget;
    QVBoxLayout *verticalLayout_3;
    QPushButton *ContentsButton;
    QPushButton *SettingsButton;
    QSpacerItem *verticalSpacer;
    QPushButton *BackButton;

    void setupUi(QWidget *ReadingMenu)
    {
        if (ReadingMenu->objectName().isEmpty())
            ReadingMenu->setObjectName(QStringLiteral("ReadingMenu"));
        ReadingMenu->resize(70, 547);
        ReadingMenu->setMinimumSize(QSize(70, 0));
        ReadingMenu->setMaximumSize(QSize(70, 16777215));
        verticalLayout_2 = new QVBoxLayout(ReadingMenu);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        MainWidget = new QWidget(ReadingMenu);
        MainWidget->setObjectName(QStringLiteral("MainWidget"));
        verticalLayout_3 = new QVBoxLayout(MainWidget);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        ContentsButton = new QPushButton(MainWidget);
        ContentsButton->setObjectName(QStringLiteral("ContentsButton"));
        ContentsButton->setMinimumSize(QSize(70, 70));
        ContentsButton->setMaximumSize(QSize(70, 70));

        verticalLayout_3->addWidget(ContentsButton);

        SettingsButton = new QPushButton(MainWidget);
        SettingsButton->setObjectName(QStringLiteral("SettingsButton"));
        SettingsButton->setMinimumSize(QSize(70, 70));
        SettingsButton->setMaximumSize(QSize(70, 70));

        verticalLayout_3->addWidget(SettingsButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        BackButton = new QPushButton(MainWidget);
        BackButton->setObjectName(QStringLiteral("BackButton"));
        BackButton->setMinimumSize(QSize(70, 70));
        BackButton->setMaximumSize(QSize(70, 70));

        verticalLayout_3->addWidget(BackButton);


        verticalLayout_2->addWidget(MainWidget);


        retranslateUi(ReadingMenu);

        QMetaObject::connectSlotsByName(ReadingMenu);
    } // setupUi

    void retranslateUi(QWidget *ReadingMenu)
    {
        ReadingMenu->setWindowTitle(QApplication::translate("ReadingMenu", "Form", Q_NULLPTR));
        ContentsButton->setText(QString());
        SettingsButton->setText(QString());
        BackButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ReadingMenu: public Ui_ReadingMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_READING_MENU_H

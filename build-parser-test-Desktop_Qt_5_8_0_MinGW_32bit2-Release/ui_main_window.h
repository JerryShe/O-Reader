/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "library_layout.h"
#include "settings_layout.h"
#include "synchronization_layout.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *MainWidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *TopBarWidget;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *min_button;
    QPushButton *full_size_button;
    QPushButton *exit_button;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *LeftMenu;
    QPushButton *Library;
    QPushButton *Settings;
    QPushButton *Synchronization;
    QWidget *LeftExpandingWidget;
    QPushButton *Logout;
    QVBoxLayout *TabsLayout;
    LibraryLayout *LibraryWidget;
    SettingsLayout *SettingsWidget;
    SynchronizationLayout *SynchronizationWidget;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1173, 660);
        verticalLayout = new QVBoxLayout(MainWindow);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        MainWidget = new QWidget(MainWindow);
        MainWidget->setObjectName(QStringLiteral("MainWidget"));
        verticalLayout_2 = new QVBoxLayout(MainWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        TopBarWidget = new QWidget(MainWidget);
        TopBarWidget->setObjectName(QStringLiteral("TopBarWidget"));
        TopBarWidget->setMinimumSize(QSize(0, 25));
        TopBarWidget->setMaximumSize(QSize(16777215, 25));
        horizontalLayout_4 = new QHBoxLayout(TopBarWidget);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(1122, 4, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

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
        QFont font;
        font.setPointSize(40);
        min_button->setFont(font);
        min_button->setFocusPolicy(Qt::NoFocus);
        min_button->setStyleSheet(QStringLiteral(""));
        min_button->setText(QStringLiteral(""));
        min_button->setShortcut(QStringLiteral(""));
        min_button->setAutoDefault(false);
        min_button->setFlat(true);

        horizontalLayout_4->addWidget(min_button);

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
        full_size_button->setFont(font);
        full_size_button->setFocusPolicy(Qt::NoFocus);
        full_size_button->setStyleSheet(QStringLiteral(""));
        full_size_button->setText(QStringLiteral(""));
        full_size_button->setShortcut(QStringLiteral(""));
        full_size_button->setAutoDefault(false);
        full_size_button->setFlat(true);

        horizontalLayout_4->addWidget(full_size_button);

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
        QFont font1;
        font1.setPointSize(12);
        exit_button->setFont(font1);
        exit_button->setFocusPolicy(Qt::NoFocus);
        exit_button->setStyleSheet(QStringLiteral(""));
        exit_button->setText(QStringLiteral(""));
        exit_button->setShortcut(QStringLiteral(""));
        exit_button->setAutoDefault(false);
        exit_button->setFlat(true);

        horizontalLayout_4->addWidget(exit_button);


        verticalLayout_2->addWidget(TopBarWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        LeftMenu = new QVBoxLayout();
        LeftMenu->setSpacing(0);
        LeftMenu->setObjectName(QStringLiteral("LeftMenu"));
        LeftMenu->setSizeConstraint(QLayout::SetDefaultConstraint);
        LeftMenu->setContentsMargins(0, 0, 0, -1);
        Library = new QPushButton(MainWidget);
        Library->setObjectName(QStringLiteral("Library"));
        sizePolicy.setHeightForWidth(Library->sizePolicy().hasHeightForWidth());
        Library->setSizePolicy(sizePolicy);
        Library->setMinimumSize(QSize(70, 100));
        Library->setMaximumSize(QSize(70, 100));
        Library->setFocusPolicy(Qt::NoFocus);
        Library->setStyleSheet(QStringLiteral(""));
        Library->setText(QStringLiteral(""));
        Library->setIconSize(QSize(90, 90));
        Library->setCheckable(true);
        Library->setAutoDefault(true);
        Library->setFlat(true);

        LeftMenu->addWidget(Library);

        Settings = new QPushButton(MainWidget);
        Settings->setObjectName(QStringLiteral("Settings"));
        sizePolicy.setHeightForWidth(Settings->sizePolicy().hasHeightForWidth());
        Settings->setSizePolicy(sizePolicy);
        Settings->setMinimumSize(QSize(70, 100));
        Settings->setMaximumSize(QSize(70, 100));
        Settings->setFocusPolicy(Qt::NoFocus);
        Settings->setText(QStringLiteral(""));
        Settings->setCheckable(true);
        Settings->setFlat(true);

        LeftMenu->addWidget(Settings);

        Synchronization = new QPushButton(MainWidget);
        Synchronization->setObjectName(QStringLiteral("Synchronization"));
        sizePolicy.setHeightForWidth(Synchronization->sizePolicy().hasHeightForWidth());
        Synchronization->setSizePolicy(sizePolicy);
        Synchronization->setMinimumSize(QSize(70, 100));
        Synchronization->setMaximumSize(QSize(70, 100));
        Synchronization->setFocusPolicy(Qt::NoFocus);
        Synchronization->setText(QStringLiteral(""));
        Synchronization->setCheckable(true);
        Synchronization->setFlat(true);

        LeftMenu->addWidget(Synchronization);

        LeftExpandingWidget = new QWidget(MainWidget);
        LeftExpandingWidget->setObjectName(QStringLiteral("LeftExpandingWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(LeftExpandingWidget->sizePolicy().hasHeightForWidth());
        LeftExpandingWidget->setSizePolicy(sizePolicy1);
        LeftExpandingWidget->setMinimumSize(QSize(70, 0));
        LeftExpandingWidget->setMaximumSize(QSize(70, 16777215));
        LeftExpandingWidget->setFocusPolicy(Qt::NoFocus);

        LeftMenu->addWidget(LeftExpandingWidget);

        Logout = new QPushButton(MainWidget);
        Logout->setObjectName(QStringLiteral("Logout"));
        sizePolicy.setHeightForWidth(Logout->sizePolicy().hasHeightForWidth());
        Logout->setSizePolicy(sizePolicy);
        Logout->setMinimumSize(QSize(70, 70));
        Logout->setMaximumSize(QSize(70, 70));
        Logout->setFocusPolicy(Qt::NoFocus);
        Logout->setText(QStringLiteral(""));
        Logout->setCheckable(true);
        Logout->setFlat(true);

        LeftMenu->addWidget(Logout);


        horizontalLayout->addLayout(LeftMenu);

        TabsLayout = new QVBoxLayout();
        TabsLayout->setSpacing(0);
        TabsLayout->setObjectName(QStringLiteral("TabsLayout"));
        TabsLayout->setSizeConstraint(QLayout::SetFixedSize);
        TabsLayout->setContentsMargins(-1, -1, -1, 0);
        LibraryWidget = new LibraryLayout(MainWidget);
        LibraryWidget->setObjectName(QStringLiteral("LibraryWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(LibraryWidget->sizePolicy().hasHeightForWidth());
        LibraryWidget->setSizePolicy(sizePolicy2);
        LibraryWidget->setFocusPolicy(Qt::StrongFocus);

        TabsLayout->addWidget(LibraryWidget);

        SettingsWidget = new SettingsLayout(MainWidget);
        SettingsWidget->setObjectName(QStringLiteral("SettingsWidget"));
        sizePolicy2.setHeightForWidth(SettingsWidget->sizePolicy().hasHeightForWidth());
        SettingsWidget->setSizePolicy(sizePolicy2);
        SettingsWidget->setMinimumSize(QSize(100, 100));
        SettingsWidget->setFocusPolicy(Qt::StrongFocus);

        TabsLayout->addWidget(SettingsWidget);

        SynchronizationWidget = new SynchronizationLayout(MainWidget);
        SynchronizationWidget->setObjectName(QStringLiteral("SynchronizationWidget"));
        sizePolicy2.setHeightForWidth(SynchronizationWidget->sizePolicy().hasHeightForWidth());
        SynchronizationWidget->setSizePolicy(sizePolicy2);
        SynchronizationWidget->setMinimumSize(QSize(100, 100));
        SynchronizationWidget->setFocusPolicy(Qt::StrongFocus);

        TabsLayout->addWidget(SynchronizationWidget);


        horizontalLayout->addLayout(TabsLayout);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(MainWidget);


        retranslateUi(MainWindow);

        min_button->setDefault(false);
        full_size_button->setDefault(false);
        exit_button->setDefault(false);
        Library->setDefault(true);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H

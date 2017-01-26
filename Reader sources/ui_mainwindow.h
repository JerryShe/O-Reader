/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "settings_layout.h"
#include "synchronization_layout.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *MainWidget;
    QVBoxLayout *verticalLayout;
    QWidget *TopBarWidget;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *min_button;
    QPushButton *full_size_button;
    QPushButton *exit_button;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *LeftMenu;
    QPushButton *Library;
    QPushButton *Settings;
    QPushButton *Synchronization;
    QWidget *LeftExpandingWidget;
    QPushButton *Logout;
    QVBoxLayout *TabsLayout;
    QVBoxLayout *ButtonsLayout;
    QHBoxLayout *LibraryButtons;
    QPushButton *_Find;
    QPushButton *_Sort;
    QComboBox *_SortBox;
    QPushButton *_Group;
    QComboBox *_GroupBox;
    QPushButton *_AddBooks;
    QPushButton *_Delete;
    QPushButton *_ChangeViewMode;
    QPushButton *_Upscale;
    QPushButton *_Downscale;
    settingslayout *SettingsLayout;
    synchronizationlayout *SynchronizationLayout;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->setEnabled(true);
        MainWindow->resize(1200, 710);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1060, 550));
        MainWindow->setFocusPolicy(Qt::NoFocus);
        MainWindow->setContextMenuPolicy(Qt::NoContextMenu);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        MainWindow->setAutoFillBackground(true);
        MainWindow->setStyleSheet(QLatin1String("MainWindow\n"
"{\n"
"background: none;\n"
"border: 10px solid grey; \n"
"outline: red solid 8px;\n"
"}"));
        MainWindow->setAnimated(true);
        MainWindow->setDockNestingEnabled(true);
        MainWindow->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks|QMainWindow::ForceTabbedDocks|QMainWindow::GroupedDragging|QMainWindow::VerticalTabs);
        MainWindow->setUnifiedTitleAndToolBarOnMac(true);
        MainWidget = new QWidget(MainWindow);
        MainWidget->setObjectName(QStringLiteral("MainWidget"));
        sizePolicy.setHeightForWidth(MainWidget->sizePolicy().hasHeightForWidth());
        MainWidget->setSizePolicy(sizePolicy);
        QFont font;
        font.setStyleStrategy(QFont::PreferAntialias);
        MainWidget->setFont(font);
        MainWidget->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(MainWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        TopBarWidget = new QWidget(MainWidget);
        TopBarWidget->setObjectName(QStringLiteral("TopBarWidget"));
        TopBarWidget->setMinimumSize(QSize(0, 25));
        TopBarWidget->setMaximumSize(QSize(16777215, 25));
        horizontalLayout_3 = new QHBoxLayout(TopBarWidget);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(1122, 4, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

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
        QFont font1;
        font1.setPointSize(40);
        min_button->setFont(font1);
        min_button->setStyleSheet(QStringLiteral(""));
        min_button->setText(QStringLiteral(""));
        min_button->setShortcut(QStringLiteral(""));
        min_button->setAutoDefault(false);
        min_button->setFlat(true);

        horizontalLayout_3->addWidget(min_button);

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
        full_size_button->setFont(font1);
        full_size_button->setStyleSheet(QStringLiteral(""));
        full_size_button->setText(QStringLiteral(""));
        full_size_button->setShortcut(QStringLiteral(""));
        full_size_button->setAutoDefault(false);
        full_size_button->setFlat(true);

        horizontalLayout_3->addWidget(full_size_button);

        exit_button = new QPushButton(TopBarWidget);
        exit_button->setObjectName(QStringLiteral("exit_button"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(exit_button->sizePolicy().hasHeightForWidth());
        exit_button->setSizePolicy(sizePolicy1);
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
        QFont font2;
        font2.setPointSize(12);
        exit_button->setFont(font2);
        exit_button->setStyleSheet(QStringLiteral(""));
        exit_button->setText(QStringLiteral(""));
        exit_button->setShortcut(QStringLiteral(""));
        exit_button->setAutoDefault(false);
        exit_button->setFlat(true);

        horizontalLayout_3->addWidget(exit_button);


        verticalLayout->addWidget(TopBarWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        LeftMenu = new QVBoxLayout();
        LeftMenu->setSpacing(0);
        LeftMenu->setObjectName(QStringLiteral("LeftMenu"));
        LeftMenu->setSizeConstraint(QLayout::SetDefaultConstraint);
        LeftMenu->setContentsMargins(0, 0, 0, -1);
        Library = new QPushButton(MainWidget);
        Library->setObjectName(QStringLiteral("Library"));
        sizePolicy1.setHeightForWidth(Library->sizePolicy().hasHeightForWidth());
        Library->setSizePolicy(sizePolicy1);
        Library->setMinimumSize(QSize(70, 100));
        Library->setMaximumSize(QSize(70, 100));
        Library->setStyleSheet(QStringLiteral(""));
        Library->setText(QStringLiteral(""));
        Library->setIconSize(QSize(90, 90));
        Library->setCheckable(true);
        Library->setAutoDefault(true);
        Library->setFlat(true);

        LeftMenu->addWidget(Library);

        Settings = new QPushButton(MainWidget);
        Settings->setObjectName(QStringLiteral("Settings"));
        sizePolicy1.setHeightForWidth(Settings->sizePolicy().hasHeightForWidth());
        Settings->setSizePolicy(sizePolicy1);
        Settings->setMinimumSize(QSize(70, 100));
        Settings->setMaximumSize(QSize(70, 100));
        Settings->setText(QStringLiteral(""));
        Settings->setCheckable(true);
        Settings->setFlat(true);

        LeftMenu->addWidget(Settings);

        Synchronization = new QPushButton(MainWidget);
        Synchronization->setObjectName(QStringLiteral("Synchronization"));
        sizePolicy1.setHeightForWidth(Synchronization->sizePolicy().hasHeightForWidth());
        Synchronization->setSizePolicy(sizePolicy1);
        Synchronization->setMinimumSize(QSize(70, 100));
        Synchronization->setMaximumSize(QSize(70, 100));
        Synchronization->setText(QStringLiteral(""));
        Synchronization->setCheckable(true);
        Synchronization->setFlat(true);

        LeftMenu->addWidget(Synchronization);

        LeftExpandingWidget = new QWidget(MainWidget);
        LeftExpandingWidget->setObjectName(QStringLiteral("LeftExpandingWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(LeftExpandingWidget->sizePolicy().hasHeightForWidth());
        LeftExpandingWidget->setSizePolicy(sizePolicy2);
        LeftExpandingWidget->setMinimumSize(QSize(70, 0));
        LeftExpandingWidget->setMaximumSize(QSize(70, 16777215));

        LeftMenu->addWidget(LeftExpandingWidget);

        Logout = new QPushButton(MainWidget);
        Logout->setObjectName(QStringLiteral("Logout"));
        sizePolicy1.setHeightForWidth(Logout->sizePolicy().hasHeightForWidth());
        Logout->setSizePolicy(sizePolicy1);
        Logout->setMinimumSize(QSize(70, 70));
        Logout->setMaximumSize(QSize(70, 70));
        Logout->setText(QStringLiteral(""));
        Logout->setCheckable(true);
        Logout->setFlat(true);

        LeftMenu->addWidget(Logout);


        horizontalLayout_2->addLayout(LeftMenu);

        TabsLayout = new QVBoxLayout();
        TabsLayout->setSpacing(0);
        TabsLayout->setObjectName(QStringLiteral("TabsLayout"));
        TabsLayout->setSizeConstraint(QLayout::SetFixedSize);
        TabsLayout->setContentsMargins(-1, -1, -1, 0);
        ButtonsLayout = new QVBoxLayout();
        ButtonsLayout->setSpacing(0);
        ButtonsLayout->setObjectName(QStringLiteral("ButtonsLayout"));
        ButtonsLayout->setSizeConstraint(QLayout::SetMinimumSize);
        LibraryButtons = new QHBoxLayout();
        LibraryButtons->setSpacing(0);
        LibraryButtons->setObjectName(QStringLiteral("LibraryButtons"));
        LibraryButtons->setSizeConstraint(QLayout::SetMinimumSize);
        LibraryButtons->setContentsMargins(-1, 0, -1, -1);
        _Find = new QPushButton(MainWidget);
        _Find->setObjectName(QStringLiteral("_Find"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(_Find->sizePolicy().hasHeightForWidth());
        _Find->setSizePolicy(sizePolicy3);
        _Find->setMinimumSize(QSize(120, 30));
        _Find->setMaximumSize(QSize(16777215, 30));
        _Find->setCheckable(true);

        LibraryButtons->addWidget(_Find);

        _Sort = new QPushButton(MainWidget);
        _Sort->setObjectName(QStringLiteral("_Sort"));
        _Sort->setMinimumSize(QSize(120, 30));
        _Sort->setMaximumSize(QSize(16777215, 30));
        _Sort->setStyleSheet(QStringLiteral(""));

        LibraryButtons->addWidget(_Sort);

        _SortBox = new QComboBox(MainWidget);
        _SortBox->setObjectName(QStringLiteral("_SortBox"));
        _SortBox->setMinimumSize(QSize(0, 30));
        _SortBox->setStyleSheet(QStringLiteral(""));
        _SortBox->setInsertPolicy(QComboBox::InsertAtTop);
        _SortBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        _SortBox->setIconSize(QSize(0, 0));
        _SortBox->setFrame(false);

        LibraryButtons->addWidget(_SortBox);

        _Group = new QPushButton(MainWidget);
        _Group->setObjectName(QStringLiteral("_Group"));
        _Group->setEnabled(false);
        _Group->setMinimumSize(QSize(120, 30));
        _Group->setMaximumSize(QSize(16777215, 30));

        LibraryButtons->addWidget(_Group);

        _GroupBox = new QComboBox(MainWidget);
        _GroupBox->setObjectName(QStringLiteral("_GroupBox"));
        _GroupBox->setEnabled(false);
        _GroupBox->setMinimumSize(QSize(101, 30));
        _GroupBox->setStyleSheet(QStringLiteral(""));
        _GroupBox->setInsertPolicy(QComboBox::InsertAtTop);
        _GroupBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        _GroupBox->setFrame(false);

        LibraryButtons->addWidget(_GroupBox);

        _AddBooks = new QPushButton(MainWidget);
        _AddBooks->setObjectName(QStringLiteral("_AddBooks"));
        sizePolicy3.setHeightForWidth(_AddBooks->sizePolicy().hasHeightForWidth());
        _AddBooks->setSizePolicy(sizePolicy3);
        _AddBooks->setMinimumSize(QSize(120, 30));
        _AddBooks->setMaximumSize(QSize(16777215, 30));

        LibraryButtons->addWidget(_AddBooks);

        _Delete = new QPushButton(MainWidget);
        _Delete->setObjectName(QStringLiteral("_Delete"));
        sizePolicy3.setHeightForWidth(_Delete->sizePolicy().hasHeightForWidth());
        _Delete->setSizePolicy(sizePolicy3);
        _Delete->setMinimumSize(QSize(120, 30));
        _Delete->setMaximumSize(QSize(16777215, 30));

        LibraryButtons->addWidget(_Delete);

        _ChangeViewMode = new QPushButton(MainWidget);
        _ChangeViewMode->setObjectName(QStringLiteral("_ChangeViewMode"));
        _ChangeViewMode->setMinimumSize(QSize(30, 30));
        _ChangeViewMode->setMaximumSize(QSize(30, 30));
        _ChangeViewMode->setText(QStringLiteral(""));
        _ChangeViewMode->setShortcut(QStringLiteral(""));
        _ChangeViewMode->setCheckable(true);

        LibraryButtons->addWidget(_ChangeViewMode);

        _Upscale = new QPushButton(MainWidget);
        _Upscale->setObjectName(QStringLiteral("_Upscale"));
        _Upscale->setMinimumSize(QSize(30, 30));
        _Upscale->setMaximumSize(QSize(30, 30));
        _Upscale->setText(QStringLiteral(""));
        _Upscale->setShortcut(QStringLiteral(""));

        LibraryButtons->addWidget(_Upscale);

        _Downscale = new QPushButton(MainWidget);
        _Downscale->setObjectName(QStringLiteral("_Downscale"));
        _Downscale->setMinimumSize(QSize(30, 30));
        _Downscale->setMaximumSize(QSize(30, 30));
        _Downscale->setText(QStringLiteral(""));
        _Downscale->setShortcut(QStringLiteral(""));

        LibraryButtons->addWidget(_Downscale);

        LibraryButtons->setStretch(0, 2);
        LibraryButtons->setStretch(1, 1);
        LibraryButtons->setStretch(2, 1);
        LibraryButtons->setStretch(3, 1);
        LibraryButtons->setStretch(4, 1);
        LibraryButtons->setStretch(5, 2);
        LibraryButtons->setStretch(6, 2);

        ButtonsLayout->addLayout(LibraryButtons);


        TabsLayout->addLayout(ButtonsLayout);

        SettingsLayout = new settingslayout(MainWidget);
        SettingsLayout->setObjectName(QStringLiteral("SettingsLayout"));
        sizePolicy.setHeightForWidth(SettingsLayout->sizePolicy().hasHeightForWidth());
        SettingsLayout->setSizePolicy(sizePolicy);
        SettingsLayout->setMinimumSize(QSize(100, 100));

        TabsLayout->addWidget(SettingsLayout);

        SynchronizationLayout = new synchronizationlayout(MainWidget);
        SynchronizationLayout->setObjectName(QStringLiteral("SynchronizationLayout"));
        sizePolicy.setHeightForWidth(SynchronizationLayout->sizePolicy().hasHeightForWidth());
        SynchronizationLayout->setSizePolicy(sizePolicy);
        SynchronizationLayout->setMinimumSize(QSize(100, 100));

        TabsLayout->addWidget(SynchronizationLayout);


        horizontalLayout_2->addLayout(TabsLayout);


        verticalLayout->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(MainWidget);
        QWidget::setTabOrder(Library, Settings);
        QWidget::setTabOrder(Settings, Synchronization);
        QWidget::setTabOrder(Synchronization, Logout);

        retranslateUi(MainWindow);

        min_button->setDefault(false);
        full_size_button->setDefault(false);
        exit_button->setDefault(false);
        Library->setDefault(true);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Reader", 0));
        _Find->setText(QApplication::translate("MainWindow", "Find", 0));
        _Sort->setText(QApplication::translate("MainWindow", "Sort by: ", 0));
        _SortBox->clear();
        _SortBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Date", 0)
         << QApplication::translate("MainWindow", "Author", 0)
         << QApplication::translate("MainWindow", "Title", 0)
        );
        _Group->setText(QApplication::translate("MainWindow", "Group by: ", 0));
        _GroupBox->clear();
        _GroupBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "None", 0)
         << QApplication::translate("MainWindow", "Author", 0)
         << QApplication::translate("MainWindow", "Title", 0)
         << QApplication::translate("MainWindow", "Genre", 0)
         << QApplication::translate("MainWindow", "Book series", 0)
        );
        _AddBooks->setText(QApplication::translate("MainWindow", "Add", 0));
        _Delete->setText(QApplication::translate("MainWindow", "Delete", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

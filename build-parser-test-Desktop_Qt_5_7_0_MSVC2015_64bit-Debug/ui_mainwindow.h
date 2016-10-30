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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "librarylayout.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *MainWidget;
    QFormLayout *MainLayout;
    QHBoxLayout *TopButtons;
    QSpacerItem *horizontalSpacer;
    QPushButton *min_button;
    QPushButton *full_size_button;
    QPushButton *exit_button;
    QSpacerItem *TopSpaser;
    QVBoxLayout *LeftMenu;
    QFrame *MenuLine;
    QPushButton *Library;
    QPushButton *Settings;
    QPushButton *Synchronization;
    QSpacerItem *MenuSpacer;
    QPushButton *Logout;
    QVBoxLayout *LibraryWindowLayout;
    QHBoxLayout *LibraryButtons;
    QPushButton *ListView;
    QPushButton *TableView;
    QComboBox *Sort;
    QPushButton *AddBook;
    QPushButton *AddFolder;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout;
    librarylayout *LibraryLayout;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1200, 710);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QPalette palette;
        QBrush brush(QColor(255, 196, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(255, 170, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        MainWindow->setPalette(palette);
        MainWindow->setContextMenuPolicy(Qt::PreventContextMenu);
        MainWindow->setStyleSheet(QStringLiteral(""));
        MainWidget = new QWidget(MainWindow);
        MainWidget->setObjectName(QStringLiteral("MainWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(MainWidget->sizePolicy().hasHeightForWidth());
        MainWidget->setSizePolicy(sizePolicy1);
        MainWidget->setStyleSheet(QStringLiteral("#MainWidget {background-color:rgb(162, 0, 70);}"));
        MainLayout = new QFormLayout(MainWidget);
        MainLayout->setSpacing(6);
        MainLayout->setContentsMargins(11, 11, 11, 11);
        MainLayout->setObjectName(QStringLiteral("MainLayout"));
        MainLayout->setSizeConstraint(QLayout::SetNoConstraint);
        MainLayout->setHorizontalSpacing(0);
        MainLayout->setVerticalSpacing(2);
        MainLayout->setContentsMargins(0, 5, 2, 0);
        TopButtons = new QHBoxLayout();
        TopButtons->setSpacing(10);
        TopButtons->setObjectName(QStringLiteral("TopButtons"));
        TopButtons->setSizeConstraint(QLayout::SetNoConstraint);
        TopButtons->setContentsMargins(-1, -1, 10, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        TopButtons->addItem(horizontalSpacer);

        min_button = new QPushButton(MainWidget);
        min_button->setObjectName(QStringLiteral("min_button"));
        min_button->setMinimumSize(QSize(20, 20));
        min_button->setMaximumSize(QSize(20, 20));
        QPalette palette1;
        QBrush brush2(QColor(255, 255, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        QBrush brush3(QColor(255, 0, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Highlight, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Link, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Highlight, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Link, brush3);
        QBrush brush4(QColor(120, 120, 120, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Highlight, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Link, brush3);
        min_button->setPalette(palette1);
        QFont font;
        font.setPointSize(40);
        min_button->setFont(font);
        min_button->setStyleSheet(QLatin1String("#min_button\n"
"{\n"
"	border-image: url(:min.png);\n"
"	border: none;\n"
"	background:none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"#min_button:hover \n"
"{\n"
"	background-color:rgb(150, 0, 65);\n"
"}"));
        min_button->setShortcut(QStringLiteral(""));
        min_button->setAutoDefault(false);
        min_button->setFlat(true);

        TopButtons->addWidget(min_button);

        full_size_button = new QPushButton(MainWidget);
        full_size_button->setObjectName(QStringLiteral("full_size_button"));
        full_size_button->setMinimumSize(QSize(20, 20));
        full_size_button->setMaximumSize(QSize(20, 20));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette2.setBrush(QPalette::Active, QPalette::Highlight, brush3);
        palette2.setBrush(QPalette::Active, QPalette::Link, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::Highlight, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::Link, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::Highlight, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::Link, brush3);
        full_size_button->setPalette(palette2);
        full_size_button->setFont(font);
        full_size_button->setStyleSheet(QLatin1String("#full_size_button\n"
"{\n"
"	border-image: url(:full_size.png);\n"
"	border: none;\n"
"	background:none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"#full_size_button:hover \n"
"{\n"
"	background-color:rgb(150, 0, 65);\n"
"}"));
        full_size_button->setShortcut(QStringLiteral(""));
        full_size_button->setAutoDefault(false);
        full_size_button->setFlat(true);

        TopButtons->addWidget(full_size_button);

        exit_button = new QPushButton(MainWidget);
        exit_button->setObjectName(QStringLiteral("exit_button"));
        exit_button->setMinimumSize(QSize(20, 20));
        exit_button->setMaximumSize(QSize(20, 20));
        exit_button->setSizeIncrement(QSize(1, 1));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette3.setBrush(QPalette::Active, QPalette::Highlight, brush3);
        palette3.setBrush(QPalette::Active, QPalette::Link, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::Highlight, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::Link, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::Highlight, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::Link, brush3);
        exit_button->setPalette(palette3);
        QFont font1;
        font1.setPointSize(12);
        exit_button->setFont(font1);
        exit_button->setStyleSheet(QLatin1String("#exit_button\n"
"{\n"
"	border-image: url(:exit.png);\n"
"	border: none;\n"
"	background:none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"#exit_button:hover \n"
"{\n"
"	background-color:rgb(203, 0, 88);\n"
"}"));
        exit_button->setShortcut(QStringLiteral(""));
        exit_button->setAutoDefault(false);
        exit_button->setFlat(true);

        TopButtons->addWidget(exit_button);


        MainLayout->setLayout(0, QFormLayout::FieldRole, TopButtons);

        TopSpaser = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        MainLayout->setItem(1, QFormLayout::FieldRole, TopSpaser);

        LeftMenu = new QVBoxLayout();
        LeftMenu->setSpacing(0);
        LeftMenu->setObjectName(QStringLiteral("LeftMenu"));
        LeftMenu->setSizeConstraint(QLayout::SetFixedSize);
        LeftMenu->setContentsMargins(0, 0, 0, -1);
        MenuLine = new QFrame(MainWidget);
        MenuLine->setObjectName(QStringLiteral("MenuLine"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(MenuLine->sizePolicy().hasHeightForWidth());
        MenuLine->setSizePolicy(sizePolicy2);
        MenuLine->setMinimumSize(QSize(90, 1));
        MenuLine->setMaximumSize(QSize(90, 1));
        QPalette palette4;
        MenuLine->setPalette(palette4);
        MenuLine->setStyleSheet(QLatin1String("#line\n"
"{\n"
"\n"
" border-style: groove none none none;\n"
" border-color:rgb(130, 0, 60);\n"
" border-width: 1px;\n"
"}"));
        MenuLine->setFrameShadow(QFrame::Raised);
        MenuLine->setLineWidth(0);
        MenuLine->setMidLineWidth(0);
        MenuLine->setFrameShape(QFrame::HLine);

        LeftMenu->addWidget(MenuLine);

        Library = new QPushButton(MainWidget);
        Library->setObjectName(QStringLiteral("Library"));
        sizePolicy2.setHeightForWidth(Library->sizePolicy().hasHeightForWidth());
        Library->setSizePolicy(sizePolicy2);
        Library->setMinimumSize(QSize(90, 120));
        Library->setMaximumSize(QSize(90, 120));
        Library->setStyleSheet(QStringLiteral(""));
        Library->setIconSize(QSize(90, 90));
        Library->setAutoDefault(true);
        Library->setFlat(true);

        LeftMenu->addWidget(Library);

        Settings = new QPushButton(MainWidget);
        Settings->setObjectName(QStringLiteral("Settings"));
        sizePolicy2.setHeightForWidth(Settings->sizePolicy().hasHeightForWidth());
        Settings->setSizePolicy(sizePolicy2);
        Settings->setMinimumSize(QSize(90, 120));
        Settings->setMaximumSize(QSize(90, 120));
        Settings->setStyleSheet(QStringLiteral(""));
        Settings->setFlat(true);

        LeftMenu->addWidget(Settings);

        Synchronization = new QPushButton(MainWidget);
        Synchronization->setObjectName(QStringLiteral("Synchronization"));
        sizePolicy2.setHeightForWidth(Synchronization->sizePolicy().hasHeightForWidth());
        Synchronization->setSizePolicy(sizePolicy2);
        Synchronization->setMinimumSize(QSize(90, 120));
        Synchronization->setMaximumSize(QSize(90, 120));
        Synchronization->setStyleSheet(QStringLiteral(""));
        Synchronization->setFlat(true);

        LeftMenu->addWidget(Synchronization);

        MenuSpacer = new QSpacerItem(20, 12000, QSizePolicy::Minimum, QSizePolicy::Expanding);

        LeftMenu->addItem(MenuSpacer);

        Logout = new QPushButton(MainWidget);
        Logout->setObjectName(QStringLiteral("Logout"));
        sizePolicy2.setHeightForWidth(Logout->sizePolicy().hasHeightForWidth());
        Logout->setSizePolicy(sizePolicy2);
        Logout->setMinimumSize(QSize(90, 90));
        Logout->setMaximumSize(QSize(90, 90));
        Logout->setStyleSheet(QStringLiteral(""));
        Logout->setFlat(true);

        LeftMenu->addWidget(Logout);


        MainLayout->setLayout(2, QFormLayout::LabelRole, LeftMenu);

        LibraryWindowLayout = new QVBoxLayout();
        LibraryWindowLayout->setSpacing(0);
        LibraryWindowLayout->setObjectName(QStringLiteral("LibraryWindowLayout"));
        LibraryWindowLayout->setSizeConstraint(QLayout::SetMinimumSize);
        LibraryButtons = new QHBoxLayout();
        LibraryButtons->setSpacing(0);
        LibraryButtons->setObjectName(QStringLiteral("LibraryButtons"));
        LibraryButtons->setSizeConstraint(QLayout::SetMinimumSize);
        LibraryButtons->setContentsMargins(-1, 0, -1, -1);
        ListView = new QPushButton(MainWidget);
        ListView->setObjectName(QStringLiteral("ListView"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(ListView->sizePolicy().hasHeightForWidth());
        ListView->setSizePolicy(sizePolicy3);
        ListView->setMinimumSize(QSize(0, 30));
        ListView->setMaximumSize(QSize(16777215, 30));

        LibraryButtons->addWidget(ListView);

        TableView = new QPushButton(MainWidget);
        TableView->setObjectName(QStringLiteral("TableView"));
        sizePolicy3.setHeightForWidth(TableView->sizePolicy().hasHeightForWidth());
        TableView->setSizePolicy(sizePolicy3);
        TableView->setMinimumSize(QSize(0, 30));
        TableView->setMaximumSize(QSize(16777215, 30));
        TableView->setSizeIncrement(QSize(0, 40));

        LibraryButtons->addWidget(TableView);

        Sort = new QComboBox(MainWidget);
        Sort->setObjectName(QStringLiteral("Sort"));
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(Sort->sizePolicy().hasHeightForWidth());
        Sort->setSizePolicy(sizePolicy4);
        Sort->setMinimumSize(QSize(150, 30));
        Sort->setMaximumSize(QSize(16777215, 30));
        Sort->setFrame(false);

        LibraryButtons->addWidget(Sort);

        AddBook = new QPushButton(MainWidget);
        AddBook->setObjectName(QStringLiteral("AddBook"));
        sizePolicy3.setHeightForWidth(AddBook->sizePolicy().hasHeightForWidth());
        AddBook->setSizePolicy(sizePolicy3);
        AddBook->setMinimumSize(QSize(0, 30));
        AddBook->setMaximumSize(QSize(16777215, 30));

        LibraryButtons->addWidget(AddBook);

        AddFolder = new QPushButton(MainWidget);
        AddFolder->setObjectName(QStringLiteral("AddFolder"));
        sizePolicy3.setHeightForWidth(AddFolder->sizePolicy().hasHeightForWidth());
        AddFolder->setSizePolicy(sizePolicy3);
        AddFolder->setMinimumSize(QSize(0, 30));
        AddFolder->setMaximumSize(QSize(16777215, 30));

        LibraryButtons->addWidget(AddFolder);


        LibraryWindowLayout->addLayout(LibraryButtons);

        scrollArea = new QScrollArea(MainWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setStyleSheet(QLatin1String("#scrollArea\n"
"{\n"
"	background-color:rgb(170, 0, 73);\n"
"	color: white;\n"
"\n"
"}"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setFrameShadow(QFrame::Plain);
        scrollArea->setLineWidth(0);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        scrollArea->setWidgetResizable(false);
        scrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1102, 643));
        scrollAreaWidgetContents->setStyleSheet(QLatin1String("#scrollAreazwidgetContens\n"
"{\n"
"	background-color:rgb(170, 0, 73);\n"
"	color: white;\n"
"}"));
        horizontalLayout = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        LibraryLayout = new librarylayout(scrollAreaWidgetContents);
        LibraryLayout->setObjectName(QStringLiteral("LibraryLayout"));
        LibraryLayout->setMinimumSize(QSize(0, 20));
        LibraryLayout->setStyleSheet(QLatin1String("#LibraryLayout\n"
"{\n"
"	background-color:rgb(170, 0, 73);\n"
"	color: white;\n"
"\n"
"}"));

        horizontalLayout->addWidget(LibraryLayout);

        scrollArea->setWidget(scrollAreaWidgetContents);
        LibraryLayout->raise();
        LibraryLayout->raise();

        LibraryWindowLayout->addWidget(scrollArea);


        MainLayout->setLayout(2, QFormLayout::FieldRole, LibraryWindowLayout);

        MainWindow->setCentralWidget(MainWidget);
        QWidget::setTabOrder(exit_button, full_size_button);
        QWidget::setTabOrder(full_size_button, min_button);
        QWidget::setTabOrder(min_button, Library);
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        min_button->setText(QString());
        full_size_button->setText(QString());
        exit_button->setText(QString());
        Library->setText(QString());
        Settings->setText(QString());
        Synchronization->setText(QString());
        Logout->setText(QString());
        ListView->setText(QApplication::translate("MainWindow", "List view", 0));
        TableView->setText(QApplication::translate("MainWindow", "Table view", 0));
        AddBook->setText(QApplication::translate("MainWindow", "Add book", 0));
        AddFolder->setText(QApplication::translate("MainWindow", "Add folder", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

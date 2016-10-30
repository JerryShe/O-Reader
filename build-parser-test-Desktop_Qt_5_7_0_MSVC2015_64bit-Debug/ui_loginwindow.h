/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QWidget *MainWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *TopButtons;
    QSpacerItem *horizontalSpacer;
    QPushButton *min_button;
    QPushButton *full_size_button;
    QPushButton *exit_button;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QLineEdit *Name;
    QLineEdit *Pass;
    QHBoxLayout *horizontalLayout;
    QCheckBox *Remember;
    QLabel *Forgot;
    QPushButton *login;
    QLabel *Registration;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QStringLiteral("LoginWindow"));
        LoginWindow->resize(1200, 710);
        LoginWindow->setToolButtonStyle(Qt::ToolButtonFollowStyle);
        LoginWindow->setAnimated(false);
        MainWidget = new QWidget(LoginWindow);
        MainWidget->setObjectName(QStringLiteral("MainWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWidget->sizePolicy().hasHeightForWidth());
        MainWidget->setSizePolicy(sizePolicy);
        MainWidget->setStyleSheet(QStringLiteral("#MainWidget {background-color:rgb(162, 0, 70);}"));
        gridLayout = new QGridLayout(MainWidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(2, 5, 2, 2);
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


        gridLayout->addLayout(TopButtons, 0, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(20);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        verticalSpacer_2 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        Name = new QLineEdit(MainWidget);
        Name->setObjectName(QStringLiteral("Name"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Name->sizePolicy().hasHeightForWidth());
        Name->setSizePolicy(sizePolicy1);
        Name->setMinimumSize(QSize(400, 35));
        Name->setMaximumSize(QSize(350, 35));
        QFont font2;
        font2.setPointSize(10);
        Name->setFont(font2);
        Name->setStyleSheet(QLatin1String("#Name\n"
"{\n"
"	background-color:rgb(130, 0, 55);\n"
"	color: white;\n"
"}"));
        Name->setFrame(false);
        Name->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(Name);

        Pass = new QLineEdit(MainWidget);
        Pass->setObjectName(QStringLiteral("Pass"));
        Pass->setMinimumSize(QSize(400, 35));
        Pass->setMaximumSize(QSize(350, 25));
        QPalette palette3;
        QBrush brush3(QColor(255, 255, 255, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        QBrush brush4(QColor(130, 0, 55, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush4);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush3);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush3);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush4);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush4);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush4);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush4);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush4);
        Pass->setPalette(palette3);
        Pass->setFont(font2);
        Pass->setStyleSheet(QLatin1String("#Pass\n"
"{\n"
"	background-color:rgb(130, 0, 55);\n"
"	color: white;\n"
"}"));
        Pass->setInputMask(QStringLiteral(""));
        Pass->setText(QStringLiteral(""));
        Pass->setFrame(false);
        Pass->setEchoMode(QLineEdit::Password);
        Pass->setAlignment(Qt::AlignCenter);
        Pass->setPlaceholderText(QStringLiteral("password"));

        verticalLayout->addWidget(Pass);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        Remember = new QCheckBox(MainWidget);
        Remember->setObjectName(QStringLiteral("Remember"));
        Remember->setMinimumSize(QSize(0, 20));
        Remember->setMaximumSize(QSize(16777215, 16777215));
        Remember->setStyleSheet(QLatin1String("#Remember\n"
"{\n"
"	color: white;\n"
"}\n"
"\n"
"#Remember:hover\n"
"{\n"
"	color: rgb(151, 151, 227);\n"
"}\n"
"\n"
"#Remember::indicator:off\n"
"{\n"
"	image: url(:check_no.png);\n"
"}\n"
"\n"
"#Remember::indicator:on\n"
"{\n"
"	image: url(:check_ok.png);\n"
"}\n"
""));
        Remember->setText(QStringLiteral("Remember my password"));
        Remember->setIconSize(QSize(20, 20));
        Remember->setShortcut(QStringLiteral(""));
        Remember->setChecked(true);
        Remember->setAutoRepeat(true);
        Remember->setAutoExclusive(true);
        Remember->setTristate(false);

        horizontalLayout->addWidget(Remember);

        Forgot = new QLabel(MainWidget);
        Forgot->setObjectName(QStringLiteral("Forgot"));
        Forgot->setMinimumSize(QSize(0, 0));
        Forgot->setMaximumSize(QSize(120, 16777215));
        Forgot->setStyleSheet(QLatin1String("#Forgot\n"
"{\n"
"	color: white;\n"
"}\n"
"\n"
"#Forgot:hover\n"
"{\n"
"	color: rgb(151, 151, 227);\n"
"}"));
        Forgot->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(Forgot);


        verticalLayout->addLayout(horizontalLayout);

        login = new QPushButton(MainWidget);
        login->setObjectName(QStringLiteral("login"));
        sizePolicy1.setHeightForWidth(login->sizePolicy().hasHeightForWidth());
        login->setSizePolicy(sizePolicy1);
        login->setMinimumSize(QSize(400, 40));
        login->setMaximumSize(QSize(400, 25));
        QFont font3;
        font3.setFamily(QStringLiteral("DejaVu Sans Light"));
        font3.setPointSize(14);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setWeight(50);
        font3.setKerning(false);
        font3.setStyleStrategy(QFont::PreferAntialias);
        login->setFont(font3);
        login->setStyleSheet(QLatin1String("#login{\n"
"	background-color:rgb(151, 151, 227);\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"#login:hover\n"
"{\n"
"	background-color:rgb(130, 130, 195);\n"
"}"));
        login->setText(QStringLiteral("Log in"));
        login->setShortcut(QStringLiteral(""));
        login->setAutoDefault(false);
        login->setFlat(true);

        verticalLayout->addWidget(login);

        Registration = new QLabel(MainWidget);
        Registration->setObjectName(QStringLiteral("Registration"));
        Registration->setMinimumSize(QSize(0, 0));
        Registration->setMaximumSize(QSize(100, 16777215));
        Registration->setStyleSheet(QLatin1String("#Registration\n"
"{\n"
"	color: white;\n"
"}\n"
"\n"
"#Registration:hover\n"
"{\n"
"	color: rgb(151, 151, 227);\n"
"}"));
        Registration->setScaledContents(false);
        Registration->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(Registration);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);

        LoginWindow->setCentralWidget(MainWidget);

        retranslateUi(LoginWindow);

        min_button->setDefault(false);
        full_size_button->setDefault(false);
        exit_button->setDefault(false);
        login->setDefault(false);


        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QApplication::translate("LoginWindow", "MainWindow", 0));
        min_button->setText(QString());
        full_size_button->setText(QString());
        exit_button->setText(QString());
        Name->setInputMask(QString());
        Name->setText(QString());
        Name->setPlaceholderText(QApplication::translate("LoginWindow", "email", 0));
        Forgot->setText(QApplication::translate("LoginWindow", "Forgot your password?", 0));
        Registration->setText(QApplication::translate("LoginWindow", "Create account", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H

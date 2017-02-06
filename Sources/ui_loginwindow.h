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
    QSpacerItem *topRightHorizontalSpacer;
    QPushButton *min_button;
    QPushButton *full_size_button;
    QPushButton *exit_button;
    QSpacerItem *leftHorizontalSpacer;
    QSpacerItem *rightHorizontalSpacer;
    QSpacerItem *topLeftHorizontalSpacer;
    QVBoxLayout *verticalLayout;
    QSpacerItem *topVerticalSpacer;
    QLabel *Error;
    QLineEdit *Name;
    QLineEdit *Pass;
    QLineEdit *repeatPassword;
    QHBoxLayout *horizontalLayout;
    QCheckBox *Remember;
    QSpacerItem *horizontalSpacer;
    QPushButton *Recovery;
    QPushButton *login;
    QPushButton *Registration;
    QSpacerItem *bottomVerticalSpacer;

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
        MainWidget->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(MainWidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(2, 0, 0, 2);
        TopButtons = new QHBoxLayout();
        TopButtons->setSpacing(0);
        TopButtons->setObjectName(QStringLiteral("TopButtons"));
        TopButtons->setSizeConstraint(QLayout::SetNoConstraint);
        TopButtons->setContentsMargins(-1, -1, 0, 5);
        topRightHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        TopButtons->addItem(topRightHorizontalSpacer);

        min_button = new QPushButton(MainWidget);
        min_button->setObjectName(QStringLiteral("min_button"));
        min_button->setMinimumSize(QSize(25, 25));
        min_button->setMaximumSize(QSize(25, 25));
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
        full_size_button->setMinimumSize(QSize(25, 25));
        full_size_button->setMaximumSize(QSize(25, 25));
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
        exit_button->setMinimumSize(QSize(25, 25));
        exit_button->setMaximumSize(QSize(25, 25));
        exit_button->setSizeIncrement(QSize(1, 1));
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

        leftHorizontalSpacer = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(leftHorizontalSpacer, 1, 0, 1, 1);

        rightHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(rightHorizontalSpacer, 1, 2, 1, 1);

        topLeftHorizontalSpacer = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(topLeftHorizontalSpacer, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(20);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout->setContentsMargins(0, -1, -1, -1);
        topVerticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(topVerticalSpacer);

        Error = new QLabel(MainWidget);
        Error->setObjectName(QStringLiteral("Error"));
        Error->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(Error);

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
        font2.setKerning(true);
        font2.setStyleStrategy(QFont::PreferAntialias);
        Name->setFont(font2);
        Name->setStyleSheet(QStringLiteral(""));
        Name->setFrame(false);
        Name->setAlignment(Qt::AlignCenter);
        Name->setCursorMoveStyle(Qt::LogicalMoveStyle);

        verticalLayout->addWidget(Name);

        Pass = new QLineEdit(MainWidget);
        Pass->setObjectName(QStringLiteral("Pass"));
        Pass->setMinimumSize(QSize(400, 35));
        Pass->setMaximumSize(QSize(350, 35));
        QFont font3;
        font3.setPointSize(10);
        font3.setStyleStrategy(QFont::PreferAntialias);
        Pass->setFont(font3);
        Pass->setStyleSheet(QStringLiteral(""));
        Pass->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        Pass->setInputMask(QStringLiteral(""));
        Pass->setText(QStringLiteral(""));
        Pass->setFrame(false);
        Pass->setEchoMode(QLineEdit::Password);
        Pass->setAlignment(Qt::AlignCenter);
        Pass->setReadOnly(false);

        verticalLayout->addWidget(Pass);

        repeatPassword = new QLineEdit(MainWidget);
        repeatPassword->setObjectName(QStringLiteral("repeatPassword"));
        repeatPassword->setMinimumSize(QSize(400, 35));
        repeatPassword->setMaximumSize(QSize(400, 35));
        repeatPassword->setFont(font3);
        repeatPassword->setInputMask(QStringLiteral(""));
        repeatPassword->setText(QStringLiteral(""));
        repeatPassword->setFrame(false);
        repeatPassword->setEchoMode(QLineEdit::Password);
        repeatPassword->setAlignment(Qt::AlignCenter);
        repeatPassword->setReadOnly(false);

        verticalLayout->addWidget(repeatPassword);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        horizontalLayout->setContentsMargins(-1, 1, -1, -1);
        Remember = new QCheckBox(MainWidget);
        Remember->setObjectName(QStringLiteral("Remember"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(Remember->sizePolicy().hasHeightForWidth());
        Remember->setSizePolicy(sizePolicy2);
        Remember->setMinimumSize(QSize(145, 22));
        Remember->setMaximumSize(QSize(150, 22));
        QFont font4;
        font4.setStyleStrategy(QFont::PreferAntialias);
        Remember->setFont(font4);
        Remember->setLayoutDirection(Qt::LeftToRight);
        Remember->setStyleSheet(QStringLiteral(""));
        Remember->setIconSize(QSize(20, 20));
        Remember->setShortcut(QStringLiteral(""));
        Remember->setChecked(true);
        Remember->setAutoRepeat(true);
        Remember->setAutoExclusive(true);
        Remember->setTristate(false);

        horizontalLayout->addWidget(Remember);

        horizontalSpacer = new QSpacerItem(128, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        Recovery = new QPushButton(MainWidget);
        Recovery->setObjectName(QStringLiteral("Recovery"));
        sizePolicy1.setHeightForWidth(Recovery->sizePolicy().hasHeightForWidth());
        Recovery->setSizePolicy(sizePolicy1);
        Recovery->setMinimumSize(QSize(120, 22));
        Recovery->setMaximumSize(QSize(120, 22));
        Recovery->setFont(font4);
        Recovery->setLayoutDirection(Qt::LeftToRight);
        Recovery->setStyleSheet(QStringLiteral(""));
        Recovery->setFlat(true);

        horizontalLayout->addWidget(Recovery);


        verticalLayout->addLayout(horizontalLayout);

        login = new QPushButton(MainWidget);
        login->setObjectName(QStringLiteral("login"));
        sizePolicy1.setHeightForWidth(login->sizePolicy().hasHeightForWidth());
        login->setSizePolicy(sizePolicy1);
        login->setMinimumSize(QSize(400, 35));
        login->setMaximumSize(QSize(400, 35));
        QFont font5;
        font5.setFamily(QStringLiteral("DejaVu Sans Light"));
        font5.setPointSize(14);
        font5.setBold(false);
        font5.setItalic(false);
        font5.setWeight(50);
        font5.setKerning(false);
        font5.setStyleStrategy(QFont::PreferAntialias);
        login->setFont(font5);
        login->setStyleSheet(QStringLiteral(""));
        login->setShortcut(QStringLiteral(""));
        login->setAutoDefault(false);
        login->setFlat(true);

        verticalLayout->addWidget(login);

        Registration = new QPushButton(MainWidget);
        Registration->setObjectName(QStringLiteral("Registration"));
        Registration->setMinimumSize(QSize(160, 18));
        Registration->setMaximumSize(QSize(80, 20));
        Registration->setFont(font4);
        Registration->setLayoutDirection(Qt::LeftToRight);
        Registration->setAutoDefault(false);
        Registration->setFlat(true);

        verticalLayout->addWidget(Registration);

        bottomVerticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayout->addItem(bottomVerticalSpacer);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);

        gridLayout->setColumnMinimumWidth(0, 100);
        LoginWindow->setCentralWidget(MainWidget);

        retranslateUi(LoginWindow);

        min_button->setDefault(false);
        full_size_button->setDefault(false);
        exit_button->setDefault(false);
        login->setDefault(false);
        Registration->setDefault(false);


        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QApplication::translate("LoginWindow", "Reader", 0));
        min_button->setText(QString());
        full_size_button->setText(QString());
        exit_button->setText(QString());
        Error->setText(QApplication::translate("LoginWindow", "Error!", 0));
        Name->setInputMask(QString());
        Name->setText(QString());
        Name->setPlaceholderText(QApplication::translate("LoginWindow", "email", 0));
        Pass->setPlaceholderText(QApplication::translate("LoginWindow", "password", 0));
        repeatPassword->setPlaceholderText(QApplication::translate("LoginWindow", "confirm password", 0));
        Remember->setText(QApplication::translate("LoginWindow", "Remember my password", 0));
        Recovery->setText(QApplication::translate("LoginWindow", "Forgot your password?", 0));
        login->setText(QApplication::translate("LoginWindow", "Log in", 0));
        Registration->setText(QApplication::translate("LoginWindow", "Create account", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H

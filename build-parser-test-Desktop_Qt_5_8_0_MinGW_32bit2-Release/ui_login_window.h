/********************************************************************************
** Form generated from reading UI file 'login_window.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_WINDOW_H
#define UI_LOGIN_WINDOW_H

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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QGridLayout *gridLayout;
    QWidget *MainWidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *TopButtons;
    QSpacerItem *topRightHorizontalSpacer;
    QPushButton *min_button;
    QPushButton *full_size_button;
    QPushButton *exit_button;
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
    QSpacerItem *rightHorizontalSpacer;

    void setupUi(QWidget *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QStringLiteral("LoginWindow"));
        LoginWindow->resize(959, 596);
        gridLayout = new QGridLayout(LoginWindow);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        MainWidget = new QWidget(LoginWindow);
        MainWidget->setObjectName(QStringLiteral("MainWidget"));
        gridLayout_2 = new QGridLayout(MainWidget);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(3, 3, 3, 3);
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


        gridLayout_2->addLayout(TopButtons, 0, 3, 1, 1);

        topLeftHorizontalSpacer = new QSpacerItem(276, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(topLeftHorizontalSpacer, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(20);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout->setContentsMargins(0, -1, -1, -1);
        topVerticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(topVerticalSpacer);

        Error = new QLabel(MainWidget);
        Error->setObjectName(QStringLiteral("Error"));
        Error->setFont(font1);
        Error->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(Error);

        Name = new QLineEdit(MainWidget);
        Name->setObjectName(QStringLiteral("Name"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Name->sizePolicy().hasHeightForWidth());
        Name->setSizePolicy(sizePolicy);
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
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Remember->sizePolicy().hasHeightForWidth());
        Remember->setSizePolicy(sizePolicy1);
        Remember->setMinimumSize(QSize(175, 22));
        Remember->setMaximumSize(QSize(175, 22));
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

        horizontalSpacer = new QSpacerItem(128, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        Recovery = new QPushButton(MainWidget);
        Recovery->setObjectName(QStringLiteral("Recovery"));
        sizePolicy.setHeightForWidth(Recovery->sizePolicy().hasHeightForWidth());
        Recovery->setSizePolicy(sizePolicy);
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
        sizePolicy.setHeightForWidth(login->sizePolicy().hasHeightForWidth());
        login->setSizePolicy(sizePolicy);
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


        gridLayout_2->addLayout(verticalLayout, 1, 1, 1, 1);

        rightHorizontalSpacer = new QSpacerItem(275, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(rightHorizontalSpacer, 1, 2, 1, 2);


        gridLayout->addWidget(MainWidget, 0, 0, 1, 1);


        retranslateUi(LoginWindow);

        min_button->setDefault(false);
        full_size_button->setDefault(false);
        exit_button->setDefault(false);
        login->setDefault(false);
        Registration->setDefault(false);


        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QWidget *LoginWindow)
    {
        LoginWindow->setWindowTitle(QApplication::translate("LoginWindow", "Form", Q_NULLPTR));
        min_button->setText(QString());
        full_size_button->setText(QString());
        exit_button->setText(QString());
        Error->setText(QApplication::translate("LoginWindow", "Error!", Q_NULLPTR));
        Name->setInputMask(QString());
        Name->setText(QString());
        Name->setPlaceholderText(QApplication::translate("LoginWindow", "email", Q_NULLPTR));
        Pass->setPlaceholderText(QApplication::translate("LoginWindow", "password", Q_NULLPTR));
        repeatPassword->setPlaceholderText(QApplication::translate("LoginWindow", "confirm password", Q_NULLPTR));
        Remember->setText(QApplication::translate("LoginWindow", "Remember my password", Q_NULLPTR));
        Recovery->setText(QApplication::translate("LoginWindow", "Forgot your password?", Q_NULLPTR));
        login->setText(QApplication::translate("LoginWindow", "Log in", Q_NULLPTR));
        Registration->setText(QApplication::translate("LoginWindow", "Create account", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_WINDOW_H

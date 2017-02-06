/********************************************************************************
** Form generated from reading UI file 'settings_profilelayout.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_PROFILELAYOUT_H
#define UI_SETTINGS_PROFILELAYOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Settings_ProfileLayout
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label_2;
    QPushButton *ChangePasswordButton;
    QFrame *line_63;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *SaveButton;

    void setupUi(QFrame *Settings_ProfileLayout)
    {
        if (Settings_ProfileLayout->objectName().isEmpty())
            Settings_ProfileLayout->setObjectName(QStringLiteral("Settings_ProfileLayout"));
        Settings_ProfileLayout->resize(959, 646);
        Settings_ProfileLayout->setFrameShape(QFrame::NoFrame);
        Settings_ProfileLayout->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(Settings_ProfileLayout);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(30, 20, 20, 20);
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetFixedSize);
        formLayout->setHorizontalSpacing(0);
        formLayout->setVerticalSpacing(5);
        label_2 = new QLabel(Settings_ProfileLayout);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(180, 30));
        label_2->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        ChangePasswordButton = new QPushButton(Settings_ProfileLayout);
        ChangePasswordButton->setObjectName(QStringLiteral("ChangePasswordButton"));
        ChangePasswordButton->setMinimumSize(QSize(300, 30));
        ChangePasswordButton->setMaximumSize(QSize(300, 30));

        formLayout->setWidget(0, QFormLayout::FieldRole, ChangePasswordButton);

        line_63 = new QFrame(Settings_ProfileLayout);
        line_63->setObjectName(QStringLiteral("line_63"));
        line_63->setMaximumSize(QSize(480, 10));
        line_63->setFrameShape(QFrame::HLine);
        line_63->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(1, QFormLayout::SpanningRole, line_63);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(2, QFormLayout::SpanningRole, verticalSpacer);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        SaveButton = new QPushButton(Settings_ProfileLayout);
        SaveButton->setObjectName(QStringLiteral("SaveButton"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SaveButton->sizePolicy().hasHeightForWidth());
        SaveButton->setSizePolicy(sizePolicy);
        SaveButton->setMinimumSize(QSize(200, 30));
        SaveButton->setMaximumSize(QSize(200, 30));
        QFont font;
        font.setPointSize(13);
        SaveButton->setFont(font);

        horizontalLayout->addWidget(SaveButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Settings_ProfileLayout);

        QMetaObject::connectSlotsByName(Settings_ProfileLayout);
    } // setupUi

    void retranslateUi(QFrame *Settings_ProfileLayout)
    {
        Settings_ProfileLayout->setWindowTitle(QApplication::translate("Settings_ProfileLayout", "Frame", 0));
        label_2->setText(QApplication::translate("Settings_ProfileLayout", "Change password", 0));
        ChangePasswordButton->setText(QApplication::translate("Settings_ProfileLayout", "Change", 0));
        SaveButton->setText(QApplication::translate("Settings_ProfileLayout", "Save settings", 0));
    } // retranslateUi

};

namespace Ui {
    class Settings_ProfileLayout: public Ui_Settings_ProfileLayout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_PROFILELAYOUT_H

/********************************************************************************
** Form generated from reading UI file 'settings_programlayout.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_PROGRAMLAYOUT_H
#define UI_SETTINGS_PROGRAMLAYOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Settings_ProgramLayout
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *InterfaceStyle;
    QComboBox *InterfaceStyleBox;
    QFrame *line_62;
    QLabel *label_2;
    QComboBox *LanguageBox;
    QFrame *line_63;
    QLabel *TopBarShow;
    QComboBox *TopBarShowBox;
    QFrame *line_64;
    QLabel *TurnByWheel;
    QComboBox *TurnByWheelBox;
    QFrame *line_68;
    QLabel *TurnByTap;
    QComboBox *TurnByTapBox;
    QFrame *line_65;
    QSpacerItem *verticalSpacer_2;
    QLabel *TurnForward;
    QHBoxLayout *horizontalLayout;
    QPushButton *FTurnForward;
    QPushButton *STurnForward;
    QFrame *line_66;
    QLabel *TurnBackward;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *FTurnBackward;
    QPushButton *STurnBackward;
    QFrame *line_67;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *SaveButton;

    void setupUi(QFrame *Settings_ProgramLayout)
    {
        if (Settings_ProgramLayout->objectName().isEmpty())
            Settings_ProgramLayout->setObjectName(QStringLiteral("Settings_ProgramLayout"));
        Settings_ProgramLayout->resize(914, 577);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Settings_ProgramLayout->sizePolicy().hasHeightForWidth());
        Settings_ProgramLayout->setSizePolicy(sizePolicy);
        Settings_ProgramLayout->setStyleSheet(QStringLiteral(""));
        Settings_ProgramLayout->setFrameShape(QFrame::NoFrame);
        Settings_ProgramLayout->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(Settings_ProgramLayout);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(30, 20, 20, 20);
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
        InterfaceStyle = new QLabel(Settings_ProgramLayout);
        InterfaceStyle->setObjectName(QStringLiteral("InterfaceStyle"));
        InterfaceStyle->setMinimumSize(QSize(180, 30));
        InterfaceStyle->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, InterfaceStyle);

        InterfaceStyleBox = new QComboBox(Settings_ProgramLayout);
        InterfaceStyleBox->insertItems(0, QStringList()
         << QStringLiteral("Red")
        );
        InterfaceStyleBox->setObjectName(QStringLiteral("InterfaceStyleBox"));
        InterfaceStyleBox->setMinimumSize(QSize(300, 30));
        InterfaceStyleBox->setMaximumSize(QSize(300, 30));
        InterfaceStyleBox->setCurrentText(QStringLiteral("Red"));
        InterfaceStyleBox->setInsertPolicy(QComboBox::InsertAtCurrent);

        formLayout->setWidget(0, QFormLayout::FieldRole, InterfaceStyleBox);

        line_62 = new QFrame(Settings_ProgramLayout);
        line_62->setObjectName(QStringLiteral("line_62"));
        line_62->setMinimumSize(QSize(0, 10));
        line_62->setMaximumSize(QSize(480, 10));
        line_62->setFrameShape(QFrame::HLine);
        line_62->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(1, QFormLayout::SpanningRole, line_62);

        label_2 = new QLabel(Settings_ProgramLayout);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(180, 30));
        label_2->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        LanguageBox = new QComboBox(Settings_ProgramLayout);
        LanguageBox->insertItems(0, QStringList()
         << QStringLiteral("English")
         << QString::fromUtf8("\320\240\321\203\321\201\321\201\320\272\320\270\320\271")
        );
        LanguageBox->setObjectName(QStringLiteral("LanguageBox"));
        LanguageBox->setMinimumSize(QSize(300, 30));
        LanguageBox->setMaximumSize(QSize(300, 30));
        LanguageBox->setCurrentText(QStringLiteral("English"));

        formLayout->setWidget(2, QFormLayout::FieldRole, LanguageBox);

        line_63 = new QFrame(Settings_ProgramLayout);
        line_63->setObjectName(QStringLiteral("line_63"));
        line_63->setMinimumSize(QSize(0, 10));
        line_63->setMaximumSize(QSize(480, 10));
        line_63->setFrameShape(QFrame::HLine);
        line_63->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(3, QFormLayout::SpanningRole, line_63);

        TopBarShow = new QLabel(Settings_ProgramLayout);
        TopBarShow->setObjectName(QStringLiteral("TopBarShow"));
        TopBarShow->setMinimumSize(QSize(180, 30));
        TopBarShow->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(4, QFormLayout::LabelRole, TopBarShow);

        TopBarShowBox = new QComboBox(Settings_ProgramLayout);
        TopBarShowBox->setObjectName(QStringLiteral("TopBarShowBox"));
        TopBarShowBox->setMinimumSize(QSize(300, 30));
        TopBarShowBox->setMaximumSize(QSize(300, 30));

        formLayout->setWidget(4, QFormLayout::FieldRole, TopBarShowBox);

        line_64 = new QFrame(Settings_ProgramLayout);
        line_64->setObjectName(QStringLiteral("line_64"));
        line_64->setMinimumSize(QSize(0, 10));
        line_64->setMaximumSize(QSize(480, 10));
        line_64->setFrameShape(QFrame::HLine);
        line_64->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(5, QFormLayout::SpanningRole, line_64);

        TurnByWheel = new QLabel(Settings_ProgramLayout);
        TurnByWheel->setObjectName(QStringLiteral("TurnByWheel"));
        TurnByWheel->setMinimumSize(QSize(180, 30));
        TurnByWheel->setMaximumSize(QSize(180, 30));
        TurnByWheel->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(6, QFormLayout::LabelRole, TurnByWheel);

        TurnByWheelBox = new QComboBox(Settings_ProgramLayout);
        TurnByWheelBox->setObjectName(QStringLiteral("TurnByWheelBox"));
        TurnByWheelBox->setMinimumSize(QSize(300, 30));
        TurnByWheelBox->setMaximumSize(QSize(180, 30));

        formLayout->setWidget(6, QFormLayout::FieldRole, TurnByWheelBox);

        line_68 = new QFrame(Settings_ProgramLayout);
        line_68->setObjectName(QStringLiteral("line_68"));
        line_68->setMinimumSize(QSize(0, 10));
        line_68->setMaximumSize(QSize(480, 10));
        line_68->setFrameShape(QFrame::HLine);
        line_68->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(7, QFormLayout::SpanningRole, line_68);

        TurnByTap = new QLabel(Settings_ProgramLayout);
        TurnByTap->setObjectName(QStringLiteral("TurnByTap"));
        TurnByTap->setMinimumSize(QSize(180, 30));
        TurnByTap->setMaximumSize(QSize(180, 30));
        TurnByTap->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(8, QFormLayout::LabelRole, TurnByTap);

        TurnByTapBox = new QComboBox(Settings_ProgramLayout);
        TurnByTapBox->setObjectName(QStringLiteral("TurnByTapBox"));
        TurnByTapBox->setMinimumSize(QSize(300, 30));
        TurnByTapBox->setMaximumSize(QSize(180, 30));

        formLayout->setWidget(8, QFormLayout::FieldRole, TurnByTapBox);

        line_65 = new QFrame(Settings_ProgramLayout);
        line_65->setObjectName(QStringLiteral("line_65"));
        line_65->setMinimumSize(QSize(0, 10));
        line_65->setMaximumSize(QSize(480, 10));
        line_65->setFrameShape(QFrame::HLine);
        line_65->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(9, QFormLayout::SpanningRole, line_65);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        formLayout->setItem(10, QFormLayout::LabelRole, verticalSpacer_2);

        TurnForward = new QLabel(Settings_ProgramLayout);
        TurnForward->setObjectName(QStringLiteral("TurnForward"));
        TurnForward->setMinimumSize(QSize(180, 30));
        TurnForward->setMaximumSize(QSize(180, 30));
        TurnForward->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(11, QFormLayout::LabelRole, TurnForward);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 0);
        FTurnForward = new QPushButton(Settings_ProgramLayout);
        FTurnForward->setObjectName(QStringLiteral("FTurnForward"));
        FTurnForward->setMinimumSize(QSize(150, 30));
        FTurnForward->setMaximumSize(QSize(150, 30));
        FTurnForward->setText(QStringLiteral(""));
        FTurnForward->setCheckable(true);

        horizontalLayout->addWidget(FTurnForward);

        STurnForward = new QPushButton(Settings_ProgramLayout);
        STurnForward->setObjectName(QStringLiteral("STurnForward"));
        STurnForward->setMinimumSize(QSize(150, 30));
        STurnForward->setMaximumSize(QSize(150, 30));
        STurnForward->setText(QStringLiteral(""));
        STurnForward->setCheckable(true);

        horizontalLayout->addWidget(STurnForward);


        formLayout->setLayout(11, QFormLayout::FieldRole, horizontalLayout);

        line_66 = new QFrame(Settings_ProgramLayout);
        line_66->setObjectName(QStringLiteral("line_66"));
        line_66->setMinimumSize(QSize(0, 10));
        line_66->setMaximumSize(QSize(480, 10));
        line_66->setFrameShape(QFrame::HLine);
        line_66->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(12, QFormLayout::SpanningRole, line_66);

        TurnBackward = new QLabel(Settings_ProgramLayout);
        TurnBackward->setObjectName(QStringLiteral("TurnBackward"));
        TurnBackward->setMinimumSize(QSize(180, 30));
        TurnBackward->setMaximumSize(QSize(180, 30));
        TurnBackward->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(13, QFormLayout::LabelRole, TurnBackward);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, -1, 0);
        FTurnBackward = new QPushButton(Settings_ProgramLayout);
        FTurnBackward->setObjectName(QStringLiteral("FTurnBackward"));
        FTurnBackward->setMinimumSize(QSize(150, 30));
        FTurnBackward->setMaximumSize(QSize(150, 30));
        FTurnBackward->setText(QStringLiteral(""));
        FTurnBackward->setCheckable(true);

        horizontalLayout_2->addWidget(FTurnBackward);

        STurnBackward = new QPushButton(Settings_ProgramLayout);
        STurnBackward->setObjectName(QStringLiteral("STurnBackward"));
        STurnBackward->setMinimumSize(QSize(150, 30));
        STurnBackward->setMaximumSize(QSize(150, 30));
        STurnBackward->setText(QStringLiteral(""));
        STurnBackward->setCheckable(true);

        horizontalLayout_2->addWidget(STurnBackward);


        formLayout->setLayout(13, QFormLayout::FieldRole, horizontalLayout_2);

        line_67 = new QFrame(Settings_ProgramLayout);
        line_67->setObjectName(QStringLiteral("line_67"));
        line_67->setMinimumSize(QSize(0, 10));
        line_67->setMaximumSize(QSize(480, 10));
        line_67->setFrameShape(QFrame::HLine);
        line_67->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(14, QFormLayout::SpanningRole, line_67);


        verticalLayout->addLayout(formLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, -1, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        SaveButton = new QPushButton(Settings_ProgramLayout);
        SaveButton->setObjectName(QStringLiteral("SaveButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(SaveButton->sizePolicy().hasHeightForWidth());
        SaveButton->setSizePolicy(sizePolicy1);
        SaveButton->setMinimumSize(QSize(200, 30));
        SaveButton->setMaximumSize(QSize(200, 30));
        QFont font;
        font.setPointSize(13);
        SaveButton->setFont(font);

        horizontalLayout_4->addWidget(SaveButton);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(Settings_ProgramLayout);

        QMetaObject::connectSlotsByName(Settings_ProgramLayout);
    } // setupUi

    void retranslateUi(QFrame *Settings_ProgramLayout)
    {
        Settings_ProgramLayout->setWindowTitle(QApplication::translate("Settings_ProgramLayout", "Frame", 0));
        InterfaceStyle->setText(QApplication::translate("Settings_ProgramLayout", "Interface style", 0));
        label_2->setText(QApplication::translate("Settings_ProgramLayout", "Language", 0));
        TopBarShow->setText(QApplication::translate("Settings_ProgramLayout", "Show top bar in full screen mode", 0));
        TopBarShowBox->clear();
        TopBarShowBox->insertItems(0, QStringList()
         << QApplication::translate("Settings_ProgramLayout", "No", 0)
         << QApplication::translate("Settings_ProgramLayout", "Yes", 0)
        );
        TopBarShowBox->setCurrentText(QApplication::translate("Settings_ProgramLayout", "No", 0));
        TurnByWheel->setText(QApplication::translate("Settings_ProgramLayout", "Turn pages with the mouse wheel", 0));
        TurnByWheelBox->clear();
        TurnByWheelBox->insertItems(0, QStringList()
         << QApplication::translate("Settings_ProgramLayout", "No", 0)
         << QApplication::translate("Settings_ProgramLayout", "Yes", 0)
        );
        TurnByWheelBox->setCurrentText(QApplication::translate("Settings_ProgramLayout", "No", 0));
        TurnByTap->setText(QApplication::translate("Settings_ProgramLayout", "Turn pages with the click", 0));
        TurnByTapBox->clear();
        TurnByTapBox->insertItems(0, QStringList()
         << QApplication::translate("Settings_ProgramLayout", "No", 0)
         << QApplication::translate("Settings_ProgramLayout", "Yes", 0)
        );
        TurnByTapBox->setCurrentText(QApplication::translate("Settings_ProgramLayout", "No", 0));
        TurnForward->setText(QApplication::translate("Settings_ProgramLayout", "Turn the page forward", 0));
        TurnBackward->setText(QApplication::translate("Settings_ProgramLayout", "Turn the page backward", 0));
        SaveButton->setText(QApplication::translate("Settings_ProgramLayout", "Save settings", 0));
    } // retranslateUi

};

namespace Ui {
    class Settings_ProgramLayout: public Ui_Settings_ProgramLayout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_PROGRAMLAYOUT_H

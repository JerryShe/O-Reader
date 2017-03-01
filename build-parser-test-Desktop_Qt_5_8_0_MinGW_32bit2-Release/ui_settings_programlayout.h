/********************************************************************************
** Form generated from reading UI file 'settings_programlayout.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
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
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Settings_ProgramLayout
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *InterfaceButton;
    QWidget *InterfaceLayout;
    QFormLayout *formLayout_3;
    QLabel *InterfaceStyle;
    QComboBox *InterfaceStyleBox;
    QFrame *line_62;
    QLabel *Language;
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
    QPushButton *KeysButton;
    QWidget *KeysLayout;
    QFormLayout *formLayout_4;
    QLabel *TurnForward;
    QHBoxLayout *horizontalLayout;
    QPushButton *FTurnForward;
    QPushButton *STurnForward;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line_66;
    QLabel *TurnBackward;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *FTurnBackward;
    QPushButton *STurnBackward;
    QSpacerItem *horizontalSpacer_3;
    QFrame *line_67;
    QSpacerItem *verticalSpacer;
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
        scrollArea = new QScrollArea(Settings_ProgramLayout);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 864, 505));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        InterfaceButton = new QPushButton(scrollAreaWidgetContents_2);
        InterfaceButton->setObjectName(QStringLiteral("InterfaceButton"));
        InterfaceButton->setMinimumSize(QSize(520, 25));
        InterfaceButton->setMaximumSize(QSize(520, 25));

        verticalLayout_3->addWidget(InterfaceButton);

        InterfaceLayout = new QWidget(scrollAreaWidgetContents_2);
        InterfaceLayout->setObjectName(QStringLiteral("InterfaceLayout"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(InterfaceLayout->sizePolicy().hasHeightForWidth());
        InterfaceLayout->setSizePolicy(sizePolicy1);
        formLayout_3 = new QFormLayout(InterfaceLayout);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        formLayout_3->setHorizontalSpacing(0);
        formLayout_3->setVerticalSpacing(5);
        formLayout_3->setContentsMargins(10, 0, 10, 15);
        InterfaceStyle = new QLabel(InterfaceLayout);
        InterfaceStyle->setObjectName(QStringLiteral("InterfaceStyle"));
        InterfaceStyle->setMinimumSize(QSize(180, 30));
        InterfaceStyle->setAlignment(Qt::AlignCenter);

        formLayout_3->setWidget(0, QFormLayout::LabelRole, InterfaceStyle);

        InterfaceStyleBox = new QComboBox(InterfaceLayout);
        InterfaceStyleBox->insertItems(0, QStringList()
         << QStringLiteral("Red")
        );
        InterfaceStyleBox->setObjectName(QStringLiteral("InterfaceStyleBox"));
        InterfaceStyleBox->setMinimumSize(QSize(300, 30));
        InterfaceStyleBox->setMaximumSize(QSize(300, 30));
        InterfaceStyleBox->setCurrentText(QStringLiteral("Red"));
        InterfaceStyleBox->setInsertPolicy(QComboBox::InsertAtCurrent);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, InterfaceStyleBox);

        line_62 = new QFrame(InterfaceLayout);
        line_62->setObjectName(QStringLiteral("line_62"));
        line_62->setMinimumSize(QSize(0, 10));
        line_62->setMaximumSize(QSize(480, 10));
        line_62->setFrameShape(QFrame::HLine);
        line_62->setFrameShadow(QFrame::Sunken);

        formLayout_3->setWidget(1, QFormLayout::SpanningRole, line_62);

        Language = new QLabel(InterfaceLayout);
        Language->setObjectName(QStringLiteral("Language"));
        Language->setMinimumSize(QSize(180, 30));
        Language->setAlignment(Qt::AlignCenter);

        formLayout_3->setWidget(2, QFormLayout::LabelRole, Language);

        LanguageBox = new QComboBox(InterfaceLayout);
        LanguageBox->insertItems(0, QStringList()
         << QStringLiteral("English")
         << QString::fromUtf8("\320\240\321\203\321\201\321\201\320\272\320\270\320\271")
        );
        LanguageBox->setObjectName(QStringLiteral("LanguageBox"));
        LanguageBox->setMinimumSize(QSize(300, 30));
        LanguageBox->setMaximumSize(QSize(300, 30));
        LanguageBox->setCurrentText(QStringLiteral("English"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, LanguageBox);

        line_63 = new QFrame(InterfaceLayout);
        line_63->setObjectName(QStringLiteral("line_63"));
        line_63->setMinimumSize(QSize(0, 10));
        line_63->setMaximumSize(QSize(480, 10));
        line_63->setFrameShape(QFrame::HLine);
        line_63->setFrameShadow(QFrame::Sunken);

        formLayout_3->setWidget(3, QFormLayout::SpanningRole, line_63);

        TopBarShow = new QLabel(InterfaceLayout);
        TopBarShow->setObjectName(QStringLiteral("TopBarShow"));
        TopBarShow->setMinimumSize(QSize(180, 30));
        TopBarShow->setAlignment(Qt::AlignCenter);

        formLayout_3->setWidget(4, QFormLayout::LabelRole, TopBarShow);

        TopBarShowBox = new QComboBox(InterfaceLayout);
        TopBarShowBox->setObjectName(QStringLiteral("TopBarShowBox"));
        TopBarShowBox->setMinimumSize(QSize(300, 30));
        TopBarShowBox->setMaximumSize(QSize(300, 30));

        formLayout_3->setWidget(4, QFormLayout::FieldRole, TopBarShowBox);

        line_64 = new QFrame(InterfaceLayout);
        line_64->setObjectName(QStringLiteral("line_64"));
        line_64->setMinimumSize(QSize(0, 10));
        line_64->setMaximumSize(QSize(480, 10));
        line_64->setFrameShape(QFrame::HLine);
        line_64->setFrameShadow(QFrame::Sunken);

        formLayout_3->setWidget(5, QFormLayout::SpanningRole, line_64);

        TurnByWheel = new QLabel(InterfaceLayout);
        TurnByWheel->setObjectName(QStringLiteral("TurnByWheel"));
        TurnByWheel->setMinimumSize(QSize(180, 30));
        TurnByWheel->setMaximumSize(QSize(180, 30));
        TurnByWheel->setAlignment(Qt::AlignCenter);

        formLayout_3->setWidget(6, QFormLayout::LabelRole, TurnByWheel);

        TurnByWheelBox = new QComboBox(InterfaceLayout);
        TurnByWheelBox->setObjectName(QStringLiteral("TurnByWheelBox"));
        TurnByWheelBox->setMinimumSize(QSize(300, 30));
        TurnByWheelBox->setMaximumSize(QSize(180, 30));

        formLayout_3->setWidget(6, QFormLayout::FieldRole, TurnByWheelBox);

        line_68 = new QFrame(InterfaceLayout);
        line_68->setObjectName(QStringLiteral("line_68"));
        line_68->setMinimumSize(QSize(0, 10));
        line_68->setMaximumSize(QSize(480, 10));
        line_68->setFrameShape(QFrame::HLine);
        line_68->setFrameShadow(QFrame::Sunken);

        formLayout_3->setWidget(7, QFormLayout::SpanningRole, line_68);

        TurnByTap = new QLabel(InterfaceLayout);
        TurnByTap->setObjectName(QStringLiteral("TurnByTap"));
        TurnByTap->setMinimumSize(QSize(180, 30));
        TurnByTap->setMaximumSize(QSize(180, 30));
        TurnByTap->setAlignment(Qt::AlignCenter);

        formLayout_3->setWidget(8, QFormLayout::LabelRole, TurnByTap);

        TurnByTapBox = new QComboBox(InterfaceLayout);
        TurnByTapBox->setObjectName(QStringLiteral("TurnByTapBox"));
        TurnByTapBox->setMinimumSize(QSize(300, 30));
        TurnByTapBox->setMaximumSize(QSize(180, 30));

        formLayout_3->setWidget(8, QFormLayout::FieldRole, TurnByTapBox);

        line_65 = new QFrame(InterfaceLayout);
        line_65->setObjectName(QStringLiteral("line_65"));
        line_65->setMinimumSize(QSize(0, 10));
        line_65->setMaximumSize(QSize(480, 10));
        line_65->setFrameShape(QFrame::HLine);
        line_65->setFrameShadow(QFrame::Sunken);

        formLayout_3->setWidget(9, QFormLayout::SpanningRole, line_65);


        verticalLayout_3->addWidget(InterfaceLayout);

        KeysButton = new QPushButton(scrollAreaWidgetContents_2);
        KeysButton->setObjectName(QStringLiteral("KeysButton"));
        KeysButton->setMinimumSize(QSize(520, 25));
        KeysButton->setMaximumSize(QSize(520, 25));

        verticalLayout_3->addWidget(KeysButton);

        KeysLayout = new QWidget(scrollAreaWidgetContents_2);
        KeysLayout->setObjectName(QStringLiteral("KeysLayout"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(KeysLayout->sizePolicy().hasHeightForWidth());
        KeysLayout->setSizePolicy(sizePolicy2);
        KeysLayout->setMinimumSize(QSize(0, 0));
        formLayout_4 = new QFormLayout(KeysLayout);
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        formLayout_4->setHorizontalSpacing(0);
        formLayout_4->setVerticalSpacing(5);
        formLayout_4->setContentsMargins(10, 0, 10, 15);
        TurnForward = new QLabel(KeysLayout);
        TurnForward->setObjectName(QStringLiteral("TurnForward"));
        TurnForward->setMinimumSize(QSize(180, 30));
        TurnForward->setMaximumSize(QSize(180, 30));
        TurnForward->setAlignment(Qt::AlignCenter);

        formLayout_4->setWidget(0, QFormLayout::LabelRole, TurnForward);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 0);
        FTurnForward = new QPushButton(KeysLayout);
        FTurnForward->setObjectName(QStringLiteral("FTurnForward"));
        FTurnForward->setMinimumSize(QSize(150, 30));
        FTurnForward->setMaximumSize(QSize(150, 30));
        FTurnForward->setText(QStringLiteral(""));
        FTurnForward->setCheckable(true);

        horizontalLayout->addWidget(FTurnForward);

        STurnForward = new QPushButton(KeysLayout);
        STurnForward->setObjectName(QStringLiteral("STurnForward"));
        STurnForward->setMinimumSize(QSize(150, 30));
        STurnForward->setMaximumSize(QSize(150, 30));
        STurnForward->setText(QStringLiteral(""));
        STurnForward->setCheckable(true);

        horizontalLayout->addWidget(STurnForward);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        formLayout_4->setLayout(0, QFormLayout::FieldRole, horizontalLayout);

        line_66 = new QFrame(KeysLayout);
        line_66->setObjectName(QStringLiteral("line_66"));
        line_66->setMinimumSize(QSize(0, 10));
        line_66->setMaximumSize(QSize(480, 10));
        line_66->setFrameShape(QFrame::HLine);
        line_66->setFrameShadow(QFrame::Sunken);

        formLayout_4->setWidget(1, QFormLayout::SpanningRole, line_66);

        TurnBackward = new QLabel(KeysLayout);
        TurnBackward->setObjectName(QStringLiteral("TurnBackward"));
        TurnBackward->setMinimumSize(QSize(180, 30));
        TurnBackward->setMaximumSize(QSize(180, 30));
        TurnBackward->setAlignment(Qt::AlignCenter);

        formLayout_4->setWidget(2, QFormLayout::LabelRole, TurnBackward);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, -1, 0);
        FTurnBackward = new QPushButton(KeysLayout);
        FTurnBackward->setObjectName(QStringLiteral("FTurnBackward"));
        FTurnBackward->setMinimumSize(QSize(150, 30));
        FTurnBackward->setMaximumSize(QSize(150, 30));
        FTurnBackward->setText(QStringLiteral(""));
        FTurnBackward->setCheckable(true);

        horizontalLayout_2->addWidget(FTurnBackward);

        STurnBackward = new QPushButton(KeysLayout);
        STurnBackward->setObjectName(QStringLiteral("STurnBackward"));
        STurnBackward->setMinimumSize(QSize(150, 30));
        STurnBackward->setMaximumSize(QSize(150, 30));
        STurnBackward->setText(QStringLiteral(""));
        STurnBackward->setCheckable(true);

        horizontalLayout_2->addWidget(STurnBackward);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        formLayout_4->setLayout(2, QFormLayout::FieldRole, horizontalLayout_2);

        line_67 = new QFrame(KeysLayout);
        line_67->setObjectName(QStringLiteral("line_67"));
        line_67->setMinimumSize(QSize(0, 10));
        line_67->setMaximumSize(QSize(480, 10));
        line_67->setFrameShape(QFrame::HLine);
        line_67->setFrameShadow(QFrame::Sunken);

        formLayout_4->setWidget(3, QFormLayout::SpanningRole, line_67);


        verticalLayout_3->addWidget(KeysLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents_2);

        verticalLayout->addWidget(scrollArea);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, -1, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        SaveButton = new QPushButton(Settings_ProgramLayout);
        SaveButton->setObjectName(QStringLiteral("SaveButton"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(SaveButton->sizePolicy().hasHeightForWidth());
        SaveButton->setSizePolicy(sizePolicy3);
        SaveButton->setMinimumSize(QSize(200, 30));
        SaveButton->setMaximumSize(QSize(200, 30));
        QFont font;
        font.setPointSize(13);
        SaveButton->setFont(font);

        horizontalLayout_4->addWidget(SaveButton);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalLayout->setStretch(0, 1);

        retranslateUi(Settings_ProgramLayout);

        QMetaObject::connectSlotsByName(Settings_ProgramLayout);
    } // setupUi

    void retranslateUi(QFrame *Settings_ProgramLayout)
    {
        Settings_ProgramLayout->setWindowTitle(QApplication::translate("Settings_ProgramLayout", "Frame", Q_NULLPTR));
        InterfaceButton->setText(QApplication::translate("Settings_ProgramLayout", "Interface", Q_NULLPTR));
        InterfaceStyle->setText(QApplication::translate("Settings_ProgramLayout", "Interface style", Q_NULLPTR));
        Language->setText(QApplication::translate("Settings_ProgramLayout", "Language", Q_NULLPTR));
        TopBarShow->setText(QApplication::translate("Settings_ProgramLayout", "Hide top bar in full screen mode", Q_NULLPTR));
        TopBarShowBox->clear();
        TopBarShowBox->insertItems(0, QStringList()
         << QApplication::translate("Settings_ProgramLayout", "No", Q_NULLPTR)
         << QApplication::translate("Settings_ProgramLayout", "Yes", Q_NULLPTR)
        );
        TopBarShowBox->setCurrentText(QApplication::translate("Settings_ProgramLayout", "No", Q_NULLPTR));
        TurnByWheel->setText(QApplication::translate("Settings_ProgramLayout", "Turn pages with the mouse wheel", Q_NULLPTR));
        TurnByWheelBox->clear();
        TurnByWheelBox->insertItems(0, QStringList()
         << QApplication::translate("Settings_ProgramLayout", "No", Q_NULLPTR)
         << QApplication::translate("Settings_ProgramLayout", "Yes", Q_NULLPTR)
        );
        TurnByWheelBox->setCurrentText(QApplication::translate("Settings_ProgramLayout", "No", Q_NULLPTR));
        TurnByTap->setText(QApplication::translate("Settings_ProgramLayout", "Turn pages with the click", Q_NULLPTR));
        TurnByTapBox->clear();
        TurnByTapBox->insertItems(0, QStringList()
         << QApplication::translate("Settings_ProgramLayout", "No", Q_NULLPTR)
         << QApplication::translate("Settings_ProgramLayout", "Yes", Q_NULLPTR)
        );
        TurnByTapBox->setCurrentText(QApplication::translate("Settings_ProgramLayout", "No", Q_NULLPTR));
        KeysButton->setText(QApplication::translate("Settings_ProgramLayout", "Keys", Q_NULLPTR));
        TurnForward->setText(QApplication::translate("Settings_ProgramLayout", "Turn the page forward", Q_NULLPTR));
        TurnBackward->setText(QApplication::translate("Settings_ProgramLayout", "Turn the page backward", Q_NULLPTR));
        SaveButton->setText(QApplication::translate("Settings_ProgramLayout", "Save settings", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Settings_ProgramLayout: public Ui_Settings_ProgramLayout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_PROGRAMLAYOUT_H

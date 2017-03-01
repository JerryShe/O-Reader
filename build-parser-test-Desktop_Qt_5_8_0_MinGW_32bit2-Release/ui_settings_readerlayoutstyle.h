/********************************************************************************
** Form generated from reading UI file 'settings_readerlayoutstyle.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_READERLAYOUTSTYLE_H
#define UI_SETTINGS_READERLAYOUTSTYLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Settings_ReaderLayoutStyle
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *ShowButton;
    QWidget *StyleWidget;
    QFormLayout *formLayout;
    QFrame *line_17;
    QLabel *Family;
    QFontComboBox *NameBox;
    QFrame *line_22;
    QLabel *Size;
    QComboBox *SizeBox;
    QFrame *line_18;
    QLabel *Style;
    QComboBox *StyleBox;
    QFrame *line_19;
    QLabel *Color;
    QPushButton *ColorBox;
    QFrame *line_20;
    QLabel *LineSpacing;
    QComboBox *LineSpacingBox;
    QFrame *line_21;
    QLabel *Alignment;
    QComboBox *AlignmentBox;

    void setupUi(QWidget *Settings_ReaderLayoutStyle)
    {
        if (Settings_ReaderLayoutStyle->objectName().isEmpty())
            Settings_ReaderLayoutStyle->setObjectName(QStringLiteral("Settings_ReaderLayoutStyle"));
        Settings_ReaderLayoutStyle->resize(480, 313);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Settings_ReaderLayoutStyle->sizePolicy().hasHeightForWidth());
        Settings_ReaderLayoutStyle->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(Settings_ReaderLayoutStyle);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        ShowButton = new QPushButton(Settings_ReaderLayoutStyle);
        ShowButton->setObjectName(QStringLiteral("ShowButton"));
        ShowButton->setMinimumSize(QSize(250, 30));
        ShowButton->setMaximumSize(QSize(480, 30));
        QFont font;
        font.setPointSize(10);
        ShowButton->setFont(font);

        verticalLayout->addWidget(ShowButton);

        StyleWidget = new QWidget(Settings_ReaderLayoutStyle);
        StyleWidget->setObjectName(QStringLiteral("StyleWidget"));
        formLayout = new QFormLayout(StyleWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        line_17 = new QFrame(StyleWidget);
        line_17->setObjectName(QStringLiteral("line_17"));
        line_17->setMaximumSize(QSize(460, 10));
        line_17->setFrameShape(QFrame::HLine);
        line_17->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(0, QFormLayout::SpanningRole, line_17);

        Family = new QLabel(StyleWidget);
        Family->setObjectName(QStringLiteral("Family"));
        Family->setMinimumSize(QSize(150, 30));
        Family->setMaximumSize(QSize(150, 30));

        formLayout->setWidget(1, QFormLayout::LabelRole, Family);

        NameBox = new QFontComboBox(StyleWidget);
        NameBox->setObjectName(QStringLiteral("NameBox"));
        NameBox->setMinimumSize(QSize(200, 30));
        NameBox->setMaximumSize(QSize(300, 30));
        NameBox->setFrame(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, NameBox);

        line_22 = new QFrame(StyleWidget);
        line_22->setObjectName(QStringLiteral("line_22"));
        line_22->setMaximumSize(QSize(460, 10));
        line_22->setFrameShape(QFrame::HLine);
        line_22->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(2, QFormLayout::SpanningRole, line_22);

        Size = new QLabel(StyleWidget);
        Size->setObjectName(QStringLiteral("Size"));
        Size->setMinimumSize(QSize(150, 30));
        Size->setMaximumSize(QSize(150, 30));

        formLayout->setWidget(3, QFormLayout::LabelRole, Size);

        SizeBox = new QComboBox(StyleWidget);
        SizeBox->setObjectName(QStringLiteral("SizeBox"));
        SizeBox->setMinimumSize(QSize(200, 30));
        SizeBox->setMaximumSize(QSize(300, 30));

        formLayout->setWidget(3, QFormLayout::FieldRole, SizeBox);

        line_18 = new QFrame(StyleWidget);
        line_18->setObjectName(QStringLiteral("line_18"));
        line_18->setMaximumSize(QSize(460, 10));
        line_18->setFrameShape(QFrame::HLine);
        line_18->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(4, QFormLayout::SpanningRole, line_18);

        Style = new QLabel(StyleWidget);
        Style->setObjectName(QStringLiteral("Style"));
        Style->setMinimumSize(QSize(150, 30));
        Style->setMaximumSize(QSize(150, 30));

        formLayout->setWidget(5, QFormLayout::LabelRole, Style);

        StyleBox = new QComboBox(StyleWidget);
        StyleBox->setObjectName(QStringLiteral("StyleBox"));
        StyleBox->setMinimumSize(QSize(200, 30));
        StyleBox->setMaximumSize(QSize(300, 30));

        formLayout->setWidget(5, QFormLayout::FieldRole, StyleBox);

        line_19 = new QFrame(StyleWidget);
        line_19->setObjectName(QStringLiteral("line_19"));
        line_19->setMaximumSize(QSize(460, 10));
        line_19->setFrameShape(QFrame::HLine);
        line_19->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(6, QFormLayout::SpanningRole, line_19);

        Color = new QLabel(StyleWidget);
        Color->setObjectName(QStringLiteral("Color"));
        Color->setMinimumSize(QSize(150, 30));
        Color->setMaximumSize(QSize(150, 30));

        formLayout->setWidget(7, QFormLayout::LabelRole, Color);

        ColorBox = new QPushButton(StyleWidget);
        ColorBox->setObjectName(QStringLiteral("ColorBox"));
        ColorBox->setMinimumSize(QSize(200, 30));
        ColorBox->setMaximumSize(QSize(300, 30));
        ColorBox->setFont(font);

        formLayout->setWidget(7, QFormLayout::FieldRole, ColorBox);

        line_20 = new QFrame(StyleWidget);
        line_20->setObjectName(QStringLiteral("line_20"));
        line_20->setMaximumSize(QSize(460, 10));
        line_20->setFrameShape(QFrame::HLine);
        line_20->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(8, QFormLayout::SpanningRole, line_20);

        LineSpacing = new QLabel(StyleWidget);
        LineSpacing->setObjectName(QStringLiteral("LineSpacing"));
        LineSpacing->setMinimumSize(QSize(150, 30));
        LineSpacing->setMaximumSize(QSize(150, 30));

        formLayout->setWidget(9, QFormLayout::LabelRole, LineSpacing);

        LineSpacingBox = new QComboBox(StyleWidget);
        LineSpacingBox->setObjectName(QStringLiteral("LineSpacingBox"));
        LineSpacingBox->setMinimumSize(QSize(200, 30));
        LineSpacingBox->setMaximumSize(QSize(300, 30));

        formLayout->setWidget(9, QFormLayout::FieldRole, LineSpacingBox);

        line_21 = new QFrame(StyleWidget);
        line_21->setObjectName(QStringLiteral("line_21"));
        line_21->setMaximumSize(QSize(460, 10));
        line_21->setFrameShape(QFrame::HLine);
        line_21->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(10, QFormLayout::SpanningRole, line_21);

        Alignment = new QLabel(StyleWidget);
        Alignment->setObjectName(QStringLiteral("Alignment"));
        Alignment->setMinimumSize(QSize(150, 30));
        Alignment->setMaximumSize(QSize(150, 30));

        formLayout->setWidget(11, QFormLayout::LabelRole, Alignment);

        AlignmentBox = new QComboBox(StyleWidget);
        AlignmentBox->setObjectName(QStringLiteral("AlignmentBox"));
        AlignmentBox->setMinimumSize(QSize(200, 30));
        AlignmentBox->setMaximumSize(QSize(300, 30));

        formLayout->setWidget(11, QFormLayout::FieldRole, AlignmentBox);


        verticalLayout->addWidget(StyleWidget);


        retranslateUi(Settings_ReaderLayoutStyle);

        QMetaObject::connectSlotsByName(Settings_ReaderLayoutStyle);
    } // setupUi

    void retranslateUi(QWidget *Settings_ReaderLayoutStyle)
    {
        Settings_ReaderLayoutStyle->setWindowTitle(QApplication::translate("Settings_ReaderLayoutStyle", "Form", Q_NULLPTR));
        ShowButton->setText(QApplication::translate("Settings_ReaderLayoutStyle", "PushButton", Q_NULLPTR));
        Family->setText(QApplication::translate("Settings_ReaderLayoutStyle", "Family", Q_NULLPTR));
        Size->setText(QApplication::translate("Settings_ReaderLayoutStyle", "Size", Q_NULLPTR));
        SizeBox->clear();
        SizeBox->insertItems(0, QStringList()
         << QApplication::translate("Settings_ReaderLayoutStyle", "6", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "7", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "8", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "9", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "10", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "11", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "12", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "13", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "14", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "15", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "16", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "17", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "18", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "19", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "20", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "21", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "22", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "24", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "26", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "27", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "28", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "29", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "30", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "31", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "32", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "33", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "34", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "35", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "36", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "37", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "38", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "39", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "40", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "41", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "42", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "43", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "44", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "45", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "46", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "47", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "48", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "49", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "50", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "51", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "52", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "53", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "54", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "55", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "56", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "57", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "58", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "59", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "60", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "61", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "62", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "63", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "64", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "65", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "66", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "67", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "68", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "69", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "70", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "71", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "72", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "73", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "74", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "75", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "76", Q_NULLPTR)
        );
        Style->setText(QApplication::translate("Settings_ReaderLayoutStyle", "Style", Q_NULLPTR));
        StyleBox->clear();
        StyleBox->insertItems(0, QStringList()
         << QApplication::translate("Settings_ReaderLayoutStyle", "Regular", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "Bold", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "Italic", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "Bold & Italic", Q_NULLPTR)
        );
        Color->setText(QApplication::translate("Settings_ReaderLayoutStyle", "Color", Q_NULLPTR));
        ColorBox->setText(QApplication::translate("Settings_ReaderLayoutStyle", "some color", Q_NULLPTR));
        LineSpacing->setText(QApplication::translate("Settings_ReaderLayoutStyle", "Line spacing", Q_NULLPTR));
        Alignment->setText(QApplication::translate("Settings_ReaderLayoutStyle", "Alignment", Q_NULLPTR));
        AlignmentBox->clear();
        AlignmentBox->insertItems(0, QStringList()
         << QApplication::translate("Settings_ReaderLayoutStyle", "Justify", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "Left", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "Right", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayoutStyle", "Center", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class Settings_ReaderLayoutStyle: public Ui_Settings_ReaderLayoutStyle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_READERLAYOUTSTYLE_H

/********************************************************************************
** Form generated from reading UI file 'settings_readerlayout.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_READERLAYOUT_H
#define UI_SETTINGS_READERLAYOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "settings_readerlayoutstyle.h"

QT_BEGIN_NAMESPACE

class Ui_Settings_ReaderLayout
{
public:
    QGridLayout *gridLayout;
    QScrollArea *ReaderSettingArea;
    QWidget *ReaderSettingsContent;
    QVBoxLayout *verticalLayout_2;
    QPushButton *OverallSettings;
    QWidget *_OverallSettingsWidget;
    QFormLayout *formLayout_2;
    QFrame *line_2;
    QLabel *BackgroundType;
    QComboBox *BackgroundTypeBox;
    QFrame *line;
    QFormLayout *formLayout_3;
    QLabel *BackgroundImage;
    QPushButton *BackgroundImageBox;
    QLabel *BackgroundColor;
    QPushButton *BackgroundColorBox;
    QFrame *line_62;
    QLabel *ColumnNumber;
    QComboBox *ColumnNumberBox;
    QFrame *line_61;
    QLabel *TextAntiAliasing;
    QComboBox *TextAntiAliasingBox;
    QFrame *line_3;
    QLabel *ParagraphLeftIdent;
    QComboBox *ParagraphLeftIdentBox;
    QFrame *line_4;
    QLabel *ParagraphTopIdent;
    QComboBox *ParagraphTopIdentBox;
    QFrame *line_5;
    QLabel *TextLeftIdent;
    QComboBox *TextLeftIdentBox;
    QFrame *line_6;
    QLabel *TextRightIndent;
    QComboBox *TextRightIdentBox;
    QFrame *line_7;
    QLabel *TextTopIdent;
    QComboBox *TextTopIndentBox;
    QFrame *line_8;
    QLabel *TextBottomIndent;
    QComboBox *TextBottomIndentBox;
    Settings_ReaderLayoutStyle *RegularStyle;
    Settings_ReaderLayoutStyle *EmphasizedStyle;
    Settings_ReaderLayoutStyle *TitleStyle;
    Settings_ReaderLayoutStyle *SubtitleStyle;
    Settings_ReaderLayoutStyle *NoteStyle;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *RightLayout;
    QWidget *TextBackground;
    QHBoxLayout *horizontalLayout_2;
    QTextBrowser *TextExample;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *SaveButton;
    QHBoxLayout *TopLayout;
    QLabel *label;
    QComboBox *StyleBox;
    QLineEdit *NewStyleName;
    QPushButton *YepButton;
    QPushButton *NopeButton;
    QSpacerItem *horizontalSpacer;
    QFrame *line_15;

    void setupUi(QFrame *Settings_ReaderLayout)
    {
        if (Settings_ReaderLayout->objectName().isEmpty())
            Settings_ReaderLayout->setObjectName(QStringLiteral("Settings_ReaderLayout"));
        Settings_ReaderLayout->resize(1398, 734);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Settings_ReaderLayout->sizePolicy().hasHeightForWidth());
        Settings_ReaderLayout->setSizePolicy(sizePolicy);
        Settings_ReaderLayout->setMinimumSize(QSize(0, 0));
        Settings_ReaderLayout->setStyleSheet(QLatin1String("QScrollBar:vertical {\n"
"     border: none;\n"
"     background: none;\n"
"     width: 12px;\n"
"     margin: 0px;\n"
" }\n"
" QScrollBar::handle:vertical {\n"
"     border: none;\n"
"     background: white;\n"
"     min-height: 20px;\n"
" }\n"
" QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {\n"
"     height: 0px;\n"
" }\n"
"\n"
" QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\n"
"     background: none;\n"
" }"));
        Settings_ReaderLayout->setFrameShape(QFrame::NoFrame);
        Settings_ReaderLayout->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(Settings_ReaderLayout);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetNoConstraint);
        gridLayout->setHorizontalSpacing(30);
        gridLayout->setVerticalSpacing(5);
        gridLayout->setContentsMargins(30, 20, 20, 20);
        ReaderSettingArea = new QScrollArea(Settings_ReaderLayout);
        ReaderSettingArea->setObjectName(QStringLiteral("ReaderSettingArea"));
        sizePolicy.setHeightForWidth(ReaderSettingArea->sizePolicy().hasHeightForWidth());
        ReaderSettingArea->setSizePolicy(sizePolicy);
        ReaderSettingArea->setMinimumSize(QSize(400, 0));
        ReaderSettingArea->setMaximumSize(QSize(700, 16777215));
        ReaderSettingArea->setStyleSheet(QStringLiteral(""));
        ReaderSettingArea->setFrameShape(QFrame::NoFrame);
        ReaderSettingArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ReaderSettingArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        ReaderSettingArea->setWidgetResizable(true);
        ReaderSettingArea->setAlignment(Qt::AlignCenter);
        ReaderSettingsContent = new QWidget();
        ReaderSettingsContent->setObjectName(QStringLiteral("ReaderSettingsContent"));
        ReaderSettingsContent->setGeometry(QRect(0, 0, 480, 649));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ReaderSettingsContent->sizePolicy().hasHeightForWidth());
        ReaderSettingsContent->setSizePolicy(sizePolicy1);
        ReaderSettingsContent->setMinimumSize(QSize(400, 0));
        ReaderSettingsContent->setSizeIncrement(QSize(1, 1));
        ReaderSettingsContent->setLayoutDirection(Qt::LeftToRight);
        ReaderSettingsContent->setStyleSheet(QStringLiteral(""));
        verticalLayout_2 = new QVBoxLayout(ReaderSettingsContent);
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout_2->setContentsMargins(0, 10, 0, 0);
        OverallSettings = new QPushButton(ReaderSettingsContent);
        OverallSettings->setObjectName(QStringLiteral("OverallSettings"));
        OverallSettings->setMinimumSize(QSize(250, 30));
        OverallSettings->setMaximumSize(QSize(480, 30));
        QFont font;
        font.setPointSize(10);
        OverallSettings->setFont(font);

        verticalLayout_2->addWidget(OverallSettings);

        _OverallSettingsWidget = new QWidget(ReaderSettingsContent);
        _OverallSettingsWidget->setObjectName(QStringLiteral("_OverallSettingsWidget"));
        _OverallSettingsWidget->setMinimumSize(QSize(0, 50));
        _OverallSettingsWidget->setStyleSheet(QStringLiteral(""));
        formLayout_2 = new QFormLayout(_OverallSettingsWidget);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        formLayout_2->setHorizontalSpacing(0);
        formLayout_2->setVerticalSpacing(5);
        formLayout_2->setContentsMargins(10, 0, 10, 15);
        line_2 = new QFrame(_OverallSettingsWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setMaximumSize(QSize(460, 10));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        formLayout_2->setWidget(0, QFormLayout::SpanningRole, line_2);

        BackgroundType = new QLabel(_OverallSettingsWidget);
        BackgroundType->setObjectName(QStringLiteral("BackgroundType"));
        BackgroundType->setMinimumSize(QSize(150, 25));
        BackgroundType->setMaximumSize(QSize(150, 30));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, BackgroundType);

        BackgroundTypeBox = new QComboBox(_OverallSettingsWidget);
        BackgroundTypeBox->setObjectName(QStringLiteral("BackgroundTypeBox"));
        BackgroundTypeBox->setMinimumSize(QSize(200, 30));
        BackgroundTypeBox->setMaximumSize(QSize(300, 30));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, BackgroundTypeBox);

        line = new QFrame(_OverallSettingsWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setMaximumSize(QSize(460, 10));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        formLayout_2->setWidget(2, QFormLayout::SpanningRole, line);

        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        formLayout_3->setHorizontalSpacing(0);
        formLayout_3->setVerticalSpacing(0);
        formLayout_3->setContentsMargins(-1, -1, 0, 0);
        BackgroundImage = new QLabel(_OverallSettingsWidget);
        BackgroundImage->setObjectName(QStringLiteral("BackgroundImage"));
        BackgroundImage->setMinimumSize(QSize(150, 25));
        BackgroundImage->setMaximumSize(QSize(150, 30));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, BackgroundImage);

        BackgroundImageBox = new QPushButton(_OverallSettingsWidget);
        BackgroundImageBox->setObjectName(QStringLiteral("BackgroundImageBox"));
        BackgroundImageBox->setMinimumSize(QSize(200, 30));
        BackgroundImageBox->setMaximumSize(QSize(300, 30));
        BackgroundImageBox->setFont(font);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, BackgroundImageBox);

        BackgroundColor = new QLabel(_OverallSettingsWidget);
        BackgroundColor->setObjectName(QStringLiteral("BackgroundColor"));
        BackgroundColor->setMinimumSize(QSize(150, 25));
        BackgroundColor->setMaximumSize(QSize(150, 30));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, BackgroundColor);

        BackgroundColorBox = new QPushButton(_OverallSettingsWidget);
        BackgroundColorBox->setObjectName(QStringLiteral("BackgroundColorBox"));
        BackgroundColorBox->setMinimumSize(QSize(200, 30));
        BackgroundColorBox->setMaximumSize(QSize(300, 30));
        BackgroundColorBox->setFont(font);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, BackgroundColorBox);


        formLayout_2->setLayout(3, QFormLayout::SpanningRole, formLayout_3);

        line_62 = new QFrame(_OverallSettingsWidget);
        line_62->setObjectName(QStringLiteral("line_62"));
        line_62->setMaximumSize(QSize(460, 10));
        line_62->setFrameShape(QFrame::HLine);
        line_62->setFrameShadow(QFrame::Sunken);

        formLayout_2->setWidget(4, QFormLayout::SpanningRole, line_62);

        ColumnNumber = new QLabel(_OverallSettingsWidget);
        ColumnNumber->setObjectName(QStringLiteral("ColumnNumber"));
        ColumnNumber->setMinimumSize(QSize(150, 25));
        ColumnNumber->setMaximumSize(QSize(150, 30));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, ColumnNumber);

        ColumnNumberBox = new QComboBox(_OverallSettingsWidget);
        ColumnNumberBox->insertItems(0, QStringList()
         << QStringLiteral("1")
         << QStringLiteral("2")
         << QStringLiteral("3")
         << QStringLiteral("4")
         << QStringLiteral("5")
        );
        ColumnNumberBox->setObjectName(QStringLiteral("ColumnNumberBox"));
        ColumnNumberBox->setMinimumSize(QSize(200, 30));
        ColumnNumberBox->setMaximumSize(QSize(300, 30));
        ColumnNumberBox->setCurrentText(QStringLiteral("1"));

        formLayout_2->setWidget(5, QFormLayout::FieldRole, ColumnNumberBox);

        line_61 = new QFrame(_OverallSettingsWidget);
        line_61->setObjectName(QStringLiteral("line_61"));
        line_61->setMaximumSize(QSize(460, 10));
        line_61->setFrameShape(QFrame::HLine);
        line_61->setFrameShadow(QFrame::Sunken);

        formLayout_2->setWidget(6, QFormLayout::SpanningRole, line_61);

        TextAntiAliasing = new QLabel(_OverallSettingsWidget);
        TextAntiAliasing->setObjectName(QStringLiteral("TextAntiAliasing"));
        TextAntiAliasing->setMinimumSize(QSize(150, 25));
        TextAntiAliasing->setMaximumSize(QSize(150, 30));

        formLayout_2->setWidget(7, QFormLayout::LabelRole, TextAntiAliasing);

        TextAntiAliasingBox = new QComboBox(_OverallSettingsWidget);
        TextAntiAliasingBox->setObjectName(QStringLiteral("TextAntiAliasingBox"));
        TextAntiAliasingBox->setMinimumSize(QSize(200, 30));
        TextAntiAliasingBox->setMaximumSize(QSize(300, 30));

        formLayout_2->setWidget(7, QFormLayout::FieldRole, TextAntiAliasingBox);

        line_3 = new QFrame(_OverallSettingsWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setMaximumSize(QSize(460, 10));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        formLayout_2->setWidget(8, QFormLayout::SpanningRole, line_3);

        ParagraphLeftIdent = new QLabel(_OverallSettingsWidget);
        ParagraphLeftIdent->setObjectName(QStringLiteral("ParagraphLeftIdent"));
        ParagraphLeftIdent->setMinimumSize(QSize(150, 25));
        ParagraphLeftIdent->setMaximumSize(QSize(150, 30));

        formLayout_2->setWidget(9, QFormLayout::LabelRole, ParagraphLeftIdent);

        ParagraphLeftIdentBox = new QComboBox(_OverallSettingsWidget);
        ParagraphLeftIdentBox->setObjectName(QStringLiteral("ParagraphLeftIdentBox"));
        ParagraphLeftIdentBox->setMinimumSize(QSize(200, 30));
        ParagraphLeftIdentBox->setMaximumSize(QSize(300, 30));
        ParagraphLeftIdentBox->setCurrentText(QStringLiteral("0"));

        formLayout_2->setWidget(9, QFormLayout::FieldRole, ParagraphLeftIdentBox);

        line_4 = new QFrame(_OverallSettingsWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setMaximumSize(QSize(460, 10));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        formLayout_2->setWidget(10, QFormLayout::SpanningRole, line_4);

        ParagraphTopIdent = new QLabel(_OverallSettingsWidget);
        ParagraphTopIdent->setObjectName(QStringLiteral("ParagraphTopIdent"));
        ParagraphTopIdent->setMinimumSize(QSize(150, 25));
        ParagraphTopIdent->setMaximumSize(QSize(150, 30));

        formLayout_2->setWidget(11, QFormLayout::LabelRole, ParagraphTopIdent);

        ParagraphTopIdentBox = new QComboBox(_OverallSettingsWidget);
        ParagraphTopIdentBox->setObjectName(QStringLiteral("ParagraphTopIdentBox"));
        ParagraphTopIdentBox->setMinimumSize(QSize(200, 30));
        ParagraphTopIdentBox->setMaximumSize(QSize(300, 30));

        formLayout_2->setWidget(11, QFormLayout::FieldRole, ParagraphTopIdentBox);

        line_5 = new QFrame(_OverallSettingsWidget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setMaximumSize(QSize(460, 10));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        formLayout_2->setWidget(12, QFormLayout::SpanningRole, line_5);

        TextLeftIdent = new QLabel(_OverallSettingsWidget);
        TextLeftIdent->setObjectName(QStringLiteral("TextLeftIdent"));
        TextLeftIdent->setMinimumSize(QSize(150, 25));
        TextLeftIdent->setMaximumSize(QSize(150, 30));

        formLayout_2->setWidget(13, QFormLayout::LabelRole, TextLeftIdent);

        TextLeftIdentBox = new QComboBox(_OverallSettingsWidget);
        TextLeftIdentBox->setObjectName(QStringLiteral("TextLeftIdentBox"));
        TextLeftIdentBox->setMinimumSize(QSize(200, 30));
        TextLeftIdentBox->setMaximumSize(QSize(300, 30));

        formLayout_2->setWidget(13, QFormLayout::FieldRole, TextLeftIdentBox);

        line_6 = new QFrame(_OverallSettingsWidget);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setMaximumSize(QSize(460, 10));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        formLayout_2->setWidget(14, QFormLayout::SpanningRole, line_6);

        TextRightIndent = new QLabel(_OverallSettingsWidget);
        TextRightIndent->setObjectName(QStringLiteral("TextRightIndent"));
        TextRightIndent->setMinimumSize(QSize(150, 25));
        TextRightIndent->setMaximumSize(QSize(150, 30));

        formLayout_2->setWidget(15, QFormLayout::LabelRole, TextRightIndent);

        TextRightIdentBox = new QComboBox(_OverallSettingsWidget);
        TextRightIdentBox->setObjectName(QStringLiteral("TextRightIdentBox"));
        TextRightIdentBox->setMinimumSize(QSize(200, 30));
        TextRightIdentBox->setMaximumSize(QSize(300, 30));

        formLayout_2->setWidget(15, QFormLayout::FieldRole, TextRightIdentBox);

        line_7 = new QFrame(_OverallSettingsWidget);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setMaximumSize(QSize(460, 10));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);

        formLayout_2->setWidget(16, QFormLayout::SpanningRole, line_7);

        TextTopIdent = new QLabel(_OverallSettingsWidget);
        TextTopIdent->setObjectName(QStringLiteral("TextTopIdent"));
        TextTopIdent->setMinimumSize(QSize(150, 25));
        TextTopIdent->setMaximumSize(QSize(150, 30));

        formLayout_2->setWidget(17, QFormLayout::LabelRole, TextTopIdent);

        TextTopIndentBox = new QComboBox(_OverallSettingsWidget);
        TextTopIndentBox->setObjectName(QStringLiteral("TextTopIndentBox"));
        TextTopIndentBox->setMinimumSize(QSize(200, 30));
        TextTopIndentBox->setMaximumSize(QSize(300, 30));

        formLayout_2->setWidget(17, QFormLayout::FieldRole, TextTopIndentBox);

        line_8 = new QFrame(_OverallSettingsWidget);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setMaximumSize(QSize(460, 10));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);

        formLayout_2->setWidget(18, QFormLayout::SpanningRole, line_8);

        TextBottomIndent = new QLabel(_OverallSettingsWidget);
        TextBottomIndent->setObjectName(QStringLiteral("TextBottomIndent"));
        TextBottomIndent->setMinimumSize(QSize(150, 25));
        TextBottomIndent->setMaximumSize(QSize(150, 30));

        formLayout_2->setWidget(19, QFormLayout::LabelRole, TextBottomIndent);

        TextBottomIndentBox = new QComboBox(_OverallSettingsWidget);
        TextBottomIndentBox->setObjectName(QStringLiteral("TextBottomIndentBox"));
        TextBottomIndentBox->setMinimumSize(QSize(200, 30));
        TextBottomIndentBox->setMaximumSize(QSize(300, 30));

        formLayout_2->setWidget(19, QFormLayout::FieldRole, TextBottomIndentBox);


        verticalLayout_2->addWidget(_OverallSettingsWidget);

        RegularStyle = new Settings_ReaderLayoutStyle(ReaderSettingsContent);
        RegularStyle->setObjectName(QStringLiteral("RegularStyle"));

        verticalLayout_2->addWidget(RegularStyle);

        EmphasizedStyle = new Settings_ReaderLayoutStyle(ReaderSettingsContent);
        EmphasizedStyle->setObjectName(QStringLiteral("EmphasizedStyle"));

        verticalLayout_2->addWidget(EmphasizedStyle);

        TitleStyle = new Settings_ReaderLayoutStyle(ReaderSettingsContent);
        TitleStyle->setObjectName(QStringLiteral("TitleStyle"));

        verticalLayout_2->addWidget(TitleStyle);

        SubtitleStyle = new Settings_ReaderLayoutStyle(ReaderSettingsContent);
        SubtitleStyle->setObjectName(QStringLiteral("SubtitleStyle"));

        verticalLayout_2->addWidget(SubtitleStyle);

        NoteStyle = new Settings_ReaderLayoutStyle(ReaderSettingsContent);
        NoteStyle->setObjectName(QStringLiteral("NoteStyle"));

        verticalLayout_2->addWidget(NoteStyle);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        ReaderSettingArea->setWidget(ReaderSettingsContent);

        gridLayout->addWidget(ReaderSettingArea, 2, 0, 1, 1);

        RightLayout = new QVBoxLayout();
        RightLayout->setSpacing(0);
        RightLayout->setObjectName(QStringLiteral("RightLayout"));
        RightLayout->setContentsMargins(0, -1, 0, -1);
        TextBackground = new QWidget(Settings_ReaderLayout);
        TextBackground->setObjectName(QStringLiteral("TextBackground"));
        TextBackground->setMinimumSize(QSize(200, 335));
        horizontalLayout_2 = new QHBoxLayout(TextBackground);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        TextExample = new QTextBrowser(TextBackground);
        TextExample->setObjectName(QStringLiteral("TextExample"));
        sizePolicy1.setHeightForWidth(TextExample->sizePolicy().hasHeightForWidth());
        TextExample->setSizePolicy(sizePolicy1);
        TextExample->setMinimumSize(QSize(200, 335));
        TextExample->setFrameShape(QFrame::NoFrame);
        TextExample->setFrameShadow(QFrame::Plain);
        TextExample->setLineWidth(0);
        TextExample->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        TextExample->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        TextExample->setOverwriteMode(true);
        TextExample->setTextInteractionFlags(Qt::NoTextInteraction);
        TextExample->setOpenLinks(false);

        horizontalLayout_2->addWidget(TextExample);


        RightLayout->addWidget(TextBackground);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        RightLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        SaveButton = new QPushButton(Settings_ReaderLayout);
        SaveButton->setObjectName(QStringLiteral("SaveButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(SaveButton->sizePolicy().hasHeightForWidth());
        SaveButton->setSizePolicy(sizePolicy2);
        SaveButton->setMinimumSize(QSize(200, 30));
        SaveButton->setMaximumSize(QSize(200, 30));
        QFont font1;
        font1.setPointSize(13);
        SaveButton->setFont(font1);

        horizontalLayout->addWidget(SaveButton);


        RightLayout->addLayout(horizontalLayout);

        RightLayout->setStretch(0, 1);

        gridLayout->addLayout(RightLayout, 2, 2, 1, 1);

        TopLayout = new QHBoxLayout();
        TopLayout->setSpacing(0);
        TopLayout->setObjectName(QStringLiteral("TopLayout"));
        label = new QLabel(Settings_ReaderLayout);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(100, 30));
        label->setMaximumSize(QSize(250, 30));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);

        TopLayout->addWidget(label);

        StyleBox = new QComboBox(Settings_ReaderLayout);
        StyleBox->setObjectName(QStringLiteral("StyleBox"));
        sizePolicy2.setHeightForWidth(StyleBox->sizePolicy().hasHeightForWidth());
        StyleBox->setSizePolicy(sizePolicy2);
        StyleBox->setMinimumSize(QSize(100, 30));
        StyleBox->setMaximumSize(QSize(300, 30));
        StyleBox->setEditable(false);
        StyleBox->setInsertPolicy(QComboBox::InsertAtTop);

        TopLayout->addWidget(StyleBox);

        NewStyleName = new QLineEdit(Settings_ReaderLayout);
        NewStyleName->setObjectName(QStringLiteral("NewStyleName"));
        sizePolicy2.setHeightForWidth(NewStyleName->sizePolicy().hasHeightForWidth());
        NewStyleName->setSizePolicy(sizePolicy2);
        NewStyleName->setMinimumSize(QSize(100, 30));
        NewStyleName->setMaximumSize(QSize(300, 30));

        TopLayout->addWidget(NewStyleName);

        YepButton = new QPushButton(Settings_ReaderLayout);
        YepButton->setObjectName(QStringLiteral("YepButton"));
        YepButton->setMinimumSize(QSize(30, 30));
        YepButton->setMaximumSize(QSize(30, 30));
        YepButton->setText(QStringLiteral(""));

        TopLayout->addWidget(YepButton);

        NopeButton = new QPushButton(Settings_ReaderLayout);
        NopeButton->setObjectName(QStringLiteral("NopeButton"));
        NopeButton->setMinimumSize(QSize(30, 30));
        NopeButton->setMaximumSize(QSize(30, 30));
        NopeButton->setText(QStringLiteral(""));
        NopeButton->setCheckable(false);

        TopLayout->addWidget(NopeButton);


        gridLayout->addLayout(TopLayout, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        line_15 = new QFrame(Settings_ReaderLayout);
        line_15->setObjectName(QStringLiteral("line_15"));
        line_15->setMinimumSize(QSize(400, 0));
        line_15->setMaximumSize(QSize(610, 10));
        line_15->setFrameShape(QFrame::HLine);
        line_15->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_15, 1, 0, 1, 1);

        gridLayout->setColumnStretch(2, 1);
        gridLayout->setColumnMinimumWidth(0, 480);
        gridLayout->setColumnMinimumWidth(2, 100);

        retranslateUi(Settings_ReaderLayout);

        QMetaObject::connectSlotsByName(Settings_ReaderLayout);
    } // setupUi

    void retranslateUi(QFrame *Settings_ReaderLayout)
    {
        Settings_ReaderLayout->setWindowTitle(QApplication::translate("Settings_ReaderLayout", "Frame", Q_NULLPTR));
        OverallSettings->setText(QApplication::translate("Settings_ReaderLayout", "Overall", Q_NULLPTR));
        BackgroundType->setText(QApplication::translate("Settings_ReaderLayout", "Background type", Q_NULLPTR));
        BackgroundTypeBox->clear();
        BackgroundTypeBox->insertItems(0, QStringList()
         << QApplication::translate("Settings_ReaderLayout", "Image", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "Color", Q_NULLPTR)
        );
        BackgroundImage->setText(QApplication::translate("Settings_ReaderLayout", "Background image", Q_NULLPTR));
        BackgroundImageBox->setText(QApplication::translate("Settings_ReaderLayout", "Standart image", Q_NULLPTR));
        BackgroundColor->setText(QApplication::translate("Settings_ReaderLayout", "Background color", Q_NULLPTR));
        BackgroundColorBox->setText(QApplication::translate("Settings_ReaderLayout", "some color", Q_NULLPTR));
        ColumnNumber->setText(QApplication::translate("Settings_ReaderLayout", "Number of text columns", Q_NULLPTR));
        TextAntiAliasing->setText(QApplication::translate("Settings_ReaderLayout", "Text anti-aliasing", Q_NULLPTR));
        TextAntiAliasingBox->clear();
        TextAntiAliasingBox->insertItems(0, QStringList()
         << QApplication::translate("Settings_ReaderLayout", "Yes", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "No", Q_NULLPTR)
        );
        ParagraphLeftIdent->setText(QApplication::translate("Settings_ReaderLayout", "Paragraph left indent", Q_NULLPTR));
        ParagraphLeftIdentBox->clear();
        ParagraphLeftIdentBox->insertItems(0, QStringList()
         << QApplication::translate("Settings_ReaderLayout", "0", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "1", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "2", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "3", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "4", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "5", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "6", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "7", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "8", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "9", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "10", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "11", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "12", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "13", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "14", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "15", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "16", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "17", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "18", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "19", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "20", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "21", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "22", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "24", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "26", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "27", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "28", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "29", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "30", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "31", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "32", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "33", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "34", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "35", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "36", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "37", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "38", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "39", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "40", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "41", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "42", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "43", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "44", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "45", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "46", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "47", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "48", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "49", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "50", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "51", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "52", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "53", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "54", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "55", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "56", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "57", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "58", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "59", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "60", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "61", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "62", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "63", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "64", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "65", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "66", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "67", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "68", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "69", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "70", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "71", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "72", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "73", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "74", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "75", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "76", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "77", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "78", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "79", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "80", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "81", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "82", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "83", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "84", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "85", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "86", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "87", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "88", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "89", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "90", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "91", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "92", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "93", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "94", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "95", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "96", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "97", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "98", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "99", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "100", Q_NULLPTR)
        );
        ParagraphTopIdent->setText(QApplication::translate("Settings_ReaderLayout", "Paragraph top indent", Q_NULLPTR));
        ParagraphTopIdentBox->clear();
        ParagraphTopIdentBox->insertItems(0, QStringList()
         << QApplication::translate("Settings_ReaderLayout", "0", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "1", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "2", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "3", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "4", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "5", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "6", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "7", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "8", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "9", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "10", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "11", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "12", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "13", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "14", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "15", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "16", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "17", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "18", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "19", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "20", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "21", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "22", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "24", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "26", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "27", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "28", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "29", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "30", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "31", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "32", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "33", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "34", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "35", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "36", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "37", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "38", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "39", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "40", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "41", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "42", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "43", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "44", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "45", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "46", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "47", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "48", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "49", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "50", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "51", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "52", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "53", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "54", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "55", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "56", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "57", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "58", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "59", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "60", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "61", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "62", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "63", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "64", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "65", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "66", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "67", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "68", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "69", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "70", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "71", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "72", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "73", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "74", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "75", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "76", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "77", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "78", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "79", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "80", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "81", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "82", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "83", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "84", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "85", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "86", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "87", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "88", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "89", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "90", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "91", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "92", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "93", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "94", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "95", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "96", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "97", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "98", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "99", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "100", Q_NULLPTR)
        );
        TextLeftIdent->setText(QApplication::translate("Settings_ReaderLayout", "Text left indent", Q_NULLPTR));
        TextLeftIdentBox->clear();
        TextLeftIdentBox->insertItems(0, QStringList()
         << QApplication::translate("Settings_ReaderLayout", "0", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "1", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "2", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "3", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "4", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "5", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "6", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "7", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "8", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "9", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "10", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "11", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "12", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "13", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "14", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "15", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "16", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "17", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "18", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "19", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "20", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "21", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "22", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "24", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "26", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "27", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "28", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "29", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "30", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "31", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "32", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "33", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "34", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "35", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "36", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "37", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "38", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "39", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "40", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "41", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "42", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "43", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "44", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "45", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "46", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "47", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "48", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "49", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "50", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "51", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "52", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "53", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "54", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "55", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "56", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "57", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "58", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "59", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "60", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "61", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "62", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "63", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "64", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "65", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "66", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "67", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "68", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "69", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "70", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "71", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "72", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "73", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "74", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "75", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "76", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "77", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "78", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "79", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "80", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "81", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "82", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "83", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "84", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "85", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "86", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "87", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "88", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "89", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "90", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "91", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "92", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "93", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "94", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "95", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "96", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "97", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "98", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "99", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "100", Q_NULLPTR)
        );
        TextRightIndent->setText(QApplication::translate("Settings_ReaderLayout", "Text right indent", Q_NULLPTR));
        TextRightIdentBox->clear();
        TextRightIdentBox->insertItems(0, QStringList()
         << QApplication::translate("Settings_ReaderLayout", "0", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "1", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "2", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "3", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "4", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "5", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "6", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "7", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "8", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "9", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "10", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "11", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "12", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "13", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "14", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "15", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "16", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "17", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "18", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "19", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "20", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "21", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "22", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "24", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "26", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "27", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "28", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "29", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "30", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "31", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "32", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "33", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "34", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "35", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "36", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "37", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "38", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "39", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "40", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "41", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "42", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "43", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "44", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "45", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "46", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "47", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "48", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "49", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "50", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "51", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "52", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "53", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "54", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "55", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "56", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "57", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "58", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "59", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "60", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "61", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "62", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "63", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "64", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "65", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "66", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "67", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "68", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "69", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "70", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "71", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "72", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "73", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "74", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "75", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "76", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "77", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "78", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "79", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "80", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "81", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "82", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "83", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "84", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "85", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "86", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "87", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "88", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "89", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "90", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "91", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "92", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "93", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "94", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "95", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "96", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "97", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "98", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "99", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "100", Q_NULLPTR)
        );
        TextTopIdent->setText(QApplication::translate("Settings_ReaderLayout", "Text top indent", Q_NULLPTR));
        TextTopIndentBox->clear();
        TextTopIndentBox->insertItems(0, QStringList()
         << QApplication::translate("Settings_ReaderLayout", "0", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "1", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "2", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "3", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "4", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "5", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "6", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "7", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "8", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "9", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "10", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "11", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "12", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "13", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "14", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "15", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "16", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "17", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "18", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "19", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "20", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "21", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "22", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "24", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "26", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "27", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "28", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "29", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "30", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "31", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "32", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "33", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "34", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "35", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "36", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "37", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "38", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "39", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "40", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "41", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "42", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "43", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "44", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "45", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "46", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "47", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "48", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "49", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "50", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "51", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "52", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "53", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "54", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "55", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "56", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "57", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "58", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "59", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "60", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "61", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "62", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "63", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "64", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "65", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "66", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "67", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "68", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "69", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "70", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "71", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "72", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "73", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "74", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "75", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "76", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "77", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "78", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "79", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "80", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "81", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "82", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "83", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "84", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "85", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "86", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "87", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "88", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "89", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "90", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "91", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "92", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "93", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "94", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "95", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "96", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "97", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "98", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "99", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "100", Q_NULLPTR)
        );
        TextBottomIndent->setText(QApplication::translate("Settings_ReaderLayout", "Text bottom indent", Q_NULLPTR));
        TextBottomIndentBox->clear();
        TextBottomIndentBox->insertItems(0, QStringList()
         << QApplication::translate("Settings_ReaderLayout", "0", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "1", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "2", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "3", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "4", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "5", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "6", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "7", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "8", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "9", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "10", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "11", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "12", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "13", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "14", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "15", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "16", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "17", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "18", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "19", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "20", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "21", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "22", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "24", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "26", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "27", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "28", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "29", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "30", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "31", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "32", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "33", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "34", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "35", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "36", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "37", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "38", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "39", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "40", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "41", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "42", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "43", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "44", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "45", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "46", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "47", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "48", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "49", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "50", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "51", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "52", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "53", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "54", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "55", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "56", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "57", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "58", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "59", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "60", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "61", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "62", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "63", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "64", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "65", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "66", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "67", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "68", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "69", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "70", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "71", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "72", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "73", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "74", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "75", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "76", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "77", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "78", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "79", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "80", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "81", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "82", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "83", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "84", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "85", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "86", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "87", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "88", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "89", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "90", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "91", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "92", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "93", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "94", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "95", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "96", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "97", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "98", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "99", Q_NULLPTR)
         << QApplication::translate("Settings_ReaderLayout", "100", Q_NULLPTR)
        );
        TextExample->setHtml(QApplication::translate("Settings_ReaderLayout", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; line-height:100%;\"><span style=\" font-size:12pt; font-weight:792; color:#ff5500;\">\320\223\320\260\321\200\321\200\320\270 \320\223\320\260\321\200\321\200\320\270\321\201\320\276\320\275</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; line-height:100%;\"><span style=\" font-size:12pt; font-weight:792; color:#ff5500;\">\302\253\320\235\320\276\320\262\321\213\320\265 \320\277\321\200\320\270\320\272\320\273\321\216\321\207\320\265\320\275"
                        "\320\270\321\217 \320\241\321\202\320\260\320\273\321\214\320\275\320\276\320\271 \320\232\321\200\321\213\321\201\321\213\302\273</span></p>\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; line-height:100%;\"><span style=\" font-size:8pt; font-style:italic; color:#55aa7f;\">\320\234\320\276\320\271\321\200\320\265 \320\270 \320\242\320\276\320\264\320\264\321\203, \321\207\321\214\320\270 \320\273\321\216\320\261\321\217\321\211\320\260\321\217 \320\277\320\276\320\274\320\276\321\211\321\214 \320\270 \320\277\320\276\320\264\320\264\320\265\321\200\320\266\320\272\320\260 \320\277\320\276\320\267\320\262\320\276\320\273\320\270\320\273\320\270 \321\215\321\202\320\276\320\271 \320\272\320\275\320\270\320\263\320\265 \320\277\320\276\321\217\320\262\320\270\321\202\321\214\321\201\321\217 \320\275\320\260 \321\201\320\262\320\265\321\202.</span></p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; ma"
                        "rgin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:50px; line-height:100%;\"><span style=\" font-size:10pt; color:#000000;\">\320\241\321\202\320\276\321\217\320\273\320\260 \320\267\320\260\320\262\320\265\321\202\320\275\320\260\321\217 \320\277\320\276\321\200\320\260 \320\264\320\275\321\217, \320\277\320\276\321\201\321\217\320\263\320\260\321\202\321\214 \320\275\320\260 \320\272\320\276\321\202\320\276\321\200\321\203\321\216 \342\200\224 \321\201\320\262\321\217\321\202\320\276\321\202\320\260\321\202\321\201\321\202\320\262\320\276, \320\276\320\264\320\270\320\275 \320\270\320\267 \321\200\320\265\320\264\321\207\320\260\320\271\321\210\320\270\321\205 \320\274\320\276\320\274\320\265\320\275\321\202\320\276\320\262 \320\262 \320\266\320\270\320\267\320\275\320\270, \320\272\320\276\320\263\320\264\320\260 \320\262\321\201\320\265 \320\270\320\264\320\265\321\202 \320\261\320\265\320\267 \321\201\321\203\321\207\320\272\320\260 \320\261\320\265\320\267 \320\267\320\260\320\264\320\276\321"
                        "\200\320\270\320\275\320\272\320\270. \320\236\321\202\320\272\320\270\320\275\321\203\320\262\321\210\320\270\321\201\321\214 \320\275\320\260 \321\201\320\277\320\270\320\275\320\272\321\203 \320\272\321\200\320\265\321\201\320\273\320\260, \321\217 \320\262\320\272\320\273\321\216\321\207\320\270\320\273 \321\201\321\202\320\265\321\200\320\265\320\276 \321\200\320\260\320\267\320\274\320\265\321\200\320\276\320\274 \321\201 \320\272\320\276\320\274\320\275\320\260\321\202\321\203 \342\200\224 \321\201\320\260\320\261\320\262\321\203\321\204\320\265\321\200\321\213 \321\201 \320\273\320\276\320\272\320\276\320\274\320\276\321\202\320\270\320\262, \320\277\320\270\321\211\320\260\320\273\320\272\320\270, \320\276\321\202 \320\272\320\276\321\202\320\276\321\200\321\213\321\205 \320\267\321\203\320\261\321\213 \320\275\320\276\321\216\321\202, \342\200\224 \320\270 \320\262\320\276\320\267\320\264\321\203\321\205 \320\275\320\260\320\277\320\276\320\270\320\273\320\260 \320\261\320\273\320\260\320\263\320\276"
                        "\320\264\320\260\321\202\321\214 \321\202\320\276\320\272\320\260\321\202\321\202\321\213 \320\270 \321\204\321\203\320\263\320\270 \320\230. \320\241. \320\221\320\260\321\205\320\260.</span></p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:50px; line-height:100%;\"><span style=\" font-size:10pt; color:#000000;\">\320\234\320\276\321\217 \320\273\320\260\320\264\320\276\320\275\321\214 \320\273\320\260\321\201\320\272\320\260\320\273\320\260 \321\201\321\202\320\260\320\272\320\260\320\275 \321\202\320\276\320\273\321\214\320\272\320\276 \321\207\321\202\320\276 \320\275\320\260\320\273\320\270\321\202\320\276\320\263\320\276 \321\202\321\200\320\265\321\205\321\201\320\276\321\202\320\273\320\265\321\202\320\275\320\265\320\263\320\276, \320\264\321\200\320\260\320\263\320\276\321\206\320\265\320\275\320\275\320\276\320\263\320\276 \320\261\321\203\321\200\320\261\320\276\320\275\320\260, \320\276\321\205\320\273\320\260"
                        "\320\266\320\264\320\265\320\275\320\275\320\276\320\263\320\276 \320\272\321\203\320\261\320\270\320\272\320\260\320\274\320\270 \320\274\320\270\320\273\320\273\320\270\320\276\320\275\320\276\320\273\320\265\321\202\320\275\320\265\320\263\320\276 \320\273\321\214\320\264\320\260, \320\264\320\276\321\201\321\202\320\260\320\262\320\273\320\265\320\275\320\275\320\276\320\263\320\276 \321\201 \320\276\320\264\320\275\320\276\320\271 \320\270\320\267 \320\262\320\275\320\265\321\210\320\275\320\270\321\205 \320\277\320\273\320\260\320\275\320\265\321\202. \320\237\321\200\320\276\321\201\321\202\320\276 \320\270\320\264\320\265\320\260\320\273\321\214\320\275\320\276! \320\221\320\273\320\260\320\263\320\276\320\264\321\203\321\210\320\275\320\276 \321\203\320\273\321\213\320\261\320\275\321\203\320\262\321\210\320\270\321\201\321\214, \321\217 \320\277\320\276\320\264\320\275\320\265\321\201 \321\201\321\202\320\260\320\272\320\260\320\275 \320\272 \320\263\321\203\320\261\320\260\320\274.</span></p>\n"
"<p"
                        " align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:50px; line-height:100%;\"><span style=\" font-size:10pt; color:#000000;\">\320\230 \321\202\321\203\321\202 \320\262 \321\200\320\260\320\271 \320\262\321\202\320\276\321\200\320\263\320\273\320\276\321\201\321\214 \320\275\320\265\321\207\321\202\320\276 \321\207\321\203\320\266\320\264\320\276\320\265, \320\261\321\203\320\264\321\202\320\276 \320\277\321\203\320\273\321\214\321\201\320\270\321\200\321\203\321\216\321\211\320\260\321\217 \320\267\321\203\320\261\320\275\320\260\321\217 \320\261\320\276\320\273\321\214 \320\270\320\273\320\270 \321\207\321\203\321\202\321\214 \321\201\320\273\321\213\321\210\320\275\321\213\320\271 \320\272\320\276\320\274\320\260\321\200\320\270\320\275\321\213\320\271 \320\267\321\203\320\264. \320\241 \320\274\320\276\320\263\321\203\321\207\320\270\320\274 \320\221\320\260\321\205\320\276\320\274 \321\201\321\205\320\273\320\265\321\201\321\202"
                        "\320\275\321\203\320\273\320\276\321\201\321\214 \321\202\320\276\320\275\320\265\320\275\321\214\320\272\320\276\320\265 \321\202\321\200\320\265\320\275\321\214\320\272\320\260\320\275\321\214\320\265. \320\247\321\203\320\262\321\201\321\202\320\262\321\203\321\217, \320\272\320\260\320\272 \320\263\321\203\320\261\321\213 \320\270\321\201\320\272\320\260\320\266\320\260\320\265\321\202 \320\276\321\201\320\272\320\260\320\273, \321\217 \320\272\320\276\321\201\320\275\321\203\320\273\321\201\321\217 \321\200\320\265\320\263\321\203\320\273\321\217\321\202\320\276\321\200\320\260 \320\263\321\200\320\276\320\274\320\272\320\276\321\201\321\202\320\270, \320\270 \320\262\320\265\320\273\320\270\320\272\320\270\320\271 \320\276\321\200\320\263\320\260\320\275 \320\266\320\260\320\273\320\276\320\261\320\275\320\276 \320\267\320\260\321\205\320\273\320\265\320\261\320\275\321\203\320\273\321\201\321\217 \320\274\320\276\320\273\321\207\320\260\320\275\320\270\320\265\320\274. \320\230 \320\264\320\262\320\265\321"
                        "\200\320\275\320\276\320\271 \320\267\320\262\320\276\320\275\320\276\320\272 \320\277\321\200\320\276\320\267\320\262\321\203\321\207\320\260\320\273 \320\262\320\277\320\276\320\273\320\275\320\265 \320\276\321\202\321\207\320\265\321\202\320\273\320\270\320\262\320\276.</span></p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:50px; line-height:100%;\"><span style=\" font-size:10pt; color:#000000;\">\320\224\320\270\320\275\321\214-\320\264\320\270\320\275\321\214\342\200\246</span></p></body></html>", Q_NULLPTR));
        SaveButton->setText(QApplication::translate("Settings_ReaderLayout", "Save settings", Q_NULLPTR));
        label->setText(QApplication::translate("Settings_ReaderLayout", "Style:", Q_NULLPTR));
        NewStyleName->setText(QApplication::translate("Settings_ReaderLayout", "New style...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Settings_ReaderLayout: public Ui_Settings_ReaderLayout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_READERLAYOUT_H

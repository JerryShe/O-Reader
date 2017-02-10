/********************************************************************************
** Form generated from reading UI file 'library_layout.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIBRARY_LAYOUT_H
#define UI_LIBRARY_LAYOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LibraryLayout
{
public:
    QVBoxLayout *VLayout;
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

    void setupUi(QWidget *LibraryLayout)
    {
        if (LibraryLayout->objectName().isEmpty())
            LibraryLayout->setObjectName(QStringLiteral("LibraryLayout"));
        LibraryLayout->resize(929, 542);
        VLayout = new QVBoxLayout(LibraryLayout);
        VLayout->setSpacing(0);
        VLayout->setObjectName(QStringLiteral("VLayout"));
        VLayout->setContentsMargins(0, 0, 0, 0);
        LibraryButtons = new QHBoxLayout();
        LibraryButtons->setSpacing(0);
        LibraryButtons->setObjectName(QStringLiteral("LibraryButtons"));
        LibraryButtons->setSizeConstraint(QLayout::SetMinimumSize);
        LibraryButtons->setContentsMargins(-1, 0, -1, -1);
        _Find = new QPushButton(LibraryLayout);
        _Find->setObjectName(QStringLiteral("_Find"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(_Find->sizePolicy().hasHeightForWidth());
        _Find->setSizePolicy(sizePolicy);
        _Find->setMinimumSize(QSize(120, 30));
        _Find->setMaximumSize(QSize(16777215, 30));
        _Find->setCheckable(true);

        LibraryButtons->addWidget(_Find);

        _Sort = new QPushButton(LibraryLayout);
        _Sort->setObjectName(QStringLiteral("_Sort"));
        _Sort->setMinimumSize(QSize(120, 30));
        _Sort->setMaximumSize(QSize(16777215, 30));
        _Sort->setStyleSheet(QStringLiteral(""));

        LibraryButtons->addWidget(_Sort);

        _SortBox = new QComboBox(LibraryLayout);
        _SortBox->setObjectName(QStringLiteral("_SortBox"));
        _SortBox->setMinimumSize(QSize(0, 30));
        _SortBox->setStyleSheet(QStringLiteral(""));
        _SortBox->setInsertPolicy(QComboBox::InsertAtTop);
        _SortBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        _SortBox->setIconSize(QSize(0, 0));
        _SortBox->setFrame(false);

        LibraryButtons->addWidget(_SortBox);

        _Group = new QPushButton(LibraryLayout);
        _Group->setObjectName(QStringLiteral("_Group"));
        _Group->setEnabled(false);
        _Group->setMinimumSize(QSize(120, 30));
        _Group->setMaximumSize(QSize(16777215, 30));

        LibraryButtons->addWidget(_Group);

        _GroupBox = new QComboBox(LibraryLayout);
        _GroupBox->setObjectName(QStringLiteral("_GroupBox"));
        _GroupBox->setEnabled(false);
        _GroupBox->setMinimumSize(QSize(101, 30));
        _GroupBox->setStyleSheet(QStringLiteral(""));
        _GroupBox->setInsertPolicy(QComboBox::InsertAtTop);
        _GroupBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        _GroupBox->setFrame(false);

        LibraryButtons->addWidget(_GroupBox);

        _AddBooks = new QPushButton(LibraryLayout);
        _AddBooks->setObjectName(QStringLiteral("_AddBooks"));
        sizePolicy.setHeightForWidth(_AddBooks->sizePolicy().hasHeightForWidth());
        _AddBooks->setSizePolicy(sizePolicy);
        _AddBooks->setMinimumSize(QSize(120, 30));
        _AddBooks->setMaximumSize(QSize(16777215, 30));

        LibraryButtons->addWidget(_AddBooks);

        _Delete = new QPushButton(LibraryLayout);
        _Delete->setObjectName(QStringLiteral("_Delete"));
        sizePolicy.setHeightForWidth(_Delete->sizePolicy().hasHeightForWidth());
        _Delete->setSizePolicy(sizePolicy);
        _Delete->setMinimumSize(QSize(120, 30));
        _Delete->setMaximumSize(QSize(16777215, 30));

        LibraryButtons->addWidget(_Delete);

        _ChangeViewMode = new QPushButton(LibraryLayout);
        _ChangeViewMode->setObjectName(QStringLiteral("_ChangeViewMode"));
        _ChangeViewMode->setMinimumSize(QSize(30, 30));
        _ChangeViewMode->setMaximumSize(QSize(30, 30));
        _ChangeViewMode->setText(QStringLiteral(""));
        _ChangeViewMode->setShortcut(QStringLiteral(""));
        _ChangeViewMode->setCheckable(true);

        LibraryButtons->addWidget(_ChangeViewMode);

        _Upscale = new QPushButton(LibraryLayout);
        _Upscale->setObjectName(QStringLiteral("_Upscale"));
        _Upscale->setMinimumSize(QSize(30, 30));
        _Upscale->setMaximumSize(QSize(30, 30));
        _Upscale->setText(QStringLiteral(""));
        _Upscale->setShortcut(QStringLiteral(""));

        LibraryButtons->addWidget(_Upscale);

        _Downscale = new QPushButton(LibraryLayout);
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

        VLayout->addLayout(LibraryButtons);


        retranslateUi(LibraryLayout);

        QMetaObject::connectSlotsByName(LibraryLayout);
    } // setupUi

    void retranslateUi(QWidget *LibraryLayout)
    {
        LibraryLayout->setWindowTitle(QApplication::translate("LibraryLayout", "Form", Q_NULLPTR));
        _Find->setText(QApplication::translate("LibraryLayout", "Find", Q_NULLPTR));
        _Sort->setText(QApplication::translate("LibraryLayout", "Sort by: ", Q_NULLPTR));
        _SortBox->clear();
        _SortBox->insertItems(0, QStringList()
         << QApplication::translate("LibraryLayout", "Date", Q_NULLPTR)
         << QApplication::translate("LibraryLayout", "Author", Q_NULLPTR)
         << QApplication::translate("LibraryLayout", "Title", Q_NULLPTR)
        );
        _Group->setText(QApplication::translate("LibraryLayout", "Group by: ", Q_NULLPTR));
        _GroupBox->clear();
        _GroupBox->insertItems(0, QStringList()
         << QApplication::translate("LibraryLayout", "None", Q_NULLPTR)
         << QApplication::translate("LibraryLayout", "Author", Q_NULLPTR)
         << QApplication::translate("LibraryLayout", "Title", Q_NULLPTR)
         << QApplication::translate("LibraryLayout", "Genre", Q_NULLPTR)
         << QApplication::translate("LibraryLayout", "Book series", Q_NULLPTR)
        );
        _AddBooks->setText(QApplication::translate("LibraryLayout", "Add", Q_NULLPTR));
        _Delete->setText(QApplication::translate("LibraryLayout", "Delete", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LibraryLayout: public Ui_LibraryLayout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIBRARY_LAYOUT_H

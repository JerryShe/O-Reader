/********************************************************************************
** Form generated from reading UI file 'synchronization_layout.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYNCHRONIZATION_LAYOUT_H
#define UI_SYNCHRONIZATION_LAYOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SynchronizationLayout
{
public:

    void setupUi(QWidget *SynchronizationLayout)
    {
        if (SynchronizationLayout->objectName().isEmpty())
            SynchronizationLayout->setObjectName(QStringLiteral("SynchronizationLayout"));
        SynchronizationLayout->resize(400, 300);

        retranslateUi(SynchronizationLayout);

        QMetaObject::connectSlotsByName(SynchronizationLayout);
    } // setupUi

    void retranslateUi(QWidget *SynchronizationLayout)
    {
        SynchronizationLayout->setWindowTitle(QApplication::translate("SynchronizationLayout", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SynchronizationLayout: public Ui_SynchronizationLayout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYNCHRONIZATION_LAYOUT_H

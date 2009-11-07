/********************************************************************************
** Form generated from reading ui file 'stepmenu.ui'
**
** Created: Fri Nov 6 12:20:00 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_STEPMENU_H
#define UI_STEPMENU_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StepMenu
{
public:

    void setupUi(QWidget *StepMenu)
    {
        if (StepMenu->objectName().isEmpty())
            StepMenu->setObjectName(QString::fromUtf8("StepMenu"));
        StepMenu->resize(400, 300);

        retranslateUi(StepMenu);

        QMetaObject::connectSlotsByName(StepMenu);
    } // setupUi

    void retranslateUi(QWidget *StepMenu)
    {
        StepMenu->setWindowTitle(QApplication::translate("StepMenu", "Form", 0, QApplication::UnicodeUTF8));
        StepMenu->setStyleSheet(QApplication::translate("StepMenu", "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0));", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(StepMenu);
    } // retranslateUi

};

namespace Ui {
    class StepMenu: public Ui_StepMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STEPMENU_H

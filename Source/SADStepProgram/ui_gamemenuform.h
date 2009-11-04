/********************************************************************************
** Form generated from reading ui file 'gamemenuform.ui'
**
** Created: Thu Oct 29 16:24:46 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_GAMEMENUFORM_H
#define UI_GAMEMENUFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *gameSelectBtn;
    QPushButton *optionsSelectBtn;
    QPushButton *exitBtn;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(223, 133);
        verticalLayout = new QVBoxLayout(Form);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gameSelectBtn = new QPushButton(Form);
        gameSelectBtn->setObjectName(QString::fromUtf8("gameSelectBtn"));

        verticalLayout->addWidget(gameSelectBtn);

        optionsSelectBtn = new QPushButton(Form);
        optionsSelectBtn->setObjectName(QString::fromUtf8("optionsSelectBtn"));

        verticalLayout->addWidget(optionsSelectBtn);

        exitBtn = new QPushButton(Form);
        exitBtn->setObjectName(QString::fromUtf8("exitBtn"));

        verticalLayout->addWidget(exitBtn);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        gameSelectBtn->setText(QApplication::translate("Form", "Start Game", 0, QApplication::UnicodeUTF8));
        optionsSelectBtn->setText(QApplication::translate("Form", "Options", 0, QApplication::UnicodeUTF8));
        exitBtn->setText(QApplication::translate("Form", "Exit", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(Form);
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEMENUFORM_H

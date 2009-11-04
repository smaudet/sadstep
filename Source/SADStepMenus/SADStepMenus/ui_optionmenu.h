/********************************************************************************
** Form generated from reading ui file 'optionmenu.ui'
**
** Created: Sat Oct 24 20:36:12 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_OPTIONMENU_H
#define UI_OPTIONMENU_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QRadioButton *easy;
    QRadioButton *normal;
    QRadioButton *hard;
    QRadioButton *expert;
    QVBoxLayout *verticalLayout_2;
    QSlider *horizontalSlider;
    QSlider *horizontalSlider_2;
    QPushButton *cancelBtn;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(249, 94);
        verticalLayout_3 = new QVBoxLayout(Form);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        easy = new QRadioButton(Form);
        easy->setObjectName(QString::fromUtf8("easy"));

        horizontalLayout->addWidget(easy);

        normal = new QRadioButton(Form);
        normal->setObjectName(QString::fromUtf8("normal"));

        horizontalLayout->addWidget(normal);

        hard = new QRadioButton(Form);
        hard->setObjectName(QString::fromUtf8("hard"));

        horizontalLayout->addWidget(hard);

        expert = new QRadioButton(Form);
        expert->setObjectName(QString::fromUtf8("expert"));

        horizontalLayout->addWidget(expert);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalSlider = new QSlider(Form);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(horizontalSlider);

        horizontalSlider_2 = new QSlider(Form);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(horizontalSlider_2);


        verticalLayout_3->addLayout(verticalLayout_2);

        cancelBtn = new QPushButton(Form);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));

        verticalLayout_3->addWidget(cancelBtn);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        easy->setText(QApplication::translate("Form", "Easy", 0, QApplication::UnicodeUTF8));
        normal->setText(QApplication::translate("Form", "Normal", 0, QApplication::UnicodeUTF8));
        hard->setText(QApplication::translate("Form", "Hard", 0, QApplication::UnicodeUTF8));
        expert->setText(QApplication::translate("Form", "Expert", 0, QApplication::UnicodeUTF8));
        cancelBtn->setText(QApplication::translate("Form", "Cancel", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(Form);
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONMENU_H

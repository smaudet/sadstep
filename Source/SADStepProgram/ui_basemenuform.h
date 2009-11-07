/********************************************************************************
** Form generated from reading ui file 'basemenuform.ui'
**
** Created: Fri Nov 6 15:07:19 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_BASEMENUFORM_H
#define UI_BASEMENUFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BaseMenuForm
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *cancelBtn;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *BaseMenuForm)
    {
        if (BaseMenuForm->objectName().isEmpty())
            BaseMenuForm->setObjectName(QString::fromUtf8("BaseMenuForm"));
        BaseMenuForm->resize(487, 360);
        verticalLayout = new QVBoxLayout(BaseMenuForm);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(BaseMenuForm);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMaximumSize(QSize(16777215, 100));
        QFont font;
        font.setFamily(QString::fromUtf8("Chiller"));
        font.setPointSize(48);
        frame->setFont(font);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Chiller"));
        font1.setPointSize(36);
        label->setFont(font1);
        label->setTextFormat(Qt::RichText);
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(false);

        verticalLayout_2->addWidget(label);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(BaseMenuForm);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(frame_2);

        frame_3 = new QFrame(BaseMenuForm);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setMaximumSize(QSize(16777215, 49));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(90, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(frame_3);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));
        okBtn->setIconSize(QSize(100, 100));

        horizontalLayout->addWidget(okBtn);

        horizontalSpacer_2 = new QSpacerItem(86, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        cancelBtn = new QPushButton(frame_3);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setIconSize(QSize(100, 100));

        horizontalLayout->addWidget(cancelBtn);

        horizontalSpacer_3 = new QSpacerItem(90, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addWidget(frame_3);


        retranslateUi(BaseMenuForm);

        QMetaObject::connectSlotsByName(BaseMenuForm);
    } // setupUi

    void retranslateUi(QWidget *BaseMenuForm)
    {
        BaseMenuForm->setWindowTitle(QApplication::translate("BaseMenuForm", "Form", 0, QApplication::UnicodeUTF8));
        BaseMenuForm->setStyleSheet(QApplication::translate("BaseMenuForm", "background-color: qconicalgradient(cx:0.5, cy:0.5, angle:0, stop:0 rgba(35, 40, 3, 255), stop:0.16 rgba(136, 106, 22, 255), stop:0.225 rgba(166, 140, 41, 255), stop:0.285 rgba(204, 181, 74, 255), stop:0.345 rgba(235, 219, 102, 255), stop:0.415 rgba(245, 236, 112, 255), stop:0.52 rgba(209, 190, 76, 255), stop:0.57 rgba(187, 156, 51, 255), stop:0.635 rgba(168, 142, 42, 255), stop:0.695 rgba(202, 174, 68, 255), stop:0.75 rgba(218, 202, 86, 255), stop:0.815 rgba(208, 187, 73, 255), stop:0.88 rgba(187, 156, 51, 255), stop:0.935 rgba(137, 108, 26, 255), stop:1 rgba(35, 40, 3, 255));", 0, QApplication::UnicodeUTF8));
        frame->setStyleSheet(QApplication::translate("BaseMenuForm", "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0));", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("BaseMenuForm", "SADStep", 0, QApplication::UnicodeUTF8));
        frame_2->setStyleSheet(QApplication::translate("BaseMenuForm", "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0));", 0, QApplication::UnicodeUTF8));
        frame_3->setStyleSheet(QApplication::translate("BaseMenuForm", "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0));", 0, QApplication::UnicodeUTF8));
        okBtn->setText(QApplication::translate("BaseMenuForm", "OK", 0, QApplication::UnicodeUTF8));
        cancelBtn->setText(QApplication::translate("BaseMenuForm", "Cancel", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(BaseMenuForm);
    } // retranslateUi

};

namespace Ui {
    class BaseMenuForm: public Ui_BaseMenuForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASEMENUFORM_H

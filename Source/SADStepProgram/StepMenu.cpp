#include "StepMenu.h"
#include "ui_stepmenu.h"

StepMenu::StepMenu(BaseMenuForm* form, QWidget* parent) :
        QWidget(parent),
        m_ui(new Ui::StepMenu)
{
    m_ui->setupUi(this);
    this->form = form;
}

StepMenu::~StepMenu()
{
    qDebug() << "StepMenu";
    delete m_ui;
    qDebug() << "StepMenu";
}

QWidget* StepMenu::getWidget() {
    return internalWidgetRep;
}

void StepMenu::setWidgetRep(QWidget* internalWidgetRep){
    this->internalWidgetRep=internalWidgetRep;
}

void StepMenu::changeEvent(QEvent *e) {
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

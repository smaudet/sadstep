#ifndef STEPMENU_H
#define STEPMENU_H

#include <QWidget>
#include <QEvent>
#include <QtDebug>
#include "BaseMenuForm.h"

class BaseMenuForm;

namespace Ui {
    class StepMenu;
}

class StepMenu: public QWidget
{
public:
    StepMenu(BaseMenuForm* form, QWidget *parent = 0);
    ~StepMenu();
    QWidget* getWidget();

protected:
    void setWidgetRep(QWidget* internalWidgetRep);
    BaseMenuForm* form;

private:
    QWidget* internalWidgetRep;
    Ui::StepMenu* m_ui;
    void changeEvent(QEvent *e);
};

#endif // STEPMENU_H

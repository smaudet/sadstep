#include "optionmenu.h"

OptionMenu::OptionMenu(BaseMenuForm* form,QWidget* parent): StepMenu(form, parent)
{
    sui = new QFile(":/menus/optionmenu.ui");
    loader = new QUiLoader();
    widget = new QWidget();
    loader->load(sui,widget);
    cancelBtn = widget->findChild<QPushButton*>("cancelBtn");
    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(cancel()));
    this->setWidgetRep(widget);
}
OptionMenu::~OptionMenu() {
    delete sui;
    delete loader;
    delete cancelBtn;
    delete widget;
}
void OptionMenu::cancel() {
    form->goToMenu(1);
}

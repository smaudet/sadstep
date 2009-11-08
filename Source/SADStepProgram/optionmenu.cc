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
    //qDebug() << parent->height() << " at Options Menu";
}
OptionMenu::~OptionMenu() {
    qDebug() << "OptionMenu";
    delete sui;
    delete loader;
    delete cancelBtn;
    delete widget;
    qDebug() << "OptionMenu";
}
void OptionMenu::cancel() {
    form->goToMenu(1);
}

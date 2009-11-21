#include "profilemenu.h"

ProfileMenu::ProfileMenu(BaseMenuForm* form, QWidget* parent): StepMenu(form, parent)
{
    sui = new QFile(":/menus/profilemenu.ui");
    loader = new QUiLoader();
    widget = new QWidget();
    loader->load(sui,widget);
    logIn = widget->findChild<QPushButton*>("logInBtn");
    connect(logIn, SIGNAL(clicked()), this, SLOT(menuSelected5()));
    this->setWidgetRep(widget->findChild<QWidget*>("Form"));
    formWidget = widget->findChild<QWidget*>("Form");
}
ProfileMenu::~ProfileMenu() {
    delete sui;
    delete loader;
    delete logIn;
    delete widget;
    delete formWidget;
}

void ProfileMenu::menuSelected5() {
    form->goToMenu(1);
}

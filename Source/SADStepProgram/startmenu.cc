#include "startmenu.h"
#include "basemenuform.h"


StartMenu::StartMenu(BaseMenuForm* form,QWidget* parent): StepMenu(form,parent)
{
    sui = new QFile(":/menus/mainmenu.ui");
    loader = new QUiLoader();
    widget = new QWidget();
    loader->load(sui,widget);
    startBtn = widget->findChild<QPushButton*>("pushButton");
    connect(startBtn, SIGNAL(clicked()), this, SLOT(menuSelected1()));
    this->setWidgetRep(widget->findChild<QWidget*>("Form"));
}
void StartMenu::menuSelected1() {
    form->goToMenu(5);
}
StartMenu::~StartMenu() {
    qDebug() << "StartMenu";
    delete sui;
    delete loader;
    delete startBtn;
    delete widget;
    qDebug() << "StartMenu";
}

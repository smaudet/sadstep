#include "startmenu.h"
#include "basemenuform.h"
#include <QPushButton>

StartMenu::StartMenu(BaseMenuForm* form,QWidget* parent): StepMenu(form,parent)
{
    sui = new QFile(":/menus/mainmenu.ui");
    loader = new QUiLoader();
    widget = new QWidget();
    loader->load(sui,widget);
    startBtn = widget->findChild<QPushButton*>("pushButton");
    connect(startBtn, SIGNAL(clicked()), this, SLOT(menuSelected1()));
    this->setWidgetRep(widget);
}
void StartMenu::menuSelected1() {
    form->goToMenu(1);
}
StartMenu::~StartMenu() {
    qDebug() << "wave";
    delete sui;
    qDebug() << "wave1";
    delete loader;
    qDebug() << "wave2";
    delete startBtn;
    qDebug() << "wave3";
    delete widget;
    qDebug() << "wave4";
}

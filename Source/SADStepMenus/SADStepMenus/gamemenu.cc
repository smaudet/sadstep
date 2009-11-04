#include "gamemenu.h"

GameMenu::GameMenu(BaseMenuForm* form, QWidget* parent): StepMenu(form,parent)
{
    sui = new QFile(":/menus/gamemenu.ui");
    loader = new QUiLoader();
    widget = new QWidget();
    loader->load(sui,widget);
    gameStartBtn = widget->findChild<QPushButton*>("gameSelectBtn");
    optionBtn = widget->findChild<QPushButton*>("optionsSelectBtn");
    exitBtn = widget->findChild<QPushButton*>("exitBtn");
    connect(gameStartBtn, SIGNAL(clicked()), this, SLOT(menuSelected2()));
    connect(optionBtn, SIGNAL(clicked()), this, SLOT(menuSelected3()));
    connect(exitBtn, SIGNAL(clicked()), this, SLOT(menuSelected4()));
    this->setWidgetRep(widget);
}
void GameMenu::menuSelected2() {
    form->goToMenu(2);
}
void GameMenu::menuSelected3() {
    form->goToMenu(3);
}
void GameMenu::menuSelected4() {
    form->goToMenu(4);
}
GameMenu::~GameMenu()
{
    delete sui;
    delete loader;
    delete gameStartBtn;
    delete optionBtn;
    delete exitBtn;
    delete widget;
}

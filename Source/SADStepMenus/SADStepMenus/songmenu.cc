#include "songmenu.h"
#include <QFile>
#include <QtUiTools>
#include <QListWidget>

SongMenu::SongMenu(BaseMenuForm* form, QWidget* parent): StepMenu(form, parent)
{
    sui = new QFile(":/menus/song.ui");
    loader = new QUiLoader();
    widget = new QWidget();
    loader->load(sui,widget);
    QListWidget* listWidget = widget->findChild<QListWidget*>("listWidget");
    listWidget->addItem("hah!");
    listWidget->addItem("We did it!");
    this->setWidgetRep(widget);
}

SongMenu::~SongMenu() {
    delete sui;
    delete loader;
    delete widget;
}

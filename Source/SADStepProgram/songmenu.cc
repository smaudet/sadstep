#include "songmenu.h"
#include <QFile>
#include <QtUiTools>
#include <QListWidget>
#include <QtDebug>

SongMenu::SongMenu(BaseMenuForm* form, QWidget* parent): StepMenu(form, parent)
{
    sui = new QFile(":/menus/song.ui");
    loader = new QUiLoader();
    widget = new QWidget();
    loader->load(sui,widget);
    listWidget = widget->findChild<QListWidget*>("listWidget");
    SongCatalogue* const cata = SongCatalogue::getInstance();
    const QList<QString>* list = cata->getFileNames();
    for (int x = 0; x < 20; x++)
    {
        listWidget->addItem(list->at(x));
    }
    this->setWidgetRep(widget);
}

SongMenu::~SongMenu() {
    qDebug() << "SongMenu";
    delete sui;
    delete loader;
    delete widget;
    qDebug() << "SongMenu";
}

const int SongMenu::getIndex()
{
     //const int number = listWidget->currentRow;
     return listWidget->currentRow();
}

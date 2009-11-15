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
    for (int x = 0; x < list->size(); x++)
    {
        listWidget->addItem(list->at(x));
    }
    this->setWidgetRep(widget->findChild<QWidget*>("Form"));
    qDebug() << listWidget->currentRow();
    connect(listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(rowChanged2(int)));

    //qDebug() << parent->height() << " at Song Menu";
}

SongMenu::~SongMenu() {
    qDebug() << "SongMenu";
    delete sui;
    delete listWidget;
    delete loader;
    delete widget;
    qDebug() << "SongMenu";
}

const int SongMenu::getIndex()
{
     //const int number = listWidget->currentRow;

   // qDebug() << listWidget->currentRow();
     qDebug() << "Brittish people";
    return songNumber;


}
void SongMenu::rowChanged2(int billybob)
{
    songNumber = billybob;
}

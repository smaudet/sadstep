#ifndef SONGMENU_H
#define SONGMENU_H

#include <QFile>
#include <QtUiTools>
#include <QWidget>
#include <QListWidget>
#include "stepmenu.h"
#include "SongCatalogue.h"
#include <QtDebug>

class SongMenu: public StepMenu
{
public:
     SongMenu(BaseMenuForm* form, QWidget* parent = 0);
    ~SongMenu();
    SongCatalogue* list;
    const int getIndex();
private:
    QFile* sui;
    QUiLoader* loader;
    QWidget* widget;
    QListWidget* listWidget;
};

#endif // SONGMENU_H

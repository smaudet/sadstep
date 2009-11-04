#ifndef SONGMENU_H
#define SONGMENU_H

#include <QFile>
#include <QtUiTools>
#include <QWidget>
#include "stepmenu.h"
#include <QtDebug>

class SongMenu: public StepMenu
{
public:
     SongMenu(BaseMenuForm* form, QWidget* parent = 0);
    ~SongMenu();
private:
    QFile* sui;
    QUiLoader* loader;
    QWidget* widget;
};

#endif // SONGMENU_H

#ifndef SONGMENU_H
#define SONGMENU_H
#include <QObject>
#include <QFile>
#include <QtUiTools>
#include <QWidget>
#include <QListWidget>
#include "stepmenu.h"
#include "SongCatalogue.h"
#include <QtDebug>

class SongMenu: public StepMenu
{
Q_OBJECT

public:
    SongMenu(BaseMenuForm* form, QWidget* parent = 0);
    ~SongMenu();
    SongCatalogue* list;
    const int getIndex();
public slots:
    void rowChanged2(int billybob); // yes its name is billybob deal with it (From: Scott)
private:
    QFile* sui;
    QUiLoader* loader;
    QWidget* widget;
    QListWidget* listWidget;
    int songNumber;
};

#endif // SONGMENU_H

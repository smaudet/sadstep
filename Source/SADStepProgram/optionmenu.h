#ifndef OPTIONMENU_H
#define OPTIONMENU_H

#include <QFile>
#include <QObject>
#include <QWidget>
#include <QtUiTools>
#include <QListWidget>
#include <QPushButton>
#include "basemenuform.h"

class OptionMenu : public StepMenu
{ Q_OBJECT
public slots:
    void cancel();
//    void menuSelected5();
//    void menuSelected6();
//    void menuSelected7();
public:
    //This GameMenu is virtually private! :D
    OptionMenu(BaseMenuForm* form,QWidget* parent=0);
   ~OptionMenu();
private:
   QPushButton* cancelBtn;
   QFile* sui;
   QUiLoader* loader;
   QWidget* widget;
};

#endif // OPTIONMENU_H

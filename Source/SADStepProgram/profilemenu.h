#ifndef PROFILEMENU_H
#define PROFILEMENU_H

#include <QtGui/QWidget>
#include <QLineEdit>
#include <QFile>
#include <QObject>
#include <QWidget>
#include <QtUiTools>
#include <QPushButton>
#include "basemenuform.h"

class ProfileMenu : public StepMenu
{ Q_OBJECT
public:
    ProfileMenu(BaseMenuForm* form, QWidget* parent=0);
   ~ProfileMenu();
public slots:
   void menuSelected5();
private:
   QPushButton* logIn;
   QFile* sui;
   QUiLoader* loader;
   QWidget* widget;
   QWidget* formWidget;
};

#endif // PROFILEMENU_H

#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QFile>
#include <QObject>
#include <QWidget>
#include <QtUiTools>
#include <QListWidget>
#include <QPushButton>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>
#include "basemenuform.h"

class GameMenu : public StepMenu
{ Q_OBJECT
//public slots:
  //  void menuSelected2();
  //  void menuSelected3();
  //  void menuSelected4();
public:
    //This GameMenu is virtually private! :D
    GameMenu(BaseMenuForm* form,QWidget* parent=0);
    ~GameMenu();
private:
    int x;
   // QPushButton* gameStartBtn;
   // QPushButton* optionBtn;
   // QPushButton* exitBtn;
    //QFile* sui;
   // QUiLoader* loader;
   // QWidget* widget;
    protected:
     void paintEvent(QPaintEvent* e);
    void keyPressEvent(QKeyEvent* e);
};

#endif // GAMEMENU_H

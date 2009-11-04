#include <QApplication>
#include "basemenuform.h"
#include <QtDebug>

//initiates window
int main(int argc, char *argv[]){
    QApplication menuApp(argc, argv);
    BaseMenuForm *sw= new BaseMenuForm();
    sw->show();
    menuApp.beep();
  return menuApp.exec();
}




#include <QtGui/QApplication>
//#include <QtDebug>
#include <QMainWindow>
#include "GameCanvas.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow* window = new QMainWindow();
    window->showFullScreen();
    GameCanvas gc(4,window);
    //GameCanvasThread* th = new GameCanvasThread(4,60);
    window->setCentralWidget(&gc);
    gc.setFocus();
//    th->getCanvas()->spawnArrow(1,1);
//    th->getCanvas()->getTimer()->start();
//    th->start();
    return a.exec();
}

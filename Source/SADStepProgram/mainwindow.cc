#include "mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    showFullScreen();
    runMenu();
}

void MainWindow::runGame() {
    qDebug() << "hel";
    canvas = new GameCanvas(4,this,30);
    qDebug() << "hel";
    setCentralWidget(canvas);
    canvas->start();
    qDebug() << "hel";
}

void MainWindow::runMenu() {
    menu = new BaseMenuForm(this);
    connect(menu,SIGNAL(runGame(int)),this,SLOT(runGame()));
    setCentralWidget(menu);
}

//Basic demonstration of keyboard use on the Game ONLY
void MainWindow::keyPressEvent(QKeyEvent* e) {
    if(e->key()==Qt::Key_Up){
        if(canvas){
            canvas->spawnArrow(1,1);
        }
        return;
    }
    if(e->key()==Qt::Key_Down){
        if(canvas){
            canvas->spawnArrow(1,3);
        }
        return;
    }
    if(e->key()==Qt::Key_Left){
        if(canvas){
            canvas->spawnArrow(1,2);
        }
        return;
    }
    if(e->key()==Qt::Key_Right){
        if(canvas){
            canvas->spawnArrow(1,4);
        }
        return;
    }
    if(e->key()==Qt::Key_Escape){
        if(canvas){
            runMenu();
        }
    }
}

MainWindow::~MainWindow()
{
   delete menu;
    delete canvas;
}

/*
  This class is simply a place-holder for game, the class that will end up
  in control of most parts of the game.
  
  It also provides the basic scheme and proof of concept for interaction between
  the user and program through a device such as a keyboard, though does not
  offer support for other devices at this time.
  
        Author: Sebastian Audet
        
  */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QObject>
#include "basemenuform.h"
#include "GameCanvas.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void runMenu();
    void runGame();
protected:
    void keyPressEvent(QKeyEvent* e);
private:
    GameCanvas* canvas;
    BaseMenuForm* menu;
    bool canwinB;
};

#endif // MAINWINDOW_H

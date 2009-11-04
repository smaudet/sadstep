#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QTextEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QLabel>
#include "basemenuform.h"
#include <QPushButton>

class MainMenu : public QMainWindow
{
public:
    MainMenu();
    //~MainMenu();
private:
    BaseMenuForm *center;/*
    QFrame *horGroupBox;
    QFrame *gridGroupBox;
    QPushButton *startBtn;
    QPushButton *gameStart;
    QPushButton *optionsBtn;
    QPushButton *exit;
    QPushButton *cancelOptions;
    QPushButton *cancelSongsBtn;
    QPushButton *songsOK;
    QPushButton *difOK;
    QPushButton *cancelDifBtn;
    QPushButton *cancelGameBtn;
    QLabel *ddr;
    QAction *startAction;
    QAction *closeAction;
    QGridLayout *layout;
    void gameMenu();
    void optionsMenu();
    void songsMenu();
    void difMenu();
    void gameScreen();
    void createGridGroupBox();
    void createHorizontalGroupBox();*/

/*private slots:
    void start();
    void songs();
    void close();
    void options();
    void cancelOpt();
    void difficulty();
    void cancelSongs();
    void blackScreen();
    void cancelDif();
    void cancelGame();*/
};

#endif // MAINMENU_H

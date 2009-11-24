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
#include <QTimer>
#include <QTimerEvent>
#include "basemenuform.h"
#include "FileIOServer.h"
#include "GameCanvas.h"
#include "timeline.h"
#include "score.h"
#include "ScoreData.h"
#include "MediaPlayer.h"
#include "profile.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void runMenu();
    void runGame(int selection);
    void gameLogic();
protected:
    void timerEvent(QTimerEvent* e);
    void keyPressEvent(QKeyEvent* e);
private:
    MediaPlayer* mp;
    bool canvasOn;
    bool needsToCloseGame;
    FileIOServer* fio;
    GameCanvas* canvas;
    BaseMenuForm* menu;
    bool canwinB;
    QListIterator<double>* itr;
    Timeline* timeline;
    int lastTimerID;
    int x;
    QList<QList<int>*>* arrows;
    ScoreData* scoreData;
    int dTimeHolder;
    Score* score;
    Profile* profile;
};

#endif // MAINWINDOW_H

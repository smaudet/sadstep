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
#include <QTime>
#include <QTimerEvent>
#include <SDL/SDL.h>
#include "BaseMenuForm.h"
#include "FileIOServer.h"
#include "GameCanvas.h"
#include "Timeline.h"
#include "Score.h"
#include "ScoreData.h"
#include "MediaPlayer.h"
#include "Profile.h"
#include "ScoreEvaluator.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int getSongTimeElapsed();

    //Not final code, please do not use
    //SDL Timing stuff
    int lastTime;
    int diffTime;
    int currentDiffTime;
    int currentSpawnTime;
    SDL_Thread* execthread;
    MediaPlayer* mp;
    QList<QList<int>*>* arrows;
    double currentArrowSpeed;
public slots:
    void runMenu();
    void runGame(int selection);
    void gameLogic();
protected:
    void timerEvent(QTimerEvent* e);
    void keyPressEvent(QKeyEvent* e);
private:
    friend int gameThread(void* data);

    int arrowIncrementVar;
    //QTime* tel;
    ScoreEvaluator* eval;
    bool canvasOn;
    bool needsToCloseGame;
    FileIOServer* fio;
    GameCanvas* canvas;
    BaseMenuForm* menu;
    bool canwinB;
    QListIterator<double>* itr;
    QListIterator<double>* deconItr;
    QListIterator<double>* bpmItr;
    QListIterator<double>* speedItr;
    QList<QListIterator<double>*>* holdItrs;
    QList<int>* press;
    Timeline* timeline;
    int lastNoteTimerID;
    int lastBPMTimerID;
    int lastSpawnArrowTime;
    int notesLocation;
    ScoreData* scoreData;
    double dTimeHolder;
    Score* score;
    Profile* profile;

    int incrementVar;
};

#endif // MAINWINDOW_H



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
#include "songmenu.h"

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
    bool firstRun;
};

#endif // MAINWINDOW_H

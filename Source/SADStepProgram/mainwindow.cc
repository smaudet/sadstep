#include "mainwindow.h"
#include <QtDebug>
#include <QTimer>
#include <QObject>
#include <QBasicTimer>
#include <QListIterator>

#include "StepReader.h"
#include "SongCatalogue.h"
#include "timeline.h"
#include "score.h"
#include "SongReader.h"

#include <QTime>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    showFullScreen();
    canvasOn = false;
    needsToCloseGame = false;
    scoreData = new ScoreData(); //class not implemented atm
    profile = new Profile("player");
    runMenu();
    fio = new FileIOServer(); // starts file IO server
    x = 0;
    dTimeHolder = 0; //holds calculated value what time key should be pressed
}

void MainWindow::gameLogic() {
    if (x >= arrows->size()-6){
        qDebug() << "should stop now";
        mp->stop();
        needsToCloseGame=true;
    }
    if (canvas) {
        //qDebug() << "Elephants!";
        //qDebug() << "Tinker Winker Dolls";
        Score* scores = new Score(); // starts score class
        bool allValYAreZero = true;
        //Note (the musical type)
        int ysize = arrows->at(x)->size();
        int* y = new int[ysize];
        for(int i=0;i<ysize;++i) {
            //Debug() << "Go Boom " << i;
            //qDebug() << x;
            y[i] = arrows->at(x)->at(i);
            if(y[i]!=0){
                allValYAreZero = false; // takes into acount <0,0,0,0> vectors
            }
        }
        if(allValYAreZero) {
            x++;
        } else {
            // qDebug() << "else reached";
            for(int i = 0;i<ysize;++i) { // spawns arrow in correct lane
                if(y[i]>0){
                    canvas->spawnArrow(1,i+1);
                }
            }
            x++;
        }
        if(needsToCloseGame) { // return to menus if song over else continue
            qDebug() << "ending";
            needsToCloseGame=false;
            runMenu();
        } else {
            qDebug() << itr->peekNext();
            lastTimerID = startTimer((int)itr->next());
        }
    }
}

void MainWindow::runGame(int selection) {
    canvasOn = true;
    // implements the instance of song catalogue
    const SongCatalogue* const catalogue = fio->getSongCatalogue();
    // TODO: for now given 0 in future will get value from user selection
    QString location = catalogue->getFileName(selection);
    // gets stepreader for specified file
    StepReader* steps = fio->getStepReader(location);
    QList<QPair<double,double>*>* bps /*= steps->getBPM()*/;
    QList<QList<QList<int>*>*>* stepData = steps->getStepData();
    qDebug() << "got to stepdata";
    //Distance in pixels, time in pixels per minute
    // starts timeline and passes required data to its constructor
    timeline = new Timeline(bps,stepData,0,800,360);
    qDebug() << "got through timeline";
    //int totalGameTime = 1 /*songs.getSongLength()*/;
    timeline->getNotes(stepData);
    score = new Score;
    // TODO: set max range to value selected by user in options
    score->setMaxRange(profile->getRange()); // gets range from profile now from value set as defults
    //TODO: get values from options menu to change Profile's values
    itr = new QListIterator<double>(*(timeline->creationTime));
    arrows = timeline->arrowGiantMeasure; //***** placeholder (getNotes)
    canvas = new GameCanvas(4,this);
    setCentralWidget(canvas);
    canvas->start();
    lastTimerID = startTimer((int)itr->next());

    SongReader* song = fio->getSongReader(location);
    mp = new MediaPlayer();
    mp->playFile(song->getSongFile());
}

void MainWindow::runMenu() {
    if(canvasOn) { // Need to delete game stuff
        //qDebug() << "canvas was on";
        delete timeline;
        delete itr;
        canvasOn = false;
        mp->stop();
    }
    //qDebug() << "end of loop";
    menu = new BaseMenuForm(this);
    connect(menu,SIGNAL(runGame(int)),this,SLOT(runGame(int)));
    setCentralWidget(menu);
    qDebug() << "Widget set?";
}

//Basic demonstration of keyboard use on the Game ONLY
void MainWindow::keyPressEvent(QKeyEvent* e) {
    if(e->key()==Qt::Key_Up){
        if(canvas){
            //if(canvas->arrowInLane (1))
            //{
            dTimeHolder = timeline->checkTime();
            //TODO: calculate time when key is pressed & compare
            score->calculateScore(250);
            // it to the dTimeCounter
            QString string1 = score->getScore();
            canvas->showScoreText(string1);


            //}

        }
        if (!canvas){
            // NOTE: Does nothing atm, will allow for arrow key selection of
            // buttons on screen
            menu->setActiveButton();
        }
        return;
    }
    if(e->key()==Qt::Key_Down){
        if(canvas){
            //if(canvas->arrowInLane (4))
            //{
            dTimeHolder = timeline->checkTime();
            //TODO: calculate time when key is pressed & compare
            // it to the dTimeCounter
            score->calculateScore(250);
            QString string2 = score->getScore();
            canvas->showScoreText(string2);
            // }
            //canvas->spawnArrow(1,4);
        }
        if (!canvas) {
            // NOTE: Does nothing atm, will allow for arrow key selection of
            // buttons on screen
            menu->setActiveButton();
        }
        return;
    }
    if(e->key()==Qt::Key_Left){
        if(canvas){
            //if(canvas->arrowInLane (2))
            // {
            dTimeHolder = timeline->checkTime();
            score->calculateScore(250); //TODO: calculate time when key is
            // pressed & compare it to the dTimeCounter
            QString string3 = score->getScore();
            canvas->showScoreText(string3);
            // }
            //canvas->spawnArrow(1,2);
        }
        if (!canvas)
        {
            // NOTE: Does nothing atm, will allow for arrow key selection of
            // buttons on screen
            menu->setActiveButton();
        }
        return;
    }
    if(e->key()==Qt::Key_Right){
        if(canvas){
            //if(canvas->arrowInLane (3))
            // {
            dTimeHolder = timeline->checkTime();
            score->calculateScore(250); //TODO: calculate time when key is
            // pressed & compare it to the dTimeCounter
            QString string4 = score->getScore();
            canvas->showScoreText(string4);
            // }
            //canvas->spawnArrow(1,3);
        }
        if (!canvas) {
            menu->setActiveButton(); // NOTE: Does nothing atm, will allow for
            // arrow key selection of buttons on screen
        }
        return;
    }
    if(e->key()==Qt::Key_Escape){
        if(canvas){
            qDebug() << score->getTotalScore() << " total Score";
            qDebug() << score->getNumberOfOk() << " OK";
            qDebug() << score->getNumberOfPerfect() << " Perfect";
            qDebug() << score->getNumberOfGood() << " Good";
            qDebug() << score->getNumberOfBad() << " bad";

            needsToCloseGame = true;

        }
    }
}

void MainWindow::timerEvent(QTimerEvent* e) {
    this->killTimer(lastTimerID);
    gameLogic();
}

MainWindow::~MainWindow() {
    qDebug() << "deleting menu";
    delete menu;
}

#include "mainwindow.h"
#include <QtDebug>
#include <QTimer>
#include <QObject>
#include <QBasicTimer>
#include <QListIterator>

#include "StepReader.h"
#include "SongCatalogue.h"
#include "timeline.h"
#include "SongReader.h"


#include <QTime>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    showFullScreen();
    tel = new QTime();
    currentArrowSpeed = 0;
    lastSpawnArrowTime = 0;
    canvasOn = false;
    needsToCloseGame = false;
    profile = new Profile("player");
    runMenu();
    fio = new FileIOServer(); // starts file IO server
    x = 0;
    dTimeHolder = 0; //holds calculated value what time key should be pressed
    press = new QList<int>;
    for (int z=0; z<5;z++)
    {
        press->append(0);
    }
}

void MainWindow::gameLogic() {
    if (x >= arrows->size()-6){
        qDebug() << "should stop now";
        mp->stop();
        needsToCloseGame=true;
    }
    if (canvas) {
        bool allValYAreZero = true;
        //Note (the musical type)
        int ysize = arrows->at(x)->size();
        int* y = new int[ysize];
        for(int i=0;i<ysize;++i) {
            y[i] = arrows->at(x)->at(i);
            if(y[i]!=0){
                allValYAreZero = false; // takes into acount <0,0,0,0> vectors
            }
        }
        if(allValYAreZero) {
            x++;
        } else {
            for(int i = 0;i<ysize;++i) { // spawns arrow in correct lane
                if(y[i]>0){
                    //qDebug() << currentArrowSpeed << " arrow speed";
                    canvas->spawnArrow(currentArrowSpeed,i+1);
                    //qDebug() << currentArrowSpeed*lastSpawnArrowTime << " = " << canvas->getDistance();
                }
            }
            x++;
        }
        if(needsToCloseGame) { // return to menus if song over else continue
            qDebug() << "ending";
            needsToCloseGame=false;
            runMenu();
        } else {
            if(itr->hasNext()) {
                int previousTime = itr->peekPrevious();
                int nextTime = itr->next();
                lastNoteTimerID = startTimer((int)(nextTime-previousTime));
            }
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
    //qDebug() << "got past step reader";
    QList<QPair<double,double>*>* bps = steps->getBPM();
    //qDebug() << "is it bps?";
    QList<QList<QList<int>*>*>* stepData = steps->getStepData();

    //qDebug() << "got to stepdata";
    //Distance in pixels, time in pixels per minute
    // starts timeline and passes required data to its constructor
    canvas = new GameCanvas(4,this,45);
    timeline = new Timeline(bps,stepData,0,canvas->getDistance(),profile->getSpeed(), steps->getOffset());
    timeline->getNotes(stepData);
    eval = new ScoreEvaluator(timeline->destructionTime, timeline->arrowGiantMeasure, profile->getRange());
    //qDebug() << "got through timeline";
    //int totalGameTime = 1 /*songs.getSongLength()*/;
    // TODO: set max range to value selected by user in options
    //TODO: get values from options menu to change Profile's values
    itr = new QListIterator<double>(*(timeline->creationTime));
    bpmItr = new QListIterator<double>(*(timeline->bpmChanges));
    speedItr = new QListIterator<double>(*(timeline->speedChanges));
    deconItr = new QListIterator<double>(*(timeline->destructionTime));
    arrows = timeline->arrowGiantMeasure; //***** placeholder (getNotes)
    setCentralWidget(canvas);
    canvas->start();

    lastNoteTimerID = startTimer((int)itr->next());
    deconItr->next();
    if(timeline->bpmChanges->size() != 0) {
        lastBPMTimerID = startTimer((int)bpmItr->next());
    }
    currentArrowSpeed = speedItr->next();

    SongReader* song = fio->getSongReader(location);
    mp = new MediaPlayer();
    mp->playFile(song->getSongFile());
    tel->start();
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
    //qDebug() << "Widget set?";
}

int MainWindow::getSongTimeElapsed() {
    return tel->elapsed();
}

//Basic demonstration of keyboard use on the Game ONLY
void MainWindow::keyPressEvent(QKeyEvent* e) {
    if(e->key()==Qt::Key_Up){
        if(canvas){
            qDebug() << "got to up press";
            press->replace(2,1);// set presssed key
            eval->setCurrentTime(tel->elapsed());
            eval->evaluateSingle(press,tel->elapsed());
            press->replace(2,0); // after sending value reset to 0


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
            qDebug() << "got to down press";
           press->replace(3,1);// set presssed key
           eval->setCurrentTime(tel->elapsed());
            eval->evaluateSingle(press,tel->elapsed());
            press->replace(3,0); // after sending value reset to 0
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
            qDebug() << "got to left press";
           press->replace(1,1);// set presssed key
           eval->setCurrentTime(tel->elapsed());
            eval->evaluateSingle(press,tel->elapsed());
            press->replace(1,0); // after sending value reset to 0
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
            qDebug() << "got to right press";
           press->replace(2,1);// set presssed key
            eval->setCurrentTime(tel->elapsed());
            eval->evaluateSingle(press,tel->elapsed());
            press->replace(2,0); // after sending value reset to 0
        }
        if (!canvas) {
            menu->setActiveButton(); // NOTE: Does nothing atm, will allow for
            // arrow key selection of buttons on screen
        }
        return;
    }
    if(e->key()==Qt::Key_Escape){
        if(canvas){
            needsToCloseGame = true;

        }
    }
}

void MainWindow::timerEvent(QTimerEvent* e) {
    if(e->timerId() == lastNoteTimerID) {
        killTimer(lastNoteTimerID);
        gameLogic();
    }
    if(e->timerId() == lastBPMTimerID) {
        killTimer(lastBPMTimerID);
        if(bpmItr->hasNext()){
            double nextBpm = bpmItr->next();
            double previousBpm = bpmItr->peekPrevious();
            if(bpmItr->hasNext()){
                currentArrowSpeed = speedItr->next();
                lastBPMTimerID = startTimer((int)(nextBpm-previousBpm));
            }
        }
    }
}

MainWindow::~MainWindow() {
    qDebug() << "deleting menu";
    delete menu;
}

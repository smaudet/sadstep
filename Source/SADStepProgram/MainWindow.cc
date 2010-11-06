#include "MainWindow.h"
#include <QtDebug>
#include <QTimer>
#include <QObject>
#include <QBasicTimer>
#include <QListIterator>

#include "StepReader.h"
#include "SongCatalogue.h"
#include "Timeline.h"
#include "SongReader.h"

#include <QTime>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    //showFullScreen();
    arrowIncrementVar = 0;
    //tel = new QTime();
    currentArrowSpeed = 0;
    lastSpawnArrowTime = 0;
    canvasOn = false;
    needsToCloseGame = false;
    profile = new Profile("player");
    runMenu();
    fio = new FileIOServer(); // starts file IO server
    notesLocation = 0;
    dTimeHolder = 0; //holds calculated value what time key should be pressed
    press = new QList<int>;
    for (int z=0; z<5;z++)
    {
        press->append(0);
    }
}

int gameThread(void* data) {
    qDebug() << "game begun";
    MainWindow* pdata = (MainWindow*)data;
    bool notReady = true;
    while(notReady){
        if(pdata->mp->isReady()){
            notReady = false;
        } else {
            qDebug() << "Waiting";
        }
    }
    //pdata->diffTime = SDL_GetTicks() - pdata->lastTime;
    while(!pdata->needsToCloseGame){
        if( SDL_GetTicks() > pdata->currentSpawnTime){ //Call this function once every beat - might be off by one
            //#1
            if ( pdata->notesLocation >= pdata->arrows->size()-1){
                qDebug() << "should stop now";
                pdata->mp->stop();
                pdata->needsToCloseGame=true;
            }
            if( !pdata->needsToCloseGame) {
                if( pdata->itr->hasNext()) {
                    //Validated as working - Sebastian Audet
                    //int previousTime =  data->itr->peekPrevious();
                    //int nextTime =  data->itr->next();
                     //data->lastNoteTimerID =  data->startTimer((int)( data->nextTime- data->previousTime));
                    pdata->currentSpawnTime = pdata->itr->next();
                }
            }

            if ( pdata->canvasOn) {
                //bool allValYAreZero = true;
                //Note (the musical type)
                QList<int>* noteRow = pdata->arrows->at(pdata->notesLocation);
                for(int i = 0;i<noteRow->size();++i) { // spawns arrow in correct lane
                    int note = noteRow->at(i);
                    if(note>0){
                        if(note==1) {
                            pdata->canvas->spawnArrow(pdata->currentArrowSpeed,i+1);
                            //qDebug() << SDL_GetTicks() - canvas->pstartTime << " start " <<timeline->creationTime->at(arrowIncrementVar) << " " << arrowIncrementVar << "construct Time";
                            //qDebug() << timeline->destructionTime->at(arrowIncrementVar) << " " << arrowIncrementVar << "destruct time";
                            ++(pdata->arrowIncrementVar);
                        }
        //                if(note==2) {
        //                    canvas->spawnHoldArrow(currentArrowSpeed,holdItrs->at(i)->next(),i+1);
        //                }
                    }
                }
                pdata->notesLocation++;
            }
             pdata->lastTime = SDL_GetTicks();
        }
    }
    return 0;
}

/**
  * First the runGame function is called. It calls a timer, which sets up for the next function.
  *
  * SDL: Instead of calling a timer, we call an SDL Thread
  */
void MainWindow::runGame(int selection) {
    canvasOn = true;
    // implements the instance of song catalogue
    const SongCatalogue* const catalogue = fio->getSongCatalogue();
    // TODO: for now given 0 in future will get value from user selection
    QString location = catalogue->getFileName(selection);
    // gets stepreader for specified file
    StepReader* steps = fio->getStepReader(location);
    QList<QPair<double,double>*>* bps = steps->getBPM();
    QList<QList<QList<int>*>*>* stepData = steps->getStepData();

    //Distance in pixels, time in pixels per minute
    //starts timeline and passes required data to its constructor
    canvas = new GameCanvas(4,this,25);
    timeline = new Timeline(bps,stepData,0,canvas->getDistance(),profile->getSpeed(), steps->getOffset());
    timeline->getNotes(stepData);
    eval = new ScoreEvaluator(timeline->destructionTime, timeline->arrowGiantMeasure, profile->getRange());
    // TODO: set max range to value selected by user in options
    //TODO: get values from options menu to change Profile's values
    itr = new QListIterator<double>(*(timeline->creationTime));
    bpmItr = new QListIterator<double>(*(timeline->bpmChanges));
    speedItr = new QListIterator<double>(*(timeline->speedChanges));
    deconItr = new QListIterator<double>(*(timeline->destructionTime));
    holdItrs = new QList<QListIterator<double>*>;
    QListIterator<QList<double>*> holdItr(*(timeline->holdCounters));
    while(holdItr.hasNext()){
        holdItrs->append(new QListIterator<double>(*(holdItr.next())));
    }
    arrows = timeline->arrowGiantMeasure; //***** placeholder (getNotes)
    setCentralWidget(canvas);
    //qDebug() << itr->peekNext();
    //lastNoteTimerID = startTimer((int)itr->next());
    currentSpawnTime = itr->next();
    deconItr->next();

    //For the BPM Changes
//    if(timeline->bpmChanges->size() != 0) {
//        lastBPMTimerID = startTimer((int)bpmItr->next());
//        qDebug() << "lastTimer" << lastBPMTimerID;
//    }

    currentArrowSpeed = speedItr->next();
    SongReader* song = fio->getSongReader(location);
    canvas->giveTimelineInfo(itr,arrows,currentArrowSpeed);
    mp = MediaPlayer::getMediaPlayerInst();
    mp->playFile(song->getSongFile());
    //tel->start();
    canvas->start();
    //execthread = SDL_CreateThread(gameThread,this);
    //lastTime = SDL_GetTicks();
}



/**
 * When the timer times out, this function kills the timer, then executes gameLogic()
 */
void MainWindow::timerEvent(QTimerEvent* e) {
    if(e->timerId() == lastNoteTimerID) {
        //qDebug() << "note timer got through" << lastNoteTimerID;
        killTimer(lastNoteTimerID);
        gameLogic();
    }
    if(e->timerId() == lastBPMTimerID) {
        //qDebug() << "bpm timer got through" << lastBPMTimerID;
        if(bpmItr->hasNext()){
            double nextBpm = bpmItr->next();
            double previousBpm = bpmItr->peekPrevious();
            if(bpmItr->hasNext()){
                currentArrowSpeed = speedItr->next();
                lastBPMTimerID = startTimer((int)(nextBpm-previousBpm));
            }
        } else {
            //qDebug() << "no more timers";
            killTimer(lastBPMTimerID);
        }
    }
}

/**
  * When the a timer is destroyed, this function:
  * 1. Looks at the progression of the song and determines whether to call it quits
  * 2. Calculates the next time to run to and starts a new timer.
  * 3. Asks the canvas to spawn arrows
  */
void MainWindow::gameLogic() {
//    qDebug () << incrementVar << "incvar";
//    qDebug() << timeline->creationTime->at(incrementVar) << " " << incrementVar << "construct Time";
//    qDebug() << timeline->destructionTime->at(incrementVar) << " " << incrementVar << "destruct time";
    if (notesLocation >= arrows->size()-1){
        qDebug() << "should stop now";
        mp->stop();
        needsToCloseGame=true;
    }
    if(needsToCloseGame) { // return to menus if song over else continue
        qDebug() << "ending";
        canvas->debug();
        if(itr->hasNext()){
            int zi = 0;
            while(itr->hasNext()){
                itr->next();
                ++zi;
            }
            qDebug() << "elements remaining: " << zi;
        }
        canvas->stop();
        needsToCloseGame=false;
        runMenu();
        qDebug() << "------------Done with song-----------";
        return;

    } else {
        if(itr->hasNext()) {
            //Validated as working - Sebastian Audet
            int previousTime = itr->peekPrevious();
            int nextTime = itr->next();
            lastNoteTimerID = startTimer((int)(nextTime-previousTime));
        }
    }

    if (canvasOn) {
        //bool allValYAreZero = true;
        //Note (the musical type)
        QList<int>* noteRow = arrows->at(notesLocation);
        for(int i = 0;i<noteRow->size();++i) { // spawns arrow in correct lane
            int note = noteRow->at(i);
            if(note>0){
                if(note==1) {
                    canvas->spawnArrow(currentArrowSpeed,i+1);
                    //qDebug() << SDL_GetTicks() - canvas->pstartTime << " start " <<timeline->creationTime->at(arrowIncrementVar) << " " << arrowIncrementVar << "construct Time";
                    //qDebug() << timeline->destructionTime->at(arrowIncrementVar) << " " << arrowIncrementVar << "destruct time";
                    ++arrowIncrementVar;
                }
//                if(note==2) {
//                    canvas->spawnHoldArrow(currentArrowSpeed,holdItrs->at(i)->next(),i+1);
//                }
            }
        }
        notesLocation++;
    }
}

void MainWindow::runMenu() {
    menu = new BaseMenuForm(this);
    connect(menu,SIGNAL(runGame(int)),this,SLOT(runGame(int)));
    setCentralWidget(menu);
    if(canvasOn) { // Need to delete game stuff
        qDebug() << "canvas was on";
        delete timeline;
        delete itr;
        canvasOn = false;
        mp->stop();
        delete canvas;
    }
}

//int MainWindow::getSongTimeElapsed() {
//    return tel->elapsed();
//}

//Basic demonstration of keyboard use on the Game ONLY
void MainWindow::keyPressEvent(QKeyEvent* e) {
    if(e->key()==Qt::Key_Up){
        if(canvasOn) {
            qDebug() << "got to up press";
            press->replace(2,1);// set presssed key
            //eval->setCurrentTime(tel->elapsed());
            //eval->evaluateSingle(press,tel->elapsed());
            press->replace(2,0); // after sending value reset to 0
        }
        if (!canvasOn) {
            // NOTE: Does nothing atm, will allow for arrow key selection of
            // buttons on screen
            menu->setActiveButton();
        }
        return;
    }
    if(e->key()==Qt::Key_Down){
        if(canvasOn){
            qDebug() << "got to down press";
           press->replace(3,1);// set presssed key
           //eval->setCurrentTime(tel->elapsed());
            //eval->evaluateSingle(press,tel->elapsed());
            press->replace(3,0); // after sending value reset to 0
        }
        if (!canvasOn) {
            // NOTE: Does nothing atm, will allow for arrow key selection of
            // buttons on screen
            menu->setActiveButton();
        }
        return;
    }
    if(e->key()==Qt::Key_Left){
        if(canvasOn){
            qDebug() << "got to left press";
           press->replace(1,1);// set presssed key
          // eval->setCurrentTime(tel->elapsed());
           // eval->evaluateSingle(press,tel->elapsed());
            press->replace(1,0); // after sending value reset to 0
        }
        if (!canvasOn)
        {
            // NOTE: Does nothing atm, will allow for arrow key selection of
            // buttons on screen
            menu->setActiveButton();
        }
        return;
    }
    if(e->key()==Qt::Key_Right){
        if(canvasOn){
            qDebug() << "got to right press";
           press->replace(2,1);// set presssed key
           // eval->setCurrentTime(tel->elapsed());
           // eval->evaluateSingle(press,tel->elapsed());
            press->replace(2,0); // after sending value reset to 0
        }
        if (!canvasOn) {
            menu->setActiveButton(); // NOTE: Does nothing atm, will allow for
            // arrow key selection of buttons on screen
        }
        return;
    }
    if(e->key()==Qt::Key_Escape){
        if(canvasOn){
            needsToCloseGame = true;
        }
        if(!canvasOn) {
            close();
        }
    }
}

MainWindow::~MainWindow() {
    qDebug() << "deleting menu";
    delete menu;
}

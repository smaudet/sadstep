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
#include <QSound>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent) {
    showFullScreen();
    canvasOn = false;
    needsToCloseGame = false;
    runMenu();
    fio = new FileIOServer(); // starts file IO server
    x = 0;
}

void MainWindow::gameLogic() {
    qDebug() << "Porpoises?";
    if (canvas) {
	qDebug() << "Elephants!";
	qDebug() << "Tinker Winker Dolls";
	//Score* scores = new Score(); // starts score class
	bool allValYAreZero = true;
	//Note
	int ysize = arrows->at(x)->size();
	int* y = new int[ysize];
	for(int i=0;i<ysize;++i) {
	    qDebug() << "Go Boom " << i;
	    qDebug() << x;
	    y[i] = arrows->at(x)->at(i);
	    if(y[i]!=0){
		allValYAreZero = false;
	    }
        }
        if(allValYAreZero)
        {
            x++;
        }
        else
        {
            qDebug() << "else reached";
            for(int i = 0;i<ysize;++i) {
                if(y[i]>0){
                    canvas->spawnArrow(1,i+1);
                }
            }
            x++;
        }
	if(needsToCloseGame) {
	    needsToCloseGame=false;
	    runMenu();
	} else {
	    lastTimerID = startTimer(itr->next());
	}
    }
}

void MainWindow::runGame() {
    canvasOn = true;
    qDebug() << "hel";
    const SongCatalogue* const catalogue = fio->getSongCatalogue(); // implements the instance of song catalogue
    qDebug() << "are you dying?";
    QString location = catalogue->getFileName(0);  // TODO: for now given 0 in future will get value from user selection
    //TODO May not compile
    qDebug() << "are you dying?";
    StepReader* steps = fio->getStepReader(&location); // gets stepreader for specified file
    qDebug() << "MM mm good File";
    QList<double>* bps = new QList<double>();
    bps->append(0.102);
    QList<QList<QList<int>*>*>* stepData = steps->getStepData();
    timeline = new Timeline(bps,stepData,0); // starts timeline and passes required data to its constructor
    int totalGameTime = 1 /*songs.getSongLength()*/;
    timeline->setDistance(200);
    timeline->getNotes(stepData);
    itr = new QListIterator<int>(*(timeline->creationTime));
    qDebug() << "hippos";
    arrows = timeline->arrowGiantMeasure; //***** placehold (getNotes) for non existant function yet to be named
   // QBasicTimer* timer = new QBasicTimer;
    qDebug() << "Cranes!";
    canvas = new GameCanvas(4,this,20);
    qDebug() << "hel";
    setCentralWidget(canvas);
    qDebug() << "hel";
    canvas->start();
    lastTimerID = startTimer(itr->next());
    qDebug() << itr->peekPrevious();
 /*
      To Scott Tollas
      From Sebastian Audet

      Ok all the code below causes the program to crash. I fixed the routines so
      that they actually work (that is they load from file). The issue is here
      something to do with the way Qt is loading the windows (or alternatively
      the way in which the menus are distructing, however good luck with that.
      You CANNOT perform your processing here, at least not before you do
      anything with the canvas so you need to use events (slots and signals will
      slow things down) to handle the timers and put your game logic inside
      those events. As for creating Timelines and reading in files and such, you
      MAY do that in here however you just need to do it before you ever ask Qt
      to construct or use the canvas. For now do as below and just use one BPM,
      I may not have the BPM code fixed by the time you read this.

      Also when you look at this code, you will be loading in a Song (wav) and
      playing that with the MusicPlayer class. There will something with images
      in here, and there will be functions installed into the canvas for
      distance, as well as a score bar on top. Lanes 1-4 will correspond
      directly.

    */
    /*const SongCatalogue* const catalogue = fio->getSongCatalogue(); // implements the instance of song catalogue
    qDebug() << "are you dying?";
    QString location = catalogue->getFileName(0);  // TODO: for now given 0 in future will get value from user selection
    //TODO May not compile
    qDebug() << "are you dying?";
    StepReader* steps = fio->getStepReader(&location); // gets stepreader for specified file
    qDebug() << "MM mm good File";
    //SongReader* songs = fio.getSongReader(location); // gets songreader for specified file
    //TODO 0 is a placeholder file
    QList<double>* bpms = new QList<double>();
    bpms->append(34);
    qDebug() << "Brraaaiinsss.... err, I mean bpmssss....";
    QList<QList<QList<int>*>*>* stepData = steps->getStepData();
    Timeline* timeline = new Timeline(/*steps->getBPM()*//*bpms,stepData,0); // starts timeline and passes required data to its constructor
    /*int totalGameTime = 1 /*songs.getSongLength()*/;
    /*timeline->setDistance(200);
    timeline->getNotes(stepData);
    qDebug() << "hippos";
    QList<QList<int>*>* arrows = timeline->arrowGiantMeasure; //***** placehold (getNotes) for non existant function yet to be named
    qDebug() << "Cranes!";
    QListIterator<int> itr(*(timeline->creationTime));
    int creationTime1 = itr.next();
    qDebug() << "Elephants!";
    int creationTime2 = itr.peekNext();
    qDebug() << "Rhinocerous";
    int timeDisplacement = creationTime2 - creationTime1; // calculates displacement from n and n+1 creation times to set value for timer
    qDebug() << "Tinker Winker Dolls";
    totalGameTime = totalGameTime - (timeDisplacement); */// calculates how mush total game time is left after spawning of arrows takes place
    /* The next lines of code take care of the 1st instance of the arrows that need to spawn
       it needs special code because of it being the first group which the other lines do not
       need otherwise it does the same thing as the loop for creating the rest of the arrows
       beyond the first set. Otherwise the game starts right when created instead of giving
       the user time to react
     *//*
    QBasicTimer* timerdud = new QBasicTimer;
    timerdud->start(8000, canvas);
    do
    {
        // does nothing
    }
    while (timerdud->isActive() == true);*/
                    //this->thread()->wait(8000);
                    //QBasicTimer* timer = new QBasicTimer;
                    //Score* scores = new Score(); // starts score class
                    // timer->start(timeDisplacement, canvas);
                    //    do
                    //    {
                    //        //does nothing while waiting for timer to finnish
                    //    }
                    //    while (timer->isActive() == true);
                    //delete timer;
                    //    int x =0;
                    //    int ysize = arrows->at(0)->size();
                    //    int* y = new int[ysize];
                    //    qDebug() << ysize;
                    //
                    //    qDebug() << "right before loop";
                    //    for (int z = 0; z<arrows->size(); z++)
                    //    {
                    //        bool allValYAreZero = true;
                    //        for(int i=0;i<ysize;++i) {
                    //            qDebug() << "Go Boom " << i;
                    //            qDebug() << x;
                    //            y[i] = arrows->at(x)->at(i);
                    //            if(y[i]!=0){
                    //                allValYAreZero = false;
                    //            }
                    //        }
                    //        if(allValYAreZero)
                    //        {
                    //            x++;
                    //        }
                    //        else
                    //        {
                    //            qDebug() << "else reached";
                    //            for(int i = 0;i<ysize;++i) {
                    //                if(y[i]>0){
                    //                    canvas->spawnArrow(1,i+1);
                    //                }
                    //            }
                    //            x++;
                    //        }
                    //    }

                    //---------------------------WARNING---------------------------
                    //
                    //                       DEPRECATED CODE
                    //
                    //---------------------------WARNING---------------------------

                    // for (totalGameTime; totalGameTime != 0; totalGameTime - timeDisplacement) // runs creation loop untill game time is 0
                    //    {
                    //        creationTime1 = itr.next();
                    //        creationTime2 = itr.peekNext();
                    //        timeDisplacement = creationTime2 - creationTime1; // see exact same line above
                    //        QBasicTimer* timer = new QBasicTimer;
                    //        timer->start(timeDisplacement, canvas);
                    //        do
                    //            {
                    //        //does nothing while waiting for timer to finnish
                    //            }
                    //        while (timer->isActive());
                    //        delete timer;
                    //        for (int z = 0; z=1; z--)
                    //    {
                    //        y0 = arrows->at(x)->at(0);
                    //        y1 = arrows->at(x)->at(1);
                    //        y2 = arrows->at(x)->at(2);
                    //        y3 = arrows->at(x)->at(3);
                    //
                    //        if ( y0 && y2 && y3 && y1 == 0)
                    //        {
                    //            x++;
                    //        }
                    //        else
                    //        {
                    //           if (y0 !=0)
                    //               canvas->spawnArrow(timeline->getArrowSpeed(),1);
                    //           if (y1 !=0)
                    //               canvas->spawnArrow(timeline->getArrowSpeed(),2);
                    //           if (y2 !=0)
                    //               canvas->spawnArrow(timeline->getArrowSpeed(),3);
                    //           if (y3 !=0)
                    //               canvas->spawnArrow(timeline->getArrowSpeed(),4);
                    //
                    //           x++;
                    //           z = 1;
                    //        } // end else statement
                    //    } // end inner creation loop
                    //  }// end whole creation loop
                    //        timer = new QBasicTimer;
                    //        timer->start(5000, canvas);
                    //        do
                    //            {
                    //        //does nothing while waiting for timer to finnish
                    //            }
                    //        while (timer->isActive());
                    //        delete timer;
    sound = new QSound("1000 Words.wav");
    sound->play();
}

void MainWindow::runMenu() {
    qDebug() << "menu running";
    if(canvasOn) { // Need to delete game stuff
        qDebug() << "canvas was on";
        delete timeline;
        delete itr;
        canvasOn = false;
        sound->stop();
    }
    qDebug() << "end of loop";
    menu = new BaseMenuForm(this);
    connect(menu,SIGNAL(runGame(int)),this,SLOT(runGame()));
    setCentralWidget(menu);
}

//Basic demonstration of keyboard use on the Game ONLY
void MainWindow::keyPressEvent(QKeyEvent* e) {
    if(e->key()==Qt::Key_Up){
        if(canvas){
            //canvas->spawnArrow(1,1);
        }
        return;
    }
    if(e->key()==Qt::Key_Down){
        if(canvas){
            //canvas->spawnArrow(1,4);
        }
        return;
    }
    if(e->key()==Qt::Key_Left){
        if(canvas){
            //canvas->spawnArrow(1,2);
        }
        return;
    }
    if(e->key()==Qt::Key_Right){
        if(canvas){
            //canvas->spawnArrow(1,3);
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
    this->killTimer(lastTimerID);
    gameLogic();
}

MainWindow::~MainWindow() {
    delete menu;
    delete canvas;
}



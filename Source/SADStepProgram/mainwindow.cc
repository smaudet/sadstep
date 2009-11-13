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
    scoreData = new ScoreData(); //class not implemented atm
    runMenu();
    fio = new FileIOServer(); // starts file IO server
    x = 0;
    dTimeHolder = 0; // holds calculated value for what time key should be pressed
}

void MainWindow::gameLogic() {
    qDebug() << "Porpoises?";
    if (canvas) {
	qDebug() << "Elephants!";
	qDebug() << "Tinker Winker Dolls";
        Score* scores = new Score(); // starts score class
	bool allValYAreZero = true;
        //Note (the musical type)
	int ysize = arrows->at(x)->size();
	int* y = new int[ysize];
	for(int i=0;i<ysize;++i) {
	    qDebug() << "Go Boom " << i;
	    qDebug() << x;
	    y[i] = arrows->at(x)->at(i);
	    if(y[i]!=0){
                allValYAreZero = false; // takes into acount <0,0,0,0> vectors
	    }
        }
        if(allValYAreZero)
        {
            x++;
        }
        else
        {
            // qDebug() << "else reached";
            for(int i = 0;i<ysize;++i) { // spawns arrow in correct lane based on file
                if(y[i]>0){
                    canvas->spawnArrow(1,i+1);
                }
                if (i == ysize)
                {
                    sound->stop();
                    needsToCloseGame=true;
                }

            }
            x++;
        }
        if(needsToCloseGame) { // returns to menus if song over else keeps going through loop
	    needsToCloseGame=false;
            runMenu();




	} else {
	    lastTimerID = startTimer(itr->next());
	}
    }
}

void MainWindow::runGame() {
    canvasOn = true;
    //qDebug() << "hel";
    const SongCatalogue* const catalogue = fio->getSongCatalogue(); // implements the instance of song catalogue
    //qDebug() << "are you dying?";
    QString location = catalogue->getFileName(0);  // TODO: for now given 0 in future will get value from user selection
    //TODO May not compile
    //qDebug() << "are you dying?";
    StepReader* steps = fio->getStepReader(&location); // gets stepreader for specified file
    //qDebug() << "MM mm good File";
    QList<double>* bps = new QList<double>();
    bps->append(0.102);
    QList<QList<QList<int>*>*>* stepData = steps->getStepData();
    timeline = new Timeline(bps,stepData,0); // starts timeline and passes required data to its constructor
    int totalGameTime = 1 /*songs.getSongLength()*/;
    timeline->setDistance(200);
    timeline->getNotes(stepData);
    score = new Score;
    score->setMaxRange(5000); // TODO: set max range to value selected by user in options
    itr = new QListIterator<int>(*(timeline->creationTime));
    //qDebug() << "hippos";
    arrows = timeline->arrowGiantMeasure; //***** placehold (getNotes) for non existant function yet to be named
   // QBasicTimer* timer = new QBasicTimer;
    //qDebug() << "Cranes!";
    canvas = new GameCanvas(4,this,20);
    //qDebug() << "hel";
    setCentralWidget(canvas);
    //qDebug() << "hel";
    canvas->start();
    lastTimerID = startTimer(itr->next());
   // qDebug() << itr->peekPrevious();

    sound = new QSound("1000 Words.wav");
    sound->play();
}

void MainWindow::runMenu() {
    // qDebug() << "menu running";
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
           //if(canvas->arrowInLane (1))
            //{
               dTimeHolder = timeline->checkTime();
               score->calculateScore(250); //TODO: calculate time when key is pressed & compare
               // it to the dTimeCounter
               QString string1 = score->getScore();
               canvas->showScoreText(string1);


           //}

        }
        return;
    }
    if(e->key()==Qt::Key_Down){
        if(canvas){
            //if(canvas->arrowInLane (4))
            //{
               dTimeHolder = timeline->checkTime();
               score->calculateScore(250); //TODO: calculate time when key is pressed & compare
               // it to the dTimeCounter
               QString string2 = score->getScore();
               canvas->showScoreText(string2);
          // }
            //canvas->spawnArrow(1,4);
        }
        return;
    }
    if(e->key()==Qt::Key_Left){
        if(canvas){
            //if(canvas->arrowInLane (2))
           // {
               dTimeHolder = timeline->checkTime();
               score->calculateScore(250); //TODO: calculate time when key is pressed & compare
               // it to the dTimeCounter
               QString string3 = score->getScore();
               canvas->showScoreText(string3);
          // }
            //canvas->spawnArrow(1,2);
        }
        return;
    }
    if(e->key()==Qt::Key_Right){
        if(canvas){
            //if(canvas->arrowInLane (3))
           // {
               dTimeHolder = timeline->checkTime();
               score->calculateScore(250); //TODO: calculate time when key is pressed & compare
               // it to the dTimeCounter
               QString string4 = score->getScore();
               canvas->showScoreText(string4);
          // }
            //canvas->spawnArrow(1,3);
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


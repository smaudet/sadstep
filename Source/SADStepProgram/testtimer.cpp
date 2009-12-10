#include "testtimer.h"
#include "MediaPlayer.h"
#include "SongCatalogue.h"
#include "FileIOServer.h"
#include <QtDebug>

TestTimer::TestTimer(QWidget* parent):QMainWindow(parent) {
    showFullScreen();
    qDebug() << "debug";
    canvas = new GameCanvas(4,this,45);
    qDebug() << "canvas";
    setCentralWidget(canvas);
    qDebug() << "jik";
    this->startTimer(7000);
    this->startTimer(3000);
    qDebug() << "timers";
    MediaPlayer* p = new MediaPlayer;
    FileIOServer* fio = new FileIOServer();
    qDebug() << "file io problem";
    const SongCatalogue* sc = fio->getSongCatalogue();
    QString loc = sc->getFileName(0);
    qDebug() << fio->getSongReader(loc)->getSongFile();
    canvas->start();
    qDebug() << canvas->getDistance();
    spawnNum=0;
    //p->playFile(fio->getSongReader(loc)->getSongFile());
}

void TestTimer::timerEvent(QTimerEvent* e){
    qDebug() << e->timerId() << "timer";
    switch(spawnNum) {
    case 0: {
	spawnNum++;
	canvas->spawnArrow(200,1);
	this->killTimer(e->timerId());
	break;
    }
    case 1: {
	spawnNum++;
	canvas->spawnHoldArrow(400,600,2);
	this->killTimer(e->timerId());
	break;
    }
    default: {
    }
    }
}

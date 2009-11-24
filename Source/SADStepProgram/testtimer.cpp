#include "testtimer.h"
#include "MediaPlayer.h"
#include "SongCatalogue.h"
#include "FileIOServer.h"
#include <QtDebug>

TestTimer::TestTimer(QWidget* parent):QMainWindow(parent) {
    showFullScreen();
    canvas = new GameCanvas(4,this,45);
    setCentralWidget(canvas);
    this->startTimer(7000);
    this->startTimer(3000);
    MediaPlayer* p = new MediaPlayer;
    FileIOServer* fio = new FileIOServer();
    const SongCatalogue* sc = fio->getSongCatalogue();
    QString loc = sc->getFileName(0);
    qDebug() << fio->getSongReader(loc)->getSongFile();
    canvas->start();
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
	canvas->spawnArrow(400,2);
	this->killTimer(e->timerId());
	break;
    }
    default: {
    }
    }
}

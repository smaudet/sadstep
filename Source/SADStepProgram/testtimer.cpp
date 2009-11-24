#include "testtimer.h"
#include "MediaPlayer.h"
#include "SongCatalogue.h"
#include "FileIOServer.h"
#include <QtDebug>

TestTimer::TestTimer(QWidget* parent):QMainWindow(parent) {
    showFullScreen();
    canvas = new GameCanvas(4,this);
    setCentralWidget(canvas);
    this->startTimer(500);
    this->startTimer(800);
    MediaPlayer* p = new MediaPlayer;
    FileIOServer* fio = new FileIOServer();
    const SongCatalogue* sc = fio->getSongCatalogue();
    QString loc = sc->getFileName(0);
    qDebug() << fio->getSongReader(loc)->getSongFile();
    p->playFile(fio->getSongReader(loc)->getSongFile());
}

void TestTimer::timerEvent(QTimerEvent* e){
    qDebug() << e->timerId() << "timer";
    canvas->spawnArrow(18,1);
}

#ifndef TESTTIMER_H
#define TESTTIMER_H

#include <QObject>
//#include <QMainWindow>
#include <QTimerEvent>
#include "GameCanvas.h"

class TestTimer: public QObject
{
public:
    TestTimer();
protected:
    void timerEvent(QTimerEvent* e);
private:
    GameCanvas* canvas;
    int spawnNum;
};

#endif // TESTTIMER_H

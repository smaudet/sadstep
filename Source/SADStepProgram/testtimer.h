#ifndef TESTTIMER_H
#define TESTTIMER_H

#include <QObject>
#include <QMainWindow>
#include <QTimerEvent>
#include "GameCanvas.h"

class TestTimer: public QMainWindow
{
public:
    TestTimer(QWidget* parent = 0);
protected:
    void timerEvent(QTimerEvent* e);
private:
    GameCanvas* canvas;
};

#endif // TESTTIMER_H

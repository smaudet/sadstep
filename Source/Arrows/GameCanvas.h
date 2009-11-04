#ifndef GAMECANVAS_H
#define GAMECANVAS_H

#include <QObject>
#include <QThread>
#include <QWidget>
#include <QList>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>
#include "Arrow.h"
#include "GraphicsTimer.h"
#include "ArrowGraphicsSet.h"

//#define DRAW_SURFACE QWidget;
//#define THREAD_TYPE QThread;

//class GameCanvas;
//
//class GameCanvasThread: public QThread {
//    public:
//        GameCanvasThread(int lanes, int fps = 60);
//        ~GameCanvasThread();
//        void run();
//        GameCanvas* getCanvas() const;
//    private:
//        GameCanvas* gc;
//};

class GameCanvas: public QWidget { Q_OBJECT
public:
    GameCanvas(int lanes,QWidget* parent, int fps = 60);
    ~GameCanvas();
    void run();
    int getPixelDistance();
    bool spawnArrow(double speed, int lane);
    bool destroyArrow(int lane);
    bool blankArrow(int lane);
    //Unsure of exactly what these two functions will be responsible for
    // - use with caution or don't use at all, as the functionality may
    //disappear in future.
    bool flashArrow(int lane);
    bool scoreArrow(int lane);
    //Allows write only access to the type used to instantiate arrows
    void setType(int type);
    int getFps() const;
    GraphicsTimer* getTimer() const;
public slots:
    void updateArrows();
protected:
    void paintEvent(QPaintEvent* e);
    void keyPressEvent(QKeyEvent* e);
private:
    //friend void GameCanvasThread::run();
    int fps;
    ArrowGraphicsSet* graphics;
    //An N-dimensional array of lanes of Arrows
    QList<QList<Arrow*>*>* arrows;
    GraphicsTimer* timer;
    int type;
    int lanes;
    int laneSize;
};

#endif // GAMECANVAS_H

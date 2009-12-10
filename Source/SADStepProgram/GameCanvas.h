#ifndef GAMECANVAS_H
#define GAMECANVAS_H

#include <QObject>
#include <QString>
#include <QThread>
#include <QWidget>
#include <QList>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>
#include "Arrow.h"
#include "GraphicsTimer.h"
#include "ArrowGraphicsSet.h"
#include <QTime>

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
    //In pixels
    int getDistance();
    bool spawnArrow(double speed, int lane);
    bool spawnHoldArrow(double speed,double distance, int lane);
    bool arrowPresent(int lane);
    bool destroyArrow(int lane);
    bool destroyHoldArrow(int lane);
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
    void start();
    void updateArrowsSpeed(double speed);
public slots:
    void updateArrows();
    void showScoreText(QString txt);
    void showComboText(QString txt);
    //Parameters may change in future
    void setScoreNumber(double score);
protected:
    void paintEvent(QPaintEvent* e);
    void keyPressEvent(QKeyEvent* e);
private:
    //friend void GameCanvasThread::run();
    int fps;
    int counter;
    double arrowSpeed;
    QImage getBackgroundImage();
    ArrowGraphicsSet* graphics;
    //An N-dimensional array of lanes of Arrows
    QList<QList<Arrow*>*>* arrows;
    QList<QList<Arrow*>*>* holdArrows;
    GraphicsTimer* timer;
    int type;
    int lanes;
    int laneSize;
    QString txt;
    int laneIndent;
    int arrowLaneSize;
    QTime* stimer;
    int totelapsed;
    const QImage* images[9];
    const QImage* images2[9];
    const QImage* images3[9];
};

#endif // GAMECANVAS_H

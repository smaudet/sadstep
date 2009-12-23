/*
 *  Author: Sebastian Audet
 */
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
#include "ProjectHeader.h"

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
    GameCanvas(int lanes,QWidget* parent = 0, int fps = 60);
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
    friend int threadFunc(void* canvas);\
    SDL_Thread* execthread;
    SDL_Rect* backgroundRect;
    double errorcount;
    int fps;
    int counter;
    bool flipb;
    double arrowSpeed;
    QImage getBackgroundImage();
    ArrowGraphicsSet* graphics;
    //An N-dimensional array of lanes of Arrows
    QList<Arrow*>* arrows;
    QList<Arrow*>* holdArrows;
    GraphicsTimer* timer;
    int type;
    int lanes;
    int laneSize;
    int reDrawSize;
    int* laneArrowSizes;
    int* laneHoldArrowSizes;
    QString txt;
    int laneIndent;
    int arrowLaneSize;
    int totelapsed;
    const QImage* images[9];
    SDL_Surface* imagesSprites[9];
    const QImage* images2[9];
    SDL_Surface* images2Sprites[9];
//    const QImage* images3[9];
    QList<QImage*>** holdImages;
    QList<SDL_Surface*>** holdSurfaces;
    const QImage* topcaps[9];
    const QImage* bottomcaps[9];
    const QImage* holdbs[9];
    SDL_Surface* screen;
    SDL_Surface* bgimage;
    SDL_Surface* lanesurfs[9];
    int laneIndents[9];
    Uint32 lastTime;
    bool is_Running;

    //For Debugging purposes
    int timeVar;
    int incrementVar;
    int startTime;
};

#endif // GAMECANVAS_H

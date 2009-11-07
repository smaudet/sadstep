#include "GameCanvas.h"
#include <QBrush>
#include <QPalette>
#include <QtDebug>
#include <QPaintEngine>

GameCanvas::GameCanvas(int lanes,QWidget* parent,int fps):
        QWidget(parent)
{
    this->lanes=lanes;
    this->setGeometry(x()/2,y()/2,parentWidget()->width(),parentWidget()->height());
    arrows = new QList<QList<Arrow*>*>();
    for(int i = 0;i<lanes;++i){
        arrows->append(new QList<Arrow*>());
    }
    timer = new GraphicsTimer(fps);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateArrows()));
    graphics = new ArrowGraphicsSet();
    laneSize=this->width()/lanes;
    graphics->loadAllGraphics(laneSize/2,laneSize/2);
    QBrush brush(getBackgroundImage());
    QPalette palette = parentWidget()->palette();
    palette.setBrush(QPalette::Window,brush);
    palette.setBrush(QPalette::WindowText,*(new QBrush(*(new QColor(255,100,0
                                                                    ,30)))));
    parentWidget()->setStyleSheet("");
    parentWidget()->setPalette(palette);
    type = 1;
    this->fps = fps;
    showScoreText("Hooray");
}

void GameCanvas::showScoreText(QString txt) {
    this->txt = txt;
}

QImage GameCanvas::getBackgroundImage() {
    //QImage& retimg = *(new QImage());
    
    return *(graphics->getGraphic(0));
}

void GameCanvas::start() {
    timer->start();
}

GameCanvas::~GameCanvas() {
    delete arrows;
    delete timer;
}

bool GameCanvas::spawnArrow(double speed,int lane) {
    if(lane>0&&lane<=lane){
        arrows->at(lane-1)->append(new Arrow(speed,type));
        return true;
    }
    return false;
}

int GameCanvas::getDistance() {
    return this->height();
}

bool GameCanvas::destroyArrow(int lane) {
    if(lane>this->lanes||lane<=0){
        qDebug() << "Tried to delete a non-existant lane " << lane;
        return false;
    } else {
        QList<Arrow*>* tlane = arrows->at(lane-1);
        if(tlane->size()>0){
            Arrow* arrow = tlane->first();
            tlane->removeFirst();
            delete arrow;
            qDebug() << "Deleted";
            return true;
        } else {
            qDebug() << "Tried to delete an arrow from a lane with no arrows";
            return false;
        }
    }
}

//TODO Does nothing yet
bool GameCanvas::blankArrow(int lane) {
    return destroyArrow(lane);
}

//TODO Does nothing yet
bool GameCanvas::flashArrow(int lane) {
    return destroyArrow(lane);
}

//TODO Does nothing yet
bool GameCanvas::scoreArrow(int lane) {
    return destroyArrow(lane);
}

void GameCanvas::paintEvent(QPaintEvent* e){
    QPainter* p = new QPainter(this);
    QListIterator<QList<Arrow*>*> itr(*arrows);
    //draw score region
    for(int i=0;i<this->lanes;++i){
        const QImage* timg = graphics->getArrowGraphic(2,i+1);
        p->drawImage((i)*laneSize/2+this->width()/4,0,*timg);
    }
    int laneNum=1;
    while(itr.hasNext()) {
        QListIterator<Arrow*> itr2(*itr.next());
        while(itr2.hasNext()){
            Arrow* arrow = itr2.next();
            const QImage* timg = graphics->getArrowGraphic(arrow->getType(),laneNum);
            int yindent = ((double)arrow->getPercentLoc()/100)*this->height();
            p->drawImage((laneNum-1)*laneSize/2+this->width()/4,this->height()-yindent,*timg);
        }
        ++laneNum;
    }
    p->drawText(this->height()/2,this->width()/4,this->height()/8,this->width()/4,Qt::AlignCenter,txt);
}

void GameCanvas::updateArrows() {
    QListIterator<QList<Arrow*>*> itr(*arrows);
    int lane = 1;
    while(itr.hasNext()) {
        QList<Arrow*>* n = itr.next();
        QListIterator<Arrow*> itr2(*n);
        while(itr2.hasNext()){
            Arrow* arrow = itr2.next();
            int loc=arrow->getPercentLoc();
            if(loc>100) {
                destroyArrow(lane);
            } else {
                arrow->giveLocation(loc+1);
            }
        }
        ++lane;
    }
    repaint();
}

int GameCanvas::getFps() const {
    return fps;
}

GraphicsTimer* GameCanvas::getTimer() const {
    return timer;
}

void GameCanvas::keyPressEvent(QKeyEvent* e){
    if(e->key()==Qt::Key_Up){
        //qDebug() << "1";
        spawnArrow(1,1);
        return;
    }
    if(e->key()==Qt::Key_Down){
        //qDebug() << "2";
        spawnArrow(1,3);
        return;
    }
    if(e->key()==Qt::Key_Left){
        //qDebug() << "3";
        spawnArrow(1,2);
        return;
    }
    if(e->key()==Qt::Key_Right){
        //qDebug() << "4";
        spawnArrow(1,4);
        return;
    }
    if(e->key()==Qt::Key_Escape){
        parentWidget()->close();
    }
}
        
//GameCanvasThread::GameCanvasThread(int lanes,int fps):gc(new GameCanvas(lanes
//                                                                        ,fps)){}
//GameCanvasThread::~GameCanvasThread(){
//    delete gc;
//}
//
//void GameCanvasThread::run(){
//    gc->getTimer()->start(gc->getFps());
//    exec();
//}
//
//GameCanvas* GameCanvasThread::getCanvas() const {
//    return gc;
//}

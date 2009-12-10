#include "GameCanvas.h"
#include <QBrush>
#include <QPalette>
#include <QtDebug>
#include <QPaintEngine>
#include <QFont>
#include <QPointF>
#include <cmath>

GameCanvas::GameCanvas(int lanes,QWidget* parent,int fps):
	QWidget(parent)
{
    this->lanes=lanes;
    this->setGeometry(x()/2,y()/2,parentWidget()->width(),parentWidget()
		      ->height());
    arrows = new QList<QList<Arrow*>*>;
    holdArrows = new QList<QList<Arrow*>*>;
    for(int i = 0;i<lanes;++i){
	arrows->append(new QList<Arrow*>);
	holdArrows->append(new QList<Arrow*>);
    }
    timer = new GraphicsTimer(1000.0/(double)fps);
    //TODO Performance boost?
    connect(timer,SIGNAL(timeout()),this,SLOT(updateArrows()));
    graphics = new ArrowGraphicsSet();
    laneSize=this->width()/lanes;
    graphics->loadAllGraphics(laneSize/2,laneSize/2);
    QBrush brush(getBackgroundImage());
    QPalette palette = parentWidget()->palette();
    palette.setBrush(QPalette::Window,brush);
    palette.setBrush(QPalette::WindowText,*(new QBrush(*(new QColor(255,100,0,30)))));
    parentWidget()->setStyleSheet("");
    parentWidget()->setPalette(palette);
    type = 1;
    stimer = new QTime();
    this->fps = fps;
    laneIndent = this->width()/4;
    arrowLaneSize = laneSize/2;
    holdImages = new QList<QList<QImage*>*>;
    qDebug() << "suspicious stuff";
    for(int i=0;i<lanes;++i) { //TODO Make Dynamic
	images[i] = graphics->getArrowGraphic(type,i+1);
	images2[i] = graphics->getArrowGraphic(type+1,i+1);
        topcaps[i] = graphics->getArrowGraphic(type+2,i+1);
        bottomcaps[i] = graphics->getArrowGraphic(type+3,i+1);
        holdbs[i] = graphics->getArrowGraphic(type+4,i+1);
        qDebug() << "pops head";
        holdImages->append(new QList<QImage*>);
        qDebug() << "hmm";
    }
    showScoreText("");
    totelapsed = 0;
    counter = 0;
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
    stimer->start();
}

GameCanvas::~GameCanvas() {
    //qDebug() << "allo";
    delete arrows;
    delete timer;
    //qDebug() << ":)";
}

//Speed = distance of screen / seconds
bool GameCanvas::spawnArrow(double speed,int lane) {
    arrowSpeed = speed;
    if(lane>0&&lane<=lane){
	//qDebug() << "successfull spawn";
	int index = lane-1;
	arrows->at(index)->append(new Arrow(images[index]->height(),type));
	return true;
    }
    return false;
}

bool GameCanvas::spawnHoldArrow(double speed, double distance, int lane) {
    arrowSpeed = speed;
    if(lane>0&&lane<=lane){
         //qDebug() << "successfull spawn";
	int index = lane-1;
	holdArrows->at(index)->append(new Arrow(distance,type));
        const QImage* tcapImage = topcaps[index];
        const QImage* bcapImage = bottomcaps[index];
        const QImage* bodyImage = holdbs[index];
        QImage* calcImage;
        if(distance < tcapImage->height()) {
            calcImage = new QImage(*tcapImage);
        }
        double extradist = (double)distance - (double)(1.5*tcapImage->height());
        if(extradist>0){
            calcImage = new QImage(tcapImage->width(),distance,QImage::Format_ARGB32);
            QPainter p(calcImage);
            //Calc part areas
            double numbody = extradist/(double)(bodyImage->height());
            int bodyuse = 0;
            double extra = numbody - std::floor(extradist/(double)(bodyImage->height()));
            if(numbody>0&&numbody<=1) {
                bodyuse = 1;
            }
            if(numbody>1){
                bodyuse = numbody;
                if(extra>0){
                    bodyuse++;
                }
            }
            //Paint part areas
            //Draw Underlay
            p.drawImage(0,tcapImage->height()/2,*bodyImage);
            //Draw Loop
            for(int i = 0;i<bodyuse;++i){
                p.drawImage(0,tcapImage->height()+i*(bodyImage->height()),*bodyImage);
            }
            //Paint image areas
            //Draw Bottom Cap
            p.drawImage(0,distance-bcapImage->height(),*bcapImage);
            //Draw Top Cap
            p.drawImage(0,0,*tcapImage);
        } else {
            qDebug() << "Unhandled Exception";
        }
/*new QImage(images[lane-1]->scaled(images[1]->width(),distance,Qt::IgnoreAspectRatio));*/
        holdImages->at(lane-1)->append(calcImage);
	return true;
    }
    return false;
}

int GameCanvas::getDistance() {
    return this->height();
}

bool GameCanvas::arrowPresent(int lane) {
    if(arrows->at(lane-1)->size()>0) {
	return true;
    }
    return false;
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

bool GameCanvas::destroyHoldArrow(int lane) {
    if(lane>this->lanes||lane<=0){
	qDebug() << "Tried to delete a non-existant lane " << lane;
	return false;
    } else {
	QList<Arrow*>* tlane = holdArrows->at(lane-1);
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
    //qDebug() << "painting";
    QPainter* p = new QPainter(this);
    p->setRenderHint(QPainter::Antialiasing,true);
    p->setRenderHint(QPainter::HighQualityAntialiasing,true);
    QListIterator<QList<Arrow*>*> itr(*arrows);
    //draw score region
    for(int i=0;i<this->lanes;++i){
	QPointF point((i)*arrowLaneSize+laneIndent,0);
	p->drawImage(point,*images2[i]);
    }
    int laneNum=1;
    while(itr.hasNext()) {
	QListIterator<Arrow*> itr2(*itr.next());
	while(itr2.hasNext()){
	    Arrow* arrow = itr2.next();
	    int yindent = (int)(arrow->getDistanceLoc());
	    //qDebug() << yindent;
	    QPointF point((laneNum-1)*arrowLaneSize+laneIndent,this->height()
			 -yindent);
	    p->drawImage(point,*images[laneNum-1]);
	}
	++laneNum;
    }
    itr = QListIterator<QList<Arrow*>*>(*holdArrows);
    laneNum=1;
    int i1 = 0;
    while(itr.hasNext()) {
        int j1 = 0;
	QListIterator<Arrow*> itr2(*itr.next());
	while(itr2.hasNext()){
	    Arrow* arrow = itr2.next();
	    int yindent = (int)(arrow->getDistanceLoc());
	    QPointF point((laneNum-1)*arrowLaneSize+laneIndent,this->height()
			 -yindent);
            p->drawImage(point,*holdImages->at(i1)->at(j1));
            ++j1;
	}
        ++i1;
	++laneNum;
    }
    p->setPen(QColor(255,0,0,255));
    QFont f;
    f.setPointSize(100);
    p->setFont(f);
    p->drawText(this->rect(),Qt::AlignCenter,txt);
    p->end();
    delete p;
}

void GameCanvas::updateArrows() {
    totelapsed+=stimer->elapsed();
    stimer->restart();
    counter++;
    if(counter==fps){
        qDebug() << totelapsed << "seconds elapsed per total frames";
        counter = 0;
        totelapsed = 0;
    }
    QListIterator<QList<Arrow*>*> itr(*arrows);
    int lane = 1;
    while(itr.hasNext()) {
	QList<Arrow*>* n = itr.next();
	QListIterator<Arrow*> itr2(*n);
	while(itr2.hasNext()){
	    Arrow* arrow = itr2.next();
	    double loc=arrow->getBottomLoc();
	    if(loc>getDistance()) {
		destroyArrow(lane);
	    } else {
		//distance = rate * time
		//time = (fps)^-1
                double distanceChange = arrowSpeed*(1.0/(double)fps);
           //qDebug() << distanceChange << "dchange";
		arrow->setDistanceLoc(arrow->getDistanceLoc()+distanceChange);
		//qDebug() << arrow->getDistanceLoc() << "distance";
	    }
	}
	++lane;
    }
    itr = QListIterator<QList<Arrow*>*>(*holdArrows);
    lane = 1;
    while(itr.hasNext()) {
	QList<Arrow*>* n = itr.next();
	QListIterator<Arrow*> itr2(*n);
	while(itr2.hasNext()){
	    Arrow* arrow = itr2.next();
	    double loc=arrow->getBottomLoc();
	    if(loc>getDistance()) {
		destroyHoldArrow(lane);
	    } else {
		//distance = rate * time
		//time = (fps)^-1
		double distanceChange = arrowSpeed*std::pow(((double)fps),-1);
		//qDebug() << distanceChange << "dchange";
		arrow->setDistanceLoc(arrow->getDistanceLoc()+distanceChange);
		//qDebug() << arrow->getDistanceLoc() << "distance";
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

void GameCanvas::showComboText(QString txt) {
    //TODO Does nothing
}

void GameCanvas::setScoreNumber(double score) {
    //TODO Does nothing
}

void GameCanvas::updateArrowsSpeed(double speed) {
    arrowSpeed = speed;
}

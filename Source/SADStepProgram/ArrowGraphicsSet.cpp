/*
 * ArrowGraphicsSet.cpp
 *
 *  Created on: Oct 16, 2009
 *      Author: Sebastian Audet
 */

#include "ArrowGraphicsSet.h"
#include <QtDebug>

ArrowGraphicsSet::ArrowGraphicsSet() {
    // TODO Auto-generated constructor stub
}

ArrowGraphicsSet::~ArrowGraphicsSet() {
    // TODO Auto-generated destructor stub
}

void ArrowGraphicsSet::loadAllGraphics(int width,int height) {
    loadGraphics();
    loadArrowGraphics(width, height);
}

void ArrowGraphicsSet::loadGraphics() {
    this->otherImages = new QList<QImage*>();
    otherImages->append(new QImage(":/arrows/background.jpg","jpg"));
}

void ArrowGraphicsSet::loadArrowGraphics(int width, int height, int lanes) {
    this->arrowImages = new QList<QList<QImage*>*>();
    for(int i=0;i<lanes;i++){
	arrowImages->append(new QList<QImage*>());
    }
    QList<QImage*>* timg = new QList<QImage*>();
    timg->append(new QImage(":/arrows/MArrow","png"));
    timg->append(new QImage(":/arrows/arrowScore","png"));
    //TODO Add support for separate images
    QListIterator<QImage*> itr(*timg);
    while(itr.hasNext()) {
	QImage* t = itr.next();
	QTransform trans;
	for(int i=0;i<lanes;++i){
	    QList<QImage*>* ta = arrowImages->at(i);
	    ta->append(
		    new QImage(t->transformed(
			    trans.rotate(-(360/lanes)*i))
			       .scaled(width,height
				       ,Qt::KeepAspectRatio,
				       Qt::SmoothTransformation)));
	}
    }
    //Hard coded - for demo purposes only
    QList<QImage*>* ta1 = arrowImages->at(0);
    ta1->append(new QImage((new QImage(":/arrows/arrowhtcapl","png")) //3
                ->scaled(width,height,Qt::KeepAspectRatio,
                         Qt::SmoothTransformation)));
    ta1->append(new QImage((new QImage(":/arrows/arrowhbcapl","png"))
                ->scaled(width,height,Qt::KeepAspectRatio,
                         Qt::SmoothTransformation)));
    ta1->append(new QImage((new QImage(":/arrows/arrowhbodyl","png")) //5
                ->scaled(width,height,Qt::KeepAspectRatio,
                         Qt::SmoothTransformation)));
    ta1 = arrowImages->at(1);
    ta1->append(new QImage((new QImage(":/arrows/arrowhtcapd","png"))
                ->scaled(width,height,Qt::KeepAspectRatio,
                         Qt::SmoothTransformation)));
    ta1->append(new QImage((new QImage(":/arrows/arrowhbcapd","png"))
                ->scaled(width,height,Qt::KeepAspectRatio,
                         Qt::SmoothTransformation)));
    ta1->append(new QImage((new QImage(":/arrows/arrowhbodyd","png"))
                ->scaled(width,height,Qt::KeepAspectRatio,
                         Qt::SmoothTransformation)));
    ta1 = arrowImages->at(2);
    ta1->append(new QImage((new QImage(":/arrows/arrowhtcapu","png"))
                ->scaled(width,height,Qt::KeepAspectRatio,
                         Qt::SmoothTransformation)));
    ta1->append(new QImage((new QImage(":/arrows/arrowhbcapu","png"))
                ->scaled(width,height,Qt::KeepAspectRatio,
                         Qt::SmoothTransformation)));
    ta1->append(new QImage((new QImage(":/arrows/arrowhbodyu","png"))
                ->scaled(width,height,Qt::KeepAspectRatio,
                         Qt::SmoothTransformation)));
    ta1 = arrowImages->at(3);
    ta1->append(new QImage((new QImage(":/arrows/arrowhtcapr","png"))
                ->scaled(width,height,Qt::KeepAspectRatio,
                         Qt::SmoothTransformation)));
    ta1->append(new QImage((new QImage(":/arrows/arrowhbcapr","png"))
                ->scaled(width,height,Qt::KeepAspectRatio,
                         Qt::SmoothTransformation)));
    ta1->append(new QImage((new QImage(":/arrows/arrowhbodyr","png"))
                ->scaled(width,height,Qt::KeepAspectRatio,
                         Qt::SmoothTransformation)));
}

const QImage* ArrowGraphicsSet::getArrowGraphic(int type, int lane) const{
    return arrowImages->at(lane-1)->at(type-1);
}

const QImage* ArrowGraphicsSet::getGraphic(int index) const{
    return otherImages->at(index);
}

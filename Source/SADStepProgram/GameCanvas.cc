#include "GameCanvas.h"
#include <QBrush>
#include <QPalette>
#include <QtDebug>
#include <QPaintEngine>
#include <QFont>
#include <QPointF>
#include <QFile>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

GameCanvas::GameCanvas(int lanes,QWidget* parent,int fps):
        QWidget(parent)
{
    /* Initialize SDL */
    if (SDL_InitSubSystem(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_JOYSTICK) < 0 ) {
            //fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());
            qDebug() << "Couldn't initialize SDL:" << SDL_GetError();
    }
    this->lanes=lanes;
    //Unsure that this command does anything...
    this->setGeometry(x()/2,y()/2,parentWidget()->width(),parentWidget()
                      ->height());
    //Create Arrow Queues
    arrows = new QList<Arrow*>[lanes];
    holdArrows = new QList<Arrow*>[lanes];
    for(int i = 0;i<lanes;++i){
    }

    //timer = new GraphicsTimer(1000.0/(double)fps);
    //connect(timer,SIGNAL(timeout()),this,SLOT(updateArrows()));

    //Graphics stuff
    graphics = new ArrowGraphicsSet();
    laneSize=this->width()/lanes;
    graphics->loadAllGraphics(laneSize/2,laneSize/2);

    //Old stuff to set background
//    QBrush brush(getBackgroundImage());
//    QPalette palette = parentWidget()->palette();
//    palette.setBrush(QPalette::Window,brush);
//    palette.setBrush(QPalette::WindowText,*(new QBrush(*(new QColor(255,100,0,30)))));

    //Stuff to appease Qt
    //parentWidget()->setStyleSheet("");
    //parentWidget()->setPalette(palette);

    //Various setup stuff
    type = 1;
    arrowSpeed = 0;
    errorcount = 0;
    timeVar = 402;
    incrementVar = 0;
    this->fps = fps; //Doesn't actually do anything - deprecate
    laneIndent = this->width()/4;
    arrowLaneSize = laneSize/2;
    reDrawSize = lanes*arrowLaneSize;
    holdImages = new QList<QImage*>*[lanes];
    holdSurfaces = new QList<SDL_Surface*>*[lanes];
    qDebug() << "suspicious stuff";
    //QFile* ifile;
    int rmask = 0x00FF0000;
    int gmask = 0x0000FF00;
    int bmask = 0x000000FF;
    int amask = 0xFF000000;
    for(int i=0;i<lanes;++i) { //TODO Make More Dynamic
        laneIndents[i] = (i*arrowLaneSize)+laneIndent;
        images[i] = graphics->getArrowGraphic(type,i+1);
        imagesSprites[i] = SDL_CreateRGBSurfaceFrom((uchar*)images[i]->bits(),
        images[i]->width(),images[i]->height(),images[i]->depth(),
        images[i]->bytesPerLine(),rmask,gmask,bmask,amask);
        qDebug() << SDL_GetError();
        images2[i] = graphics->getArrowGraphic(type+1,i+1);
        images2Sprites[i] = SDL_CreateRGBSurfaceFrom((uchar*)images2[i]->bits(),
        images2[i]->width(),images2[i]->height(),images2[i]->depth(),
        images2[i]->bytesPerLine(),rmask,gmask,bmask,amask);
        qDebug() << SDL_GetError();
        topcaps[i] = graphics->getArrowGraphic(type+2,i+1);
        bottomcaps[i] = graphics->getArrowGraphic(type+3,i+1);
        holdbs[i] = graphics->getArrowGraphic(type+4,i+1);
        holdImages[i] = new QList<QImage*>;
        holdSurfaces[i] = new QList<SDL_Surface*>; //Slow
        qDebug() << i;
    }
    totelapsed = 0;
    counter = 0;
    qDebug() << "done setting up image stuff";

    //Set up the SDL blitting stuff
    int width, height;
    Uint8  video_bpp;
    Uint32 videoflags;
    lastTime = 0;
    videoflags = SDL_SWSURFACE|SDL_ANYFORMAT|SDL_DOUBLEBUF/*|SDL_FULLSCREEN*/;
    width = parentWidget()->width();
    height = parentWidget()->height();
    video_bpp = 8;
    qDebug() << "about to set screen";
    screen = SDL_SetVideoMode(width, height, video_bpp, videoflags);

    if (!screen){
            fprintf(stderr, "Couldn't set %dx%d video mode: %s\n",
                                    width, height, SDL_GetError());
            qDebug() << "Failed on Screen";
    }

    //Setup the Background Image
    QImage* qimg = new QImage(getBackgroundImage().scaled(parentWidget()->width(),parentWidget()->height(),Qt::KeepAspectRatio));
    //Figure out x coord and y coord
    int xcoord, ycoord;
    bgimage = SDL_CreateRGBSurfaceFrom(qimg->bits(),
                                                qimg->width(),qimg->height(),qimg->depth(),
                                                qimg->bytesPerLine(),rmask,gmask,bmask,amask);
    xcoord = (parentWidget()->width() - bgimage->w)/2; // 0/2 == 0
    ycoord = (parentWidget()->height() - bgimage->h)/2; // 0/2 == 0
    backgroundRect = new SDL_Rect;
    backgroundRect->x = xcoord;
    backgroundRect->y = ycoord;
    SDL_UnlockSurface(screen);
    SDL_BlitSurface(bgimage,NULL,screen,backgroundRect);
    SDL_Flip(screen);
    //Setup lanesurfs
    SDL_Rect* tmp = new SDL_Rect;
    tmp->w=arrowLaneSize;
    tmp->h=height;
    tmp->y=0;
    for(int i=0;i<lanes;++i) {
        lanesurfs[i] = SDL_CreateRGBSurface(SDL_SWSURFACE,arrowLaneSize,height,
                                            32,rmask,gmask,bmask,amask);
        tmp->x=laneIndents[i];
        SDL_BlitSurface(screen,tmp,lanesurfs[i],NULL);
        SDL_BlitSurface(images2Sprites[i],NULL,lanesurfs[i],NULL);
    }
    qDebug() << "done setting up sdl";
}

void GameCanvas::showScoreText(QString txt) {
    this->txt = txt;
}

QImage GameCanvas::getBackgroundImage() {
    //QImage& retimg = *(new QImage());

    return *(graphics->getGraphic(0));
}

int threadFunc(void *canvas){
    GameCanvas* gcanvas = (GameCanvas*) canvas;
    gcanvas->totelapsed = 1000;
    gcanvas->lastTime = SDL_GetTicks(); //Ensure that it set properly
    while(gcanvas->is_Running){
        int tmpticks = SDL_GetTicks()-gcanvas->startTime;
        if(tmpticks>=gcanvas->totelapsed){
            gcanvas->totelapsed +=1000;
            qDebug() << (double)(gcanvas->counter) << "fps";
            qDebug() << tmpticks;
            gcanvas->counter=0;
        }
        gcanvas->updateArrows();
        SDL_Delay(5);
    }
    qDebug() << "Quitting";
}

void GameCanvas::start() {
    is_Running = true;
    execthread = SDL_CreateThread(threadFunc,this);
    startTime = SDL_GetTicks();
    qDebug() << startTime << "started Time";
}

GameCanvas::~GameCanvas() {
    qDebug() << "deleting GameCanvas";
    is_Running = false;
    SDL_KillThread(execthread);
    qDebug() << "deleting GameCanvas";
    SDL_QuitSubSystem(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_JOYSTICK);
    qDebug() << "deleting GameCanvas";
    delete []arrows;
    qDebug() << "deleting GameCanvas";
    delete []holdArrows;
//    qDebug() << "deleting GameCanvas";
//    delete timer;
    qDebug() << "deleting GameCanvas";
}

//Speed = distance of screen / seconds
bool GameCanvas::spawnArrow(double speed,int lane) {
    arrowSpeed = speed;
    if(lane>0&&lane<=lane){
        int index = lane-1;
        arrows[index].append(new Arrow(images[index]->height(),type));
        return true;
    }
    return false;
}

bool GameCanvas::spawnHoldArrow(double speed, double distance, int lane) {
    arrowSpeed = speed;
    if(lane>0&&lane<=lane){
         //qDebug() << "successfull spawn";
        int index = lane-1;
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
        holdImages[index]->append(calcImage);
        calcImage->save("./tmpHoldImg.bmp","bmp");
        SDL_Surface* tmp = SDL_LoadBMP("./tmpHoldImg.bmp");
        holdSurfaces[index]->append(tmp);
        holdArrows[index].append(new Arrow(distance,type));
        return true;
    }
    return false;
}

int GameCanvas::getDistance() {
    return this->height();
}

bool GameCanvas::arrowPresent(int lane) {
    if(arrows[lane].size()>0) {
        return true;
    }
    return false;
}

bool GameCanvas::destroyArrow(int lane) {
    if(lane>this->lanes||lane<=0){
        qDebug() << "Tried to delete a non-existant lane " << lane;
        return false;
    } else {
        QList<Arrow*>* tlane = &arrows[lane-1];
        if(tlane->size()>0){
            Arrow* arrow = tlane->first();
            tlane->removeFirst();
            ++incrementVar;
//            qDebug() << incrementVar*timeVar;
            qDebug() << SDL_GetTicks() - startTime << incrementVar << "actual destruct"; // ~ Destruct Time
            delete arrow;
            //qDebug() << "Deleted";
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
        QList<Arrow*>* tlane = &holdArrows[lane-1];
        if(tlane->size()>0){
            Arrow* arrow = tlane->first();
            tlane->removeFirst();
            delete arrow;
            //qDebug() << "Deleted";
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
    qDebug() << "ERROR PAINT EVENT BEING CALLED";
//    QPainter* p = new QPainter(this);
//    p->setRenderHint(QPainter::Antialiasing,true);
//    p->setRenderHint(QPainter::HighQualityAntialiasing,true);
//    for(int i = 0;i<lanes;++i){
//	//draw score region
//	QPointF point((i)*arrowLaneSize+laneIndent,0);
//	p->drawImage(point,*images2[i]);
//	int j1 = 0;
//	QListIterator<Arrow*> itr(arrows[i]);
//	while(itr.hasNext()){
//	    Arrow* arrow = itr.next();
//	    double loc=arrow->getBottomLoc();
//	    if(loc>getDistance()) {
//		destroyArrow(i+1);
//	    } else {
//		//distance = rate * time
//		//time = (fps)^-1
//		double distanceChange = arrowSpeed*(1.0/(double)fps);
//		arrow->addToLocation(distanceChange);
//	    }
//	    int yindent = (int)(arrow->getDistanceLoc());
//	    QPointF point((i)*arrowLaneSize+laneIndent,height()
//			 -yindent);
//	    p->drawImage(point,*images[i]);
//	}
//	QListIterator<Arrow*> itr2(holdArrows[i]);
//	while(itr2.hasNext()){
//	    Arrow* arrow = itr2.next();
//	    double loc=arrow->getBottomLoc();
//	    if(loc>getDistance()) {
//		destroyHoldArrow(i);
//	    } else {
//		//distance = rate * time
//		//time = (fps)^-1
//		double distanceChange = arrowSpeed*std::pow(((double)fps),-1);
//		arrow->addToLocation(distanceChange);
//	    }
//	    int yindent = (int)(arrow->getDistanceLoc());
//	    QPointF point((i)*arrowLaneSize+laneIndent,height()
//			 -yindent);
//	    p->drawImage(point,*holdImages->at(i)->at(j1));
//	    ++j1;
//	}
//    }
//    p->setPen(QColor(255,0,0,255));
//    QFont f;
//    f.setPointSize(100);
//    p->setFont(f);
//    p->drawText(this->rect(),Qt::AlignCenter,txt);
//    p->end();
//    delete p;
    //qDebug() << stimer->elapsed() << "paint";
}

void GameCanvas::updateArrows() {
    //distance = rate * time
    //time = timeSinceLastUpdate (ms)/1000 (ms)
    //int begintime = SDL_GetTicks();
    counter++;
    Uint32 timeSpent = SDL_GetTicks() - lastTime; //Unreliable after 49 days
    lastTime = SDL_GetTicks();
    //(pixels/sec)*(timeSpent msec/1000msec)*1sec
    double distanceChange = arrowSpeed*((double) timeSpent/1000.0);
    //qDebug() << (int)distanceChange << "distanceChange" << distanceChange;
    errorcount += distanceChange - std::floor(distanceChange);
    if(errorcount>1){//TODO Performance issue?
        distanceChange = std::floor(distanceChange)+std::floor(errorcount);
        errorcount = errorcount - std::floor(errorcount);
    }
    //qDebug() << errorcount;
    SDL_Rect point;
    SDL_Surface* sprite;
    for(int i = 0;i<lanes;++i){
        //draw score region
        sprite = lanesurfs[i];
        point.x = laneIndents[i];
        point.y = 0;
        point.w = arrowLaneSize;
        point.h = height();
        //SDL_UnlockSurface(screen);
        SDL_BlitSurface(sprite,NULL,screen,&point);
        int j1 = 0;
        QListIterator<Arrow*> itr(arrows[i]);
        while(itr.hasNext()){
            Arrow* arrow = itr.next();
            double loc=arrow->getBottomLoc();
            if(loc>getDistance()) {
                destroyArrow(i+1);
            } else {
                arrow->addToLocation(distanceChange);
            }
            int yindent = (int)(arrow->getDistanceLoc());
            sprite = imagesSprites[i];
            point.y = height()-yindent;
            point.h = sprite->h;
            SDL_BlitSurface(sprite,NULL,screen,&point);
        }
        //TODO Needs to be inserted in main render queue
        QListIterator<Arrow*> itr2(holdArrows[i]);
        while(itr2.hasNext()){
            Arrow* arrow = itr2.next();
            double loc=arrow->getBottomLoc();
            if(loc>getDistance()) {
                destroyHoldArrow(i+1);
            } else {
                arrow->addToLocation(distanceChange);
            }
            sprite = holdSurfaces[i]->at(j1);
            int yindent = (int)(arrow->getDistanceLoc());
            point.y = height()-yindent;
            point.h = sprite->h;
            //SDL_UnlockSurface(screen);
            SDL_BlitSurface(sprite,NULL,screen,&point);
            ++j1;
        }
    }
    //Render text
    //TODO Unimplemented - use SDL_ttf


    SDL_UnlockSurface(screen);
    //Update the screen
    //if ( (screen->flags & SDL_DOUBLEBUF) == SDL_DOUBLEBUF ) {
            SDL_Flip(screen);
    //}
    //qDebug() << 1000.0/(double)(SDL_GetTicks() - begintime) << "fps";
    //qDebug() << SDL_GetTicks() - begintime << "elapsed in update func";
    //qDebug() << 1000.0/timeSpent << "fps";
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

#include "SongMenu.h"
#include <QFile>
//#include <QtUiTools>
#include <QListWidget>
#include <QtDebug>
#include <QPainter>
#include <QPicture>
#include <QGridLayout>
#include <QPoint>
#include <QPaintEngine>
#include "FileIOServer.h"
#include <QImage>
#include "MediaPlayer.h"

SongMenu::SongMenu(BaseMenuForm* form, QWidget* parent): StepMenu(form, parent) {
    songMenuON = true;
    x = 0;
    songNumber = 0;
    this->setWidgetRep(this);
    IO = new FileIOServer();
    myPlayer = MediaPlayer::getMediaPlayerInst();
}
SongMenu::~SongMenu() {
    songMenuON = false;
}
int SongMenu::getIndex() {
    return songNumber;
}
void SongMenu::paintEvent(QPaintEvent* e) {
    SongCatalogue* const cata = SongCatalogue::getInstance();
    list = cata->getFileNames();
    QPainter* p = new QPainter(this);
    p->setPen(Qt::blue);
    p->setBrush(Qt::red);
    //selectedSong = 0;/*(x+2);*/
    /* TODO: load background image waiting for song reader to work correctly
    qDebug()<< " before image load";
    qDebug()<< IO->getSongReader(selectedSong)->getBackGroundFile();
    backroundImage.load(IO->getSongReader(selectedSong)->getBackGroundFile());
    point.setX(0.0);
    point.setY(0.0);
    p->drawImage(point,backroundImage);
    */
    // draw red box for song info
    p->drawRect((form->width()/3)*2,(form->height()/4), form->width()/3, (form->height()/2));
    p->setBrush(Qt::blue);

    p->setFont(QFont("Arial", 10));
    p->drawRect(0,(form->height()/4) +(form->height()/10), form->width()/3, (form->height()/8));
    songNumber = 0;
    p->setPen(Qt::black);
    p->drawText(0,(form->height()/3)-(form->height()/10)*2,list->at(0));
    qDebug()<< " 1";
    p->drawText(0, (form->height()/3)-(form->height()/10), list->at(0));
    qDebug()<< " 2";
    p->drawText(0, (form->height()/3), list->at(0));
    qDebug()<< " 3";
    p->setFont(QFont("Arial", 15));
    qDebug()<< " 4";
    p->drawText(0, (form->height()/3)+(form->height()/10), list->at(0));
    selectedSong = list->at(0);
    p->drawText((form->width()/3)*2, (form->height()/3)+(form->height()/10), IO->getSongReader(selectedSong)->getSongTitle());
    p->drawText((form->width()/3)*2, (form->height()/3)+(form->height()/10)*2, IO->getSongReader(selectedSong)->getSubtitle());
    p->drawText((form->width()/3)*2, (form->height()/3)+(form->height()/10)*3, IO->getSongReader(selectedSong)->getSongArtist());

//    if ( x >=0 && x+4<=list->size()-3) {//draws blue rec in center value
//        p->drawRect(0,(form->height()/4), form->width()/3, (form->height()/8));
//    }
//    if (x+4 >= list->size()) {
//        x = list->size()-5;
//    }
//    if (x<=(-3)) {
//        x = -2;
//    }
//    if (x==(-1)) {
//        p->setFont(QFont("Arial", 10));
//        p->drawRect(0,(form->height()/4) +(form->height()/10), form->width()/3, (form->height()/8));
//        songNumber = x+2;
//        p->setPen(Qt::black);
//        p->drawText(0,(form->height()/3)-(form->height()/10)*2,list->at(x+5));
//        qDebug()<< " 1";
//        p->drawText(0, (form->height()/3)-(form->height()/10), list->at(x+4));
//        qDebug()<< " 2";
//        p->drawText(0, (form->height()/3), list->at(x+3));
//        qDebug()<< " 3";
//        p->setFont(QFont("Arial", 15));
//        qDebug()<< " 4";
//        p->drawText(0, (form->height()/3)+(form->height()/10), list->at(x+2));
//        selectedSong = list->at(x+2);
//        p->drawText((form->width()/3)*2, (form->height()/3)+(form->height()/10), IO->getSongReader(selectedSong)->getSongTitle());
//        p->drawText((form->width()/3)*2, (form->height()/3)+(form->height()/10)*2, IO->getSongReader(selectedSong)->getSubtitle());
//        p->drawText((form->width()/3)*2, (form->height()/3)+(form->height()/10)*3, IO->getSongReader(selectedSong)->getSongArtist());
//        qDebug()<< " 5";
//        p->setFont(QFont("Arial", 10));
//        p->drawText(0, (form->height()/3)+(form->height()/10)*2, list->at(x+1));
//        qDebug()<< " 6";


//    }
//    if (x==(-2)) {
//        p->setFont(QFont("Arial", 10));
//        p->drawRect(0,(form->height()/4) +(form->height()/10)*2, form->width()/3, (form->height()/8));
//        p->setPen(Qt::black);
//        songNumber = x+2;
//        p->drawText(0,(form->height()/3)-(form->height()/10)*2,list->at(x+6));

//        p->drawText(0, (form->height()/3)-(form->height()/10), list->at(x+5));
//        p->drawText(0, (form->height()/3), list->at(x+4));
//        p->drawText(0, (form->height()/3)+(form->height()/10), list->at(x+3));
//        p->setFont(QFont("Arial", 15));
//        p->drawText(0, (form->height()/3)+(form->height()/10)*2, list->at(x+2));
//        selectedSong = list->at(x+2);
//        p->drawText((form->width()/3)*2, (form->height()/3)+(form->height()/10), IO->getSongReader(selectedSong)->getSongTitle());
//        p->drawText((form->width()/3)*2, (form->height()/3)+(form->height()/10)*2, IO->getSongReader(selectedSong)->getSubtitle());
//        p->drawText((form->width()/3)*2, (form->height()/3)+(form->height()/10)*3, IO->getSongReader(selectedSong)->getSongArtist());
//        p->setFont(QFont("Arial", 10));
//    }
//    if (x+4== list->size()-2) {
//        p->drawRect(0,(form->height()/4) -(form->height()/10), form->width()/3, (form->height()/8));
//        songNumber = x+3;
//        p->setPen(Qt::black);
//        p->drawText(0,(form->height()/3)-(form->height()/10)*2,list->at(x+4));
//        p->setFont(QFont("Arial", 15));
//        p->drawText(0, (form->height()/3)-(form->height()/10), list->at(x+3));
//        selectedSong = list->at(x+3);
//        p->drawText((form->width()/3)*2, (form->height()/3)+(form->height()/10), IO->getSongReader(selectedSong)->getSongTitle());
//        p->drawText((form->width()/3)*2, (form->height()/3)+(form->height()/10)*2, IO->getSongReader(selectedSong)->getSubtitle());
//        p->drawText((form->width()/3)*2, (form->height()/3)+(form->height()/10)*3, IO->getSongReader(selectedSong)->getSongArtist());
//        p->setFont(QFont("Arial", 10));
//        p->drawText(0, (form->height()/3), list->at(x+2));
//        p->drawText(0, (form->height()/3)+(form->height()/10), list->at(x+1));
//        p->drawText(0, (form->height()/3)+(form->height()/10)*2, list->at(x));
//    }
//    if (x+4== list->size()-1) {
//        p->drawRect(0,(form->height()/4) -(form->height()/10)*2, form->width()/3, (form->height()/8));
//        songNumber =x+4;
//        p->setPen(Qt::black);
//        p->setFont(QFont("Arial", 15));
//        p->drawText(0,(form->height()/3)-(form->height()/10)*2,list->at(x+4));
//        selectedSong = list->at(x+4);
//        p->drawText((form->width()/3)*2, (form->height()/3)+(form->height()/10), IO->getSongReader(selectedSong)->getSongTitle());
//        p->drawText((form->width()/3)*2, (form->height()/3)+(form->height()/10)*2, IO->getSongReader(selectedSong)->getSubtitle());
//        p->drawText((form->width()/3)*2, (form->height()/3)+(form->height()/10)*3, IO->getSongReader(selectedSong)->getSongArtist());
//        p->setFont(QFont("Arial", 10));
//        p->drawText(0, (form->height()/3)-(form->height()/10), list->at(x+3));
//        p->drawText(0, (form->height()/3), list->at(x+2));
//        p->drawText(0, (form->height()/3)+(form->height()/10), list->at(x+1));
//        p->drawText(0, (form->height()/3)+(form->height()/10)*2, list->at(x));
//    }
//    qDebug() << list->at(x+2);
//    p->setPen(Qt::black);
//    p->setFont(QFont("Arial", 10));
//    if ( x >=0 && x+4<=list->size()-3) {//draw when list not withing 3 of endpoints
//        p->drawText(0,(form->height()/3)-(form->height()/10)*2,list->at(x+4));
//        p->drawText(0, (form->height()/3)-(form->height()/10), list->at(x+3));
//        p->setFont(QFont("Arial", 15));
//        selectedSong = list->at(x+2);
//        p->drawText((form->width()/3)*2, (form->height()/3)+(form->height()/10), IO->getSongReader(selectedSong)->getSongTitle());
//        p->drawText((form->width()/3)*2, (form->height()/3)+(form->height()/10)*2, IO->getSongReader(selectedSong)->getSubtitle());
//        p->drawText((form->width()/3)*2, (form->height()/3)+(form->height()/10)*3, IO->getSongReader(selectedSong)->getSongArtist());
//        p->drawText(0, (form->height()/3), list->at(x+2));
//        p->setFont(QFont("Arial", 10));
//        p->drawText(0, (form->height()/3)+(form->height()/10), list->at(x+1));
//        p->drawText(0, (form->height()/3)+(form->height()/10)*2, list->at(x));
//        songNumber= x+2;
//    }
//    if (myPlayer->isPlaying()==true) { // if music playing stops it before setting new song
//        myPlayer->stop();
//    }
myPlayer->playFile(IO->getSongReader(selectedSong)->getSongFile()); // plays music
//    //TODO: use song sample instead of start of song once mediaplayer functions are fixed
//    //myPlayer->pause();
//    // myPlayer->seek(IO->getSongReader(selectedSong)->getSongSampleStart());
//    //myPlayer->play();
//    songNumber = x+2;
//    qDebug() << "Eat my shorts 16";
    delete p;
}
////Keep space to a minimum - Sebastian Audet
    void SongMenu::keyPressEvent(QKeyEvent* e) {
//    qDebug() << "MAD PERSON HERE!!!!!!!!";
//    if(e->key()==Qt::Key_Return){
        myPlayer->stop();
//        qDebug()<< "Did you know L,";
//        songNumber = x+2;
//        qDebug()<< "Gods of death";
//        qDebug()<< (list->at(x+2)) << " song given";
//        form->goToMenu(300);
//        qDebug()<< "like apples";
//    }
//    if(e->key()==Qt::Key_Up) {
//        ++x;
//        qDebug()<< x <<" x";
//        update();
//    }
//    if(e->key()==Qt::Key_Down) {
//        --x;
//        qDebug()<< x <<  x <<" x";
//        update();
//    }
//    if(e->key()==Qt::Key_Escape) {
//        myPlayer->stop();
//        form->goToMenu((1)); // TODO: make it run game //Sebastian - what?!
//    }
    return;
}

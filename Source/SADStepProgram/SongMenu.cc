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
    numberSelected = 0;
    songNumber = 0;
    this->setWidgetRep(this);
    IO = new FileIOServer();
    myPlayer = MediaPlayer::getMediaPlayerInst();
    firstRun = true;
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
    // TODO: load background image waiting for song reader to work correctly
   // " before image load"

    //Not implemented

    /*  if (IO->getSongReader(selectedSong)->getBackGroundFile() != NULL)
    {
    backroundImage.load(IO->getSongReader(selectedSong)->getBackGroundFile());
    point.setX(0.0);
    point.setY(0.0);
    p->drawImage(point,backroundImage);
    } */

    // draw red box for song info
    p->drawRect((form->width()/3)*2,(form->height()/4), form->width()/3, (form->height()/2));
    p->setBrush(Qt::blue);

    p->setFont(QFont("Arial", 10));
    p->drawRect(0,(form->height()/4) +(form->height()/10), form->width()/3, (form->height()/8));
    songNumber = 0;
    p->setPen(Qt::black);

    if (list->size() <= x+3)
    {
         p->drawText(0,(form->height()/3)-(form->height()/10)*2," ERROR: Does Not Exist");
    }
    else
    {
         p->drawText(0,(form->height()/3)-(form->height()/10)*2,list->at(x+3));
    }
    qDebug()<< " 1";

    if (list->size() <= x+2)
    {
      p->drawText(0, (form->height()/3)-(form->height()/10), "ERROR: Does Not Exist");
    }
     else
     {
       p->drawText(0, (form->height()/3)-(form->height()/10), list->at(x+2));
   }

    qDebug()<< " 2";
    if (list->size() <=x+1)
    {
    p->drawText(0, (form->height()/3), "ERROR: Does Not Exist");
    }
    else
    {
     p->drawText(0, (form->height()/3), list->at(x+1));
    }
    qDebug()<< " 3";
    p->setFont(QFont("Arial", 15));

     qDebug()<< " 4a";
    if (list->size() <= x)
    {
        qDebug()<< " 4b";
    p->drawText(0, (form->height()/3)+(form->height()/10), "ERROR: Does Not Exist");
    selectedSong = list->at(x);
    numberSelected = x;
    }
    else
    {
        p->drawText(0, (form->height()/3)+(form->height()/10), list->at(x));
            selectedSong = list->at(x);
            numberSelected = x;
    }
    qDebug()<< " 5";

    p->drawText((form->width()/3)*2, (form->height()/3)+(form->height()/10), IO->getSongReader(selectedSong)->getSongTitle());
    p->drawText((form->width()/3)*2, (form->height()/3)+(form->height()/10)*2, IO->getSongReader(selectedSong)->getSubtitle());
    p->drawText((form->width()/3)*2, (form->height()/3)+(form->height()/10)*3, IO->getSongReader(selectedSong)->getSongArtist());



if (firstRun == true)
    {
    selectedSong=list->at((x));
myPlayer->playFile(IO->getSongReader(selectedSong)->getSongFile());
firstRun = false;
}
    delete p;
}
    void SongMenu::keyPressEvent(QKeyEvent* e) {
    qDebug() << "MAD PERSON HERE!!!!!!!!";
    if(e->key()==Qt::Key_Return){
        myPlayer->stop();
        qDebug()<< "Did you know L,";
        songNumber = numberSelected;
        qDebug()<< "Gods of death";
        qDebug()<< (list->at(x)) << " song given";
        form->goToMenu(300);
        qDebug()<< "like apples";
    }
    if(e->key()==Qt::Key_Up) {
        if( x < list->size()-1)
        {
            if (myPlayer->isPlaying()==true){ // if music playing stops it before setting new song
                myPlayer->stop();}
        ++x;
        selectedSong=list->at((x));
        myPlayer->playFile(IO->getSongReader(selectedSong)->getSongFile()); // plays music
        }




        update();


    }
    if(e->key()==Qt::Key_Down) {
        if( x > 0)
         {
            if (myPlayer->isPlaying()==true) { // if music playing stops it before setting new song
                myPlayer->stop();}
         --x;
         selectedSong=list->at((x));
          myPlayer->playFile(IO->getSongReader(selectedSong)->getSongFile()); // plays music
         }


         update();


    }
    if(e->key()==Qt::Key_Escape) {
        myPlayer->stop();
        form->goToMenu((1)); // TODO: make it run game //Sebastian - what?!
    }
    return;
}

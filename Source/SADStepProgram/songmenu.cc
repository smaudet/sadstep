#include "songmenu.h"

#include <QFile>
#include <QtUiTools>
#include <QListWidget>
#include <QtDebug>
#include <QPainter>
#include <QPicture>
#include <QGridLayout>
#include <QPoint>
#include <QPaintEngine>
#include "FileIOServer.h"

#include "MediaPlayer.h"

SongMenu::SongMenu(BaseMenuForm* form, QWidget* parent): StepMenu(form, parent)
{
    songMenuON = true;
    x = 0;
    songNumber = 0;
    this->setWidgetRep(this);

}

SongMenu::~SongMenu()
{
    songMenuON = false;
}

int SongMenu::getIndex()
{
    return songNumber;
}

void SongMenu::paintEvent(QPaintEvent* e)
{



    SongCatalogue* const cata = SongCatalogue::getInstance();
    list = cata->getFileNames();
    QPainter* p = new QPainter(this);
    p->setPen(Qt::blue);
    p->setBrush(Qt::blue);
    if ( x >=0 && x+4<=list->size()-3)
    {
        p->drawRect(0,(form->height()/4), form->width()/3, (form->height()/8));
    }
    if (x+4 >= list->size())
    {
        x = list->size()-5;
    }
    if (x<=(-3))
    {
        x = -2;
    }
    if (x==(-1))
    {
        p->setFont(QFont("Arial", 10));
        p->drawRect(0,(form->height()/4) +(form->height()/10), form->width()/3, (form->height()/8));
        songNumber = x+2;
        p->setPen(Qt::black);
        p->drawText(0,(form->height()/3)-(form->height()/10)*2,list->at(x+5));
        qDebug()<< " 1";
        p->drawText(0, (form->height()/3)-(form->height()/10), list->at(x+4));
        qDebug()<< " 2";
        p->drawText(0, (form->height()/3), list->at(x+3));
        qDebug()<< " 3";
        p->setFont(QFont("Arial", 15));
        qDebug()<< " 4";
        p->drawText(0, (form->height()/3)+(form->height()/10), list->at(x+2));
        qDebug()<< " 5";
        p->setFont(QFont("Arial", 10));
        p->drawText(0, (form->height()/3)+(form->height()/10)*2, list->at(x+1));
        qDebug()<< " 6";


    }
    if (x==(-2))
    {
        p->setFont(QFont("Arial", 10));
        p->drawRect(0,(form->height()/4) +(form->height()/10)*2, form->width()/3, (form->height()/8));
        p->setPen(Qt::black);
        songNumber = x+2;
        p->drawText(0,(form->height()/3)-(form->height()/10)*2,list->at(x+6));

        p->drawText(0, (form->height()/3)-(form->height()/10), list->at(x+5));
        p->drawText(0, (form->height()/3), list->at(x+4));
        p->drawText(0, (form->height()/3)+(form->height()/10), list->at(x+3));
        p->setFont(QFont("Arial", 15));
        p->drawText(0, (form->height()/3)+(form->height()/10)*2, list->at(x+2));
        p->setFont(QFont("Arial", 10));
    }
    if (x+4== list->size()-2)
    {
        p->drawRect(0,(form->height()/4) -(form->height()/10), form->width()/3, (form->height()/8));
        songNumber = x+4;
        p->setPen(Qt::black);
        p->drawText(0,(form->height()/3)-(form->height()/10)*2,list->at(x+4));
        p->setFont(QFont("Arial", 15));
        p->drawText(0, (form->height()/3)-(form->height()/10), list->at(x+3));
        p->setFont(QFont("Arial", 10));
        p->drawText(0, (form->height()/3), list->at(x+2));
        p->drawText(0, (form->height()/3)+(form->height()/10), list->at(x+1));
        p->drawText(0, (form->height()/3)+(form->height()/10)*2, list->at(x));
    }
    if (x+4== list->size()-1)
    {
        p->drawRect(0,(form->height()/4) -(form->height()/10)*2, form->width()/3, (form->height()/8));
        songNumber =x+3;
        p->setPen(Qt::black);
        p->setFont(QFont("Arial", 15));
        p->drawText(0,(form->height()/3)-(form->height()/10)*2,list->at(x+4));
        p->setFont(QFont("Arial", 10));
        p->drawText(0, (form->height()/3)-(form->height()/10), list->at(x+3));
        p->drawText(0, (form->height()/3), list->at(x+2));
        p->drawText(0, (form->height()/3)+(form->height()/10), list->at(x+1));
        p->drawText(0, (form->height()/3)+(form->height()/10)*2, list->at(x));
    }

       qDebug() << list->at(x+2);
     /*FileIOServer* IO = new FileIOServer();
        qDebug()<< "HELLO";
        QString smName = (list->at(x+2));
         qDebug()<< "HELLO";
        QString alpha = IO->getSongReader(&smName)->getSongFile();
         qDebug()<< "HELLO";
        MediaPlayer* myPlayer = new MediaPlayer();
         qDebug()<< "HELLO";
        qDebug() << myPlayer->playFile(alpha);
         qDebug()<< "HELLO";*/

    p->setPen(Qt::black);
    p->setFont(QFont("Arial", 10));

    if ( x >=0 && x+4<=list->size()-3)
    {
        p->drawText(0,(form->height()/3)-(form->height()/10)*2,list->at(x+4));
        p->drawText(0, (form->height()/3)-(form->height()/10), list->at(x+3));
        p->setFont(QFont("Arial", 15));
        p->drawText(0, (form->height()/3), list->at(x+2));
        p->setFont(QFont("Arial", 10));
        p->drawText(0, (form->height()/3)+(form->height()/10), list->at(x+1));
        p->drawText(0, (form->height()/3)+(form->height()/10)*2, list->at(x));
        songNumber= x+2;
    }



    songNumber = x+2;
    qDebug() << "Eat my shorts 16";
    delete p;

}

void SongMenu::keyPressEvent(QKeyEvent* e)
{
    qDebug() << "MAD PERSON HERE!!!!!!!!";

    if(e->key()==Qt::Key_Return)
    {


        qDebug()<< "Did you know L,";
        songNumber = x+2;
        qDebug()<< "Gods of death";
        qDebug()<< (list->at(x+2)) << " song given";
        form->goToMenu(300);
        qDebug()<< "like apples";


    }




    if(e->key()==Qt::Key_Up)
    {

        ++x;
        qDebug()<< x <<" x";


        update();


    }



    if(e->key()==Qt::Key_Down)
    {

        --x;
        qDebug()<< x <<  x <<" x";


        update();


    }



    if(e->key()==Qt::Key_Escape)
    {


        form->goToMenu((1)); // TODO: make it run game


    }
    return;
}




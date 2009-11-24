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


    //TODO: MAKE IT SO PROGRAM DOES NOT CRASH WHEN PROGRAM TRIES TO GO BEYOND BOUNDS OF QLIST list
    SongCatalogue* const cata = SongCatalogue::getInstance();
    const QList<QString>* list = cata->getFileNames();
    QPainter* p = new QPainter(this);
    p->setPen(Qt::blue);
    p->setBrush(Qt::blue);
    if ( x >=0 && x+4<=list->size())
    {
        p->drawRect(0,(form->height()/4), form->width()/3, (form->height()/8));
    }
    if (x==(-3))
    {
        x = -2;
    }
    if (x==(-1))
    {
        x++;
        p->drawRect(0,(form->height()/4) +(form->height()/10), form->width()/3, (form->height()/8));
        songNumber = x+2;
        p->setPen(Qt::black);
        p->drawText(0,(form->height()/3)-(form->height()/10)*2,list->at(x+5));
        p->drawText(0, (form->height()/3)-(form->height()/10), list->at(x+4));
        p->drawText(0, (form->height()/3), list->at(x+3));
        p->setFont(QFont("Arial", 15));
        p->drawText(0, (form->height()/3)+(form->height()/10), list->at(x+2));
        p->setFont(QFont("Arial", 10));
        p->drawText(0, (form->height()/3)+(form->height()/10)*2, list->at(x+1));
        x--;
    }
    if (x==(-2))
    {
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
        songNumber = list->size()-2;
    }
    if (x+4== list->size()-1)
    {
        p->drawRect(0,(form->height()/4) -(form->height()/10)*2, form->width()/3, (form->height()/8));
        songNumber = list->size()-1;
    }
    if (x+4 == list->size())
    {
        x = list->size()-3;
    }
       qDebug() << list->at(x);
    /* FileIOServer* IO = new FileIOServer();
        qDebug()<< "HELLO";
        QString smName = (list->at(x+2));
         qDebug()<< "HELLO";
        QString alpha = IO->getSongReader(&smName)->getSongFile();
         qDebug()<< "HELLO";
        MediaPlayer* myPlayer = new MediaPlayer();
         qDebug()<< "HELLO";
        qDebug() << myPlayer->playFile(alpha);
         qDebug()<< "HELLO"; */

    p->setPen(Qt::black);
    p->setFont(QFont("Arial", 10));

    if ( x >=0 && x+4<=list->size())
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
        form->goToMenu((0),false);
        qDebug()<< "like apples";


    }




    if(e->key()==Qt::Key_Up)
    {

        x++;


        update();


    }



    if(e->key()==Qt::Key_Down)
    {

        x--;


        update();


    }



    if(e->key()==Qt::Key_Escape)
    {


        form->goToMenu((1),false); // TODO: make it run game


    }
    return;
}




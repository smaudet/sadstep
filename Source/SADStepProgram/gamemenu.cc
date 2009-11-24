#include "gamemenu.h"

GameMenu::GameMenu(BaseMenuForm* form, QWidget* parent): StepMenu(form,parent)
{
    /*sui = new QFile(":/menus/gamemenu.ui");
    loader = new QUiLoader();
    loader->load(sui,this);
    gameStartBtn = this->findChild<QPushButton*>("gameSelectBtn");
    // gamestartBtn->move((parent->width()/(2)), (parent->height()/(2)));
    x = 3;
    this->setWidgetRep(this);

    //qDebug() << parent->height() << " at Game Menu";
}
/*void GameMenu::menuSelected2() {
    form->goToMenu(2);
}
void GameMenu::menuSelected3() {
    form->goToMenu(3);
}
void GameMenu::menuSelected4() {
    form->goToMenu(4);
}*/
GameMenu::~GameMenu() {
    qDebug() << "GameStuff";
    qDebug() << "GameStuff";
}
void GameMenu::paintEvent(QPaintEvent* e)
{

    QPainter* p = new QPainter(this);
    p->setBrush(Qt::blue);
    if (x==3)
    {
    p->drawRect(form->width()/2.3,(form->height()/4), form->width()/6, (form->height()/10));
}
    if(x==2)
    {
        p->drawRect(form->width()/2.3,(form->height()/4)+(form->height()/10), form->width()/8, (form->height()/10));
    }
    if (x==1)
    {
        p->drawRect(form->width()/2.3,(form->height()/4)+(form->height()/10)*2, form->width()/16, (form->height()/10));
    }
    p->setFont(QFont("Arial", 25));
    p->setPen(Qt::black);
    p->drawText(form->width()/2.3, form->height()/3, "START GAME");
    p->drawText(form->width()/2.3, (form->height()/3)+(form->height()/10), "OPTIONS");
    p->drawText(form->width()/2.3, (form->height()/3)+(form->height()/10)*2, "EXIT");
    //p->drawImage(this->getSelector()); //TODO: implement getting image from getSelector
    delete p;

}
void GameMenu::keyPressEvent(QKeyEvent* e)
{
    qDebug() << "start of game menu paint event";

    if(e->key()==Qt::Key_Return)
    {
        update();
        if ( x==3)
        {
            form->goToMenu(2);
        }
        if (x==2)
        {
            form->goToMenu(3);
        }
        if (x==1)
        {
            form->goToMenu(4);
        }
    }

    if(e->key()==Qt::Key_Up)
    {
        if (x != 3)
        {
            x++;
            update();
        }
        else
            return;

    }
    if (e->key()==Qt::Key_Down)
    {
        if (x != 1)
        {
            x--;
            update();
        }
        else
            return;
    }

}



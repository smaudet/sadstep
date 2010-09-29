#include "StartMenu.h"
#include "BaseMenuForm.h"


StartMenu::StartMenu(BaseMenuForm* form,QWidget* parent): StepMenu(form,parent)
{
   /* sui = new QFile(":/menus/mainmenu.ui");
    loader = new QUiLoader();
    loader->load(sui,this);
    startBtn = this->findChild<QPushButton*>("pushButton");
    connect(startBtn, SIGNAL(clicked()), this, SLOT(menuSelected1()));
    */
    //this->setFocus();

    qDebug() << this->hasFocus() << "has focus (startMenu)";
    qDebug()<< this->isVisible() << "is visible (startMenu)";
}
//void StartMenu::menuSelected1()
//{
//    form->goToMenu(1);
//}
StartMenu::~StartMenu() {
   // qDebug() << "StartMenu";
   // delete sui;
    //delete loader;
    //delete startBtn;
   // qDebug() << "StartMenu";
}

void StartMenu::keyPressEvent(QKeyEvent* e)
{
    qDebug() << "start of startmenu paint event";

    if(e->key()==Qt::Key_Return)
    {
        form->goToMenu(1);


    }
}
void StartMenu::paintEvent(QPaintEvent* e)
{
    QPainter* p = new QPainter(this);
    p->setFont(QFont("Arial", 25));
    p->setBrush(Qt::blue);
    //p->drawImage(this->getSelector()); //TODO: implement getting image from getSelector
    p->drawRect(form->width()/2.5,(form->height()/4), form->width()/6, (form->height()/10));
    p->setPen(Qt::black);
    p->drawText(form->width()/2.3, form->height()/3, "START");
    delete p;

}

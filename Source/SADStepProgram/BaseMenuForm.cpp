#include "BaseMenuForm.h"
#include "ui_basemenuform.h"
#include "StartMenu.h"
#include "SongMenu.h"
#include "GameMenu.h"
#include <QMainWindow>
#include <QtDebug>

BaseMenuForm::BaseMenuForm(QWidget *parent) :
        QWidget(parent),
        m_ui(new Ui::BaseMenuForm) {
    newSpeed = 0;
    optionMenu = false;
    newRange = 0;
    m_ui->setupUi(this);
    connect(m_ui->cancelBtn,SIGNAL(clicked()),this,SLOT(mainMenu()));
    connect(m_ui->okBtn,SIGNAL(clicked()),this,SLOT(runGame()));
    showButtonWindow = true;
    parent->setStyleSheet(this->styleSheet());
    goToMenu(0, true);
    qDebug() << parent->height() << " at Base Menu Form";
    // change
}

void BaseMenuForm::runGame() {
    qDebug() << "tt";
    goToMenu(BaseMenuForm::RUN_GAME);
}

bool BaseMenuForm::mainMenu() {
    goToMenu(1);
    return false; //FIXME
}

BaseMenuForm::~BaseMenuForm() {
    delete m_ui;
}

/*
  * Sebastian Audet
  * This function places a StepMenu inside window.
  * It should be noted that the behavior of this function is subject to change, but that
  * at the moment it sets itself using the widget from menu->getWidget()
  */
//TODO fix layout for arbitrary widgets
void BaseMenuForm::setMenuWidget(StepMenu* menu) {
    //menu->setParent(m_ui->frame_2);
    //qDebug() << menu->getWidget()->size() << "WIDGET";

    //Fake laying out frame_2
    m_ui->frame_2->setGeometry(QRect(0,0,parentWidget()->width(),parentWidget()
                                     ->height()-m_ui->frame->height()-200));

    //Add Widget to layout
    m_ui->gLayout->addWidget(menu,2,2,1,1,0);
    //qDebug() << menu->getWidget()->size() << "WIDGET";
    qDebug()<<menu->isHidden() << " is hidden?";
    menu->setFocus();
    qDebug() << menu->hasFocus() << "has focus?";


    /* if (optionMenu)
    {
        int inth = (m_ui->frame_2->height() - menu->getWidget()->height())/2;
        int intw = (m_ui->frame_2->width() - menu->getWidget()->width())/2;
        up = new QSpacerItem(0,inth,QSizePolicy::Minimum,QSizePolicy::Minimum);
        left = new QSpacerItem(intw,0,QSizePolicy::Preferred,QSizePolicy::Minimum);
        down = new QSpacerItem(0,inth,QSizePolicy::Minimum,QSizePolicy::Minimum);
        right = new QSpacerItem(intw,0,QSizePolicy::Preferred,QSizePolicy::Minimum);

        m_ui->gLayout->addItem(up, 1,2,1,1,Qt::AlignHCenter);
        m_ui->gLayout->addItem(down, 3,2,1,1,Qt::AlignHCenter);
        m_ui->gLayout->addItem(left, 2,1,1,1,Qt::AlignVCenter);
        m_ui->gLayout->addItem(right, 2,3,1,1,Qt::AlignVCenter);

    } */
}

bool BaseMenuForm::setButtonsVisible(bool visible){
    if(!visible) {
        m_ui->frame_3->hide();
    } else {
        m_ui->frame_3->show();
    }
    return visible;
}

bool BaseMenuForm::toggleButtonWindow() {
    return (showButtonWindow = setButtonsVisible(!showButtonWindow));
}

/*bool BaseMenuForm::toggleOK() {
    showOK = !showOK;
    if(showOK) {
        m_ui->okBtn->show();
    } else {
        m_ui->okBtn->hide();
    }
    return showOK;
}

bool BaseMenuForm::toggleCancel() {
    showCancel = !showCancel;
    if(showCancel) {
        m_ui->cancelBtn->show();
    } else {
        m_ui->cancelBtn->hide();
    }
    return showCancel;
}*/


void BaseMenuForm::goToMenu(int index, bool firstRun) {
    if(!firstRun){
        delete stepMenu;
    }
    switch(index) {
    case 0: {
            qDebug() << "case 0:";
            stepMenu = new StartMenu(this);
            setButtonsVisible(false);
            //stepMenu->setFocus();
            setMenuWidget(stepMenu);
            break;
        }
    case 1: {
            qDebug() << "case 1:";
            stepMenu = new GameMenu(this);
            setButtonsVisible(false);
            changeLabel(0);
            //stepMenu->setFocus();
            setMenuWidget(stepMenu);
            stepMenu->repaint();
            break;
        }
    case 2: {
            qDebug() << "case 2:";
            stepMenu = new SongMenu(this);
            //stepMenu->setVisible(true);
            setButtonsVisible(false);
            changeLabel(2);
            // qDebug() << "Eat my roomates shorts";
            //stepMenu->setFocus();
            setMenuWidget(stepMenu);
            //qDebug() << "Eat my shorts 0";
            break;
        }
    case 3:{} //Does Nothing intentionally!!!!!!!!!!!!!!!!!
              // Forces Game to Quit
    case 4: {
            qDebug() << "case 4:";
            close();
            break;
        }
    case 5:{
            /*
             qDebug() << "case 3:";
            stepMenu = new OptionMenu(this);
            setButtonsVisible(false);
            changeLabel(1);
            //stepMenu->setFocus();
            optionMenu = true;
            setMenuWidget(stepMenu);
            break;
            */
        }

    case 300: { // Run Game

            qDebug() << "Set To " << ((SongMenu*)stepMenu)->getIndex();
            //newSpeed = (((OptionMenu*)stepMenu)->getSpeed());
            //qDebug() << newSpeed;
            //newRange = (((OptionMenu*)stepMenu)->getRange());
            //qDebug() << newRange;
            emit runGame(((SongMenu*)stepMenu)->getIndex());
            break;
        }
    default:{
            stepMenu = new StartMenu(this);
            //stepMenu->setFocus();
            setButtonsVisible(false);
            break;
        }
    };
}

void BaseMenuForm::changeLabel(int labelChange){
    sui = new QFile(":/menus/basemenu.ui");
    switch(labelChange) {
    case 0: {

            m_ui->label->setText("Game Menu");
            break;
        }
    case 1: {

            m_ui->label->setText("Options Menu");
            break;
        }
    case 2: {

            m_ui->label->setText("Song Menu");
            break;
        }
    }
}

void BaseMenuForm::closeEvent(QCloseEvent* e) {
    this->parentWidget()->close();
}

void BaseMenuForm::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void BaseMenuForm::setActiveButton()
{
    /* if (m_ui->cancelBtn->isChecked())
    {
        m_ui->cancelBtn->setChecked(false);
        m_ui->okBtn->setChecked(true);
    }
   if (m_ui->okBtn->isChecked())
    {
       m_ui->okBtn->setChecked(false);
       m_ui->cancelBtn->setChecked(true);

    }*/
}
int BaseMenuForm::getRange()
{
    return (newRange = 0);
}
int BaseMenuForm::getSpeed()
{
    return (newSpeed = 0);
}



#include "basemenuform.h"
#include "ui_basemenuform.h"
#include "startmenu.h"
#include "songmenu.h"
#include "gamemenu.h"
#include "optionmenu.h"
#include <QMainWindow>
#include <QtDebug>

BaseMenuForm::BaseMenuForm(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::BaseMenuForm)
{
    m_ui->setupUi(this);
    connect(m_ui->cancelBtn,SIGNAL(clicked()),this,SLOT(mainMenu()));
    connect(m_ui->okBtn,SIGNAL(clicked()),this,SLOT(runGame()));
    showButtonWindow = true;
    parent->setStyleSheet(this->styleSheet());
    goToMenu(0, true);
}

void BaseMenuForm::runGame() {
    qDebug() << "tt";
    goToMenu(BaseMenuForm::RUN_GAME);
}

bool BaseMenuForm::mainMenu() {
    goToMenu(1);
}

BaseMenuForm::~BaseMenuForm()
{
    qDebug() << "forward";
    delete m_ui;
    qDebug() << "twilight";
}

void BaseMenuForm::setMenuWidget(StepMenu* menu) {
    menu->getWidget()->setParent(m_ui->frame_2);
    m_ui->horizontalLayout_2->addWidget(menu->getWidget());
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
            stepMenu = new StartMenu(this);
            setButtonsVisible(false);
            setMenuWidget(stepMenu);
            }
            break;
        case 1: {
            stepMenu = new GameMenu(this);
            setButtonsVisible(false);
            changeLabel(0);
            setMenuWidget(stepMenu);
            break;
        }
        case 2: {
            stepMenu = new SongMenu(this);
            setButtonsVisible(true);
            changeLabel(2);
            setMenuWidget(stepMenu);
            break;
        }
        case 3: {
            stepMenu = new OptionMenu(this);
            setButtonsVisible(false);
            changeLabel(1);
            setMenuWidget(stepMenu);
            break;
        }
        case 4: {
            close();
            break;
        }
        case 300: { // Run Game
            emit runGame(0);
            break;
        }
        default:{
            stepMenu = new StartMenu(this);
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

#include "OptionMenu.h"
#include "Profile.h"

OptionMenu::OptionMenu(BaseMenuForm* form,QWidget* parent): StepMenu(form, parent)
{
    speed = 3000;
    range = 500;
    sui = new QFile(":/menus/optionmenu.ui");
    loader = new QUiLoader();
    //widget = new QWidget();
    loader->load(sui,this);
    cancelBtn = this->findChild<QPushButton*>("cancelBtn");
    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(cancel()));
    this->setWidgetRep(this->findChild<QWidget*>("Form"));

    speedSlider = this->findChild<QSlider*>("horizontalSlider");

    rangeSlider = this->findChild<QSlider*>("horizontalSlider_2");
    easy = this->findChild<QRadioButton*>("easy");
    normal = this->findChild<QRadioButton*>("normal");
    hard = this->findChild<QRadioButton*>("hard");
    expert = this->findChild<QRadioButton*>("expert");
    //qDebug() << parent->height() << " at Options Menu";

    speedSlider->setMaximum(5000);
    speedSlider->setMinimum(1000);
    speedSlider->setTickInterval(1000);
    speedSlider->setTickPosition(QSlider::TicksAbove);
    rangeSlider->setMinimum(1);
    rangeSlider->setMaximum(1000);
    rangeSlider->setTickInterval(100);
    rangeSlider->setTickPosition(QSlider::TicksAbove);
    connect(rangeSlider, SIGNAL(sliderMoved(int)), this, SLOT(rangeChange(int)));
    connect(speedSlider, SIGNAL(sliderMoved(int)), this, SLOT(speedChange(int)));
     //TODO: get pointer for location of profile class that is created at start of game
}
OptionMenu::~OptionMenu() {
    qDebug() << "OptionMenu";
    delete sui;
    delete loader;
    delete cancelBtn;
    //delete widget;
    delete speedSlider;
    delete rangeSlider;
    delete expert;
    delete easy;
    delete normal;
    delete hard;

    //delete widget->findChild<QHBoxLayout*>("HL");

    qDebug() << "OptionMenu";
}
void OptionMenu::cancel() {
    form->goToMenu(1);
}

void OptionMenu::speedChange (int speedChanged)
{
    speed = speedSlider->value();
    //speed = speedChanged;

    qDebug() << speed << " speed";
}
void OptionMenu::rangeChange (int rangeChanged)
{      range = rangeSlider->value();
    //range = rangeChanged;
    qDebug() << range << " range";
}
int OptionMenu::getRange()
{
    qDebug() << range << " range 2";
    return range;

}
int OptionMenu::getSpeed()
{
    qDebug() << speed << " speed 2";
    return speed;
}

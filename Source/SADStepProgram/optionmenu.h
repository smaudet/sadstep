#ifndef OPTIONMENU_H
#define OPTIONMENU_H

#include <QFile>
#include <QObject>
#include <QWidget>
#include <QtUiTools>
#include <QListWidget>
#include <QPushButton>
#include "basemenuform.h"
#include <QRadioButton>

class OptionMenu : public StepMenu
{ Q_OBJECT
public slots:
    void cancel();
    void rangeChange(int rangeChanged);
    void speedChange(int speedChanged);

    //    void menuSelected5();
    //    void menuSelected6();
    //    void menuSelected7();
public:
    //This GameMenu is virtually private! :D
    OptionMenu(BaseMenuForm* form,QWidget* parent=0);
    ~OptionMenu();
    int getSpeed();
    int getRange();
private:
    QPushButton* cancelBtn;
    QRadioButton* easy;
    QRadioButton* normal;
    QRadioButton* hard;
    QRadioButton* expert;
    QFile* sui;
    QUiLoader* loader;
    QWidget* widget;
    QSlider* speedSlider;
    QSlider* rangeSlider;
    int speed;
    int range;
};

#endif // OPTIONMENU_H

#ifndef MMCLASS_H
#define MMCLASS_H

#include <QFile>
#include <QObject>
#include <QWidget>
#include <QtUiTools>
#include <QListWidget>
#include <QPushButton>
#include <QtDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>
#include "stepmenu.h"

class StartMenu: public StepMenu
{ Q_OBJECT
//public slots:
    //void menuSelected1();
public:
    StartMenu(BaseMenuForm* form, QWidget* parent = 0);
    virtual ~StartMenu();
/*private:
    QPushButton *startBtn;
    QFile* sui;
    QUiLoader* loader;
    QWidget* widget;*/
protected:
    void paintEvent(QPaintEvent* e);
    void keyPressEvent(QKeyEvent* e);
};

#endif // MMCLASS_H

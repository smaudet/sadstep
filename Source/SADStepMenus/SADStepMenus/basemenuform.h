#ifndef BASEMENUFORM_H
#define BASEMENUFORM_H

#include <QtGui/QWidget>
#include <QObject>
#include "stepmenu.h"

class StepMenu;

namespace Ui {
    class BaseMenuForm;
}

class BaseMenuForm : public QWidget {
    Q_OBJECT
public:
    BaseMenuForm(QWidget *parent = 0);
    ~BaseMenuForm();
    //enum BaseMenuOps;
    void setMenuWidget(StepMenu* menu);
    bool setButtonsVisible(bool visible);
    bool toggleButtonWindow();
    bool toggleOK();
    bool toggleCancel();
    void goToMenu(int index, bool firstRun = false);
//    void runGame();
//    void runElse();
public slots:
    bool close();
    bool mainMenu();
protected:
    void changeEvent(QEvent *e);
private:
    bool showButtonWindow;
    bool showOK;
    bool showCancel;
    StepMenu* stepMenu;
    Ui::BaseMenuForm *m_ui;
};

#endif // BASEMENUFORM_H

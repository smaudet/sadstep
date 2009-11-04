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
    enum BaseMenuOps {
        RUN_GAME = 300
    };
    void setMenuWidget(StepMenu* menu);
    bool setButtonsVisible(bool visible);
    bool toggleButtonWindow();
    bool toggleOK();
    bool toggleCancel();
    void goToMenu(int index, bool firstRun = false);
//    void runGame();
//    void runElse();
public slots:
    bool mainMenu();
    void runGame();
signals:
    void runGame(int index);
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

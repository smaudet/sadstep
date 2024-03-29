#ifndef BASEMENUFORM_H
#define BASEMENUFORM_H

#include <QtGui/QWidget>
#include <QObject>
#include <QLabel>
#include <QFile>
#include "StepMenu.h"
#include <QGridLayout>
#include <QSpacerItem>


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
    QLabel* label;
    void setMenuWidget(StepMenu* menu);
    void setActiveButton();
    bool setButtonsVisible(bool visible);
    bool toggleButtonWindow();
    bool toggleOK();
    bool toggleCancel();
    void goToMenu(int index, bool firstRun = false);
    void changeLabel(int labelChange);
    //    void runGame();
    //    void runElse();
public slots:
    bool mainMenu();
    void runGame();
    int getSpeed();
    int getRange();

signals:
    void runGame(int index);
protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent* e);

private:
    bool showButtonWindow;
    bool showOK;
    bool showCancel;
    bool optionMenu; // used for if creating options menu
    QFile* sui;
    StepMenu* stepMenu;
    Ui::BaseMenuForm *m_ui;
    QSpacerItem* up;
    QSpacerItem* down;
    QSpacerItem* left;
    QSpacerItem* right;
    QRect* rect();
    int newSpeed;
    int newRange;


};

#endif // BASEMENUFORM_H

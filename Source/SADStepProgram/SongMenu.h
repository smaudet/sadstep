#ifndef SONGMENU_H
#define SONGMENU_H
#include <QObject>
#include <QFile>
//#include <QtUiTools>
#include <QWidget>
#include <QListWidget>
#include "StepMenu.h"
#include "SongCatalogue.h"
#include <QtDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QString>
#include <QPoint>
#include "FileIOServer.h"
#include "MediaPlayer.h"
#include <QImage>
#include <QPointF>

class SongMenu: public StepMenu
{
    Q_OBJECT
public:
    SongMenu(BaseMenuForm* form, QWidget* parent = 0);
    ~SongMenu();
    const QList <QString>* list;
    int getIndex();
    MediaPlayer* myPlayer;


//public slots:
  //  void rowChanged2(int billybob); // yes its name is billybob deal with it
    // (From: Scott)
private:
//    QFile* sui;
//    QUiLoader* loader;
//    QWidget* widget;
//    QListWidget* listWidget;
    int songNumber;
    int x;
    bool songMenuON;
    FileIOServer* IO;
    QString selectedSong;
    QPointF point;
    QImage backroundImage;

protected:
    void paintEvent(QPaintEvent* e);
    void keyPressEvent(QKeyEvent* e);
    void playMusic(QString smName);
};

#endif // SONGMENU_H

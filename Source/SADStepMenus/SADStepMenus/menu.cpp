#include "menu.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFile>
#include <QTextDocument>
#include <QMessageBox>
#include <QIcon>
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QAction>
#include <QPalette>
#include "basemenuform.h"
#include "songmenu.h"
#include <QtDebug>

//Start Screen
MainMenu::MainMenu():QMainWindow()
{
  qDebug() << "1";
  showFullScreen();
  qDebug() << "2";
  center = new BaseMenuForm();
  qDebug() << "3";
  center->setMenuWidget(new SongMenu());
  //center->toggleButtonWindow();
  setCentralWidget(center);
  setStyleSheet(center->styleSheet());
}

//Game Menu
//void MainMenu::gameMenu()
//{
//  center = new QWidget();
//  gameStart = new QPushButton("Game Start");
//  optionsBtn = new QPushButton("Options");
//  exit = new QPushButton("Exit");
//  setCentralWidget(center);
//  connect(exit, SIGNAL(clicked()), this, SLOT(close()));
//  connect(optionsBtn, SIGNAL(clicked()), this, SLOT(options()));
//  connect(gameStart, SIGNAL(clicked()), this, SLOT(songs()));
//  layout = new QGridLayout(center);
//  layout->addWidget(gameStart);
//  layout->addWidget(optionsBtn);
//  layout->addWidget(exit);
//}
//
////Options Menu
//void MainMenu::optionsMenu()
//{
//  center = new QWidget();
//  setCentralWidget(center);
//  cancelOptions = new QPushButton("Cancel");
//  connect(cancelOptions, SIGNAL(clicked()), this, SLOT(cancelOpt()));
//  layout = new QGridLayout(center);
//  layout->addWidget(cancelOptions);
//}
//
////Songs Menu
//void MainMenu::songsMenu()
//{
//  center = new QWidget();
//  setCentralWidget(center);
//  songsOK = new QPushButton("OK");
//  cancelSongsBtn = new QPushButton("Cancel");
//  connect(songsOK, SIGNAL(clicked()), this, SLOT(difficulty()));
//  connect(cancelSongsBtn, SIGNAL(clicked()), this, SLOT(cancelSongs()));
//  layout = new QGridLayout(center);
//  layout->addWidget(songsOK);
//  layout->addWidget(cancelSongsBtn);
//  createHorizontalGroupBox();
//  createGridGroupBox();
//}
//
////Difficulty Menu
//void MainMenu::difMenu()
//{
//  center = new QWidget();
//  setCentralWidget(center);
//  difOK = new QPushButton("OK");
//  cancelDifBtn = new QPushButton("Cancel");
//  connect(difOK, SIGNAL(clicked()), this, SLOT(blackScreen()));
//  connect(cancelDifBtn, SIGNAL(clicked()), this, SLOT(cancelDif()));
//  layout = new QGridLayout(center);
//  layout->addWidget(difOK);
//  layout->addWidget(cancelDifBtn);
//}
//
////Game Screen
//void MainMenu::gameScreen()
//{
//  center = new QWidget();
//  setCentralWidget(center);
//  cancelGameBtn = new QPushButton("Cancel");
//  connect(cancelGameBtn, SIGNAL(clicked()), this, SLOT(cancelGame()));
//  layout = new QGridLayout(center);
//  layout->addWidget(cancelGameBtn);
//}
//void MainMenu::createGridGroupBox()
// {
//   gridGroupBox = new QFrame();
//   QGridLayout *gridLayout = new QGridLayout();
//
//   gridGroupBox->setLayout(gridLayout);
// }
//void MainMenu::createHorizontalGroupBox()
// {
//horGroupBox= new QFrame();
//QHBoxLayout *horLayout = new QHBoxLayout();
//
//songsOK= new QPushButton("OK");
//cancelSongsBtn = new QPushButton("Cancel");
//
//horLayout->addWidget(songsOK);
//horLayout->addWidget(cancelSongsBtn);
//
//horGroupBox->setLayout(horLayout);
//layout->addWidget(horGroupBox);
// }
//void MainMenu::start()
//{
//  gameMenu();
//  //MainMenu::~MainMenu();
//}
//void MainMenu::options()
//{
//  optionsMenu();
//}
//void MainMenu::songs()
//{
//  songsMenu();
//}
//void MainMenu::close()
//{
// close();
//}
//void MainMenu::cancelOpt()
//{
// gameMenu();
//}
//void MainMenu::difficulty()
//{
// difMenu();
//}
//void MainMenu::cancelSongs()
//{
// gameMenu();
//}
//void MainMenu::cancelDif()
//{
// songsMenu();
//}
//void MainMenu::blackScreen()
//{
// gameScreen();
//}
//void MainMenu::cancelGame()
//{
// difMenu();
//}

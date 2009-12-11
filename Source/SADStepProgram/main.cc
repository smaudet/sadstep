#include <QtGui/QApplication>
#include <QtDebug>
//#include <QTest>
//#define QT_NO_DEBUG_OUTPUT

#include "mainwindow.h"
//#include "Tests.h";
#include "testtimer.h"
#include <QTime>
#include <QList>
#include <QListIterator>
#include "FileIOServer.h"
#include <QPair>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//	Tests* tests = new Tests();
//	QTest::qExec(tests);
    //TestTimer t;
//    FileIOServer* io = new FileIOServer();
//    QString loc = io->getSongCatalogue()->getFileName(0);
//    io->getStepReader(loc)->getStepData();
    //Debug Code for FileIOServer
//        FileIOServer* server = new FileIOServer();
//        int elapsedTime = 0;
//        QTime t;
//        int numFiles = server->getSongCatalogue()->getFileNames()->size();
//        for(int i = 0;i<numFiles;++i){
//            t.restart();
//            QString oname = server->getSongCatalogue()->getFileName(i);
//            qDebug() << oname << " file name";
//            SongReader* songreader = server->getSongReader(oname);
//            StepReader* stepreader = server->getStepReader(oname);
//            elapsedTime+=t.elapsed();
//            qDebug() << songreader->getBackGroundFile() << "background title";
//            qDebug() << songreader->getCredits() << "credits";
//            qDebug() << songreader->getSongArtist() << "song artist";
//            qDebug() << songreader->getSongFile() << "song file";
//            QListIterator<QPair<double,QString>*> itr(*(songreader->
//                                                        getBGAnimations()));
//            QPair<double,QString>* pair;
//            qDebug() << "bg anims:";
//            while(itr.hasNext()){
//                pair = itr.next();
//                qDebug() << pair->first << " " << pair->second;
//            }
//            qDebug() << songreader->getSongLyricsPath() << " lyrics path";
//            qDebug() << songreader->getSongSampleLength() << " song sample length";
//            qDebug() << songreader->getSongSampleStart() << " sample start";
//            qDebug() << songreader->getSongSelectable() << " song selectable";
//            qDebug() << songreader->getSongSubtitles()->readLine() << " lyrics";
//            qDebug() << songreader->getSongTitle() << " title";
//            QList<QPair<double,double>*>* bpms = stepreader->getBPM();
//            QListIterator<QPair<double,double>*> itr2(*bpms);
//            qDebug() << "bpms:";
//            while(itr2.hasNext()){
//                QPair<double,double>* pair = itr2.next();
//                qDebug() << pair->first << " " << pair->second;
//            }
//        }
//        qDebug() << elapsedTime;
//        qDebug() << elapsedTime/numFiles;
    return a.exec();
}

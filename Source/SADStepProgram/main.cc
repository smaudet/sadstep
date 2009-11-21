#include <QtGui/QApplication>
#include <QTime>
//#include <QTest>
//#define QT_NO_DEBUG_OUTPUT

#include "mainwindow.h"
#include "Tests.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();
//    Tests* tests = new Tests();
//    QTest::qExec(tests);
    FileIOServer* server = new FileIOServer();
    int elapsedTime = 0;
    int numFiles = server->getSongCatalogue()->getFileNames()->size();
    for(int i = 0;i<numFiles;++i){
	QString oname = server->getSongCatalogue()->getFileName(i);
	SongReader* songreader = server->getSongReader(oname);
	StepReader* stepreader = server->getStepReader(oname);
	elapsedTime+=QTime::currentTime().msec();
    }
    qDebug() << elapsedTime;
    qDebug() << elapsedTime/numFiles;
    return a.exec();
}

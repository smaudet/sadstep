#include <QtGui/QApplication>
#include <QtDebug>
//#include <QTest>
//#define QT_NO_DEBUG_OUTPUT

#include "mainwindow.h"
//#include "Tests.h";
#include "TestTimer.h"

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
    return a.exec();
}

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
    return a.exec();
}

#include <QtGui/QApplication>
#include <QtDebug>
//#include <QTest>
//#define QT_NO_DEBUG_OUTPUT

#include "mainwindow.h"
//#include "Tests.h";

int main(int argc, char *argv[])
{
    qDebug() << "start 0";
    QApplication a(argc, argv);
    qDebug() << "start";
    MainWindow w;
   w.show();
        //Tests* tests = new Tests();
        //QTest::qExec(tests);
    return a.exec();
}

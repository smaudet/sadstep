#include <QtGui/QApplication>
//#include <QTest>
//#define QT_NO_DEBUG_OUTPUT

#include "mainwindow.h"
//#include "Tests.h";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
   w.show();
        //Tests* tests = new Tests();
        //QTest::qExec(tests);
    return a.exec();
}

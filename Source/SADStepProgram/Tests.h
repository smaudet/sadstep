#ifndef TESTS_H
#define TESTS_H

//#include <QtTest/QtTest>
#include <QObject>

class Tests: public QObject {
    Q_OBJECT
public:
    Tests();
private slots:
    void testSongFile();
};

#endif // TESTS_H

#ifndef FILETESTRUNNER_H
#define FILETESTRUNNER_H

#include <QObject>
#include <QtTest/QtTest>

class FileTestRunner : public QObject
{
    Q_OBJECT
public:
    FileTestRunner();
private slots:
    void testFilesFound();
    void testFileReader();
};

#endif // FILETESTRUNNER_H

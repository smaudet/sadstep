#include "FileTestRunner.h"
#include "FileIOServer.h"
#include "SMFileReader.h"
#include <QtDebug>

//QTEST_MAIN(FileTestRunner)

FileTestRunner::FileTestRunner()
{
}

void FileTestRunner::testFileReader() {
    FileIOServer* io = new FileIOServer();
    SMFileReader* r = (SMFileReader*) io->getStepReader("Songs\\Amaranth - Full\\Amaranth_full.sm");
    //qDebug() << "Trying to verify";
    QVERIFY(r!=0);
    //qDebug() << "Done verification";
    QVERIFY(r->getStepData()!=0);
    QVERIFY(r->getStepData()->size()>0);
    QVERIFY(r->getBPM()->size()>0);
}

void FileTestRunner::testFilesFound() {
    FileIOServer* io = new FileIOServer();
    QVERIFY(io->getSongCatalogue()->getFileNames()->size()>0);
}

#include "Tests.h"
#include "FileIOServer.h"
#include <QString>
#include <QtDebug>
#include <QList>

Tests::Tests(){
}

void Tests::testSongFile() {
    FileIOServer* server = new FileIOServer();
    for(int i = 0;i<server->getSongCatalogue()->getFileNames()->size();++i){
	QString oname = server->getSongCatalogue()->getFileName(i);
	QString songname = server->getSongReader(&oname)->getSongFile();
	qDebug() << songname;
	QList<double>* bpms = server->getStepReader(&oname)->getBPM();
    }
}

#include <QString>
#include <QtDebug>
#include <QList>
#include <QListIterator>
#include <QPair>

#include "Tests.h"
#include "FileIOServer.h"
#include "SongReader.h"
#include "StepReader.h"

Tests::Tests(){
}

void Tests::testSongFile() {
    FileIOServer* server = new FileIOServer();
    for(int i = 0;i<server->getSongCatalogue()->getFileNames()->size();++i){
	QString oname = server->getSongCatalogue()->getFileName(i);
	SongReader* songreader = server->getSongReader(oname);
	StepReader* stepreader = server->getStepReader(oname);
//	qDebug() << songreader->getBackGroundFile();
//	qDebug() << songreader->getCredits();
//	qDebug() << songreader->getSongArtist();
//	QListIterator<QPair<double,QString>*> itr(*(songreader->getBGAnimations()));
//	QListIterator<QPair<double,QString>*> itr2(*(songreader->getMenuBGAnimations()));
//	while(itr.hasNext()) {
//	    QPair<double,QString>* i = itr.next();
//	    qDebug() << i->first << " " << i->second;
//	}
//	while(itr2.hasNext()) {
//	    QPair<double,QString>* i = itr.next();
//	    qDebug() << i->first << " " << i->second;
//	}
//	qDebug() << songreader->getSongFile();
//	qDebug() << songreader->getSongLength();
//	qDebug() << songreader->getSongLyricsPath();
//	qDebug() << songreader->getSongSampleLength();
//	qDebug() << songreader->getSongSampleStart();
//	qDebug() << songreader->getSongSelectable();
//	qDebug() << songreader->getSongSubtitles().readLine();
//	qDebug() << songreader->getSongTitle();
//        QList<QPair<double,double>*>* bpms = server->getStepReader(&oname)->getBPM();
    }
}
